/*=======================================================================================
** File Name:  phase_3_msg.h
**
** Title:  Message Definition Header File for PHASE_3 Application
**
** $Author:    Colin John
** $Revision: 1.1 $
** $Date:      2021-11-22
**
** Purpose:  To define PHASE_3's command and telemetry message defintions 
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2021-11-22 | Colin John | Build #: Code Started
**
**=====================================================================================*/
    
#ifndef _PHASE_3_MSG_H_
#define _PHASE_3_MSG_H_

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
** PHASE_3 command codes
*/
#define PHASE_3_NOOP_CC                 0
#define PHASE_3_RESET_CC                1

/*
** Local Structure Declarations
*/
typedef struct
{
    uint8              TlmHeader[CFE_SB_TLM_HDR_SIZE];
    uint8              usCmdCnt;
    uint8              usCmdErrCnt;

    /* TODO:  Add declarations for additional housekeeping data here */

} PHASE_3_HkTlm_t;


#endif /* _PHASE_3_MSG_H_ */

/*=======================================================================================
** End of file phase_3_msg.h
**=====================================================================================*/
    