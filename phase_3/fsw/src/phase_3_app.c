/*=======================================================================================
** File Name:  phase_3_app.c
**
** Title:  Function Definitions for PHASE_3 Application
**
** $Author:    Colin John
** $Revision: 1.1 $
** $Date:      2021-11-22
**
** Purpose:  This source file contains all necessary function definitions to run PHASE_3
**           application.
**
** Functions Defined:
**    Function X - Brief purpose of function X
**    Function Y - Brief purpose of function Y
**    Function Z - Brief purpose of function Z
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to all functions in the file.
**    2. List the external source(s) and event(s) that can cause the funcs in this
**       file to execute.
**    3. List known limitations that apply to the funcs in this file.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2021-11-22 | Colin John | Build #: Code Started
**
**=====================================================================================*/

/*
** Pragmas
*/

/*
** Include Files
*/
#include <string.h>

#include "cfe.h"

#include "phase_3_platform_cfg.h"
#include "phase_3_mission_cfg.h"
#include "phase_3_app.h"

/*
** Local Defines
*/

/*
** Local Structure Declarations
*/

/*
** External Global Variables
*/

/*
** Global Variables
*/
PHASE_3_AppData_t  g_PHASE_3_AppData;

/*
** Local Variables
*/

/*
** Local Function Definitions
*/
    
/*=====================================================================================
** Name: PHASE_3_InitEvent
**
** Purpose: To initialize and register event table for PHASE_3 application
**
** Arguments:
**    None
**
** Returns:
**    int32 iStatus - Status of initialization
**
** Routines Called:
**    CFE_EVS_Register
**    CFE_ES_WriteToSysLog
**
** Called By:
**    PHASE_3_InitApp
**
** Global Inputs/Reads:
**    TBD
**
** Global Outputs/Writes:
**    g_PHASE_3_AppData.EventTbl
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  Colin John 
**
** History:  Date Written  2021-11-22
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
int32 PHASE_3_InitEvent()
{
    int32  iStatus=CFE_SUCCESS;

    /* Create the event table */
    memset((void*)g_PHASE_3_AppData.EventTbl, 0x00, sizeof(g_PHASE_3_AppData.EventTbl));

    g_PHASE_3_AppData.EventTbl[0].EventID = PHASE_3_RESERVED_EID;
    g_PHASE_3_AppData.EventTbl[1].EventID = PHASE_3_INF_EID;
    g_PHASE_3_AppData.EventTbl[2].EventID = PHASE_3_INIT_INF_EID;
    g_PHASE_3_AppData.EventTbl[3].EventID = PHASE_3_ILOAD_INF_EID;
    g_PHASE_3_AppData.EventTbl[4].EventID = PHASE_3_CDS_INF_EID;
    g_PHASE_3_AppData.EventTbl[5].EventID = PHASE_3_CMD_INF_EID;

    g_PHASE_3_AppData.EventTbl[ 6].EventID = PHASE_3_ERR_EID;
    g_PHASE_3_AppData.EventTbl[ 7].EventID = PHASE_3_INIT_ERR_EID;
    g_PHASE_3_AppData.EventTbl[ 8].EventID = PHASE_3_ILOAD_ERR_EID;
    g_PHASE_3_AppData.EventTbl[ 9].EventID = PHASE_3_CDS_ERR_EID;
    g_PHASE_3_AppData.EventTbl[10].EventID = PHASE_3_CMD_ERR_EID;
    g_PHASE_3_AppData.EventTbl[11].EventID = PHASE_3_PIPE_ERR_EID;
    g_PHASE_3_AppData.EventTbl[12].EventID = PHASE_3_MSGID_ERR_EID;
    g_PHASE_3_AppData.EventTbl[13].EventID = PHASE_3_MSGLEN_ERR_EID;

    /* Register the table with CFE */
    iStatus = CFE_EVS_Register(g_PHASE_3_AppData.EventTbl,
                               PHASE_3_EVT_CNT, CFE_EVS_BINARY_FILTER);
    if (iStatus != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("PHASE_3 - Failed to register with EVS (0x%08X)\n", iStatus);
    }

    return (iStatus);
}
    
