/**
  ******************************************************************************
  *
  * @file    lw_logger.c
  * @author  
  * @brief   
  *
  ******************************************************************************
  * @attention
  *
  * 
  *
  ******************************************************************************
  **/
  
  
/*********************
 *      INCLUDES
 *********************/
#include "lw_logger.h"
/**********************
 *      MACROS
 **********************/

/*********************
 *      DEFINES
 *********************/

/**********************
 *   GLOBAL VARIABLES
 **********************/ 

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/
static lw_logger_printf_t logger_callback = NULL;
static char logger_buf[LW_LOGGER_BUFFER_SIZE];
/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
void lw_logger_init(lw_logger_printf_t callback)
{
    logger_callback = callback;
}

void lw_logger_deinit(void)
{
    logger_callback = NULL;
}

void lw_logger_write(const char * fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    if (logger_callback != NULL)
    {
        int len = vsnprintf(logger_buf, sizeof(logger_buf), fmt, args);
        logger_callback(logger_buf, len);
    }
    va_end(args);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/



/******************************* (END OF FILE) *********************************/



 







