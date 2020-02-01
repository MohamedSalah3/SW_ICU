/*
 * softwareICU.c
 * Created: 29/01/2020 01:51:19 م
 *  Author: mo
 */
#include "registers.h"
#include "SwICU.h"
#include "Interrupts.h"
#include "timers.h"
#include "led.h"
#include "ledConfig.h"
#include "util/delay.h"
uint8_t tcnt0_value=0;
int main(void)
{
	Led_Init(LED_0);
	Led_Init(LED_1);
	Led_Init(LED_2);
	Led_Init(LED_3);
  timer2Init(T2_NORMAL_MODE,T2_OC2_DIS,T2_PRESCALER_NO,10,0,0,T2_POLLING);
	gpioPortDirection(GPIOC,HIGH);
	SwICU_Init(SwICU_EdgeRisiging);
		while(1)
  	{
		tcnt0_value=timer0Read();
		SET_BIT(PORTC_DATA,1);
		timer2Start();
		timer2DelayUs(1);
		CLEAR_BIT(PORTC_DATA,1);
		SwICU_Read(&tcnt0_value);
    }

}