/*=====================================================================================
** Name: PHASE_3_InitPipe
**
** Purpose: To initialize all message pipes and subscribe to messages for PHASE_3 application
**
** Arguments:
**    None
**
** Returns:
**    int32 iStatus - Status of initialization
**
** Routines Called:
**    CFE_SB_CreatePipe
**    CFE_SB_Subscribe
**    CFE_ES_WriteToSysLog
**
** Called By:
**    PHASE_3_InitApp
**
** Global Inputs/Reads:
**    None
**
** Global Outputs/Writes:
**    g_PHASE_3_AppData.usSchPipeDepth
**    g_PHASE_3_AppData.cSchPipeName
**    g_PHASE_3_AppData.SchPipeId
**    g_PHASE_3_AppData.usCmdPipeDepth
**    g_PHASE_3_AppData.cCmdPipeName
**    g_PHASE_3_AppData.CmdPipeId
**    g_PHASE_3_AppData.usTlmPipeDepth
**    g_PHASE_3_AppData.cTlmPipeName
**    g_PHASE_3_AppData.TlmPipeId
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  Colin John 
**
** History:  Date Written  2021-11-22
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
int32 PHASE_3_InitPipe()
{
    int32  iStatus=CFE_SUCCESS;

    /* Init schedule pipe */
    g_PHASE_3_AppData.usSchPipeDepth = PHASE_3_SCH_PIPE_DEPTH;
    memset((void*)g_PHASE_3_AppData.cSchPipeName, '\0', sizeof(g_PHASE_3_AppData.cSchPipeName));
    strncpy(g_PHASE_3_AppData.cSchPipeName, "PHASE_3_SCH_PIPE", OS_MAX_API_NAME-1);

    /* Subscribe to Wakeup messages */
    iStatus = CFE_SB_CreatePipe(&g_PHASE_3_AppData.SchPipeId,
                                 g_PHASE_3_AppData.usSchPipeDepth,
                                 g_PHASE_3_AppData.cSchPipeName);
    if (iStatus == CFE_SUCCESS)
    {
        iStatus = CFE_SB_SubscribeEx(PHASE_3_WAKEUP_MID, g_PHASE_3_AppData.SchPipeId, CFE_SB_Default_Qos, 1);

        if (iStatus != CFE_SUCCESS)
        {
            CFE_ES_WriteToSysLog("PHASE_3 - Sch Pipe failed to subscribe to PHASE_3_WAKEUP_MID. (0x%08X)\n", iStatus);
            goto PHASE_3_InitPipe_Exit_Tag;
        }
        
    }
    else
    {
        CFE_ES_WriteToSysLog("PHASE_3 - Failed to create SCH pipe (0x%08X)\n", iStatus);
        goto PHASE_3_InitPipe_Exit_Tag;
    }

    /* Init command pipe */
    g_PHASE_3_AppData.usCmdPipeDepth = PHASE_3_CMD_PIPE_DEPTH ;
    memset((void*)g_PHASE_3_AppData.cCmdPipeName, '\0', sizeof(g_PHASE_3_AppData.cCmdPipeName));
    strncpy(g_PHASE_3_AppData.cCmdPipeName, "PHASE_3_CMD_PIPE", OS_MAX_API_NAME-1);

    /* Subscribe to command messages */
    iStatus = CFE_SB_CreatePipe(&g_PHASE_3_AppData.CmdPipeId,
                                 g_PHASE_3_AppData.usCmdPipeDepth,
                                 g_PHASE_3_AppData.cCmdPipeName);
    if (iStatus == CFE_SUCCESS)
    {
        /* Subscribe to command messages */
        iStatus = CFE_SB_Subscribe(PHASE_3_CMD_MID, g_PHASE_3_AppData.CmdPipeId);

        if (iStatus != CFE_SUCCESS)
        {
            CFE_ES_WriteToSysLog("PHASE_3 - CMD Pipe failed to subscribe to PHASE_3_CMD_MID. (0x%08X)\n", iStatus);
            goto PHASE_3_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_Subscribe(PHASE_3_SEND_HK_MID, g_PHASE_3_AppData.CmdPipeId);

        if (iStatus != CFE_SUCCESS)
        {
            CFE_ES_WriteToSysLog("PHASE_3 - CMD Pipe failed to subscribe to PHASE_3_SEND_HK_MID. (0x%08X)\n", iStatus);
            goto PHASE_3_InitPipe_Exit_Tag;
        }
        
    }
    else
    {
        CFE_ES_WriteToSysLog("PHASE_3 - Failed to create CMD pipe (0x%08X)\n", iStatus);
        goto PHASE_3_InitPipe_Exit_Tag;
    }

    /* Init telemetry pipe */
    g_PHASE_3_AppData.usTlmPipeDepth = PHASE_3_TLM_PIPE_DEPTH;
    memset((void*)g_PHASE_3_AppData.cTlmPipeName, '\0', sizeof(g_PHASE_3_AppData.cTlmPipeName));
    strncpy(g_PHASE_3_AppData.cTlmPipeName, "PHASE_3_TLM_PIPE", OS_MAX_API_NAME-1);

    /* Subscribe to telemetry messages on the telemetry pipe */
    iStatus = CFE_SB_CreatePipe(&g_PHASE_3_AppData.TlmPipeId,
                                 g_PHASE_3_AppData.usTlmPipeDepth,
                                 g_PHASE_3_AppData.cTlmPipeName);
    if (iStatus == CFE_SUCCESS)
    {
        /* TODO:  Add CFE_SB_Subscribe() calls for other apps' output data here.
        **
        ** Examples:
        **     CFE_SB_Subscribe(GNCEXEC_OUT_DATA_MID, g_PHASE_3_AppData.TlmPipeId);
        */
    }
    else
    {
        CFE_ES_WriteToSysLog("PHASE_3 - Failed to create TLM pipe (0x%08X)\n", iStatus);
        goto PHASE_3_InitPipe_Exit_Tag;
    }

PHASE_3_InitPipe_Exit_Tag:
    return (iStatus);
}
    
