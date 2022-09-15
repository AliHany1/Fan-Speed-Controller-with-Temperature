/*********************************************
 *  File Name: ADC_Driver.c                 *
 *                                          *
 *  Created on: Oct 5, 2021                 *
 *  Author: Ali Hany                        *
 *********************************************/

#include "ADC_Driver.h"
#include <avr/io.h>
#include "gpio.h"
#include "common_macros.h"

/*********************************************************
 *                   Function Definitions               *
 ********************************************************/

void ADC_init(const ADC_ConfigType * Config_Ptr)
{
	/* Use internal 2.56V with external capacitor at AREF pin */
	ADMUX = (ADMUX & 0x3F) | ((Config_Ptr -> ref_volt ) << REFS0);
	ADCSRA=(ADCSRA & 0xF8) | ( (Config_Ptr -> prescaler) & 0x07);
	SET_BIT(ADCSRA,ADEN);
    CLEAR_BIT(ADCSRA,ADIE);

}

uint16 ADC_readChannel(uint8 CH_num)
{
	CH_num &= 0x07;
	ADMUX = (ADMUX & 0xE0) | (CH_num & 0x07);
	SET_BIT(ADCSRA,ADSC);
	while (BIT_IS_CLEAR(ADCSRA,ADIF));
	SET_BIT(ADCSRA,ADIF);
	return ADC;
}
