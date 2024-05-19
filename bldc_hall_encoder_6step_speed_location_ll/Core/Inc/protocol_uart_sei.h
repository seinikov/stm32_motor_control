#ifndef __PROTOCOL_UART_H__
#define __PROTOCOL_UART_H__

#define CMD_SET_SPEED_PARA_TARGET       0x33
#define CMD_SET_SPEED_PARA_P            0xCC
#define CMD_SET_SPEED_PARA_I            0x55
#define CMD_SET_SPEED_PARA_D            0xAA

#define CMD_SET_LOCATION_PARA_TARGET    0x34
#define CMD_SET_LOCATION_PARA_P         0xCD
#define CMD_SET_LOCATION_PARA_I         0x56
#define CMD_SET_LOCATION_PARA_D         0xAB

#define CMD_FLASH_SAVE        0xEE

#define UART_BUFFER_LEN       64

void Protocol_UARTxRXProcess(void);

#endif
