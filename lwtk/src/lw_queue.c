/**
  ******************************************************************************
  *
  * @file    lw_queue.c
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
#include "lw_queue.h"
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

/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
void lw_queue_init(lw_queue_t * q, uint8_t * buffer, uint16_t item_size, uint16_t capacity)
{
    q->buffer = buffer;
    q->item_size = item_size;
    q->capacity = capacity;
    q->head = 0;
    q->tail = 0;
    q->count = 0;
}

bool lw_queue_send_front(lw_queue_t * q, const void * item)
{
    if(q->count == q->capacity) {
        return false; 
    }
    q->head = (q->head == 0) ? (q->capacity - 1) : (q->head - 1);
    LW_QUEUE_MEMCPY(&q->buffer[q->head * q->item_size], item, q->item_size);
    q->count++;
    return true;
}

bool lw_queue_send_back(lw_queue_t * q, const void * item)
{
    if(q->count == q->capacity) {
        return false; 
    }
    LW_QUEUE_MEMCPY(&q->buffer[q->tail * q->item_size], item, q->item_size);
    q->tail = (q->tail + 1) % q->capacity;
    q->count++;
    return true;
}

bool lw_queue_receive_front(lw_queue_t * q,  void * item)
{
    if(q->count == 0) {
        return false; 
    }
    LW_QUEUE_MEMCPY(item, &q->buffer[q->head * q->item_size], q->item_size);
    q->head = (q->head + 1) % q->capacity;
    q->count--;
    return true;
}

bool lw_queue_receive_back(lw_queue_t * q,  void * item)
{
    if(q->count == 0) {
        return false; 
    }
    q->tail = (q->tail == 0) ? (q->capacity - 1) : (q->tail - 1);
    LW_QUEUE_MEMCPY(item, &q->buffer[q->tail * q->item_size], q->item_size);
    q->count--;
    return true;
}

void lw_queue_reset(lw_queue_t * q)
{
    q->head = 0;
    q->tail = 0;
    q->count = 0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/




/******************************* (END OF FILE) *********************************/



 







