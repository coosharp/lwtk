/**
  ******************************************************************************
  *
  * @file    lw_timer.c
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
#include "lw_timer.h"
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
static uint32_t get_timer_remaining_time(lw_timer_t * timer, uint32_t now_tick);
static lw_timer_t * alloc_timer(void);
static void free_timer(lw_timer_t * timer);
/**********************
 *  STATIC VARIABLES
 **********************/
static lw_timer_t * gs_mempool = NULL;
static lw_timer_t * free_list = NULL;     
static lw_timer_t * used_list = NULL; 

static uint32_t gsul_timer_ticks = 0;
/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
void lw_timer_init(lw_timer_t * timer_buf, uint32_t buf_size)
{
    gs_mempool = timer_buf;
    uint32_t timer_count = buf_size / sizeof(lw_timer_t);

    LW_TIMER_MEMSET(gs_mempool, 0, buf_size);

    free_list = NULL;
    used_list = NULL;

    for(uint32_t i = 0; i < timer_count; i++){
        gs_mempool[i].next = free_list;
        free_list = &gs_mempool[i];
    }
}

lw_timer_t * lw_timer_create(lw_timer_cb_t timer_cb, uint32_t period, void * user_data)
{
    lw_timer_t * timer = alloc_timer();
    if(timer == NULL) {
        return NULL;
    }

    timer->timer_cb = timer_cb;
    timer->period = period;
    timer->repeat_count = LW_TIMER_REPEAT_INFINITE;
    timer->user_data = user_data;
    timer->last_run = 0;
    timer->paused = 0;
    timer->auto_delete = 0;

    return timer;
}

void lw_timer_delete(lw_timer_t * timer)
{
    if(timer)
        free_timer(timer);
}

void lw_timer_increase_tick(uint32_t tick_period)
{
    gsul_timer_ticks += tick_period;
} 

uint32_t lw_timer_handler(void)
{
    uint32_t now_tick = gsul_timer_ticks;
    lw_timer_t * timer_node = used_list;

    while (timer_node != NULL) {
        if (!timer_node->paused && (now_tick - timer_node->last_run) >= timer_node->period) {
            
            timer_node->last_run = now_tick;
            
            /* Timer period elapsed, call the timer callback */
            if (timer_node->timer_cb) {
                timer_node->timer_cb(timer_node);
            }

            /* Handle repeat count */
            if (timer_node->repeat_count > 0) {
                timer_node->repeat_count--;
                if (timer_node->repeat_count == 0) {
                    lw_timer_t * to_delete = timer_node;
                    timer_node = timer_node->next; /* Move to next before deletion */
                    if (to_delete->auto_delete) {
                        free_timer(to_delete);
                    }
                    continue; /* Skip the increment of timer_node */
                }
            }
        }
        timer_node = timer_node->next;
    }

    uint32_t time_until_next = LW_TIMER_NO_TIMER_READY;
    lw_timer_t * timer_node = used_list;
    while(timer_node) {
        if(!timer_node->paused) {
            uint32_t remaining_time = get_timer_remaining_time(timer_node, now_tick);
            if(remaining_time < time_until_next)
                time_until_next = remaining_time;
        }
        timer_node = timer_node->next;
    }

    return time_until_next;
}

void lw_timer_pause(lw_timer_t * timer)
{
    if(timer)
        timer->paused = 1;
}

void lw_timer_resume(lw_timer_t * timer)
{
    if(timer)
        timer->paused = 0;
}

void lw_timer_ready(lw_timer_t * timer)
{
    if(timer)
        timer->last_run = gsul_timer_ticks - timer->period - 1;
}

void lw_timer_reset(lw_timer_t * timer)
{   
    if(timer)
        timer->last_run = gsul_timer_ticks;
}

void lw_timer_set_repeat_count(lw_timer_t * timer, int32_t repeat_count)
{
    if(timer)
        timer->repeat_count = repeat_count;
}

void lw_timer_set_auto_delete(lw_timer_t * timer, bool auto_delete)
{
    if(timer)
        timer->auto_delete = auto_delete ? 1 : 0;
}

void lw_timer_set_period(lw_timer_t * timer, uint32_t period)
{
    if(timer)
        timer->period = period;
}

void lw_timer_set_callback(lw_timer_t * timer, lw_timer_cb_t timer_cb)
{
    if(timer)
        timer->timer_cb = timer_cb;
}

void lw_timer_set_user_data(lw_timer_t * timer,  void * user_data)
{
    if(timer)
        timer->user_data = user_data;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
static uint32_t get_timer_remaining_time(lw_timer_t * timer, uint32_t now_tick)
{
    if(timer->paused) {
        return LW_TIMER_NO_TIMER_READY;
    }

    uint32_t elapsed = now_tick - timer->last_run;
    if(elapsed >= timer->period) {
        return 0;
    } 
    else {
        return timer->period - elapsed;
    }
}

static lw_timer_t * alloc_timer(void)
{

}

static void free_timer(lw_timer_t * timer)
{

}



/******************************* (END OF FILE) *********************************/



 







