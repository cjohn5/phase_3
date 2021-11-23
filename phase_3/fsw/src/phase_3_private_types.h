/*=======================================================================================
** File Name:  phase_3_private_types.h
**
** Title:  Type Header File for PHASE_3 Application
**
** $Author:    Colin John
** $Revision: 1.1 $
** $Date:      2021-11-22
**
** Purpose:  This header file contains declarations and definitions of all PHASE_3's private
**           data structures and data types.
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2021-11-22 | Colin John | Build #: Code Started
**
**=====================================================================================*/
    
#ifndef _PHASE_3_PRIVATE_TYPES_H_
#define _PHASE_3_PRIVATE_TYPES_H_

/*
** Pragmas
*/

/*
** Include Files
*/
#include "cfe.h"

/*
** Local Defines
*/

/*
** Local Structure Declarations
*/

typedef struct
{
    uint8  ucCmdHeader[CFE_SB_CMD_HDR_SIZE];
} PHASE_3_NoArgCmd_t;


typedef struct
{
    uint32  counter;

    /* TODO:  Add input data to this application here, such as raw data read from I/O
    **        devices or data subscribed from other apps' output data.
    */

} PHASE_3_InData_t;

typedef struct
{
    uint8   ucTlmHeader[CFE_SB_TLM_HDR_SIZE];
    uint32  uiCounter;
} PHASE_3_OutData_t;

/* TODO:  Add more private structure definitions here, if necessary. */

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

#endif /* _PHASE_3_PRIVATE_TYPES_H_ */

/*=======================================================================================
** End of file phase_3_private_types.h
**=====================================================================================*/
    