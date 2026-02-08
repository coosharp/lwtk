/**
  ******************************************************************************
  *
  * @file    lw_timer.h
  * @author  
  * @brief   Header file of timer module.
  *
  ******************************************************************************
  **/
  
#ifndef _LW_TIMER_H
#define _LW_TIMER_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
/*********************
 *      DEFINES
 *********************/
#define LW_TIMER_REPEAT_INFINITE     (-1)
#define LW_TIMER_NO_TIMER_READY      0xFFFFFFFF

#define LW_TIMER_MEMCPY(dst, src, size) memcpy(dst, src, size)
#define LW_TIMER_MEMSET(buf, value, size) memset(buf, value, size)
#define LW_TIMER_MEMMOVE(dst, src, size) memmove(dst, src, size)

typedef struct lw_timer lw_timer_t;
typedef void (* lw_timer_cb_t)(lw_timer_t * timer);

struct lw_timer
{
    lw_timer_t * next;
    lw_timer_t * prev;
    uint32_t period;           /**< How often the timer should run */
    uint32_t last_run;         /**< Last time the timer ran */
    lw_timer_cb_t timer_cb;    /**< Timer function */
    void * user_data;          /**< Custom user data */
    int32_t repeat_count;      /**< 1: One time;  -1 : infinity;  n>0: residual times */
    uint32_t paused : 1;
    uint32_t auto_delete : 1;
};
/**********************
 *      TYPEDEFS
 **********************/
 
/**********************
*  GLOBAL PROTOTYPES
 **********************/

static inline void * lw_timer_get_user_data(lw_timer_t * timer)
{
    return timer->user_data;
}

static inline bool lw_timer_is_paused(lw_timer_t * timer)
{
    return timer->paused != 0;
}

static inline uint32_t lw_timer_get_period(lw_timer_t * timer)
{
    return timer->period;
}

void         lw_timer_init            (lw_timer_t * timer_buf, uint32_t buf_size);
lw_timer_t * lw_timer_create          (lw_timer_cb_t timer_cb, uint32_t period, void * user_data);
void         lw_timer_delete          (lw_timer_t * timer);
void         lw_timer_increase_tick   (uint32_t tick_period);
uint32_t     lw_timer_handler         (void);
void         lw_timer_pause           (lw_timer_t * timer);
void         lw_timer_resume          (lw_timer_t * timer);
void         lw_timer_ready           (lw_timer_t * timer);
void         lw_timer_reset           (lw_timer_t * timer);
void         lw_timer_set_repeat_count(lw_timer_t * timer, int32_t repeat_count);
void         lw_timer_set_auto_delete (lw_timer_t * timer, bool auto_delete);
void         lw_timer_set_period      (lw_timer_t * timer, uint32_t period);
void         lw_timer_set_callback    (lw_timer_t * timer, lw_timer_cb_t timer_cb);
void         lw_timer_set_user_data   (lw_timer_t * timer,  void * user_data);

/**********************
 *      MACROS
 **********************/




#ifdef __cplusplus
}
#endif

#endif /*_LW_TIMER_H*/


/******************************* (END OF FILE) *********************************/


