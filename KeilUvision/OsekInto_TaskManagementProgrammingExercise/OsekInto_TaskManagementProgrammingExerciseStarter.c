/**
 * @file OsekIntro_TaskManagementProgrammingExerciseStarter.c
 * @author Sarea Alhariri (Sarea.h95@outlook.com)
 * @brief  Task managememt programming exercise starter file.  
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

/* define this to 1 when using Launchpad and 0 for simulation */
#define USE_HW 0




#define RED_STATE_TOGGLE_NUMBER   3U
#define GREEN_STATE_TOGGLE_NUMBER 7U
#define BLUE_STATE_TOGGLE_NUMBER  7U 
#define WHITE_STATE_TOGGLE_NUMBER 5U

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
  ActivateTask(AppTask_Red);
  TerminateTask(); 
}
TASK(AppTask_Red)
{
   uint8_t l_index = 0U; 
   uint8_t l_Pin1Toggle = GPIO_PIN_1; 
   
   for(l_index = 0U; l_index < RED_STATE_TOGGLE_NUMBER; l_index++){
#if USE_HW
      GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,l_Pin1Toggle); 
#endif
		 g_SimulatedLedSignal = l_Pin1Toggle; 
		 l_Pin1Toggle ^= GPIO_PIN_1; 
     SWTimer_Delay(100U);
   }
#if USE_HW   
	 GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,l_Pin1Toggle); 
#endif	
	 g_SimulatedLedSignal = l_Pin1Toggle; 
	 SWTimer_Delay(100U);
	 
   ChainTask(AppTask_Green); 
}

TASK(AppTask_Green)
{
   uint8_t l_index = 0U; 
   uint8_t l_Pin3Toggle = GPIO_PIN_3; 
   
   for(l_index = 0U; l_index < GREEN_STATE_TOGGLE_NUMBER; l_index++){
#if USE_HW
		 GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,l_Pin3Toggle); 
#endif     
		 g_SimulatedLedSignal = l_Pin3Toggle; 
		 l_Pin3Toggle ^= GPIO_PIN_3; 
     SWTimer_Delay(100U);
   }
#if USE_HW		 
   GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,l_Pin3Toggle); 
#endif   
	 g_SimulatedLedSignal = l_Pin3Toggle; 
	 SWTimer_Delay(100U); 
	 
   ChainTask(AppTask_Blue); 
}
/*******************************************************************************
 * TODO: 
 * Add your implementation for AppTask_Blue task 
 ******************************************************************************/
 TASK(AppTask_Blue)
{
   uint8_t l_index = 0U; 
   uint8_t l_Pin2Toggle = GPIO_PIN_2; 
   
   for(l_index = 0U; l_index < BLUE_STATE_TOGGLE_NUMBER; l_index++){
#if USE_HW
		 GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,l_Pin2Toggle); 
#endif     
		 g_SimulatedLedSignal = l_Pin2Toggle; 
		 l_Pin2Toggle ^= GPIO_PIN_2; 
     SWTimer_Delay(50U);
   }
#if USE_HW		 
   GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,l_Pin2Toggle); 
#endif   
	 g_SimulatedLedSignal = l_Pin2Toggle; 
	 SWTimer_Delay(50U); 
	 
   ChainTask(AppTask_White); 
}


 /******************************************************************************
 * TODO: 
 * Add your implementation for AppTask_White task 
 ******************************************************************************/
 TASK(AppTask_White)
{
   uint8_t l_index = 0U; 
   uint8_t l_Pin123Toggle = (GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3); 
   
   for(l_index = 0U; l_index < WHITE_STATE_TOGGLE_NUMBER; l_index++){
#if USE_HW
		 GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,l_Pin123Toggle); 
#endif     
		 g_SimulatedLedSignal = l_Pin123Toggle; 
		 l_Pin123Toggle ^= (GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3); 
     SWTimer_Delay(50U);
   }
#if USE_HW		 
   GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,l_Pin123Toggle); 
#endif   
	 g_SimulatedLedSignal = l_Pin123Toggle; 
	 SWTimer_Delay(50U); 
	 
   ChainTask(AppTask_Red); 
}

