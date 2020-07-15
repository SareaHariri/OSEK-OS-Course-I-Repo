/**
 * @file counter.h
 * @author Sarea Alhariri (Sarea.h95@outlook.com)
 * @brief system counter module interface
 * @version 0.1
 * @date 2020-01-24
 *
 * @copyright Copyright (c) 2020
 *
 */
#ifndef COUNTER_H_
#define COUNTER_H_
#include <stdint.h>

extern void SysTick_Init(void);
extern void OsCnt_IncrSystemCounter(void);
extern uint32_t OsCnt_GetSystemCounter(void);

#endif
