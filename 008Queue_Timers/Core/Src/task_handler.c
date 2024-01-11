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

state_t eCurrState = sMainMenu;

const char *pcMainMenuErrorMsg = "Invalid input\n";

extern TaskHandle_t xMenuTaskHandle;
extern TaskHandle_t xCmdTaskHandle;
extern TaskHandle_t xPrintTaskHandle;
extern TaskHandle_t xLedTaskHandle;
extern TaskHandle_t xRtcTaskHandle;

extern QueueHandle_t q_print;

extern void process_command(command_t *cmd);


void menu_task(void *pvParam)
{
	BaseType_t ret = pdFALSE;
	command_t *xpCmd;

	while(1) {

		const char *pcMainMenuMsg = "===============================\n"
									"|			Menu		       |\n"
									"===============================\n"
									"		Led Effect  -----> 0    \n"
									"		Date & Time -----> 1    \n"
									"		Exit		-----> 2    \n"
									"		Enter your choice here : ";

		xQueueSendToBack(q_print, &pcMainMenuMsg, portMAX_DELAY);

		/* Wait for notification from command handler task */
		memset(&xpCmd, 0, sizeof(command_t));
		ret = xTaskNotifyWait(0x00, 0x00, (uint32_t *)xpCmd, portMAX_DELAY);
		if(ret) {

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
						xQueueSendToBack(q_print, &pcMainMenuErrorMsg, portMAX_DELAY);
						continue;
						break;
					}
				}
			}
		}

		/* wait until other tasks notify after completion */
		xTaskNotifyWait(0x00, 0x00, NULL, portMAX_DELAY);
	}
}

void cmd_handler_task(void *pvParam)
{
	BaseType_t ret = pdFALSE;
	command_t cmd;

	while(1) {

		// Wait until data is received
		ret = xTaskNotifyWait(0x00, 0x00, NULL, portMAX_DELAY);
		if(ret) {

			process_command(&cmd);
		}
	}
}

void print_task(void *pvParam)
{
	while(1) {

	}
}

void led_task(void *pvParam)
{
	while(1) {

	}
}

void rtc_task(void *pvParam)
{
	while(1) {

	}
}
