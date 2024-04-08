#ifndef __PROTOCOL_UART_H__
#define __PROTOCOL_UART_H__

#define CMD_SET_PARA_TARGET   0x33
#define CMD_SET_PARA_P        0xCC
#define CMD_SET_PARA_I        0x55
#define CMD_SET_PARA_D        0xAA
#define CMD_FLASH_SAVE        0xEE

#define UART_BUFFER_LEN       64

void Protocol_UARTxRXProcess(void);

#endif
