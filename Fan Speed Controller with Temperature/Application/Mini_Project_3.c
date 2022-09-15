/*********************************************
 *  File Name: Mini_project_3.c             *
 *                                          *
 *  Created on: Oct 5, 2021                 *
 *  Author: Ali Hany                        *
 *********************************************/

#include <avr/io.h>
#include "lcd.h"
#include "gpio.h"
#include "ADC_Driver.h"
#include "common_macros.h"
#include "lm35_sensor.h"
#include "DC_Motor.h"
#include "PWM.h"

typedef enum
{
	OFF,ON
}FanState;

int main(void)
{
	uint8 temp = 0;
	FanState State;

	/* Create configuration structure for ADC driver */
	ADC_ConfigType ADC_Config = {Internal,F_CPU_8};

	LCD_init(); /* initialize LCD driver */
	ADC_init(&ADC_Config); /* initialize ADC driver */

	DcMotor_Init(); /* initialize DC Motor driver */

	LCD_displayStringRowColumn(0, 4,"Fan is ");

	LCD_displayStringRowColumn(1,4,"Temp =     C ");

	while (1)
	{
		if ( State == ON)
		{
			LCD_displayStringRowColumn(0, 11, "ON");
		}
		else if ( State == OFF)
		{
			LCD_displayStringRowColumn(0, 11, "OFF");
		}

		temp = LM35_getTemperature();

		if(temp < 30)
		{
			State = OFF;

			DcMotor_Rotate(Stop, 0);
		}
		else if (temp >= 30)
		{
			State = ON;

			LCD_displayCharacter(' ');  /* To prevent error like "ONF" to be written */

			if(temp >= 30 && temp < 60)
			{
				DcMotor_Rotate(CW,25);
			}
			else if(temp >= 60 && temp < 90)
			{
				DcMotor_Rotate(CW,50);
			}
			else if(temp >= 90 && temp < 120)
			{
				DcMotor_Rotate(CW,75);
			}
			else if(temp >= 120)
			{
				DcMotor_Rotate(CW,100);
			}
		}

		LCD_moveCursor(1,11);

		if(temp >= 100)
		{
			LCD_intgerToString(temp);
		}
		else
		{
			LCD_intgerToString(temp);
			/* In case the digital value is two or one digits print space in the next digit place */
			LCD_displayCharacter(' ');
		}
	}


}
