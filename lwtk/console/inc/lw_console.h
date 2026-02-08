/**
 * @file lw_console.h
 *
 */
  
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
 *      MACROS
 *********************/
#define LW_CONSOLE_RX_BUF_SIZE         1024

#define LW_CONSOLE_PROMPT              ">> "

#define LW_CONSOLE_CTRL_A              0x01
#define LW_CONSOLE_CTRL_Z              0x1A
#define LW_CONSOLE_CTRL_C              0x03
#define LW_CONSOLE_CTRL_U              0x15
#define LW_CONSOLE_CTRL_W              0x17
#define LW_CONSOLE_CTRL_N              0x0E
#define LW_CONSOLE_CTRL_Q              0x11

#define LW_CONSOLE_CR                  0x0D
#define LW_CONSOLE_LF                  0x0A
#define LW_CONSOLE_BACKSPACE           0x08
#define LW_CONSOLE_TAB                 0x09
#define LW_CONSOLE_SPACE               0x20
#define LW_CONSOLE_DEL                 0x7F
#define LW_CONSOLE_ESC                 0x1B
/*********************
 *    DECLARATIONS
 *********************/

typedef int (* lw_console_command_fn_t)(int argc, char * argv[]);

typedef struct lw_console_command lw_console_command_t;

struct lw_console_command
{
    const char * name;
    const char * desc;
    lw_console_command_fn_t fn;
};

/**********************
*  GLOBAL PROTOTYPES
 **********************/
void lw_console_loop(void);





#ifdef __cplusplus
}
#endif

#endif /*_LW_CONSOLE_H*/


/******************************* (END OF FILE) *********************************/


