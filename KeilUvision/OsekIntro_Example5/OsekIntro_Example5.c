/**
 * @file OsekIntro_Example6.c
 * @author Sarea Alhariri (Sarea.h95@outlook.com)
 * @brief  LED state machine
 * @version 0.1
 * @date 2020-05-9
 *
 * @copyright Sarea Alhariri - All rights reserved
 *
 */
#include <stdbool.h>
#include <stdint.h>
#include "gpio.h"
#include "hw_memmap.h"
#include "os.h"
#include "sysctl.h"
#include "tm4c123gh6pm.h"


#define NUMBER_OF_DELAY_CYCLES 0x003FFFFFU

DeclareTask(Task_Init);
DeclareTask(Task_White);
DeclareTask(Task_Red);
DeclareTask(Task_Green);
DeclareTask(Task_Blue);

static void SetLedCurrentState(void);

void SystemInit(void) {}
int main(void) {
  StartOS();
  return 0;
}

TASK(Task_White) {

  uint32_t l_PF0 = 0U;
  uint32_t l_PF4 = 0U;

  while (1) {

    SetLedCurrentState();
    SysCtlDelay(NUMBER_OF_DELAY_CYCLES);

    l_PF0 = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0);
    l_PF4 = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4);

    if ((l_PF0 | l_PF4) == 0x10) {
      ActivateTask(Task_Red);
    } else if ((l_PF0 | l_PF4) == 0x01) {
      ActivateTask(Task_Blue);
    }
  }
}

TASK(Task_Red) {
  uint32_t l_PF0 = 0U;
  uint32_t l_PF4 = 0U;

  while (1) {

    SetLedCurrentState();
    SysCtlDelay(NUMBER_OF_DELAY_CYCLES);

    l_PF0 = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0);
    l_PF4 = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4);

    if ((l_PF0 | l_PF4) == 0x10) {
      ChainTask(Task_Green);
    } else if ((l_PF0 | l_PF4) == 0x01) {
      ChainTask(Task_Blue);
    } else {
      TerminateTask();
    }
  }
}

TASK(Task_Green) {
  uint32_t l_PF0 = 0U;
  uint32_t l_PF4 = 0U;

  while (1) {
    SetLedCurrentState();
    SysCtlDelay(NUMBER_OF_DELAY_CYCLES);

    l_PF0 = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0);
    l_PF4 = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4);

    if ((l_PF0 | l_PF4) == 0x10) {
      ChainTask(Task_Blue);
    } else if ((l_PF0 | l_PF4) == 0x01) {
      ChainTask(Task_Red);
    } else {
      TerminateTask();
    }
  }
}

TASK(Task_Blue) {
  uint32_t l_PF0 = 0U;
  uint32_t l_PF4 = 0U;

  while (1) {
    SetLedCurrentState();
    SysCtlDelay(NUMBER_OF_DELAY_CYCLES);

    l_PF0 = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0);
    l_PF4 = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4);

    if ((l_PF0 | l_PF4) == 0x10) {
      ChainTask(Task_Red);
    } else if ((l_PF0 | l_PF4) == 0x01) {
      ChainTask(Task_Green);
    } else {
      TerminateTask();
    }
  }
}

TASK(Task_Init) {

  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  GPIO_PORTF_LOCK_R = 0x4c4f434b;
  GPIO_PORTF_CR_R = 0x01f;
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
  GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4 | GPIO_PIN_0);

  GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4 | GPIO_PIN_0, GPIO_STRENGTH_2MA,
                   GPIO_PIN_TYPE_STD_WPU);

  TerminateTask();
}

static void SetLedCurrentState(void) {
  TaskType l_CurrentTask = (TaskType)0;

  GetTaskID(&l_CurrentTask);

  switch (l_CurrentTask) {
  case Task_White:
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3,
                 GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
    break;
  case Task_Red:
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3,
                 GPIO_PIN_1);
    break;
  case Task_Green:
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3,
                 GPIO_PIN_3);
    break;
  case Task_Blue:
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3,
                 GPIO_PIN_2);
    break;
  default:
    break;
  }
}
