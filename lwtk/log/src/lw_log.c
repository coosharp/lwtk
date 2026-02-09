/**
 * @file lw_log.c
 *
 */
  
/*********************
 *      INCLUDES
 *********************/
#include "lw_log.h"
/**********************
 *  STATIC VARIABLES
 **********************/
static lw_log_printf_t fnLogCallback = NULL;
static char ucLogBuf[LW_LOG_BUFFER_SIZE];
/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
void lw_log_init(lw_log_printf_t callback)
{
    fnLogCallback = callback;
}

void lw_log_deinit(void)
{
    fnLogCallback = NULL;
}

void lw_log_write(const char * fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    if (fnLogCallback != NULL)
    {
        int len = vsnprintf(ucLogBuf, sizeof(ucLogBuf), fmt, args);
        fnLogCallback(ucLogBuf, len);
    }
    va_end(args);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/



/******************************* (END OF FILE) *********************************/



 







