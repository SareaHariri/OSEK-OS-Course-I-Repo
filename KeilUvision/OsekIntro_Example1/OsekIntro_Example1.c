/**
 * @file OsekIntro_Example1.c
 * @author Sarea Alhariri (Sarea.h95@outlook.com)
 * @brief  simple example to clarify Task Activation/Termination 
 * @version 0.1
 * @date 2020-05-1
 *
 * @copyright Sarea Alhariri - All rights reserved
 *
 */

#include "os.h"

DeclareTask(TaskA);
DeclareTask(TaskB);
DeclareTask(TaskC); 

static void SimpleDelay(void);

uint32_t TaskA_Counter = 0u;
uint32_t TaskB_Counter = 0u;
uint32_t TaskC_Counter = 0u;

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
    
   while(1)
   {
      TaskA_Counter++;
      SimpleDelay();      
      ActivateTask(TaskB);/*TaksA is preemtable. This is a scheduling point*/
      ActivateTask(TaskC);       
   }
}
TASK(TaskB)
{
   TaskB_Counter++; 
   SimpleDelay();
   TerminateTask();
}

TASK(TaskC)
{
   TaskC_Counter++;
   SimpleDelay();   
   TerminateTask();
}

static void SimpleDelay(void)
{
   uint32_t i = 0u; 
   
   while(i < 10000U){i++;}
}