/*=====================================================================================
** Name: PHASE_3_InitData
**
** Purpose: To initialize global variables used by PHASE_3 application
**
** Arguments:
**    None
**
** Returns:
**    int32 iStatus - Status of initialization
**
** Routines Called:
**    CFE_SB_InitMsg
**
** Called By:
**    PHASE_3_InitApp
**
** Global Inputs/Reads:
**    TBD
**
** Global Outputs/Writes:
**    g_PHASE_3_AppData.InData
**    g_PHASE_3_AppData.OutData
**    g_PHASE_3_AppData.HkTlm
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  Colin John 
**
** History:  Date Written  2021-11-22
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
int32 PHASE_3_InitData()
{
    int32  iStatus=CFE_SUCCESS;

    /* Init input data */
    memset((void*)&g_PHASE_3_AppData.InData, 0x00, sizeof(g_PHASE_3_AppData.InData));

    /* Init output data */
    memset((void*)&g_PHASE_3_AppData.OutData, 0x00, sizeof(g_PHASE_3_AppData.OutData));
    CFE_SB_InitMsg(&g_PHASE_3_AppData.OutData,
                   PHASE_3_OUT_DATA_MID, sizeof(g_PHASE_3_AppData.OutData), TRUE);

    /* Init housekeeping packet */
    memset((void*)&g_PHASE_3_AppData.HkTlm, 0x00, sizeof(g_PHASE_3_AppData.HkTlm));
    CFE_SB_InitMsg(&g_PHASE_3_AppData.HkTlm,
                   PHASE_3_HK_TLM_MID, sizeof(g_PHASE_3_AppData.HkTlm), TRUE);

    return (iStatus);
}
    
/*=====================================================================================
** Name: PHASE_3_InitApp
**
** Purpose: To initialize all data local to and used by PHASE_3 application
**
** Arguments:
**    None
**
** Returns:
**    int32 iStatus - Status of initialization
**
** Routines Called:
**    CFE_ES_RegisterApp
**    CFE_ES_WriteToSysLog
**    CFE_EVS_SendEvent
**    OS_TaskInstallDeleteHandler
**    PHASE_3_InitEvent
**    PHASE_3_InitPipe
**    PHASE_3_InitData
**
** Called By:
**    PHASE_3_AppMain
**
** Global Inputs/Reads:
**    TBD
**
** Global Outputs/Writes:
**    TBD
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  Colin John 
**
** History:  Date Written  2021-11-22
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
int32 PHASE_3_InitApp()
{
    int32  iStatus=CFE_SUCCESS;

    g_PHASE_3_AppData.uiRunStatus = CFE_ES_APP_RUN;

    iStatus = CFE_ES_RegisterApp();
    if (iStatus != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("PHASE_3 - Failed to register the app (0x%08X)\n", iStatus);
        goto PHASE_3_InitApp_Exit_Tag;
    }

    if ((PHASE_3_InitEvent() != CFE_SUCCESS) || 
        (PHASE_3_InitPipe() != CFE_SUCCESS) || 
        (PHASE_3_InitData() != CFE_SUCCESS) ||
        (PHASE_3_InitILoadTbl() != CFE_SUCCESS))
    {
        iStatus = -1;
        goto PHASE_3_InitApp_Exit_Tag;
    }

    /* Install the cleanup callback */
    OS_TaskInstallDeleteHandler((void*)&PHASE_3_CleanupCallback);

