/*
 * LS7366R.h
 *
 *  Created on: Oct 14, 2024
 *      Author: udaykumar
 */

#ifndef INC_LS7366R_H_
#define INC_LS7366R_H_

#include "main.h"

extern SPI_HandleTypeDef hspi1;

/* ------------------------ LS7366R Command Macros ------------------------ */
#define CLEAR_COUNTER                0x20  // Command to clear the counter
#define CLEAR_STATUS                 0x30  // Command to clear the status register

#define READ_OTR                     0x68  // Command to read OTR (Output Transfer Register)
#define READ_COUNTER                 0x60  // Command to read the current counter value
#define READ_STATUS                  0x70  // Command to read the status register

#define LOAD_COUNTER                 0xE0  // Command to load the OTR (Output Transfer Register) into the counter
#define LOAD_OTR                     0xE4  // Command to load DTR into OTR (Output Transfer Register)

#define WRITE_DTR                    0x98  // Command to write data into the Data Transfer Register (DTR)
#define WRITE_MODE0                  0x88  // Command to write to Mode0 register
#define WRITE_MODE1                  0x90  // Command to write to Mode1 register

/* ------------------------ Count Operating Modes ------------------------ */
#define FOURX_COUNT                  0x03  // x4 quadrature count mode (four counts per quadrature cycle)
#define NON_QUADRATURE  			 0x00

//Index modes
#define DISABLE_INDX 0x00       //index_disabled
#define INDX_LOADC 0x10         //index_load_CNTR
#define INDX_RESETC 0x20        //index_rest_CNTR
#define INDX_LOADO 0x30         //index_load_OL

/* ------------------------ Count Byte Modes ------------------------ */
// Defines how many bytes are used for counting (max value based on byte mode)
#define FOURBYTE_COUNTER             0x00  // 4-byte counter, counts from 0 to 4,294,967,295
#define THREEBYTE_COUNTER            0x01  // 3-byte counter, counts from 0 to 16,777,215
#define TWOBYTE_COUNTER              0x02  // 2-byte counter, counts from 0 to 65,535
#define ONEBYTE_COUNTER              0x03  // 1-byte counter, counts from 0 to 255

/* ------------------------ Function Prototypes ------------------------ */
void LS7366R_Init(uint8_t byte_mode);
void LS7366R_ClearCounter(void);
void LS7366R_ClearStatus(void);
void LS7366R_LoadCounter(uint32_t counter_val);
uint32_t LS7366R_ReadCounter(void);
uint8_t LS7366R_ReadStatus(void);
uint32_t LS7366R_ReadOTR(void);

#endif /* INC_LS7366R_H_ */
