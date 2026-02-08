/**
 * @file lw_console.c
 *
 */
  
/*********************
 *      INCLUDES
 *********************/
#include "lw_console.h"
#include <stdio.h>
/**********************
 *  STATIC PROTOTYPES
 **********************/
static bool waiting_for_command(const char * prompt);
/**********************
 *  STATIC VARIABLES
 **********************/
static uint8_t ucRxBuf[LW_CONSOLE_RX_BUF_SIZE];
static uint8_t * pBufRead;
static uint8_t * pBufWrite;

static uint32_t ulCmdCnt = 0;
static const lw_console_command_t * pCmdHandle = NULL;

static bool bConsoleRunning = false;
/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
void lw_console_init(void)
{

}


void lw_console_loop(void)
{
    bConsoleRunning = true;

    while(bConsoleRunning) {
        waiting_for_command(LW_CONSOLE_PROMPT);
    }
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
static void rxbuf_push_char(char ch)
{
    if(pBufWrite == pBufRead + LW_CONSOLE_RX_BUF_SIZE - 1) {
        pBufWrite = pBufRead;
    }
    *pBufWrite++ = ch;
}

static bool rxbuf_pop_char(char * ch)
{
    if(pBufRead == pBufWrite) {
        return false;
    }
    *ch = *pBufRead++;
    return true;
}

static void send_char(char ch)
{
    /* handle */
}


static void send_string(const char * str)
{
    while(*str) {
        send_char(*str++);
    }
} 

static bool waiting_for_command(const char * prompt)
{
    char ch;

    if(prompt) {
        send_string(prompt);
    }

    for(;;) {

        if(false == pop_char(&ch)) continue;

        switch(ch) {
            case LW_CONSOLE_CR:
                send_char(LW_CONSOLE_CR);
                send_char(LW_CONSOLE_LF);
                break;
            default:
                break;
        }
    }
}



/******************************* (END OF FILE) *********************************/



 







