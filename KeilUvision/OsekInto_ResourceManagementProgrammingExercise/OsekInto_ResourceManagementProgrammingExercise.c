/**
 * @file OsekIntro_Example1.c
 * @author Sarea Alhariri (Sarea.h95@outlook.com)
 * @brief  Resource management programming exercise starter file. 
 * @version 0.1
 * @date 2020-05-30
 *
 * @copyright Sarea Alhariri - All rights reserved
 *
 */

#include "os.h"
#include "SWTimer.h"
#include "gpio.h"
#include "sysctl.h"
#include "hw_memmap.h"
#include "tm4c123gh6pm.h"

#define USE_HW 1

static uint32_t g_SimulatedLedSignal = 0U; 

void SystemInit(void)
{
}
int main(void)
{
  StartOS();
  while(1); /* Should not be executed */
  return 0;
}

TASK(AppTask_Init)
{
#if USE_HW
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
  GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4 | GPIO_PIN_0);
  GPIO_PORTF_LOCK_R = 0x4c4f434b;
  GPIO_PORTF_CR_R = 0x01f;
  GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4 | GPIO_PIN_0, GPIO_STRENGTH_2MA,
                   GPIO_PIN_TYPE_STD_WPU);

#endif                   
  TerminateTask(); 
}
TASK(AppTask_Green)
{
   /*Led on */
   g_SimulatedLedSignal = 0x08U ; 
#if USE_HW
   GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1, GPIO_PIN_3);
#endif 
   SWTimer_Delay(200U); 
	#if USE_HW
   GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1,0U);
#endif 

   g_SimulatedLedSignal = 0x00U ; 
   TerminateTask(); 
}
TASK(AppTask_Red)
{
   /* RED Led Toggle */
#if USE_HW 
	static uint8_t l_Bit1 = GPIO_PIN_1; 
   GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1,
                 l_Bit1);
   l_Bit1 ^= GPIO_PIN_1;                
#endif 
   g_SimulatedLedSignal ^= 0x02; 
   TerminateTask(); 
}
