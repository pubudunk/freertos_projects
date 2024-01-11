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

extern TaskHandle_t xMenuTaskHandle;
extern TaskHandle_t xCmdTaskHandle;
extern TaskHandle_t xPrintTaskHandle;
extern TaskHandle_t xLedTaskHandle;
extern TaskHandle_t xRtcTaskHandle;

extern QueueHandle_t q_print;

extern UART_HandleTypeDef huart5;


void menu_task(void *pvParam)
{
	command_t *xpCmd = NULL;
	const char *pcMainMenuMsg = "===============================\n"
								"|            Menu             |\n"
								"===============================\n"
								"    Led Effect  -----> 0    \n"
								"    Date & Time -----> 1    \n"
								"    Exit        -----> 2    \n"
								"    Enter your choice here : ";

	while(1) {

		xQueueSendToBack(q_print, &pcMainMenuMsg, portMAX_DELAY);

		/* Wait for notification from command handler task */
		xTaskNotifyWait(0x00, 0x00, (uint32_t *)xpCmd, portMAX_DELAY);
		if(xpCmd) {
			if(1 == xpCmd->len) {
				/* command received. Valid length. It should be in the first byte. */
				switch(xpCmd->payload[0]) {
				case '0':
					eCurrState = sLedEffect;
					xTaskNotify(xLedTaskHandle, 0x00, eNoAction);
					break;
				case '1':
					eCurrState = sRtcMenu;
					xTaskNotify(xRtcTaskHandle, 0x00, eNoAction);
					break;
				case '2':
					vTaskEndScheduler();
					break;
				default:
					xQueueSendToBack(q_print, &pcMenuInvalidEntryErrMsg, portMAX_DELAY);
					continue;
					break;
				}

				/* wait until other tasks notify after completion */
				xTaskNotifyWait(0x00, 0x00, NULL, portMAX_DELAY);
			} else {
				xQueueSendToBack(q_print, &pcMenuInvalidEntryErrMsg, portMAX_DELAY);
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

		process_command(&cmd);
	}
}

void print_task(void *pvParam)
{
	uint32_t *printMsg = NULL;
	while(1) {
		xQueueReceive(q_print, &printMsg, portMAX_DELAY);
		HAL_UART_Transmit(&huart5, (uint8_t *)printMsg, strlen((char *)printMsg), HAL_MAX_DELAY);
	}
}

void led_task(void *pvParam)
{
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
		xQueueSendToBack(q_print, &pcLedMenuMsg, portMAX_DELAY);

		/* Wait for notification from command handler task */
		xTaskNotifyWait(0x00, 0x00, (uint32_t *)xpCmd, portMAX_DELAY);
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
					LedEffect(xpCmd->payload[0]-48);
					break;
				default:
					xQueueSendToBack(q_print, &pcMenuInvalidEntryErrMsg, portMAX_DELAY);
					break;
				}
			}
		} else {
			xQueueSendToBack(q_print, &pcMenuInvalidEntryErrMsg, portMAX_DELAY);
		}

		/* Set state to main menu */
		eCurrState = sMainMenu;

		/* notify main menu task */
		xTaskNotify(xMenuTaskHandle, 0x00, eNoAction);
	}
}

void rtc_task(void *pvParam)
{
	while(1) {

	}
}
