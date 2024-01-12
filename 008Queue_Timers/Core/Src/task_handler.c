/*
 * task_handler.c
 *
 *  Created on: Jan 9, 2024
 *      Author: pubudu
 */

#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <string.h>

#include "cmd_handler.h"
#include "led.h"

state_t eCurrState = sMainMenu;

const char *pcMenuInvalidEntryErrMsg = "Invalid input\n";

extern TaskHandle_t xTaskHandles[ 5 ];
extern QueueHandle_t xQueues[ 2 ];

extern UART_HandleTypeDef huart5;

extern void show_time_date(void);
void rtc_configure_time(RTC_TimeTypeDef *time, uint8_t ucTimeFormat);
extern void rtc_configure_date(RTC_DateTypeDef *date);
extern int validate_rtc_information(RTC_TimeTypeDef *time , RTC_DateTypeDef *date);

void menu_task(void *pvParam)
{
	uint32_t ulCmdAddr = 0;
	command_t *xpCmd = NULL;
	const char *pcMainMenuMsg = "===============================\n"
								"|            Menu             |\n"
								"===============================\n"
								"    Led Effect  -----> 0    \n"
								"    Date & Time -----> 1    \n"
								"    Exit        -----> 2    \n"
								"    Enter your choice here : ";

	while(1) {

		xQueueSendToBack(xQueues[QPRINT], &pcMainMenuMsg, portMAX_DELAY);

		/* Wait for notification from command handler task */
		xTaskNotifyWait(0x00, 0x00, &ulCmdAddr, portMAX_DELAY);
		xpCmd = (command_t *)ulCmdAddr;
		if(xpCmd) {
			if(1 == xpCmd->len) {
				/* command received. Valid length. It should be in the first byte. */
				switch(xpCmd->payload[0]) {
				case '0':
					eCurrState = sLedEffect;
					xTaskNotify(xTaskHandles[TLED], 0x00, eNoAction);
					break;
				case '1':
					eCurrState = sRtcMenu;
					xTaskNotify(xTaskHandles[TRTC], 0x00, eNoAction);
					break;
				case '2':
					vTaskEndScheduler();
					break;
				default:
					xQueueSendToBack(xQueues[QPRINT], &pcMenuInvalidEntryErrMsg, portMAX_DELAY);
					continue;
					break;
				}

				/* wait until other tasks notify after completion */
				xTaskNotifyWait(0x00, 0x00, NULL, portMAX_DELAY);
			} else {
				xQueueSendToBack(xQueues[QPRINT], &pcMenuInvalidEntryErrMsg, portMAX_DELAY);
			}
		}
	}
}

void cmd_handler_task(void *pvParam)
{
	command_t cmd;

	while(1) {

		// Wait until data is received
		xTaskNotifyWait(0x00, 0x00, NULL, portMAX_DELAY);
		memset(&cmd, 0, sizeof(cmd));
		process_command(&cmd);
	}
}

void print_task(void *pvParam)
{
	uint32_t *printMsg = NULL;
	while(1) {
		xQueueReceive(xQueues[QPRINT], &printMsg, portMAX_DELAY);
		HAL_UART_Transmit(&huart5, (uint8_t *)printMsg, strlen((char *)printMsg), HAL_MAX_DELAY);
	}
}

