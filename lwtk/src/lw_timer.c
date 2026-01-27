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
static lw_timer_t * alloc_timer(void);
static void free_timer(lw_timer_t * timer);
/**********************
 *  STATIC VARIABLES
 **********************/
static lw_timer_t * gs_mempool = NULL;
static lw_timer_t * free_list = NULL;     
static lw_timer_t * used_list = NULL; 
/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
void lw_timer_init(void)
{

}

lw_timer_t * lw_timer_create()
{

}

void lw_timer_delete(lw_timer_t * timer)
{

}

void lw_timer_pause(lw_timer_t * timer)
{

}

void lw_timer_resume(lw_timer_t * timer)
{

}

void lw_timer_ready(lw_timer_t * timer)
{

}

void lw_timer_reset(lw_timer_t * timer)
{

}

void lw_timer_set_repeat_count(lw_timer_t * timer, int32_t repeat_count)
{

}

void lw_timer_set_auto_delete(lw_timer_t * timer, bool auto_delete)
{

}

void lw_timer_set_period(lw_timer_t * timer, uint32_t period)
{

}

void lw_timer_set_callback(lw_timer_t * timer, lw_timer_cb_t timer_cb, void * user_data)
{

}

void lw_timer_set_user_data(lw_timer_t * timer,  void * user_data)
{

}

void lw_timer_increase_tick(uint32_t tick_period)
{

} 

void lw_timer_handler(void)
{

}
/**********************
 *   STATIC FUNCTIONS
 **********************/
static lw_timer_t * alloc_timer(void)
{

}

static void free_timer(lw_timer_t * timer)
{

}



/******************************* (END OF FILE) *********************************/



 







