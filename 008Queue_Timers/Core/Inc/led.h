/*
 * led.h
 *
 *  Created on: Jan 10, 2024
 *      Author: pubudukarunaratna
 */

#ifndef INC_LED_H_
#define INC_LED_H_

void LedEffectNone(void);
void LedEffect(uint8_t ucEffect);

#define EFFECT_1	0		/* Red LED Blinking 			*/
#define EFFECT_2	1		/* Green LED Blinking 			*/
#define EFFECT_3	2		/* Both Led Alternate Blinking 	*/

#endif /* INC_LED_H_ */