PHASE_3_InitApp_Exit_Tag:
    if (iStatus == CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(PHASE_3_INIT_INF_EID, CFE_EVS_INFORMATION,
                          "PHASE_3 - Application initialized");
    }
    else
    {
        CFE_ES_WriteToSysLog("PHASE_3 - Application failed to initialize\n");
    }

    return (iStatus);
}
    
/*=====================================================================================
** Name: PHASE_3_CleanupCallback
**
** Purpose: To handle any neccesary cleanup prior to application exit
**
** Arguments:
**    None
**
** Returns:
**    None
**
** Routines Called:
**    TBD
**
** Called By:
**    TBD
**
** Global Inputs/Reads:
**    TBD
**
** Global Outputs/Writes:
**    TBD
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  Colin John 
**
** History:  Date Written  2021-11-22
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
void PHASE_3_CleanupCallback()
{
    /* TODO:  Add code to cleanup memory and other cleanup here */
}
    
/*=====================================================================================
** Name: PHASE_3_RcvMsg
**
** Purpose: To receive and process messages for PHASE_3 application
**
** Arguments:
**    None
**
** Returns:
**    int32 iStatus - Status of initialization 
**
** Routines Called:
**    CFE_SB_RcvMsg
**    CFE_SB_GetMsgId
**    CFE_EVS_SendEvent
**    CFE_ES_PerfLogEntry
**    CFE_ES_PerfLogExit
**    PHASE_3_ProcessNewCmds
**    PHASE_3_ProcessNewData
**    PHASE_3_SendOutData
**
** Called By:
**    PHASE_3_Main
**
** Global Inputs/Reads:
**    g_PHASE_3_AppData.SchPipeId
**
** Global Outputs/Writes:
**    g_PHASE_3_AppData.uiRunStatus
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  Colin John 
**
** History:  Date Written  2021-11-22
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
int32 PHASE_3_RcvMsg(int32 iBlocking)
{
    int32           iStatus=CFE_SUCCESS;
    CFE_SB_Msg_t*   MsgPtr=NULL;
    CFE_SB_MsgId_t  MsgId;

    /* Stop Performance Log entry */
    CFE_ES_PerfLogExit(PHASE_3_MAIN_TASK_PERF_ID);

    /* Wait for WakeUp messages from scheduler */
    iStatus = CFE_SB_RcvMsg(&MsgPtr, g_PHASE_3_AppData.SchPipeId, iBlocking);

    /* Start Performance Log entry */
    CFE_ES_PerfLogEntry(PHASE_3_MAIN_TASK_PERF_ID);

    if (iStatus == CFE_SUCCESS)
    {
        MsgId = CFE_SB_GetMsgId(MsgPtr);
        switch (MsgId)
	{
            case PHASE_3_WAKEUP_MID:
                PHASE_3_ProcessNewCmds();
                PHASE_3_ProcessNewData();

                /* TODO:  Add more code here to handle other things when app wakes up */

                /* The last thing to do at the end of this Wakeup cycle should be to
                   automatically publish new output. */
                PHASE_3_SendOutData();
                break;

            default:
                CFE_EVS_SendEvent(PHASE_3_MSGID_ERR_EID, CFE_EVS_ERROR,
                                  "PHASE_3 - Recvd invalid SCH msgId (0x%08X)", MsgId);
        }
    }
    else if (iStatus == CFE_SB_NO_MESSAGE)
    {
        /* If there's no incoming message, you can do something here, or nothing */
    }
    else
    {
        /* This is an example of exiting on an error.
        ** Note that a SB read error is not always going to result in an app quitting.
        */
        CFE_EVS_SendEvent(PHASE_3_PIPE_ERR_EID, CFE_EVS_ERROR,
			  "PHASE_3: SB pipe read error (0x%08X), app will exit", iStatus);
        g_PHASE_3_AppData.uiRunStatus= CFE_ES_APP_ERROR;
    }

    return (iStatus);
}
    
