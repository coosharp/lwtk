/**
  ******************************************************************************
  *
  * @file    lw_console.h
  * @author  
  * @brief   Header file of console module.
  *
  ******************************************************************************
  **/
  
#ifndef _LW_CONSOLE_H
#define _LW_CONSOLE_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
/*********************
 *      DEFINES
 *********************/
#define LW_CONSOLE_CMD_NAME_MAX_LEN    16

typedef int (* lw_console_command_fn_t)(int argc, char * argv[]);

typedef lw_console_command lw_console_command_t;

struct lw_console_command
{
    char name[LW_CONSOLE_CMD_NAME_MAX_LEN];
    lw_console_command_fn_t fn;
    const char * help;
};
/**********************
 *      TYPEDEFS
 **********************/
 
/**********************
*  GLOBAL PROTOTYPES
 **********************/




/**********************
 *      MACROS
 **********************/





#ifdef __cplusplus
}
#endif

#endif /*_LW_CONSOLE_H*/


/******************************* (END OF FILE) *********************************/


