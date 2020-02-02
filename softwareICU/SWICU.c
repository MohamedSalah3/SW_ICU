/*
 * SWICU.c
 *
 * Created: 29/01/2020 01:51:56 م
 *  Author: mo
 */
#include "SwICU.h"
#include "Interrupts.h"
#include "timers.h"
#include "registers.h"
#define RESOLUTION 256
#define PRESCALER 1
#define CPU 16000000
#define TIME_TAKEN_FOR_1_CM 0.000058
void SwICU_Init(EN_SwICU_Edge_t a_en_inputCaptureEdge)
{
/*Make External interrup work first via Any logical change*/
timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,T0_PRESCALER_NO,0,0,T0_INTERRUPT_NORMAL);
G_interrupt_Enable();
EX_interrupt_enable2();
/*change the interrupt activation status*/
SwICU_SetCfgEdge(SwICU_EdgeRisiging);

}

void SwICU_SetCfgEdge(EN_SwICU_Edge_t a_en_inputCaptureEdgeedge)
{
	switch (a_en_inputCaptureEdgeedge) {
		case SwICU_EdgeFalling :
	{		SwICU_Stop();
		
		SET_BIT(MCUCSR,6);
		break;
	}
	case SwICU_EdgeRisiging:
	{SwICU_Start();


	CLEAR_BIT(MCUCSR,6);
	break;
	}

	}

}
void SwICU_Read(volatile uint8_t * a_pu8_capt)
{
	unsigned int  Num_of_Ticks=0;
	float Num_of_mm=0;
	float time=0.0;
	float TICKTIME=(float)PRESCALER/(float)CPU;
	Num_of_Ticks=((* a_pu8_capt)+(u32_ovf_counter * RESOLUTION));
	time=(float)Num_of_Ticks*TICKTIME;
	Num_of_mm=time/TIME_TAKEN_FOR_1_CM;
	timer2Start();
	timer2DelayMs(100);
	PORTB_DATA=((unsigned int)Num_of_mm<<4);
timer2Start();
timer2DelayMs(100);
}


void SwICU_Stop(void)
{
timer0Stop();
}

void SwICU_Start(void)
{
timer0Start();
}
EN_SwICU_Edge_t SwICU_GetCfgEdge(void)
{
	if (MCUCSR & 0x40)
	{
		return SwICU_EdgeRisiging;
	}
	else{return SwICU_EdgeFalling;}
	
}	
