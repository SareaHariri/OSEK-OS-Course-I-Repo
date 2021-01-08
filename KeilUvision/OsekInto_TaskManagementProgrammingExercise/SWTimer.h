/**
 * @file SWTimer.h
 * @author Sarea Alhariri (Sarea.h95@outlook.com)
 * @brief  software timer simple interface  
 * @version 0.1
 * @date 2021-01-05
 *
 * @copyright Sarea Alhariri - All rights reserved
 *
 */
#include <stdint.h>

/**
 * @brief  Increment the number ticks by one
 * @return none 
 * @param  none
 * 
 */
extern void SWTimer_TickIncrement(void);

/**
 * @brief Blocking delay till the TickDelay is expired.
 * @return none 
 * @param TickDelay 
 * 
 */
extern void SWTimer_Delay(uint32_t TickDelay);

