/**
 * @file OsekIntro_Example3.c
 * @author Sarea Alhariri (Sarea.h95@outlook.com)
 * @brief  mixed preemtive scheduling policy example 
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
uint32_t i = 0;

void SystemInit(void)
{
}
int main(void)
{
  StartOS();
  return 0;
}

TASK(TaskA)
{
   while(1){
      TaskA_Counter++;
      SimpleDelay();
      ActivateTask(TaskB);
      SimpleDelay();
      Schedule(); 
   }
}
TASK(TaskB)
{
   TaskB_Counter++; 
   SimpleDelay();
   ActivateTask(TaskC); 
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
