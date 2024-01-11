/*
 * led.c
 *
 *  Created on: Jan 10, 2024
 *      Author: pubudukarunaratna
 */

#include "main.h"
#include "FreeRTOS.h"
#include "timers.h"

#include "led.h"
TimerHandle_t xLedTimers[ 3 ] = {};

void LedEffectNone(void)
{
	/* stop all timers */
	for(int i = 0; i < 3; i++)
		xTimerStop(xLedTimers[EFFECT_1 + i], portMAX_DELAY);

	HAL_GPIO_WritePin(GPIOG, LD3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOG, LD4_Pin, GPIO_PIN_RESET);
}

void LedEffect(uint8_t ucEffect)
{
	switch(ucEffect) {
	case EFFECT_1:
	case EFFECT_2:
	case EFFECT_3:
		LedEffectNone();
		xTimerStart(xLedTimers[ucEffect], portMAX_DELAY);
		break;
	default:
		break;
	}
}

static void LedEffect_1(void)
{
	HAL_GPIO_TogglePin(GPIOG, LD3_Pin);
}

static void LedEffect_2(void)
{
	HAL_GPIO_TogglePin(GPIOG, LD4_Pin);
}

void LedEffect_3(void)
{
	static uint8_t count = 0;

	if(0 == count) {
		HAL_GPIO_WritePin(GPIOG, LD3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOG, LD4_Pin, GPIO_PIN_RESET);
		count = 1;
	} else {
		HAL_GPIO_WritePin(GPIOG, LD3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOG, LD4_Pin, GPIO_PIN_SET);
		count = 0;
	}

}

void LedEffectCallback(TimerHandle_t xTimer)
{
	uint32_t ulTimerId;

	ulTimerId = (uint32_t)pvTimerGetTimerID(xTimer);

	switch(ulTimerId) {
	case 0:
		LedEffect_1();
		break;
	case 1:
		LedEffect_2();
		break;
	case 2:
		LedEffect_3();
		break;;
	default:
		break;

	}
}
