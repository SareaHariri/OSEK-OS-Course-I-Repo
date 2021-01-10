/**
 * @file OSCallbacks.c
 * @author sarea alhariri (sarea.h95@outlook.com)
 * @brief  OSEK OS callbacks file 
 * @version 0.1
 * @date 2021-01-07
 * 
 * @copyright  Sarea Alhariri - All rights reserved
 * 
 */
#include "os.h"
#include "SWTimer.h"


/**
 * @brief System timer callback.   
 * 
 */
ALARMCALLBACK(AppCB_SystemTimerUpdate)
{
   SWTimer_TickIncrement();  
}