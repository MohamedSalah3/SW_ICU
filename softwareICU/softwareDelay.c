/*
 * softwareDelay.c
 *
 * Created: 17/01/2020 03:54:09 م
 *  Author: mo
 */ 
#include "softwareDelay.h"
void softwareDelayMs(volatile uint32_t u32_delay_in_ms){
volatile uint32_t Local_Nope_counter=0;
while (u32_delay_in_ms > 0)
{
	for(Local_Nope_counter = 0 ;Local_Nope_counter<10;Local_Nope_counter++);

u32_delay_in_ms--;	

}

}