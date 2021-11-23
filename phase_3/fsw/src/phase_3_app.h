/*=======================================================================================
** File Name:  phase_3_app.h
**
** Title:  Header File for PHASE_3 Application
**
** $Author:    Colin John
** $Revision: 1.1 $
** $Date:      2021-11-22
**
** Purpose:  To define PHASE_3's internal macros, data types, global variables and
**           function prototypes
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2021-11-22 | Colin John | Build #: Code Started
**
**=====================================================================================*/
    
#ifndef _PHASE_3_APP_H_
#define _PHASE_3_APP_H_

/*
** Pragmas
*/

/*
** Include Files
*/
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "phase_3_platform_cfg.h"
#include "phase_3_mission_cfg.h"
#include "phase_3_private_ids.h"
#include "phase_3_private_types.h"
#include "phase_3_perfids.h"
#include "phase_3_msgids.h"
#include "phase_3_msg.h"

 
#include "phase_3_iload_utils.h"

/*
** Local Defines
*/
#define PHASE_3_TIMEOUT_MSEC    1000

/*
** Local Structure Declarations
*/
typedef struct
{
    /* CFE Event table */
    CFE_EVS_BinFilter_t  EventTbl[PHASE_3_EVT_CNT];

    /* CFE scheduling pipe */
    CFE_SB_PipeId_t  SchPipeId; 
    uint16           usSchPipeDepth;
    char             cSchPipeName[OS_MAX_API_NAME];

    /* CFE command pipe */
    CFE_SB_PipeId_t  CmdPipeId;
    uint16           usCmdPipeDepth;
    char             cCmdPipeName[OS_MAX_API_NAME];
    
    /* CFE telemetry pipe */
    CFE_SB_PipeId_t  TlmPipeId;
    uint16           usTlmPipeDepth;
    char             cTlmPipeName[OS_MAX_API_NAME];

    /* Task-related */
    uint32  uiRunStatus;
    
    /* ILoad table-related */
    CFE_TBL_Handle_t  ILoadTblHdl;
    PHASE_3_ILoadTblEntry_t*  ILoadTblPtr;
    
    /* Input data - from I/O devices or subscribed from other apps' output data.
       Data structure should be defined in phase_3/fsw/src/phase_3_private_types.h */
    PHASE_3_InData_t   InData;

    /* Output data - to be published at the end of a Wakeup cycle.
       Data structure should be defined in phase_3/fsw/src/phase_3_private_types.h */
    PHASE_3_OutData_t  OutData;

    /* Housekeeping telemetry - for downlink only.
       Data structure should be defined in phase_3/fsw/src/phase_3_msg.h */
    PHASE_3_HkTlm_t  HkTlm;

    /* TODO:  Add declarations for additional private data here */
} PHASE_3_AppData_t;

/*
** External Global Variables
*/

/*
** Global Variables
*/

/*
** Local Variables
*/

/*
** Local Function Prototypes
*/
int32  PHASE_3_InitApp(void);
int32  PHASE_3_InitEvent(void);
int32  PHASE_3_InitData(void);
int32  PHASE_3_InitPipe(void);

void  PHASE_3_AppMain(void);

void  PHASE_3_CleanupCallback(void);

int32  PHASE_3_RcvMsg(int32 iBlocking);

void  PHASE_3_ProcessNewData(void);
void  PHASE_3_ProcessNewCmds(void);
void  PHASE_3_ProcessNewAppCmds(CFE_SB_Msg_t*);

void  PHASE_3_ReportHousekeeping(void);
void  PHASE_3_SendOutData(void);

boolean  PHASE_3_VerifyCmdLength(CFE_SB_Msg_t*, uint16);

#endif /* _PHASE_3_APP_H_ */

/*=======================================================================================
** End of file phase_3_app.h
**=====================================================================================*/
    