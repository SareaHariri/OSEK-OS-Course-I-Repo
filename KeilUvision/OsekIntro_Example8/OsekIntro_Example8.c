/**
 * @file OsekIntro_Example1.c
 * @author Sarea Alhariri (Sarea.h95@outlook.com)
 * @brief  simple example to clarify shared resource problem 
 * @version 0.1
 * @date 2020-05-30
 *
 * @copyright Sarea Alhariri - All rights reserved
 *
 */

#include "os.h"

typedef struct task_buffer_tag
{
   TaskType SourceID; 
   uint8_t Data[8];
}TaskBuffer_t ; 


DeclareTask(TaskA);
DeclareTask(TaskB);
DeclareTask(TaskC); 

static void SimpleDelay(void);

static TaskBuffer_t ProtectedBuffer = {0U}; 
static TaskBuffer_t NotProtectedBuffer = {0U}; 

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
      
      NotProtectedBuffer.SourceID = TaskA ; 
      for(index = 0U; index < 4U; index++)
      {
         NotProtectedBuffer.Data[index] = 0xAA; 
      }
      ActivateTask(TaskC); 
      for(index = 4U; index < 8U; index++)
      {
          NotProtectedBuffer.Data[index] = 0xAA; 
      }   
      
      
      
      GetResource(SharedRes); 
      
      ProtectedBuffer.SourceID = TaskA ; 
      for(index = 0U; index < 4U; index++)
      {
         ProtectedBuffer.Data[index] = 0xAA; 
      }
      ActivateTask(TaskB); 
      for(index = 4U; index < 8U; index++)
      {
         ProtectedBuffer.Data[index] = 0xAA; 
      }
      ReleaseResource(SharedRes); 
   }
}

TASK(TaskB)
{
   uint8_t index = 0U ; 
   SimpleDelay(); 
   ProtectedBuffer.SourceID = TaskB; 
   
   for(index = 0U; index < 8U; index++)
   {
      ProtectedBuffer.Data[index] = 0xBB; 
   } 
   TerminateTask();
}

TASK(TaskC)
{
   uint8_t index = 0U ; 
   SimpleDelay(); 
   NotProtectedBuffer.SourceID = TaskC ; 
   
   for(index = 0U; index < 8U; index++)
   {
       NotProtectedBuffer.Data[index] = 0xCC; 
   } 
   TerminateTask();
}

static void SimpleDelay(void)
{
   uint32_t i = 0u; 
   
   while(i < 10000U){i++;}
}
