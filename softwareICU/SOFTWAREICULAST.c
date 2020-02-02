/*
 * SOFTWAREICULAST.c
 *
 * Created: 02/02/2020 05:32:25 م
 *  Author: mo
 */ 

#include "SwICU.h"
#include "std_types.h"
#include "registers.h"
#include "led.h"
#include "ledConfig.h"
#include "Interrupts.h"
#include "gpio.h"
#include "timers.h"
#define RESOLUTION 256
#define PRESCALER 1
#define CPU 16000000
#define TIME_TAKEN_FOR_1_CM 0.000058

volatile uint32_t u32_ovf_counter=0;

volatile unsigned int  Num_of_Ticks=0;
volatile float Num_of_mm=0;
volatile float time=0.0;
volatile float TICKTIME=0.0;
volatile uint8_t u8_icu_started =0;

int main(void)
{
    gpioPinDirection(GPIOC,BIT0,OUTPUT);/*TRiger*/
    Led_Init(LED_0);
	Led_Init(LED_1);
	Led_Init(LED_2);
    Led_Init(LED_3);
	timer2Init(T2_NORMAL_MODE,T2_OC2_DIS,T2_PRESCALER_NO,0,0,0,T2_POLLING);
    SwICU_Init(SwICU_EdgeRisiging);
	while(1)
    {
		
	gpioPinWrite(GPIOC,BIT0,HIGH);
	timer2Start();
	timer2DelayUs(10);
	u8_icu_started=1;
	//SwICU_Read(&TCNT0);
	gpioPinWrite(GPIOC,BIT0,LOW);
	timer2Start();
	timer2DelayUs(200);
	
    }
}
void Timer_interrupt_routine(void)
{
	u32_ovf_counter++;
	TICKTIME=(float)PRESCALER/(float)CPU;
	Num_of_Ticks=(TCNT0+(u32_ovf_counter * RESOLUTION));
	time=(float)Num_of_Ticks*TICKTIME;
	Num_of_mm=(time/TIME_TAKEN_FOR_1_CM);
PORTB_DATA=((uint8_t)Num_of_mm<<4);
}
void check_button(void)
{
	//if (u8_icu_started)
	//{
		
		if(SwICU_GetCfgEdge())
		{
			SwICU_SetCfgEdge(SwICU_EdgeFalling);
	        SwICU_Start();
	//	u8_icu_started=0;
		}
		else
		{
			SwICU_SetCfgEdge(SwICU_EdgeRisiging);
		u8_icu_started=0;
SwICU_Stop();
		}
		
	//}
	
			
}

	

