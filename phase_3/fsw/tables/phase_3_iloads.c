/*=======================================================================================
** File Name:  phase_3_iloads.c
**
** Title:  Default Iload Table for PHASE_3 Application
**
** $Author:    Colin John
** $Revision: 1.1 $
** $Date:      2021-11-22
**
** Purpose:  This source file contains definition of table content for PHASE_3 application's 
**           default ILoad table.
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
#include "cfe_tbl_filedef.h"
#include "phase_3_tbldefs.h"

/*
** Local Defines
*/

/*
** Local Structure Declarations
*/
static CFE_TBL_FileDef_t CFE_TBL_FileDef =
{
    /* Content format: ObjName[64], TblName[38], Desc[32], TgtFileName[20], ObjSize 
    **    ObjName - variable name of ILoad table, e.g., PHASE_3_ILoadDefTbl[]
    **    TblName - app's table name, e.g., PHASE_3.ILOAD_TBL, where PHASE_3 is the same app name
    **              used in cfe_es_startup.scr, and PHASE_3_defILoadTbl is the same table
    **              name passed in to CFE_TBL_Register()
    **    Desc - description of table in string format
    **    TgtFileName[20] - table file name, compiled as .tbl file extension
    **    ObjSize - size of the entire table
    */

    "PHASE_3_ILoadDefTbl", "PHASE_3.ILOAD_TBL", "PHASE_3 default ILoad table",
    "phase_3_iloads.tbl", (sizeof(PHASE_3_ILoadTblEntry_t) * PHASE_3_ILOAD_MAX_ENTRIES)
};

/*
** External Global Variables
*/

/*
** Global Variables
*/

/* Default PHASE_3 iLoad table data */
PHASE_3_ILoadTblEntry_t PHASE_3_ILoadDefTbl[PHASE_3_ILOAD_MAX_ENTRIES] =
{
    /* Entry 1 */
    {
        .iParam = 123

        /* TODO:  Add default values for ILoad parameters here.
        **
        ** Examples: (See example of type declarations in phase_3_tbldefs.h)
        **    .cParam   = 7,
        **    .cParams  = "Init Str Value",
        **    .ucParam  = 'A',
        **    .ucParams = "/dev/ttyUSB",
        **
        **    .sParam   = -16,
        **    .sParams  = {-3, -2, -1, 0, 1, 2, 3, 4},
        **    .usParam  = 16,
        **    .usParams = {1, 2, 3, 4, 5, 6, 7, 8},
        **
        **    .iParam   = -32,
        **    .iParams  = {-123, -234, 0, 123, 234},
        **    .uiParam  = -32,
        **    .uiParams = {123, 234, 345, 456, 678},
        **
        **    .fParam  = 32.1234,
        **    .fParams = {-12.34, 0.0, 12.34},
        **
        **    .dParam = 123.456789,
        **    .dParams = {-123.456789, 0.0, 123.456789}
        */
    }
};

/*
** Local Variables
*/

/*
** Function Prototypes
*/

/*
** Function Definitions
*/

/*=======================================================================================
** End of file phase_3_iloads.c
**=====================================================================================*/
    