/*=====================================================================================
** Name: PHASE_3_ProcessNewData
**
** Purpose: To process incoming data subscribed by PHASE_3 application
**
** Arguments:
**    None
**
** Returns:
**    None
**
** Routines Called:
**    CFE_SB_RcvMsg
**    CFE_SB_GetMsgId
**    CFE_EVS_SendEvent
**
** Called By:
**    PHASE_3_RcvMsg
**
** Global Inputs/Reads:
**    None
**
** Global Outputs/Writes:
**    None
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  Colin John 
**
** History:  Date Written  2021-11-22
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
void PHASE_3_ProcessNewData()
{
    int iStatus = CFE_SUCCESS;
    CFE_SB_Msg_t*   TlmMsgPtr=NULL;
    CFE_SB_MsgId_t  TlmMsgId;

    /* Process telemetry messages till the pipe is empty */
    while (1)
    {
        iStatus = CFE_SB_RcvMsg(&TlmMsgPtr, g_PHASE_3_AppData.TlmPipeId, CFE_SB_POLL);
        if (iStatus == CFE_SUCCESS)
        {
            TlmMsgId = CFE_SB_GetMsgId(TlmMsgPtr);
            switch (TlmMsgId)
            {
                /* TODO:  Add code to process all subscribed data here 
                **
                ** Example:
                **     case NAV_OUT_DATA_MID:
                **         PHASE_3_ProcessNavData(TlmMsgPtr);
                **         break;
                */

                default:
                    CFE_EVS_SendEvent(PHASE_3_MSGID_ERR_EID, CFE_EVS_ERROR,
                                      "PHASE_3 - Recvd invalid TLM msgId (0x%08X)", TlmMsgId);
                    break;
            }
        }
        else if (iStatus == CFE_SB_NO_MESSAGE)
        {
            break;
        }
        else
        {
            CFE_EVS_SendEvent(PHASE_3_PIPE_ERR_EID, CFE_EVS_ERROR,
                  "PHASE_3: CMD pipe read error (0x%08X)", iStatus);
            g_PHASE_3_AppData.uiRunStatus = CFE_ES_APP_ERROR;
            break;
        }
    }
}
    
/*=====================================================================================
** Name: PHASE_3_ProcessNewCmds
**
** Purpose: To process incoming command messages for PHASE_3 application
**
** Arguments:
**    None
**
** Returns:
**    None
**
** Routines Called:
**    CFE_SB_RcvMsg
**    CFE_SB_GetMsgId
**    CFE_EVS_SendEvent
**    PHASE_3_ProcessNewAppCmds
**    PHASE_3_ReportHousekeeping
**
** Called By:
**    PHASE_3_RcvMsg
**
** Global Inputs/Reads:
**    None
**
** Global Outputs/Writes:
**    None
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  Colin John 
**
** History:  Date Written  2021-11-22
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
void PHASE_3_ProcessNewCmds()
{
    int iStatus = CFE_SUCCESS;
    CFE_SB_Msg_t*   CmdMsgPtr=NULL;
    CFE_SB_MsgId_t  CmdMsgId;

    /* Process command messages till the pipe is empty */
    while (1)
    {
        iStatus = CFE_SB_RcvMsg(&CmdMsgPtr, g_PHASE_3_AppData.CmdPipeId, CFE_SB_POLL);
        if(iStatus == CFE_SUCCESS)
        {
            CmdMsgId = CFE_SB_GetMsgId(CmdMsgPtr);
            switch (CmdMsgId)
            {
                case PHASE_3_CMD_MID:
                    PHASE_3_ProcessNewAppCmds(CmdMsgPtr);
                    break;

                case PHASE_3_SEND_HK_MID:
                    PHASE_3_ReportHousekeeping();
                    break;

                /* TODO:  Add code to process other subscribed commands here
                **
                ** Example:
                **     case CFE_TIME_DATA_CMD_MID:
                **         PHASE_3_ProcessTimeDataCmd(CmdMsgPtr);
                **         break;
                */

                default:
                    CFE_EVS_SendEvent(PHASE_3_MSGID_ERR_EID, CFE_EVS_ERROR,
                                      "PHASE_3 - Recvd invalid CMD msgId (0x%08X)", CmdMsgId);
                    break;
            }
        }
        else if (iStatus == CFE_SB_NO_MESSAGE)
        {
            break;
        }
        else
        {
            CFE_EVS_SendEvent(PHASE_3_PIPE_ERR_EID, CFE_EVS_ERROR,
                  "PHASE_3: CMD pipe read error (0x%08X)", iStatus);
            g_PHASE_3_AppData.uiRunStatus = CFE_ES_APP_ERROR;
            break;
        }
    }
}
    
