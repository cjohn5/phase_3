/*=======================================================================================
** File Name:  phase_3_iload_utils.h
**
** Title:  ILoad Tables' Utility Header File for PHASE_3 Application
**
** $Author:    Colin John
** $Revision: 1.1 $
** $Date:      2021-11-22
**
** Purpose:  To define PHASE_3's ILoad table-related utility functions
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2021-11-22 | Colin John | Build #: Code Started
**
**=====================================================================================*/
    
#ifndef _PHASE_3_ILOAD_UTILS_H_
#define _PHASE_3_ILOAD_UTILS_H_

/*
** Pragmas
*/

/*
** Include Files
*/
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

/*
** Local Variables
*/

/*
** Local Function Prototypes
*/
int32  PHASE_3_InitILoadTbl(void);
int32  PHASE_3_ValidateILoadTbl(PHASE_3_ILoadTblEntry_t*);
void   PHASE_3_ProcessNewILoadTbl(void);

#endif /* _PHASE_3_ILOAD_UTILS_H_ */

/*=======================================================================================
** End of file phase_3_iload_utils.h
**=====================================================================================*/
    