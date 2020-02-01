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

void SwICU_Init(EN_SwICU_Edge_t a_en_inputCaptureEdge)
{
/*Make External interrup work first via Any logical change*/
timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,T0_PRESCALER_64,0,0,T0_INTERRUPT_NORMAL);
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
{//64 prescaler
uint64_t num_of_tics=0;
uint16_t num_of_cm=0;
//num_of_cm=(68 * (*a_pu8_capt)/1000);
num_of_tics=((* a_pu8_capt)+(u8_ovf_counter * RESOLUTION));
num_of_cm=num_of_tics/30;

PORTB_DATA=(num_of_cm<<4);
/*switch (num_of_cm) {
	case 0:
	PORTB_DATA=0b00000000;
	break;
	case 1:
	PORTB_DATA=0b00010000;
	break;
	case 2:
	PORTB_DATA=0b00100000;
	break;
	case 3:
	PORTB_DATA=0b00110000;
	break;
	case 4:
	PORTB_DATA=0x40;
	break;
	case 5:
	PORTB_DATA=0x50;
	break;
	case 6:
	PORTB_DATA=0x60;
	break;
	case 7:
	PORTB_DATA=0x70;
	break;
	case 8:
	PORTB_DATA=0x80;
	break;
	case 9:
	PORTB_DATA=0x90;
	break;
	case 10:
	PORTB_DATA=0xA0;
	break;
	case 11:
	PORTB_DATA=0x40;
	break;
	case 12:
	PORTB_DATA=0xC0;
	break;
	case 13:
	PORTB_DATA=0xD0;
	break;
	case 14:
	PORTB_DATA=0xE0;
	break;
	case 15:
	PORTB_DATA=0xF0;
	break;
}*/

}

void SwICU_Stop(void)
{
timer0Stop();
}

void SwICU_Start(void)
{
timer0Start();
}
