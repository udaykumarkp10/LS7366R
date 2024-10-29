/*
 * LS7366R.c
 *
 *  Created on: Oct 14, 2024
 *      Author: udaykumar
 */


#include "LS7366R.h"

#define CS_SET() 	HAL_GPIO_WritePin(LS7366R_CS_GPIO_Port, LS7366R_CS_Pin, GPIO_PIN_SET)
#define CS_RESET() 	HAL_GPIO_WritePin(LS7366R_CS_GPIO_Port, LS7366R_CS_Pin, GPIO_PIN_RESET)

// Function to initialize LS7366R
void LS7366R_Init(uint8_t byte_mode)
{
    // Clear Counter and Status
    LS7366R_ClearCounter();
    LS7366R_ClearStatus();

    // Set LS7366R to x4 quadrature mode (FOURX_COUNT)
    uint8_t mode0 = WRITE_MODE0;
    uint8_t mode0_data = FOURX_COUNT | INDX_LOADO ;  // Enable index pulse to reset the counter
    CS_RESET();
    HAL_SPI_Transmit(&hspi1, &mode0, 1, HAL_MAX_DELAY);
    HAL_SPI_Transmit(&hspi1, &mode0_data, 1, HAL_MAX_DELAY);
    CS_SET();

    // Set Byte Mode (e.g., 4-byte mode)
    uint8_t mode1 = WRITE_MODE1;
    CS_RESET();
    HAL_SPI_Transmit(&hspi1, &mode1, 1, HAL_MAX_DELAY);
    HAL_SPI_Transmit(&hspi1, &byte_mode, 1, HAL_MAX_DELAY);
    CS_SET();
}

// Function to clear the LS7366R status
void LS7366R_ClearStatus(void)
{
    uint8_t clear_status_cmd = CLEAR_STATUS;
    CS_RESET();
    HAL_SPI_Transmit(&hspi1, &clear_status_cmd, 1, HAL_MAX_DELAY);
    CS_SET();
}

// Function to read the status of the LS7366R
uint8_t LS7366R_ReadStatus(void)
{
    uint8_t read_cmd = READ_STATUS;
    uint8_t status = 0;

    CS_RESET();
    HAL_SPI_Transmit(&hspi1, &read_cmd, 1, HAL_MAX_DELAY);
    HAL_SPI_Receive(&hspi1, &status, 1, HAL_MAX_DELAY);
    CS_SET();

    return status;
}

// Function to clear the LS7366R counter
void LS7366R_ClearCounter(void)
{
    uint8_t clear_counter_cmd = CLEAR_COUNTER;
    CS_RESET();
    HAL_SPI_Transmit(&hspi1, &clear_counter_cmd, 1, HAL_MAX_DELAY);
    CS_SET();
}

// Function to read the current counter value
uint32_t LS7366R_ReadCounter(void)
{
    uint8_t read_cmd = READ_COUNTER;
    uint8_t data[4] = {0};

    CS_RESET();
    HAL_SPI_Transmit(&hspi1, &read_cmd, 1, HAL_MAX_DELAY);
    HAL_SPI_Receive(&hspi1, data, 4, HAL_MAX_DELAY);
    CS_SET();

    uint32_t counter_value = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
    return counter_value;
}


/*
uint32_t LS7366R_ReadOTR(void)
{
    uint8_t read_cmd = READ_OTR;  // Command to read OTR register
    uint8_t data[4] = {0};        // Buffer to store the 4-byte OTR value

    CS_RESET();
    HAL_SPI_Transmit(&hspi1, &read_cmd, 1, HAL_MAX_DELAY);  // Send READ_OTR command
    HAL_SPI_Receive(&hspi1, data, 4, HAL_MAX_DELAY);       // Receive 4 bytes (32-bit OTR)
    CS_SET();

    // Combine the received data into a single 32-bit OTR value
    uint32_t counter_value = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
    return counter_value;
}
*/

// Function to load a value into the counter
void LS7366R_LoadCounter(uint32_t counter_val)
{
    uint8_t load_counter_cmd = WRITE_DTR;
    uint8_t data[4];
    data[0] = (counter_val >> 24) & 0xFF;
    data[1] = (counter_val >> 16) & 0xFF;
    data[2] = (counter_val >> 8) & 0xFF;
    data[3] = counter_val & 0xFF;

    CS_RESET();
    HAL_SPI_Transmit(&hspi1, &load_counter_cmd, 1, HAL_MAX_DELAY);
    HAL_SPI_Transmit(&hspi1, data, 4, HAL_MAX_DELAY);
    CS_SET();

    uint8_t load_cmd = LOAD_COUNTER;
    CS_RESET();
    HAL_SPI_Transmit(&hspi1, &load_cmd, 1, HAL_MAX_DELAY);
    CS_SET();
}

