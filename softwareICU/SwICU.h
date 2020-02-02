/*
 * SwICU.h
 *
 *  Created on: Oct 27, 2019
 *      Author: Sprints
 */

#ifndef SWICU_H_
#define SWICU_H_

#include "Interrupts.h"
#include "timers.h"
extern uint32_t volatile u32_ovf_counter;
typedef enum EN_SwICU_Edge_t{SwICU_EdgeFalling = 0,
	SwICU_EdgeRisiging = 1
}EN_SwICU_Edge_t;
/*use INT0_external_interrupt or INT1_external_interrupt
for int0 take the value to  MCUCR
for int1 take the value shifted by 2
for int 2 create your own enums
*/
void SwICU_Init(EN_SwICU_Edge_t a_en_inputCaptureEdge);/*intialize timer and interrupts*/
EN_SwICU_Edge_t SwICU_GetCfgEdge(void);
void SwICU_SetCfgEdge(EN_SwICU_Edge_t a_en_inputCaptureEdgeedge);/*to change the configuration of external interrupt rising to failing and so on*/
void SwICU_Read(volatile uint8_t * a_pu8_capt);/*to read TCNT*/
void SwICU_Stop(void);/*stop timer*/
void SwICU_Start(void);/*start timer*/
/*
void SwICU_Enable(void);
void SwICU_Disable(void);
*/
#endif /* SWICU_H_ */
