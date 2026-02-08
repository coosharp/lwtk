/**
  ******************************************************************************
  *
  * @file    lw_logger.h
  * @author  
  * @brief   Header file of logger module.
  *
  ******************************************************************************
  **/
  
#ifndef _LW_LOGGER_H
#define _LW_LOGGER_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
#include <stdarg.h>
/*********************
 *      DEFINES
 *********************/
#define LW_LOGGER_ENABLE        (1)
#define LW_LOGGER_COLOR_ENABLE  (1)
#define LW_LOGGER_BUFFER_SIZE   (1024)

#define LW_LOGGER_LEVEL_TRACE   0     /* 最低级别，用于最详细的跟踪信息 */
#define LW_LOGGER_LEVEL_INFO    1     /* 重要状态信息，测试阶段使用 */
#define LW_LOGGER_LEVEL_WARN    2     /* 警告信息，提示潜在问题 */
#define LW_LOGGER_LEVEL_ERROR   3     /* 错误信息，功能异常但可恢复 */
#define LW_LOGGER_LEVEL_FATAL   4     /* 严重错误，系统可能崩溃 */
#define LW_LOGGER_LEVEL_NONE    5     /* 不输出日志 */


#define LW_LOGGER_LEVEL         (LW_LOGGER_LEVEL_TRACE)

#define LW_LOGGER_COLOR_RED     "\033[31m"
#define LW_LOGGER_COLOR_GREEN   "\033[32m"
#define LW_LOGGER_COLOR_YELLOW  "\033[33m"
#define LW_LOGGER_COLOR_BLUE    "\033[34m"
#define LW_LOGGER_COLOR_MAGENTA "\033[35m"
#define LW_LOGGER_COLOR_CYAN    "\033[36m"
#define LW_LOGGER_COLOR_WHITE   "\033[37m"
#define LW_LOGGER_COLOR_RESET   "\033[0m"


#define LW_LOGGER_COLOR_TRACE   LW_LOGGER_COLOR_CYAN
#define LW_LOGGER_COLOR_INFO    LW_LOGGER_COLOR_GREEN
#define LW_LOGGER_COLOR_WARN    LW_LOGGER_COLOR_YELLOW
#define LW_LOGGER_COLOR_ERROR   LW_LOGGER_COLOR_RED
#define LW_LOGGER_COLOR_FATAL   LW_LOGGER_COLOR_MAGENTA
#define LW_LOGGER_COLOR_USER    LW_LOGGER_COLOR_WHITE


/**********************
 *      TYPEDEFS
 **********************/
typedef void (* lw_logger_printf_t)(const char * buf, size_t len);
/**********************
*  GLOBAL PROTOTYPES
 **********************/
void lw_logger_init(lw_logger_printf_t callback);
void lw_logger_deinit(void);
void lw_logger_write(const char * fmt, ...);

/**********************
 *      MACROS
 **********************/
#if LW_LOGGER_ENABLE
    #define LW_LOGGER_OUTPUT(fmt, ...)        lw_logger_write(fmt, ##__VA_ARGS__)
#else
    #define LW_LOGGER_OUTPUT(fmt, ...)        do {} while (0)
#endif


#ifndef LW_LOGGER_TRACE
    #if LW_LOGGER_LEVEL <= LW_LOGGER_LEVEL_TRACE
        #if LW_LOGGER_COLOR_ENABLE
            #define LW_LOGGER_TRACE(fmt, ...)  LW_LOGGER_OUTPUT(LW_LOGGER_COLOR_TRACE "[Trace] [%s:%d] " fmt LW_LOGGER_COLOR_RESET "\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
        #else
            #define LW_LOGGER_TRACE(fmt, ...)  LW_LOGGER_OUTPUT("[Trace] [%s:%d] " fmt"\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
        #endif
    #else
        #define LW_LOGGER_TRACE(fmt, ...)      do {} while (0)
    #endif
#endif

