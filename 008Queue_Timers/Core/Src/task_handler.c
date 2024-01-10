/*
 * task_handler.c
 *
 *  Created on: Jan 9, 2024
 *      Author: pubudu
 */

#include "main.h"
#include "FreeRTOS.h"
#include "task.h"


extern void process_command(command_t *cmd);

void menu_task(void *pvParam)
{
	while(1) {

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
