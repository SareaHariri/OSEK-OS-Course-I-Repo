/**
 * @file SWTimer.c
 * @author Sarea Alhariri (Sarea.h95@outlook.com)
 * @brief  software timer simple implementation 
 * @version 0.1
 * @date 2021-01-05
 *
 * @copyright Sarea Alhariri - All rights reserved
 *
 */
#include <stdint.h>
#include <stdbool.h>

static uint32_t g_SystemTimer = 0U; 

void SWTimer_TickIncrement(void)
{
   g_SystemTimer++; 
}
void SWTimer_Delay(uint32_t TickDelay)
{
   uint32_t l_TimeStamp = g_SystemTimer ; 
   while(g_SystemTimer != l_TimeStamp + TickDelay); 
}
