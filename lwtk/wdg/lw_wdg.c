/**
  ******************************************************************************
  *
  * @file    lw_wdg.c
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
#include "lw_wdg.h"
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
static lw_wdg_t * volatile wdg_tail = NULL;

static uint32_t gsul_wdg_ticks = 0;
/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 

void lw_wdg_increase_tick(uint32_t tick_period)
{
    gsul_wdg_ticks += tick_period;
}

bool lw_wdg_add(lw_wdg_t * wdg, uint32_t timeout_ms, const char * name)
{
    if(timeout_ms == 0) 
        return false;

    uint32_t now_tick = gsul_wdg_ticks;

    /* Check if already on a list -> we don't want that */
    lw_wdg_t* wdg_node = wdg_tail;
    while (wdg_node != NULL) {
        if (wdg_node == wdg) {
            return false;  
        }
        wdg_node = wdg_node->next;
    }

    wdg->timeout = timeout_ms;
    wdg->last_reload_time = now_tick;
    if(name) {
        LW_WDG_MEMSET(wdg->name, 0, sizeof(wdg->name));
        LW_WDG_MEMCPY(wdg->name, name, sizeof(wdg->name) - 1);
    } else {
        LW_WDG_MEMSET(wdg->name, 0, sizeof(wdg->name));
    }

    /* Add to beginning of a list */
    wdg->next = wdg_tail;
    wdg_tail = wdg;

    return true;
}

bool lw_wdg_remove(lw_wdg_t * wdg)
{
    lw_wdg_t ** wdg_node = &wdg_tail;

    while (*wdg_node != NULL) {
        if (*wdg_node == wdg) {
            *wdg_node = (*wdg_node)->next;
            return true;
        }
        wdg_node = &(*wdg_node)->next;
    }
    return false;
}

void lw_wdg_reload(lw_wdg_t * wdg)
{
    uint32_t now_tick = gsul_wdg_ticks;
    wdg->last_reload_time = now_tick;
}

lw_wdg_t * lw_wdg_handler(void)
{
    uint32_t now_tick = gsul_wdg_ticks;
    lw_wdg_t * wdg_node = wdg_tail;

    while (wdg_node != NULL) {
        if ((now_tick - wdg_node->last_reload_time) >= wdg_node->timeout) {
            /* Watchdog timeout occurred */
            return wdg_node; /* Return the expired watchdog */
        }
        wdg_node = wdg_node->next;
    }
    return NULL; /* No watchdogs have timed out */
}
/**********************
 *   STATIC FUNCTIONS
 **********************/




/******************************* (END OF FILE) *********************************/



 







