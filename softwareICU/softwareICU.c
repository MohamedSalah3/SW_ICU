/*
 * softwareICU.c
 *
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
int main(void)
{volatile uint16_t x,y;
	gpioPortDirection(GPIOB,HIGH);
	gpioPortDirection(GPIOC,HIGH);

//	gpioPortWrite(GPIOB,LOW);
	SwICU_Init(SwICU_EdgeRisiging);
	 
	while(1)
    {
//timer0MakePulse();
PORTC_DATA |=0xff;
_delay_ms(1);
PORTC_DATA &=0x00;
//_delay_ms(1);
SwICU_Start();
SwICU_Read(&u8_ovf_counter);
SwICU_Stop();
	}
}
