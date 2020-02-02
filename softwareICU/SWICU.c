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
{//64 prescaler
uint64_t num_of_tics=0;
uint16_t num_of_cm=0;
//num_of_cm=(68 * (*a_pu8_capt)/1000);
num_of_tics=((* a_pu8_capt)+(u8_ovf_counter * RESOLUTION))/(58*16);
num_of_cm=num_of_tics/30;

//PORTB_DATA=(num_of_tics<<4);
/*
if (num_of_cm <15)
{
	PORTB_DATA=128;
}else if (num_of_cm==0)
{PORTB_DATA=0;
}
else if(num_of_cm >15 && num_of_cm <100){PORTB_DATA=255;}
*/
switch (num_of_tics) {
	case 0:{
	PORTB_DATA=0b00000000;
	timer2Start();
	timer2DelayMs(100);
	break;}
	case 1:{
	PORTB_DATA=0b00010000;
	timer2Start();
	timer2DelayMs(100);
	break;}
	case 2:{
	PORTB_DATA=0b00100000;
	timer2Start();
	timer2DelayMs(100);
	break;}
	case 3:{
	PORTB_DATA=0b00110000;
	timer2Start();
	timer2DelayMs(100);
	break;}
	case 4:{
	PORTB_DATA=0x40;
	timer2Start();
	timer2DelayMs(100);
	break;}
	case 5:{
	PORTB_DATA=0x50;
	timer2Start();
	timer2DelayMs(100);
	break;}
	case 6:{
	PORTB_DATA=0x60;
	timer2Start();
	timer2DelayMs(100);
	break;}
	case 7:{
	PORTB_DATA=0x70;
	timer2Start();
	timer2DelayMs(100);
	break;}
	case 8:{
	PORTB_DATA=0x80;
	timer2Start();
	timer2DelayMs(100);
	break;}
	case 9:{
	timer2Start();
	timer2DelayMs(100);
	PORTB_DATA=0x90;
	break;}
	case 10:{
	timer2Start();
	timer2DelayMs(100);
	PORTB_DATA=0xA0;
	break;}
	case 11:{
	timer2Start();
	timer2DelayMs(100);
	PORTB_DATA=0x40;
	break;}
	case 12:{
	timer2Start();
	timer2DelayMs(100);
	PORTB_DATA=0xC0;
	break;}
	case 13:{
	timer2Start();
	timer2DelayMs(100);
	
	PORTB_DATA=0xD0;
	break;}
	case 14:{
	timer2Start();
	timer2DelayMs(100);
	
	PORTB_DATA=0xE0;
	break;}
	case 15:{
	timer2Start();
	timer2DelayMs(100);
	PORTB_DATA=0xF0;
	break;}
	default:
	PORTB_DATA=0;
	break;
}
}


void SwICU_Stop(void)
{
timer0Stop();
}

void SwICU_Start(void)
{
timer0Start();
}