void led_task(void *pvParam)
{
	uint32_t ulCmdAddr = 0;
	command_t *xpCmd = NULL;
	const char *pcLedMenuMsg = " ===============================\n"
								"|         LED Effects         |\n"
								"===============================\n"
								"    Effect 1 -----> 1    	\n"
								"    Effect 2 -----> 2    	\n"
								"    Effect 3 -----> 3    	\n"
								"    None     -----> 0    	\n"
								"    Enter your choice here : ";

	while(1) {

		/* wait until LED event receives */
		xTaskNotifyWait(0x00, 0x00, NULL, portMAX_DELAY);

		/* send led menu to print queue */
		xQueueSendToBack(xQueues[QPRINT], &pcLedMenuMsg, portMAX_DELAY);

		/* Wait for notification from command handler task */
		xTaskNotifyWait(0x00, 0x00, &ulCmdAddr, portMAX_DELAY);
		xpCmd = (command_t *)ulCmdAddr;
		if(xpCmd) {
			if(1 == xpCmd->len) {
				/* command received. Valid length. It should be in the first byte. */
				switch(xpCmd->payload[0]) {
				case '0':
					LedEffectNone();
					break;
				case '1':
				case '2':
				case '3':
					LedEffect((EFFECT_1-1) + xpCmd->payload[0]-48);
					break;
				default:
					xQueueSendToBack(xQueues[QPRINT], &pcMenuInvalidEntryErrMsg, portMAX_DELAY);
					break;
				}
			}
		} else {
			xQueueSendToBack(xQueues[QPRINT], &pcMenuInvalidEntryErrMsg, portMAX_DELAY);
		}

		/* Set state to main menu */
		eCurrState = sMainMenu;

		/* notify main menu task */
		xTaskNotify(xTaskHandles[TMAIN], 0x00, eNoAction);
	}
}

uint8_t getnumber(uint8_t *p , int len)
{

	int value ;

	if(len > 1)
	   value =  ( ((p[0]-48) * 10) + (p[1] - 48) );
	else
		value = p[0] - 48;

	return value;

}

