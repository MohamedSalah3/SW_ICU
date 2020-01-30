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
	{
		CLEAR_BIT(MCUCSR,6);
		break;
	}
	case SwICU_EdgeRisiging:
	{
	SET_BIT(MCUCSR,6);
	break;
	}

	}

}
void SwICU_Read(volatile uint8_t * a_pu8_capt)
{
PORTB_DATA =(((* a_pu8_capt)/4)<<4);
}

void SwICU_Stop(void)
{
timer0Stop();
}

void SwICU_Start(void)
{

timer0Start();

}
