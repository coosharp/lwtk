/**
 * @file lw_log.h
 *
 */
  
#ifndef _LW_LOG_H
#define _LW_LOG_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
/*********************
 *      DEFINES
 *********************/
#define LW_LOG_ENABLE        (1)
#define LW_LOG_COLOR_ENABLE  (1)
#define LW_LOG_BUFFER_SIZE   (128)

#define LW_LOG_LEVEL_TRACE   0     /* 最低级别，用于最详细的跟踪信息 */
#define LW_LOG_LEVEL_INFO    1     /* 重要状态信息，测试阶段使用 */
#define LW_LOG_LEVEL_WARN    2     /* 警告信息，提示潜在问题 */
#define LW_LOG_LEVEL_ERROR   3     /* 错误信息，功能异常但可恢复 */
#define LW_LOG_LEVEL_FATAL   4     /* 严重错误，系统可能崩溃 */
#define LW_LOG_LEVEL_NONE    5     /* 不输出日志 */


#define LW_LOG_LEVEL         (LW_LOG_LEVEL_TRACE)

#define LW_LOG_COLOR_RED     "\033[31m"
#define LW_LOG_COLOR_GREEN   "\033[32m"
#define LW_LOG_COLOR_YELLOW  "\033[33m"
#define LW_LOG_COLOR_BLUE    "\033[34m"
#define LW_LOG_COLOR_MAGENTA "\033[35m"
#define LW_LOG_COLOR_CYAN    "\033[36m"
#define LW_LOG_COLOR_WHITE   "\033[37m"
#define LW_LOG_COLOR_RESET   "\033[0m"


#define LW_LOG_COLOR_TRACE   LW_LOG_COLOR_CYAN
#define LW_LOG_COLOR_INFO    LW_LOG_COLOR_GREEN
#define LW_LOG_COLOR_WARN    LW_LOG_COLOR_YELLOW
#define LW_LOG_COLOR_ERROR   LW_LOG_COLOR_RED
#define LW_LOG_COLOR_FATAL   LW_LOG_COLOR_MAGENTA
#define LW_LOG_COLOR_USER    LW_LOG_COLOR_WHITE


/**********************
 *      TYPEDEFS
 **********************/
typedef void (* lw_log_printf_t)(const char * buf, size_t len);
/**********************
*  GLOBAL PROTOTYPES
 **********************/
void lw_log_init(lw_log_printf_t callback);
void lw_log_deinit(void);
void lw_log_write(const char * fmt, ...);

/**********************
 *      MACROS
 **********************/
#if LW_LOG_ENABLE
    #define LW_LOG_OUTPUT(fmt, ...)        lw_log_write(fmt, ##__VA_ARGS__)
#else
    #define LW_LOG_OUTPUT(fmt, ...)        do {} while (0)
#endif


#ifndef LW_LOG_TRACE
    #if LW_LOG_LEVEL <= LW_LOG_LEVEL_TRACE
        #if LW_LOG_COLOR_ENABLE
            #define LW_LOG_TRACE(fmt, ...)  LW_LOG_OUTPUT(LW_LOG_COLOR_TRACE "[Trace] [%s:%d] " fmt LW_LOG_COLOR_RESET "\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
        #else
            #define LW_LOG_TRACE(fmt, ...)  LW_LOG_OUTPUT("[Trace] [%s:%d] " fmt"\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
        #endif
    #else
        #define LW_LOG_TRACE(fmt, ...)      do {} while (0)
    #endif
#endif

#ifndef LW_LOG_INFO
    #if LW_LOG_LEVEL <= LW_LOG_LEVEL_INFO
        #if LW_LOG_COLOR_ENABLE
            #define LW_LOG_INFO(fmt, ...)   LW_LOG_OUTPUT(LW_LOG_COLOR_INFO "[Info ] [%s:%d] " fmt LW_LOG_COLOR_RESET "\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
        #else
            #define LW_LOG_INFO(fmt, ...)   LW_LOG_OUTPUT("[Info ] [%s:%d] " fmt"\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
        #endif
    #else
        #define LW_LOG_INFO(fmt, ...)       do {} while (0)
    #endif
#endif

#ifndef LW_LOG_WARN
    #if LW_LOG_LEVEL <= LW_LOG_LEVEL_WARN
        #if LW_LOG_COLOR_ENABLE
            #define LW_LOG_WARN(fmt, ...)   LW_LOG_OUTPUT(LW_LOG_COLOR_WARN "[Warn ] [%s:%d] " fmt LW_LOG_COLOR_RESET "\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
        #else
            #define LW_LOG_WARN(fmt, ...)   LW_LOG_OUTPUT("[Warn ] [%s:%d] " fmt"\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
        #endif
    #else
        #define LW_LOG_WARN(fmt, ...)       do {} while (0)
    #endif
#endif

#ifndef LW_LOG_ERROR
    #if LW_LOG_LEVEL <= LW_LOG_LEVEL_ERROR
        #if LW_LOG_COLOR_ENABLE
            #define LW_LOG_ERROR(fmt, ...)   LW_LOG_OUTPUT(LW_LOG_COLOR_ERROR "[Error] [%s:%d] " fmt LW_LOG_COLOR_RESET "\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
        #else
            #define LW_LOG_ERROR(fmt, ...)   LW_LOG_OUTPUT("[Error] [%s:%d] " fmt"\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
        #endif
    #else
        #define LW_LOG_ERROR(fmt, ...)      do {} while (0)
    #endif
#endif

#ifndef LW_LOG_FATAL
    #if LW_LOG_LEVEL <= LW_LOG_LEVEL_FATAL
        #if LW_LOG_COLOR_ENABLE
            #define LW_LOG_FATAL(fmt, ...)   do { LW_LOG_OUTPUT(LW_LOG_COLOR_FATAL "[Fatal] [%s:%d] " fmt LW_LOG_COLOR_RESET "\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__); while(1); } while(0)
        #else
            #define LW_LOG_FATAL(fmt, ...)   do { LW_LOG_OUTPUT("[Fatal] [%s:%d] " fmt"\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__); while(1); } while(0)
        #endif
    #else
        #define LW_LOG_FATAL(fmt, ...)      do {} while (0)
    #endif
#endif

#ifndef LW_LOG_USER
    #if LW_LOG_ENABLE
        #if LW_LOG_COLOR_ENABLE
            #define LW_LOG_USER(fmt, ...)   LW_LOG_OUTPUT(LW_LOG_COLOR_USER "[User ] [%s:%d] " fmt LW_LOG_COLOR_RESET "\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
        #else
            #define LW_LOG_USER(fmt, ...)   LW_LOG_OUTPUT("[User] [%s:%d] " fmt"\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
        #endif
    #else
        #define LW_LOG_USER(fmt, ...)       do {} while (0)
    #endif
#endif


#ifndef pr_log
    #define pr_log      LW_LOG_OUTPUT
#endif

#ifndef pr_trace
    #define pr_trace    LW_LOG_TRACE
#endif

#ifndef pr_info
    #define pr_info     LW_LOG_INFO
#endif

#ifndef pr_warn
    #define pr_warn     LW_LOG_WARN
#endif

#ifndef pr_error
    #define pr_error    LW_LOG_ERROR
#endif

#ifndef pr_fatal
    #define pr_fatal    LW_LOG_FATAL
#endif

#ifndef pr_user
    #define pr_user     LW_LOG_USER
#endif



#ifdef __cplusplus
}
#endif

#endif /*_LW_LOG_H*/


/******************************* (END OF FILE) *********************************/