void rtc_task(void *param)
{
	const char *msg_rtc1 =  "===============================\n"
							"|             RTC             |\n"
							"===============================\n";

	const char* msg_rtc2 =  "Configure Time            ----> 0\n"
							"Configure Date            ----> 1\n"
							"Exit                      ----> 2\n"
							"Enter your choice here : ";


	const char *msg_rtc_hh = "Enter hour(1-12):";
	const char *msg_rtc_mm = "Enter minutes(0-59):";
	const char *msg_rtc_ss = "Enter seconds(0-59):";
	const char *msg_rtc_tf = "Enter AM/PM:";

	const char *msg_rtc_dd  = "Enter date(1-31):";
	const char *msg_rtc_mo  ="Enter month(1-12):";
	const char *msg_rtc_dow  = "Enter day(1-7 sun:1):";
	const char *msg_rtc_yr  = "Enter year(0-99):";

	const char *msg_conf = "Configuration successful\n";

	uint32_t cmd_addr;
	command_t *cmd;

	static int rtc_state = 0;
	int menu_code;

	RTC_TimeTypeDef time;
	RTC_DateTypeDef date;


#define HH_CONFIG 		0
#define MM_CONFIG 		1
#define SS_CONFIG 		2
#define TF_CONFIG 		3

#define DATE_CONFIG 	0
#define MONTH_CONFIG 	1
#define YEAR_CONFIG 	2
#define DAY_CONFIG 		3


	while(1){
		/*Notify wait (wait till someone notifies) */
		xTaskNotifyWait(0, 0, NULL, portMAX_DELAY);

		/*Print the menu and show current date and time information */
		xQueueSend(xQueues[QPRINT],&msg_rtc1, portMAX_DELAY);
		show_time_date();
		xQueueSend(xQueues[QPRINT],&msg_rtc2, portMAX_DELAY);


		while(eCurrState != sMainMenu){

			/*Wait for command notification (Notify wait) */
			xTaskNotifyWait(0, 0, &cmd_addr, portMAX_DELAY);
			cmd = (command_t*)cmd_addr;

			switch(eCurrState)
			{
				case sRtcMenu:{
					/*process RTC menu commands */
					if(cmd->len == 1)
					{
						menu_code = cmd->payload[0] - 48;
						switch(menu_code)
						{
						case 0:
							eCurrState = sRtcTimeConfig;
							xQueueSend(xQueues[QPRINT], &msg_rtc_hh, portMAX_DELAY);
							break;
						case 1:
							eCurrState = sRtcDateConfig;
							xQueueSend(xQueues[QPRINT], &msg_rtc_dd, portMAX_DELAY);
							break;
						case 2 :
							eCurrState = sMainMenu;
							break;
						default:
							eCurrState = sMainMenu;
							xQueueSend(xQueues[QPRINT], &pcMenuInvalidEntryErrMsg, portMAX_DELAY);
						}

					}else{
						eCurrState = sMainMenu;
						xQueueSend(xQueues[QPRINT], &pcMenuInvalidEntryErrMsg, portMAX_DELAY);
					}
					break;}

				case sRtcTimeConfig:{
					/*get hh, mm, ss infor and configure RTC */
					/*take care of invalid entries */
					switch(rtc_state)
						{
							case HH_CONFIG:{
								uint8_t hour = getnumber(cmd->payload , cmd->len);
								time.Hours = hour;
								rtc_state = MM_CONFIG;
								xQueueSend(xQueues[QPRINT], &msg_rtc_mm, portMAX_DELAY);
								break;}
							case MM_CONFIG:{
								uint8_t min = getnumber(cmd->payload , cmd->len);
								time.Minutes = min;
								rtc_state = SS_CONFIG;
								xQueueSend(xQueues[QPRINT], &msg_rtc_ss, portMAX_DELAY);
								break;}
							case SS_CONFIG:{
								uint8_t sec = getnumber(cmd->payload , cmd->len);
								time.Seconds = sec;
								xQueueSend(xQueues[QPRINT], &msg_rtc_tf, portMAX_DELAY);
								rtc_state = TF_CONFIG;
								break; }
							case TF_CONFIG:{
								uint8_t ucTimeFormat = 0;
								if( (0 == strcmp((char*)cmd->payload,"AM")) || (0 == strcmp((char*)cmd->payload,"am")) )
									ucTimeFormat = RTC_HOURFORMAT12_AM;
								else if( (0 == strcmp((char*)cmd->payload,"PM")) || (0 == strcmp((char*)cmd->payload,"pm")) )
									ucTimeFormat = RTC_HOURFORMAT12_PM;
								else {
									xQueueSend(xQueues[QPRINT], &pcMenuInvalidEntryErrMsg, portMAX_DELAY);
									break;
									eCurrState = sMainMenu;
									rtc_state = HH_CONFIG;
								}

								if(!validate_rtc_information(&time, NULL))
								{
									rtc_configure_time(&time, ucTimeFormat);
									xQueueSend(xQueues[QPRINT], &msg_conf, portMAX_DELAY);
									show_time_date();
								}else
									xQueueSend(xQueues[QPRINT], &pcMenuInvalidEntryErrMsg, portMAX_DELAY);

								eCurrState = sMainMenu;
								rtc_state = HH_CONFIG;
								break;}
						}

					break;}

				case sRtcDateConfig:{

					/*get date, month, day , year info and configure RTC */

					/*take care of invalid entries */
					switch(rtc_state)
						{
							case DATE_CONFIG:{
								uint8_t d = getnumber(cmd->payload , cmd->len);
								date.Date = d;
								rtc_state = MONTH_CONFIG;
								xQueueSend(xQueues[QPRINT], &msg_rtc_mo, portMAX_DELAY);
								break;}
							case MONTH_CONFIG:{
								uint8_t month = getnumber(cmd->payload , cmd->len);
								date.Month = month;
								rtc_state = DAY_CONFIG;
								xQueueSend(xQueues[QPRINT], &msg_rtc_dow, portMAX_DELAY);
								break;}
							case DAY_CONFIG:{
								uint8_t day = getnumber(cmd->payload , cmd->len);
								date.WeekDay = day;
								rtc_state = YEAR_CONFIG;
								xQueueSend(xQueues[QPRINT], &msg_rtc_yr, portMAX_DELAY);
								break;}
							case YEAR_CONFIG:{
								uint8_t year = getnumber(cmd->payload , cmd->len);
								date.Year = year;

								if(!validate_rtc_information(NULL,&date))
								{
									rtc_configure_date(&date);
									xQueueSend(xQueues[QPRINT], &msg_conf, portMAX_DELAY);
									show_time_date();
								}else
									xQueueSend(xQueues[QPRINT], &pcMenuInvalidEntryErrMsg, portMAX_DELAY);

								eCurrState = sMainMenu;
								rtc_state = 0;
								break;}
						}
					break;}
			}// switch end

		} //while end


		/*Notify menu task */
		xTaskNotify(xTaskHandles[TMAIN],0,eNoAction);

		}//while super loop end
}
