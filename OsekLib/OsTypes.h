/**
 * @file Os_Kernel.h
 * @author Sarea Alhariri (Sarea.h95@outlook.com)
 * @brief typedefs and standard types
 * @version 0.1
 * @date 2020-01-24
 *
 * @copyright Copyright (c) 2020
 *
 */
#ifndef OS_KNL_H_
#define OS_KNL_H_

#include "stdbool.h"
#include <stdint.h>
 
/*******************************************************************************
 * #defines
 ******************************************************************************/
#define INIT_TO_ZERO 0U
#define INIT_TO_ONE	 1U

/*******************************************************************************
 *  Tasks data types
 ******************************************************************************/
typedef uint8_t TaskType;
typedef TaskType* TaskRefType;
typedef enum TaskState
{
  RUNNING,
  WAITING,
  READY,
  SUSPENDED,
  INVALID_STATE
} TaskStateType;
typedef TaskStateType* TaskStateRefType;
typedef enum
{
  BASIC = 0,
  EXTENDED
} Task_Model_t;
typedef struct Task_Declarator_tag
{
  TaskType Task_ID;
  uint8_t Pri;
  void (*Pcode)(void);
  Task_Model_t Model;
} TaskDeclaratorType;
typedef TaskDeclaratorType* TaskDeclaratorRefType;
/*******************************************************************************
 * Events data types
 ******************************************************************************/
typedef uint8_t EventMaskType;
typedef EventMaskType* EventMaskRefType;
/*******************************************************************************
 * Alarms data types
 ******************************************************************************/
typedef uint32_t TickType;
typedef TickType* TickRefType;
typedef struct AlarmBaseType_tag
{
  TickType maxallowedvalue;
  TickType ticksperbase;
  TickType mincycle;
} AlarmBaseType;
typedef AlarmBaseType* AlarmBaseRefType;
typedef uint8_t AlarmType;
typedef enum
{ /* Alarm fire data type */
  ABSOLUTE = 0,
  RELATIVE
} AlarmFireType_t;
typedef enum AlarmCurrentMode_tag
{
  CURRENT_MODE_ONE_SHOT = 0,
  CURRENT_MODE_CYCLIC
} AlarmCurrentMode_t;
typedef enum
{
  ALARM_ACTION_TASK,
  ALARM_ACTION_EVENT,
  ALARM_ACTION_CALL_BACK
} AlarmAction_t;
typedef void (*AlarmCallBackType)(void);
typedef struct AlarmDeclarator_tag
{
  AlarmBaseRefType BaseRefType;
  AlarmType ID;
  AlarmAction_t Action;
  AlarmFireType_t FireType;
  TaskType Task_ID;
  EventMaskType Event;
  AlarmCallBackType CB;
} AlarmDeclaratorType;
typedef AlarmDeclaratorType* AlarmDeclaratorTypeRef;
/*******************************************************************************
 * Resources data types
 ******************************************************************************/
typedef uint8_t ResourceType;
/*******************************************************************************
 *  Common Data types [Section 13.1 in OsekOs Doc]
 ******************************************************************************/
typedef enum
{
  E_OK = 0,
  E_OS_ACCESS,
  E_OS_CALLEVEL,
  E_OS_ID,
  E_OS_LIMIT,
  E_OS_NOFUNC,
  E_OS_RESOURCE,
  E_OS_STATE,
  E_OS_VALUE
} StatusType;

typedef uint8_t AppModeType;
/*******************************************************************************
 * Task control block
 ******************************************************************************/
typedef struct tcb_tag
{
  uint32_t* Stack_Pointer;
  uint32_t* Basic_Stack_Pointer;
  void (*Task_Ptr)(void);
  TaskStateType state;
  uint32_t* DeadBeefPtr;
  uint8_t priority;
  Task_Model_t Task_Model;
  EventMaskType Set_Event;
  EventMaskType Wait_Event;
  uint8_t ResourceOccupied;
  const uint8_t IsPreemptable;
  uint8_t ScheduleRequested;
} tcb_t;
typedef enum
{
  SVC_TASK_TERMINATE = 1,
  SVC_SCHEDULE,
  SVC_ACTIVATE,
  SVC_CHAIN,
  SVC_SET_EVENT,
  SVC_WAIT_EVENT,
  SVC_CLEAR_EVENT,
  SVC_GET_RESOURCE,
  SVC_RELEASE_RESOURCE
} SVC_Number;

/*******************************************************************************
 * Alarm control block
 ******************************************************************************/
typedef struct ACB_tag
{
  TickType Fire_Time;
  TickType Cyclic_Time;
  AlarmCallBackType CB;
  AlarmAction_t Alarm_Action;
  AlarmBaseRefType Base_Type_Ref;
  TaskType Alarm_Task_ID;
  EventMaskType Alarm_Event;
  bool Enabled;
} acb_t;


/**
 * @brief Resource Control block
 *
 */
typedef struct RCB_tag
{
  uint8_t ResInUse;
  uint8_t UserTaskPri;
}RCB_t; 

#endif
