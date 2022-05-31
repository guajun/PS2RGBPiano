#ifndef __LED_H
#define __LED_H
#include "main.h"
// const uint16_t LED_num;
#define LED_num_per_strip 150
#define LED_strip_num 6
#define ResetLength 200

extern TIM_HandleTypeDef htim1;
// uint8_t Rx_data[11];
uint8_t uart_rx_data;
// uint8_t LED_GRBXY_Value[5];

// uint8_t Key_list[40];

uint8_t LED_Data_Transmit[24 * 4 * LED_num_per_strip + ResetLength];



HAL_StatusTypeDef HAL_LED_Transmit_Start_DMA(TIM_HandleTypeDef *htim, uint8_t *pData, uint16_t Length);
HAL_StatusTypeDef HAL_LED_Transmit_Stop_DMA(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_PS2_Receive_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, uint8_t *pData, uint16_t Length);
HAL_StatusTypeDef HAL_PS2_Receive_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);


void LED_Data_Init();
void LED_Data_Convert();
// void PS2_Data_Handle();
void _main();
extern UART_HandleTypeDef huart6;
extern DMA_HandleTypeDef hdma_tim1_up;
// extern DMA_HandleTypeDef hdma_tim1_ch1;

#endif