#ifndef LW_LOGGER_INFO
    #if LW_LOGGER_LEVEL <= LW_LOGGER_LEVEL_INFO
        #if LW_LOGGER_COLOR_ENABLE
            #define LW_LOGGER_INFO(fmt, ...)   LW_LOGGER_OUTPUT(LW_LOGGER_COLOR_INFO "[Info ] [%s:%d] " fmt LW_LOGGER_COLOR_RESET "\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
        #else
            #define LW_LOGGER_INFO(fmt, ...)   LW_LOGGER_OUTPUT("[Info ] [%s:%d] " fmt"\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
        #endif
    #else
        #define LW_LOGGER_INFO(fmt, ...)       do {} while (0)
    #endif
#endif

#ifndef LW_LOGGER_WARN
    #if LW_LOGGER_LEVEL <= LW_LOGGER_LEVEL_WARN
        #if LW_LOGGER_COLOR_ENABLE
            #define LW_LOGGER_WARN(fmt, ...)   LW_LOGGER_OUTPUT(LW_LOGGER_COLOR_WARN "[Warn ] [%s:%d] " fmt LW_LOGGER_COLOR_RESET "\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
        #else
            #define LW_LOGGER_WARN(fmt, ...)   LW_LOGGER_OUTPUT("[Warn ] [%s:%d] " fmt"\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
        #endif
    #else
        #define LW_LOGGER_WARN(fmt, ...)       do {} while (0)
    #endif
#endif

#ifndef LW_LOGGER_ERROR
    #if LW_LOGGER_LEVEL <= LW_LOGGER_LEVEL_ERROR
        #if LW_LOGGER_COLOR_ENABLE
            #define LW_LOGGER_ERROR(fmt, ...)   LW_LOGGER_OUTPUT(LW_LOGGER_COLOR_ERROR "[Error] [%s:%d] " fmt LW_LOGGER_COLOR_RESET "\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
        #else
            #define LW_LOGGER_ERROR(fmt, ...)   LW_LOGGER_OUTPUT("[Error] [%s:%d] " fmt"\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
        #endif
    #else
        #define LW_LOGGER_ERROR(fmt, ...)      do {} while (0)
    #endif
#endif

#ifndef LW_LOGGER_FATAL
    #if LW_LOGGER_LEVEL <= LW_LOGGER_LEVEL_FATAL
        #if LW_LOGGER_COLOR_ENABLE
            #define LW_LOGGER_FATAL(fmt, ...)   do { LW_LOGGER_OUTPUT(LW_LOGGER_COLOR_FATAL "[Fatal] [%s:%d] " fmt LW_LOGGER_COLOR_RESET "\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__); while(1); } while(0)
        #else
            #define LW_LOGGER_FATAL(fmt, ...)   do { LW_LOGGER_OUTPUT("[Fatal] [%s:%d] " fmt"\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__); while(1); } while(0)
        #endif
    #else
        #define LW_LOGGER_FATAL(fmt, ...)      do {} while (0)
    #endif
#endif

#ifndef LW_LOGGER_USER
    #if LW_LOGGER_COLOR_ENABLE
        #define LW_LOGGER_USER(fmt, ...)   LW_LOGGER_OUTPUT(LW_LOGGER_COLOR_USER "[User ] [%s:%d] " fmt LW_LOGGER_COLOR_RESET "\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
    #else
        #define LW_LOGGER_USER(fmt, ...)   LW_LOGGER_OUTPUT("[User] [%s:%d] " fmt"\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
    #endif
#endif


#ifndef pr_log
    #define pr_log      LW_LOGGER_OUTPUT
#endif

#ifndef pr_trace
    #define pr_trace    LW_LOGGER_TRACE
#endif

#ifndef pr_info
    #define pr_info     LW_LOGGER_INFO
#endif

#ifndef pr_warn
    #define pr_warn     LW_LOGGER_WARN
#endif

#ifndef pr_error
    #define pr_error    LW_LOGGER_ERROR
#endif

#ifndef pr_fatal
    #define pr_fatal    LW_LOGGER_FATAL
#endif

#ifndef pr_user
    #define pr_user     LW_LOGGER_USER
#endif










#ifdef __cplusplus
}
#endif

#endif /*_LW_LOGGER_H*/


/******************************* (END OF FILE) *********************************/


