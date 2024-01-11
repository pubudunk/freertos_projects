/*
 * cmd_handler.c
 *
 *  Created on: Jan 9, 2024
 *      Author: pubudu
 */

#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

extern TaskHandle_t xMenuTaskHandle;
extern TaskHandle_t xCmdTaskHandle;
extern TaskHandle_t xPrintTaskHandle;
extern TaskHandle_t xLedTaskHandle;
extern TaskHandle_t xRtcTaskHandle;

extern QueueHandle_t q_data;
extern state_t eCurrState;


int extract_command(command_t *cmd);

void process_command(command_t *cmd)
{
	uint8_t ret = 0;

	ret = extract_command(cmd);

	if(pdTRUE == ret) {
		switch(eCurrState)
		{
		case sMainMenu:
			xTaskNotify(xMenuTaskHandle, (uint32_t )cmd, eSetValueWithOverwrite);
			break;
		case sLedEffect:
			xTaskNotify(xLedTaskHandle, (uint32_t )cmd, eSetValueWithOverwrite);
				break;
		case sRtcMenu:
		case sRtcTimeConfig:
		case sRtcDateConfig:
		case sRtcReport:
			xTaskNotify(xRtcTaskHandle, (uint32_t )cmd, eSetValueWithOverwrite);
					break;
		default:
			break;
		}
	}
}

int extract_command(command_t *cmd)
{
	uint8_t item,i;
	BaseType_t status = pdFALSE;

	// check if data is available in the queue
	status = uxQueueMessagesWaiting(q_data);
	if(status <=0 )
		return pdFALSE;

	i = 0;
	do {

		status = xQueueReceive(q_data, &item, 0);
		if(pdTRUE == status)
			cmd->payload[i++] = item;
	} while(item != '\n');

	// last items is always '\n'. Replace with '\0'
	cmd->payload[i-i] = '\0';
	cmd->len = i-1;

	return pdTRUE;
}