/*=====================================================================================
** Name: PHASE_3_ProcessNewAppCmds
**
** Purpose: To process command messages targeting PHASE_3 application
**
** Arguments:
**    CFE_SB_Msg_t*  MsgPtr - new command message pointer
**
** Returns:
**    None
**
** Routines Called:
**    CFE_SB_GetCmdCode
**    CFE_EVS_SendEvent
**
** Called By:
**    PHASE_3_ProcessNewCmds
**
** Global Inputs/Reads:
**    None
**
** Global Outputs/Writes:
**    g_PHASE_3_AppData.HkTlm.usCmdCnt
**    g_PHASE_3_AppData.HkTlm.usCmdErrCnt
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  Colin John 
**
** History:  Date Written  2021-11-22
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
void PHASE_3_ProcessNewAppCmds(CFE_SB_Msg_t* MsgPtr)
{
    uint32  uiCmdCode=0;

    if (MsgPtr != NULL)
    {
        uiCmdCode = CFE_SB_GetCmdCode(MsgPtr);
        switch (uiCmdCode)
        {
            case PHASE_3_NOOP_CC:
                g_PHASE_3_AppData.HkTlm.usCmdCnt++;
                CFE_EVS_SendEvent(PHASE_3_CMD_INF_EID, CFE_EVS_INFORMATION,
                                  "PHASE_3 - Recvd NOOP cmd (%d)", uiCmdCode);
                break;

            case PHASE_3_RESET_CC:
                g_PHASE_3_AppData.HkTlm.usCmdCnt = 0;
                g_PHASE_3_AppData.HkTlm.usCmdErrCnt = 0;
                CFE_EVS_SendEvent(PHASE_3_CMD_INF_EID, CFE_EVS_INFORMATION,
                                  "PHASE_3 - Recvd RESET cmd (%d)", uiCmdCode);
                break;

            /* TODO:  Add code to process the rest of the PHASE_3 commands here */

            default:
                g_PHASE_3_AppData.HkTlm.usCmdErrCnt++;
                CFE_EVS_SendEvent(PHASE_3_MSGID_ERR_EID, CFE_EVS_ERROR,
                                  "PHASE_3 - Recvd invalid cmdId (%d)", uiCmdCode);
                break;
        }
    }
}
    
/*=====================================================================================
** Name: PHASE_3_ReportHousekeeping
**
** Purpose: To send housekeeping message
**
** Arguments:
**    None
**
** Returns:
**    None
**
** Routines Called:
**    TBD
**
** Called By:
**    PHASE_3_ProcessNewCmds
**
** Global Inputs/Reads:
**    None
**
** Global Outputs/Writes:
**    TBD
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  GSFC, Colin John
**
** History:  Date Written  2021-11-22
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
void PHASE_3_ReportHousekeeping()
{
    /* TODO:  Add code to update housekeeping data, if needed, here.  */

    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&g_PHASE_3_AppData.HkTlm);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&g_PHASE_3_AppData.HkTlm);
}
    
