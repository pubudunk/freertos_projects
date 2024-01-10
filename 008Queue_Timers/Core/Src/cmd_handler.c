/*
 * cmd_handler.c
 *
 *  Created on: Jan 9, 2024
 *      Author: pubudu
 */

#include "main.h"
#include "FreeRTOS.h"
#include "task.h"


extern TaskHandle_t xMenuTaskHandle;
extern TaskHandle_t xCmdTaskHandle;
extern TaskHandle_t xPrintTaskHandle;
extern TaskHandle_t xLedTaskHandle;
extern TaskHandle_t xRtcTaskHandle;

void extract_command(command_t *cmd);

void process_command(command_t *cmd)
{
	state_t curr_state = sMainMenu;

	extract_command(cmd);

	switch(curr_state)
	{
	case sMainMenu:
		xTaskNotify(xMenuTaskHandle, (uint32_t )cmd, eSetValueWithOverwrite);
		break;
	case sLedEffect:
		xTaskNotify(xLedTaskHandle, (uint32_t )cmd, eSetValueWithOverwrite);
			break;
	case sRtcEffect:
	case sRtcTimeConfig:
	case sRtcDateConfig:
	case sRtcReport:
		xTaskNotify(xRtcTaskHandle, (uint32_t )cmd, eSetValueWithOverwrite);
				break;
	default:
		break;
	}
}

void extract_command(command_t *cmd)
{

}
