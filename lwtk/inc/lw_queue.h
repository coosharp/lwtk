/**
  ******************************************************************************
  *
  * @file    lw_queue.h
  * @author  
  * @brief   Header file of queue module.
  *
  ******************************************************************************
  **/

#ifndef _LW_QUEUE_H
#define _LW_QUEUE_H


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
#define LW_QUEUE_MEMCPY(dest, src, size) memcpy(dest, src, size)
#define LW_QUEUE_MEMSET(dest, value, size) memset(dest, value, size)

typedef struct lw_queue lw_queue_t;

struct lw_queue
{
    uint8_t * buffer;
    uint16_t item_size;
    uint16_t capacity;
    uint16_t head;
    uint16_t tail;
    uint16_t count;
};
/**********************
 *      TYPEDEFS
 **********************/
 
/**********************
*  GLOBAL PROTOTYPES
 **********************/
static inline bool lw_queue_is_full(lw_queue_t * q)
{
    return (q->count == q->capacity);
}

static inline bool lw_queue_is_empty(lw_queue_t * q)
{
    return (q->count == 0);
}

static inline uint16_t lw_queue_get_count(lw_queue_t * q)
{
    return q->count;
}


/**********************
 *      MACROS
 **********************/





#ifdef __cplusplus
}
#endif

#endif /*_LW_QUEUE_H*/


/******************************* (END OF FILE) *********************************/