/*=====================================================================================
** Name: PHASE_3_SendOutData
**
** Purpose: To publish 1-Wakeup cycle output data
**
** Arguments:
**    None
**
** Returns:
**    None
**
** Routines Called:
**    TBD
**
** Called By:
**    PHASE_3_RcvMsg
**
** Global Inputs/Reads:
**    None
**
** Global Outputs/Writes:
**    TBD
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  Colin John
**
** History:  Date Written  2021-11-22
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
void PHASE_3_SendOutData()
{
    /* TODO:  Add code to update output data, if needed, here.  */

    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&g_PHASE_3_AppData.OutData);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&g_PHASE_3_AppData.OutData);
}
    
/*=====================================================================================
** Name: PHASE_3_VerifyCmdLength
**
** Purpose: To verify command length for a particular command message
**
** Arguments:
**    CFE_SB_Msg_t*  MsgPtr      - command message pointer
**    uint16         usExpLength - expected command length
**
** Returns:
**    boolean bResult - result of verification
**
** Routines Called:
**    TBD
**
** Called By:
**    PHASE_3_ProcessNewCmds
**
** Global Inputs/Reads:
**    None
**
** Global Outputs/Writes:
**    TBD
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  Colin John 
**
** History:  Date Written  2021-11-22
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
boolean PHASE_3_VerifyCmdLength(CFE_SB_Msg_t* MsgPtr,
                           uint16 usExpectedLen)
{
    boolean bResult=FALSE;
    uint16  usMsgLen=0;

    if (MsgPtr != NULL)
    {
        usMsgLen = CFE_SB_GetTotalMsgLength(MsgPtr);

        if (usExpectedLen != usMsgLen)
        {
            CFE_SB_MsgId_t MsgId = CFE_SB_GetMsgId(MsgPtr);
            uint16 usCmdCode = CFE_SB_GetCmdCode(MsgPtr);

            CFE_EVS_SendEvent(PHASE_3_MSGLEN_ERR_EID, CFE_EVS_ERROR,
                              "PHASE_3 - Rcvd invalid msgLen: msgId=0x%08X, cmdCode=%d, "
                              "msgLen=%d, expectedLen=%d",
                              MsgId, usCmdCode, usMsgLen, usExpectedLen);
            g_PHASE_3_AppData.HkTlm.usCmdErrCnt++;
        }
    }

    return (bResult);
}
    
/*=====================================================================================
** Name: PHASE_3_AppMain
**
** Purpose: To define PHASE_3 application's entry point and main process loop
**
** Arguments:
**    None
**
** Returns:
**    None
**
** Routines Called:
**    CFE_ES_RegisterApp
**    CFE_ES_RunLoop
**    CFE_ES_PerfLogEntry
**    CFE_ES_PerfLogExit
**    CFE_ES_ExitApp
**    CFE_ES_WaitForStartupSync
**    PHASE_3_InitApp
**    PHASE_3_RcvMsg
**
** Called By:
**    TBD
**
** Global Inputs/Reads:
**    TBD
**
** Global Outputs/Writes:
**    TBD
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  Colin John 
**
** History:  Date Written  2021-11-22
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
void PHASE_3_AppMain()
{
    /* Register the application with Executive Services */
    CFE_ES_RegisterApp();

    /* Start Performance Log entry */
    CFE_ES_PerfLogEntry(PHASE_3_MAIN_TASK_PERF_ID);

    /* Perform application initializations */
    if (PHASE_3_InitApp() != CFE_SUCCESS)
    {
        g_PHASE_3_AppData.uiRunStatus = CFE_ES_APP_ERROR;
    } else {
        /* Do not perform performance monitoring on startup sync */
        CFE_ES_PerfLogExit(PHASE_3_MAIN_TASK_PERF_ID);
        CFE_ES_WaitForStartupSync(PHASE_3_TIMEOUT_MSEC);
        CFE_ES_PerfLogEntry(PHASE_3_MAIN_TASK_PERF_ID);
    }

    /* Application main loop */
    while (CFE_ES_RunLoop(&g_PHASE_3_AppData.uiRunStatus) == TRUE)
    {
        PHASE_3_RcvMsg(CFE_SB_PEND_FOREVER);
    }

    /* Stop Performance Log entry */
    CFE_ES_PerfLogExit(PHASE_3_MAIN_TASK_PERF_ID);

    /* Exit the application */
    CFE_ES_ExitApp(g_PHASE_3_AppData.uiRunStatus);
} 
    
/*=======================================================================================
** End of file phase_3_app.c
**=====================================================================================*/
    