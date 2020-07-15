/**
 * @file os.h
 * @author Sarea Alhariri (Sarea.h95@outlook.com)
 * @brief  OS interface includes all interfaces to be used by app.
 * @version 0.1
 * @date 2020-01-17
 *
 * @copyright Sarea Alhariri - All rights reserved
 *
 */

#ifndef OS_H_
#define OS_H_
#include "OsCfg.h"
#include "OsTypes.h"


#define ALARMCALLBACK(CB_NAME)  void CB_NAME(void)
/* Interrupts processing services */
#define EnableAllInterrupts()  ENABLE_ALL_INT_HW_DEPENDENT()
#define DisableAllInterrupts() DISABLE_ALL_INT_HW_DEPENDENT()

/**
 * @brief  Wrappers Macros to provide the standard interfaces
 *
 */
/******************************************************************************/
#define OSErrorGetServiceId()			OsErrMgr_GetServiceID()
#define OSError_ActivateTask_TaskID()	OsErrMgr_GetTaskID()
#define OSError_ChainTask_TaskID()		OsErrMgr_GetTaskID()
#define OSError_GetTaskState_TaskID()	OsErrMgr_GetTaskID()
#define OSError_SetEvent_TaskID()		OsErrMgr_GetTaskID()
#define OSError_SetEvent_Mask()			OsErrMgr_GetEventID()
#define OSError_ClearEvent_Mask()		OsErrMgr_GetEventID()
#define OSError_GetEvent_TaskID()		OsErrMgr_GetTaskID()
#define OSError_WaitEvent_Mask()		OsErrMgr_GetEventID()
#define OSError_GetResource_ResID()		OsErrMgr_GetResID()
#define OSError_ReleaseResource_ResID() OsErrMgr_GetResID()

/**
 * @brief OS standard services IDs
 *
 */
typedef enum OSServiceIds
{
  OSServiceId_ActivateTask,
  OSServiceId_TerminateTask,
  OSServiceId_ChainTask,
  OSServiceId_Schedule,
  OSServiceId_GetTaskID,
  OSServiceId_GetTaskState,
  OSServiceId_DisableAllInterrupts,
  OSServiceId_EnableAllInterrupts,
  OSServiceId_SuspendAllInterrupts,
  OSServiceId_ResumeAllInterrupts,
  OSServiceId_SuspendOSInterrupts, /* Not supported */
  OSServiceId_ResumeOSInterrupts,  /* Not supported */
  OSServiceId_GetResource,
  OSServiceId_ReleaseResource,
  OSServiceId_SetEvent,
  OSServiceId_ClearEvent,
  OSServiceId_GetEvent,
  OSServiceId_WaitEvent,
  OSServiceId_GetAlarmBase,
  OSServiceId_GetAlarm,
  OSServiceId_SetRelAlarm,
  OSServiceId_SetAbsAlarm,
  OSServiceId_CancelAlarm,
  OSServiceId_GetActiveApplicationMode, /* Not supported */
  OSServiceId_StartOS,
  OSServiceId_ShutdownOS,  /*Not supported */
  OSServiceId_Invalid 
} OSServiceIdType;

/**
 * @brief This type store the first value written outside the valid stack range
 * and save the detected thread ID 
 * 
 */
typedef struct ErrMgr_StackOverFlow_tag
{
  uint32_t OverFlowEntry; 
  uint8_t TaskID; 
}ErrMgr_StackOverFlowContext_t;


/**
 * @brief Set the ID for Err managements module when an error is detected
 *
 * @param ID
 */
extern void OsErrMgr_SetServiceID(OSServiceIdType ID);

/**
 * @brief Get the Service ID where the error has been triggered
 *
 * @return OSServiceIdType
 */
extern OSServiceIdType OsErrMgr_GetServiceID(void);

/**
 * @brief Store the first parameter of task management servicess
 *
 * @param taskID
 */
extern void OsErrMgr_StoreTaskID(TaskType taskID);

/**
 * @brief Get the first parameter of task management services
 *
 * @param taskID
 */
extern TaskType OsErrMgr_GetTaskID(void);

/**
 * @brief Store the event ID of the event management services
 *
 * @param ev
 */
extern void OsErrMgr_StoreEventID(EventMaskType ev);

/**
 * @brief Get the event ID of the event management services
 *
 * @return EventMaskType
 */
extern EventMaskType OsErrMgr_GetEventID(void);

/**
 * @brief Set the resource ID of resource management services
 *
 * @param res
 */
extern void OsErrMgr_StoreResID(ResourceType res);

/**
 * @brief Get the resource ID of resource management services
 *
 * @return ResourceType
 */
extern ResourceType OsErrMgr_GetResID(void);

/**
 * @brief Save the overflow context 
 * 
 */
extern void OsErrMgr_SetOverFlowContext(TaskType ID, uint32_t DeadBeefOverWritten);

/**
 * @brief Get the over flow context 
 * 
 */
extern void OsErrMgr_GetOverFlowContext(TaskRefType RefID, uint32_t* pDeadBeefOverWritten);

extern void StartOS(void);

void DeclareAlarm(AlarmDeclaratorTypeRef declarator);
extern StatusType GetAlarmBase(AlarmType AlarmID, AlarmBaseRefType Info);
extern StatusType GetAlarm(AlarmType AlarmID, TickRefType Tick);
extern StatusType GetAlarm(AlarmType Alarm_ID, TickRefType Tick);
extern StatusType SetAbsAlarm(AlarmType Alarm_ID, TickType start, TickType cycle);
extern StatusType SetRelAlarm(AlarmType Alarm_ID, TickType inc, TickType cycle);
extern StatusType CancelAlarm(AlarmType Alarm_ID);

/*******************************************************************************
 * Event processing serives
 ******************************************************************************/
extern StatusType SetEvent(TaskType Task_ID, EventMaskType Mask);
extern StatusType ClearEvent(EventMaskType Mask);
extern StatusType GetEvent(TaskType Task_ID, EventMaskRefType Event);
extern StatusType WaitEvent(EventMaskType Mask);


extern void ResumeAllInterrupts(void);
extern void SuspendAllInterrupts(void);




/*******************************************************************************
 * Pre Processor Functions Prototype
 ******************************************************************************/
#define TASK(Task_Name) void OsTask_##Task_Name(void)
#define DeclareTask(TASK_ID) TASK(TASK_ID)

/*******************************************************************************
 * Functions Prototype
 ******************************************************************************/
extern StatusType ActivateTask(TaskType Task_Id);
extern StatusType TerminateTask(void);
extern StatusType ChainTask(TaskType Task_Id);
extern StatusType Schedule(void);
extern StatusType GetTaskID(TaskRefType Task_Id_Ref);
extern StatusType GetTaskState(TaskType Task_Id, TaskStateRefType Task_State_Ref);
extern void OsTask_IdleMechanism(void);


/**
 * @brief
 * enter critical sections in the code that
 * are assigned to the resource referenced by <ResID>
 *
 * @param ResID             resource ID
 * @return StatusType       E_OK no error
 *                          E_OS_ID ID is not valid
 *                          E_OS_ACCESS already occupied or not assigned to the task
 */
extern StatusType GetResource(ResourceType ResID);

/**
 * @brief
 * leave critical sections in the code that are
 * assigned to the resource referenced by <ResID>.
 *
 * @param ResID             resource ID
 * @return StatusType       E_OK no error
 *                          E_OS_ID ID is not valid
 *                          E_OS_ACCESS not assigned to the task
 *                          E_OS_NOFUNC not occupied by any task
 */
extern StatusType ReleaseResource(ResourceType ResID);



#endif /* OS_H_ */
