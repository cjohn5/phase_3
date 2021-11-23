/*=======================================================================================
** File Name:  phase_3_iload_utils.c
**
** Title:  Iload Tables' Utilities for PHASE_3 Application
**
** $Author:    Colin John
** $Revision: 1.1 $
** $Date:      2021-11-22
**
** Purpose:  This source file contains definitions of ILoad table-related utility
**           function for PHASE_3 application.
**
** Functions Defined:
**    None
**
** Limitations, Assumptions, External Events, and Notes:
**    1. One source file per CFS table!
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
#include "phase_3_iload_utils.h"

/*
** Local Defines
*/

/*
** Local Structure Declarations
*/

/*
** External Global Variables
*/
extern PHASE_3_AppData_t  g_PHASE_3_AppData;

/*
** Global Variables
*/

/*
** Local Variables
*/

/*
** Function Prototypes
*/

/*
** Function Definitions
*/
    
/*=====================================================================================
** Name: PHASE_3_InitILoadTbl
**
** Purpose: To initialize the PHASE_3's ILoad tables
**
** Arguments:
**    None
**
** Returns:
**    int32 iStatus - Status of initialization
**
** Routines Called:
**    CFE_TBL_Register
**    CFE_TBL_Load
**    CFE_TBL_Manage
**    CFE_TBL_GetAddress
**    CFE_ES_WriteToSysLog
**    PHASE_3_ValidateILoadTbl
**    PHASE_3_ProcessNewILoadTbl
**
** Called By:
**    PHASE_3_InitApp
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
** Programmer(s):  GSFC, Colin John 
**
** History:  Date Written  2021-11-22
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
int32 PHASE_3_InitILoadTbl()
{
    int32  iStatus=0;

    /* Register ILoad table */
    iStatus = CFE_TBL_Register(&g_PHASE_3_AppData.ILoadTblHdl,
                               PHASE_3_ILOAD_TABLENAME,
                               (sizeof(PHASE_3_ILoadTblEntry_t) * PHASE_3_ILOAD_MAX_ENTRIES),
                               CFE_TBL_OPT_DEFAULT,
                               PHASE_3_ValidateILoadTbl);
    if (iStatus != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("PHASE_3 - Failed to register ILoad table (0x%08X)\n", iStatus);
        goto PHASE_3_InitILoadTbl_Exit_Tag;
    }

    /* Load ILoad table file */
    iStatus = CFE_TBL_Load(g_PHASE_3_AppData.ILoadTblHdl,
                           CFE_TBL_SRC_FILE,
                           PHASE_3_ILOAD_FILENAME);
    if (iStatus != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("PHASE_3 - Failed to load ILoad Table (0x%08X)\n", iStatus);
        goto PHASE_3_InitILoadTbl_Exit_Tag;
    }

    /* Manage ILoad table */
    iStatus = CFE_TBL_Manage(g_PHASE_3_AppData.ILoadTblHdl);
    if (iStatus != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("PHASE_3 - Failed to manage ILoad table (0x%08X)\n", iStatus);
        goto PHASE_3_InitILoadTbl_Exit_Tag;
    }

    /* Make sure ILoad table is accessible by getting referencing it */
    iStatus = CFE_TBL_GetAddress((void*)&g_PHASE_3_AppData.ILoadTblPtr,
                                 g_PHASE_3_AppData.ILoadTblHdl);
    if (iStatus != CFE_TBL_INFO_UPDATED)
    {
        CFE_ES_WriteToSysLog("PHASE_3 - Failed to get ILoad table's address (0x%08X)\n", iStatus);
        goto PHASE_3_InitILoadTbl_Exit_Tag;
    }

    /* Validate ILoad table */
    iStatus = PHASE_3_ValidateILoadTbl(g_PHASE_3_AppData.ILoadTblPtr);
    if (iStatus != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("PHASE_3 - Failed to validate ILoad table (0x%08X)\n", iStatus);
        goto PHASE_3_InitILoadTbl_Exit_Tag;
    }

    /* Set new parameter values */
    PHASE_3_ProcessNewILoadTbl();

PHASE_3_InitILoadTbl_Exit_Tag:
    return (iStatus);
}
    
/*=====================================================================================
** Name: phase_3_ValidateILoadTbl
**
** Purpose: To validate the PHASE_3's ILoad tables
**
** Arguments:
**    PHASE_3_ILoadTblEntry_t*  iLoadTblPtr - pointer to the ILoad table
**
** Returns:
**    int32 iStatus - Status of table updates
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
** Programmer(s):  Colin John 
**
** History:  Date Written  2021-11-22
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
int32 PHASE_3_ValidateILoadTbl(PHASE_3_ILoadTblEntry_t* iLoadTblPtr)
{
    int32  iStatus=0;

    if (iLoadTblPtr == NULL)
    {
        iStatus = -1;
        goto PHASE_3_ValidateILoadTbl_Exit_Tag;
    }

    /* TODO:  Add code to validate new data values here.
    **
    ** Examples:
    **    if (iLoadTblPtr->sParam <= 16)
    **    {
    **        CFE_ES_WriteToSysLog("PHASE_3 - Invalid value for ILoad parameter sParam (%d)\n",
    **                             iLoadTblPtr->sParam);
    */

PHASE_3_ValidateILoadTbl_Exit_Tag:
    return (iStatus);
}
    
/*=====================================================================================
** Name: PHASE_3_ProcessNewILoadTbl
**
** Purpose: To process PHASE_3's new ILoad tables and set ILoad parameters with new values
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
** Programmer(s):  Colin John 
**
** History:  Date Written  2021-11-22
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
void PHASE_3_ProcessNewILoadTbl()
{
    /* TODO:  Add code to set new ILoad parameters with new values here.
    **
    ** Examples:
    **
    **    g_PHASE_3_AppData.latest_sParam = g_PHASE_3_AppData.ILoadTblPtr->sParam;
    **    g_PHASE_3_AppData.latest_fParam = g_PHASE_3.AppData.ILoadTblPtr->fParam;
    */
}
    
/*=======================================================================================
** End of file phase_3_iload_utils.c
**=====================================================================================*/
    