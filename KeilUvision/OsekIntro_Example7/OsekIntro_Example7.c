/**
 * @file OsekIntro_Example1.c
 * @author Sarea Alhariri (Sarea.h95@outlook.com)
 * @brief  simple example to clarify the priority ceiling pattern 
 * @version 0.1
 * @date 2020-05-30
 *
 * @copyright Sarea Alhariri - All rights reserved
 *
 */

#include "os.h"


static uint32_t TaskA_Counter = 0U; 
static uint32_t TaskB_Counter = 0U; 
static uint32_t TaskC_Counter = 0U; 

DeclareTask(TaskA);
DeclareTask(TaskB);
DeclareTask(TaskC); 

static void SimpleDelay(void);

void SystemInit(void)
{
}
int main(void)
{
 StartOS();
  while(1); /* Should not be executed */
  return 0;
}

TASK(TaskA)
{
   uint8_t index = 0U ; 
   while(1)
   {  
      SimpleDelay();
		TaskA_Counter++; 
      
      /*Task A is running at the home priority. It will be pre-empted */
      ActivateTask(TaskB);          
      ActivateTask(TaskC); 
      
      
      GetResource(SharedRes); 
      
      /* Task A is running at the ceiling priority. 
       * It will not be pre-empted by SharedRes-user task 
       */
      ActivateTask(TaskB); 
      
      
      /* Task A is running at the ceiling priority. 
       * It can be pre-empted by a higher priority task 
       * if the higher one is not configured to use the occupied resource. 
       */
      ActivateTask(TaskC); 
      
      /* Releasing a resource is a scheduling point. 
       * TaskA will be back to the home priority. 
       * Task B will be running because of the higher priority level 
       */ 
      ReleaseResource(SharedRes); 
   }
}

TASK(TaskB)
{
   SimpleDelay(); 
   TaskB_Counter++; 
   TerminateTask();
}

TASK(TaskC)
{
   SimpleDelay(); 
   TaskC_Counter++; 
   TerminateTask();
}

static void SimpleDelay(void)
{
   uint32_t i = 0u; 
   
   while(i < 10000U){i++;}
}
