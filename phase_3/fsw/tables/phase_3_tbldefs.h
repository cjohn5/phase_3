/*=======================================================================================
** File Name:  phase_3_tbldefs.h
**
** Title:  Header File for PHASE_3 Application's tables
**
** $Author:    Colin John
** $Revision: 1.1 $
** $Date:      2021-11-22
**
** Purpose:  This header file contains declarations and definitions of data structures
**           used in PHASE_3's tables.
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2021-11-22 | Colin John | Build #: Code Started
**
**=====================================================================================*/
    
#ifndef _PHASE_3_TBLDEFS_H_
#define _PHASE_3_TBLDEFS_H_

/*
** Pragmas
*/

/*
** Include Files
*/
#include "common_types.h"
#include "phase_3_mission_cfg.h"

/*
** Local Defines
*/
#define PHASE_3_ILOAD_MAX_ENTRIES  1
#define PHASE_3_ILOAD_FILENAME     "/cf/apps/phase_3_iloads.tbl"
#define PHASE_3_ILOAD_TABLENAME    "ILOAD_TBL"


/*
** Local Structure Declarations
*/ 
/* Definition for Iload table entry */
typedef struct
{
    int32  iParam;

    /* TODO:  Add type declaration for ILoad parameters here.
    **
    ** Examples:
    **    int8/char            cParam;
    **    int8/char            cParams[16];
    **    uint8/unsigned char  ucParam;
    **    uint8/unsigned char  ucParams[16];
    **
    **    int16   sParam;
    **    int16   sParams[8];
    **    uint16  usParam;
    **    uint16  usParams[8];
    **
    **    int32   iParam;
    **    int32   iParams[5];
    **    uint32  uiParam;
    **    uint32  uiParams[5];
    **
    **    float  fParam;
    **    float  fParams[3];
    **
    **    double  dParam;
    **    double  dParams[3];
    */
} PHASE_3_ILoadTblEntry_t;
    
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

#endif /* _PHASE_3_TBLDEFS_H_ */

/*=======================================================================================
** End of file phase_3_tbldefs.h
**=====================================================================================*/
    