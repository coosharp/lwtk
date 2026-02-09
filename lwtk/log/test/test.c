#include <stdio.h>
#include "lw_log.h"



int main(void)
{
    lw_log_init((lw_log_printf_t)printf);
    LW_LOG_TRACE("Trace message");
    LW_LOG_INFO("Info message");
    LW_LOG_WARN("Warn message");
    LW_LOG_ERROR("Error message");
    LW_LOG_FATAL("Fatal message");
    LW_LOG_USER("User message");


    return 0;
}