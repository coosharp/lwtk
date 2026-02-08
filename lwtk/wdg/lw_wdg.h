/**
  ******************************************************************************
  *
  * @file    lw_wdg.h
  * @author  
  * @brief   Header file of wdg module.
  *
  ******************************************************************************
  **/
  
#ifndef _LW_WDG_H
#define _LW_WDG_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
/*********************
 *      DEFINES
 *********************/
#define LW_WDG_MEMCPY(dst, src, size) memcpy(dst, src, size)
#define LW_WDG_MEMSET(buf, value, size) memset(buf, value, size)
#define LW_WDG_MEMMOVE(dst, src, size) memmove(dst, src, size)

typedef struct lw_wdg lw_wdg_t;

struct lw_wdg
{
    struct lw_wdg * next;
    uint32_t timeout_ms;
    uint32_t last_kick_ms;
    char name[16];
};
/**********************
 *      TYPEDEFS
 **********************/
 
/**********************
*  GLOBAL PROTOTYPES
 **********************/
void        lw_wdg_increase_tick(uint32_t tick_period);
bool        lw_wdg_add          (lw_wdg_t * wdg, uint32_t timeout_ms, const char * name);
bool        lw_wdg_remove       (lw_wdg_t * wdg);
void        lw_wdg_reload       (lw_wdg_t * wdg);
lw_wdg_t *  lw_wdg_handler      (void);
/**********************
 *      MACROS
 **********************/




#ifdef __cplusplus
}
#endif

#endif /*_LW_WDG_H*/


/******************************* (END OF FILE) *********************************/


