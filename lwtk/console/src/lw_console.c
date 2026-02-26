/**
 * @file lw_console.c
 *
 */
  
/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include "lw_console.h"
/**********************
 *  STATIC PROTOTYPES
 **********************/
static void rxbuf_push_char(char ch);
static bool waiting_for_command(const char * prompt);
/**********************
 *  STATIC VARIABLES
 **********************/
static lw_console_send_char_fn_t fnSendChar;
 
static uint8_t ucRxBuf[LW_CONSOLE_RX_BUF_SIZE];
static uint8_t * pBufRead;
static uint8_t * pBufWrite;

static uint8_t ucLineBuf[LW_CONSOLE_LINE_BUF_SIZE];
static uint32_t ulLineLen = 0;


static bool bConsoleRunning = false;
/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
void lw_console_init(lw_console_send_char_fn_t fn)
{
    memset(ucRxBuf, 0, sizeof(ucRxBuf));
    pBufRead = &ucRxBuf[0];
    pBufWrite= &ucRxBuf[0];
    fnSendChar = fn;
}

void lw_console_receive_irq(char ch)
{
    rxbuf_push_char(ch);
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
static inline int is_visible(uint8_t ch)
{
    return (ch >= 0x20 && ch <= 0x7F);
}

static inline int is_space(uint8_t ch)
{
    return (ch == 0x20 || ch == 0x09);
}

static inline int is_digit(uint8_t ch, uint8_t base)
{
    if(base == 10) {
        return ('0' <= ch && ch <= '9');
    }
    else if(base == 16) {
        return (('0' <= ch && ch <= '9') ||
                ('a' <= ch && ch <= 'f') ||
                ('A' <= ch && ch <= 'F'));
    }
    else {
        return 0;
    }
}

static inline int is_upper(uint8_t ch)
{
    return ('A' <= ch && ch <= 'Z');
}

static inline int is_lower(uint8_t ch)
{
    return ('a' <= ch && ch <= 'z');
}

static inline uint8_t to_upper(uint8_t ch)
{
    return is_lower(ch) ? (ch - 'a' + 'A') : ch;
}

static inline uint8_t to_lower(uint8_t ch)
{
    return is_upper(ch) ? (ch - 'A' + 'a') : ch;
}



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

static bool linebuf_write_char(char ch)
{
    if(ulLineLen < LW_CONSOLE_LINE_BUF_SIZE - 2) {
        ucLineBuf[ulLineLen++] = ch;
        return true;
    }
    else {
        return false;
    }
}

static void send_string(const char * str)
{
    while(*str) {
        fnSendChar(*str++);
    }
} 

static void delete_char(void)
{
    fnSendChar(0x08);
    fnSendChar(0x20);
    fnSendChar(0x08);
}

static void delete_all_char(void)
{
    while(ulLineLen--) {
        delete_char();
    }
}

static bool find_command()
{

}

static bool parse_command()
{
    char * ptr = &ucLineBuf[0];

    while((*ptr == ' ' || *ptr == '\t')) {
        ptr++;
    }

    if(*ptr == '\0') {
        return false;
    }
}

static bool waiting_for_command(const char * prompt)
{
    char ch;

    if(prompt) {
        send_string(prompt);
    }

    for(;;) {

        if(false == rxbuf_pop_char(&ch)) continue;

        switch(ch) {

            /* 回车，开始搜索命令 */
            case LW_CONSOLE_CR:
                if(linebuf_write_char('\0')) {
                    fnSendChar(LW_CONSOLE_LF);
                    fnSendChar(LW_CONSOLE_CR);
                    return true;
                }
                else {
                    send_string("linebuf overflow\r\n");
                    return false;
                }


            /* 换行符，忽略 */
            case LW_CONSOLE_LF:
            case 0x00:
                break;


            case LW_CONSOLE_CTRL_C:
                printf("ctrl+c\r\n");
                return false;
            case LW_CONSOLE_CTRL_Q:
                printf("ctrl+q\r\n");
                break;
            case LW_CONSOLE_CTRL_A:
                printf("ctrl+a\r\n");
                break;

            /* 退格键，删除一个字符 */    
            case LW_CONSOLE_BACKSPACE:
            case LW_CONSOLE_DEL:
                delete_char();
                break;

            /* ESC键，删除所有字符 */
            case LW_CONSOLE_ESC:
                delete_all_char();
                break;

            case LW_CONSOLE_TAB:
                if(linebuf_write_char(ch)) {
                    uint32_t total_len = ulLineLen + strlen(prompt);
                    uint32_t tab_cnt = (4 - total_len % 4) % 4;
                    while(tab_cnt--) {
                        fnSendChar(LW_CONSOLE_SPACE);
                    }
                }
                break;

            default:
                if(linebuf_write_char(ch)) {
                    fnSendChar(ch);
                }
                break;
        }
    }
}



/******************************* (END OF FILE) *********************************/



 







