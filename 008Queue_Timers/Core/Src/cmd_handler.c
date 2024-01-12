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
#include "cmd_handler.h"

//extern TaskHandle_t xMenuTaskHandle;
//extern TaskHandle_t xCmdTaskHandle;
//extern TaskHandle_t xPrintTaskHandle;
//extern TaskHandle_t xLedTaskHandle;
//extern TaskHandle_t xRtcTaskHandle;

extern TaskHandle_t xTaskHandles[ 5 ];
extern QueueHandle_t xQueues[ 2 ];

extern state_t eCurrState;


static int extract_command(command_t *cmd);

void process_command(command_t *cmd)
{
	uint8_t ret = 0;

	ret = extract_command(cmd);

	if(pdTRUE == ret) {
		switch(eCurrState)
		{
		case sMainMenu:
			xTaskNotify(xTaskHandles[TMAIN], (uint32_t )cmd, eSetValueWithOverwrite);
			break;
		case sLedEffect:
			xTaskNotify(xTaskHandles[TLED], (uint32_t )cmd, eSetValueWithOverwrite);
				break;
		case sRtcMenu:
		case sRtcTimeConfig:
		case sRtcDateConfig:
			xTaskNotify(xTaskHandles[TRTC], (uint32_t )cmd, eSetValueWithOverwrite);
					break;
		default:
			break;
		}
	}
}

static int extract_command(command_t *cmd)
{
	uint8_t item,i;
	BaseType_t status = pdFALSE;

	// check if data is available in the queue
	status = uxQueueMessagesWaiting(xQueues[QDATA]);
	if(status <=0 )
		return pdFALSE;

	i = 0;
	do {

		status = xQueueReceive(xQueues[QDATA], &item, 0);
		if(pdTRUE == status)
			cmd->payload[i++] = item;
	} while(item != '\n');

	// last items is always '\n'. Replace with '\0'
	cmd->payload[i-1] = '\0';
	cmd->len = i-1;

	return pdTRUE;
}
