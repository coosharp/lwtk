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
struct lw_wdg
{
    struct lw_wdg * next;
    uint32_t timeout_ms;
    uint32_t last_kick_ms;
};
/**********************
 *      TYPEDEFS
 **********************/
 
/**********************
*  GLOBAL PROTOTYPES
 **********************/
void lw_wdg_add(struct lw_wdg * wdg, uint32_t timeout_ms);
void lw_wdg_remove(struct lw_wdg * wdg);
void lw_wdg_reload(struct lw_wdg * wdg);
void lw_wdg_process(void);
/**********************
 *      MACROS
 **********************/




#ifdef __cplusplus
}
#endif

#endif /*_LW_WDG_H*/


/******************************* (END OF FILE) *********************************/


