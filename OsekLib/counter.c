#include "counter.h"
#include "OsCfg.h"
#include <stdint.h>

#define NVIC_ST_CTRL_R (*((volatile uint32_t*)0xE000E010))
#define NVIC_ST_RELOAD_R (*((volatile uint32_t*)0xE000E014))
#define NVIC_ST_CURRENT_R (*((volatile uint32_t*)0xE000E018))
#define NVIC_SYSPRI3_R (*((volatile uint32_t*)0xE000ED20))

#define INIT_TO_ZERO 0U

static uint32_t OsCnt_SystemCounter = INIT_TO_ZERO;

void SysTick_Init(void)
{

 NVIC_ST_CTRL_R = 0;			/* disable SysTick during setup */
 NVIC_ST_CURRENT_R = 0;		/* any write to current clears it */
 NVIC_SYSPRI3_R |= 0x20000000; /* priority 1 */
 NVIC_SYSPRI3_R |= 0x00200000; /* priority 1 to PEND SV  */
 NVIC_ST_RELOAD_R = OsCfg_SYSTEM_TICK_IN_MS * 16000u; /*TODO: 10 should be a configured value */
 NVIC_ST_CTRL_R = 0x07;		 /* enable, core clock and interrupt arm */

}

void OsCnt_IncrSystemCounter(void)
{
  OsCnt_SystemCounter++;
}

uint32_t OsCnt_GetSystemCounter(void)
{
  return OsCnt_SystemCounter;
}
