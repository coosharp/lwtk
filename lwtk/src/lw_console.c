/**
  ******************************************************************************
  *
  * @file    lw_console.c
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
#include "lw_console.h"
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
static uint32_t gsul_command_count = 0;
static const lw_console_command_t * commands_buffer = NULL;
/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
void lw_console_init()
{

}

void lw_console_send_char(char ch)
{

}

void lw_console_send_string(const char * str)
{

}

void lw_console_printf(const char * fmt, ...)
{

}

uint16_t lw_console_read_line(char * buffer, uint16_t max_len)
{
    return 0;
}



/**********************
 *   STATIC FUNCTIONS
 **********************/
static bool write_data(uint8_t * buffer, 
                       uint16_t size, 
                       uint16_t * head, 
                       uint16_t * tail, 
                       uint8_t data)
{
    uint16_t next_head = (*head + 1) % size;
    
    if (next_head == *tail) {
        return false; /* 缓冲区满 */
    }
    
    buffer[*head] = data;
    *head = next_head;
    return true;
}

static bool read_data(uint8_t * buffer, 
                      uint16_t size, 
                      uint16_t * head, 
                      uint16_t * tail, 
                      uint8_t * data)
{
    if (*head == *tail) {
        return false; /* 缓冲区空 */
    }
    
    *data = buffer[*tail];
    *tail = (*tail + 1) % size;
    return true;
}

static uint16_t available_data(uint16_t size, uint16_t head, uint16_t tail)
{
    if (head >= tail) {
        return head - tail;
    } 
    else {
        return size - (tail - head);
    }
}

static void parse_command(char * command_line, int * argc, char * argv[], int max_argc)
{
    char *ptr = command_line;
    *argc = 0;
    
    while (*ptr != '\0' && *argc < max_argc) {
        /* 跳过空格 */
        while (*ptr == ' ' || *ptr == '\t') {
            ptr++;
        }
        
        if (*ptr == '\0') {
            break;
        }
        
        /* 记录参数起始位置 */
        argv[*argc] = ptr;
        (*argc)++;
        
        /* 找到参数结束位置 */
        while (*ptr != '\0' && *ptr != ' ' && *ptr != '\t') {
            ptr++;
        }
        
        /* 字符串以空字符结尾 */
        if (*ptr != '\0') {
            *ptr = '\0';
            ptr++;
        }
    }
}

static lw_console_command_t * find_command(const char * name)
{
    for (int i = 0; i < gsul_command_count; i++) {
        if (strcmp(commands_buffer[i].name, name) == 0) {
            return &commands_buffer[i];
        }
    }
    return NULL;
}





/******************************* (END OF FILE) *********************************/



 







