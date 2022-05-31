#ifndef __LED_C__
#define __LED_C__
#include "led.h"
#include "KeyCode.h"
#include <math.h>
// #include "FastLED.h"
#include "stm32f4xx_hal_tim.h"

uint8_t uart_rx_data = 0;

/**
  * @brief  Period elapsed callback in non-blocking mode
  * @param  htim TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(htim);

  HAL_LED_Transmit_Stop_DMA(htim);
}
uint32_t Key_list[40] = {0};

uint32_t PS2_code = 0;
void PS2_Data_Handle()
{

  uint8_t Rx = uart_rx_data;

  switch (Rx)
  {
  case 0xF0:
    PS2_code |= Rx << 8;
    break;
  case 0xE0:
    PS2_code |= Rx << 16;
    break;

  default:
    PS2_code |= Rx;

    switch (PS2_code)
    {
    case PS2_KC_S:
      if (!Key_list[0])
      {
        Key_list[0] = HAL_GetTick();
      }
      break;
    case (PS2_KC_KEYBREAK + PS2_KC_S):
      Key_list[0] = 0;
      break;
    case PS2_KC_D:
      if (!Key_list[1])
      {
        Key_list[1] = HAL_GetTick();
      }
      break;
    case (PS2_KC_KEYBREAK + PS2_KC_D):
      Key_list[1] = 0;
      break;
    case PS2_KC_F:
      if (!Key_list[2])
      {
        Key_list[2] = HAL_GetTick();
      }
      break;
    case (PS2_KC_KEYBREAK + PS2_KC_F):
      Key_list[2] = 0;
      break;
    case PS2_KC_L:
      if (!Key_list[3])
      {
        Key_list[3] = HAL_GetTick();
      }
      break;
    case (PS2_KC_KEYBREAK + PS2_KC_L):
      Key_list[3] = 0;
      break;
    case PS2_KC_K:
      if (!Key_list[4])
      {
        Key_list[4] = HAL_GetTick();
      }
      break;
    case (PS2_KC_KEYBREAK + PS2_KC_K):
      Key_list[4] = 0;
      break;
    case PS2_KC_J:
      if (!Key_list[5])
      {
        Key_list[5] = HAL_GetTick();
      }
      break;
    case (PS2_KC_KEYBREAK + PS2_KC_J):
      Key_list[5] = 0;
      break;
    case PS2_KC_W:
      if (!Key_list[6])
      {
        Key_list[6] = HAL_GetTick();
      }
      break;
    case (PS2_KC_KEYBREAK + PS2_KC_W):
      Key_list[6] = 0;
      break;
    case PS2_KC_E:
      if (!Key_list[7])
      {
        Key_list[7] = HAL_GetTick();
      }
      break;
    case (PS2_KC_KEYBREAK + PS2_KC_E):
      Key_list[7] = 0;
      break;
    case PS2_KC_R:
      if (!Key_list[8])
      {
        Key_list[8] = HAL_GetTick();
      }
      break;
    case (PS2_KC_KEYBREAK + PS2_KC_R):
      Key_list[8] = 0;
      break;
    case PS2_KC_O:
      if (!Key_list[9])
      {
        Key_list[9] = HAL_GetTick();
      }
      break;
    case (PS2_KC_KEYBREAK + PS2_KC_O):
      Key_list[9] = 0;
      break;
    case PS2_KC_I:
      if (!Key_list[10])
      {
        Key_list[10] = HAL_GetTick();
      }
      break;
    case (PS2_KC_KEYBREAK + PS2_KC_I):
      Key_list[10] = 0;
      break;
    case PS2_KC_U:
      if (!Key_list[11])
      {
        Key_list[11] = HAL_GetTick();
      }
      break;
    case (PS2_KC_KEYBREAK + PS2_KC_U):
      Key_list[11] = 0;
      break;
    case PS2_KC_1:
      if (!Key_list[12])
      {
        Key_list[12] = HAL_GetTick();
      }
      break;
    case (PS2_KC_KEYBREAK + PS2_KC_1):
      Key_list[12] = 0;
      break;
    case PS2_KC_2:
      if (!Key_list[13])
      {
        Key_list[13] = HAL_GetTick();
      }
      break;
    case (PS2_KC_KEYBREAK + PS2_KC_2):
      Key_list[13] = 0;
      break;
    case PS2_KC_3:
      if (!Key_list[14])
      {
        Key_list[14] = HAL_GetTick();
      }
      break;
    case (PS2_KC_KEYBREAK + PS2_KC_3):
      Key_list[14] = 0;
      break;
    default:
      break;
    }
    // uint32_t sendbuffer = PS2_code;
    // HAL_UART_Transmit_IT(&huart6, (uint8_t *)&sendbuffer, 3);
    PS2_code = 0;
    // HAL_UART_Transmit_IT(&huart6, (uint8_t *)Key_list, 6*4);
    break;
  }
}

/**
  * @brief  Rx Transfer completed callbacks.
  * @param  huart  Pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(huart);
  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_UART_RxCpltCallback could be implemented in the user file
   */
  // HAL_UART_Transmit_IT(&huart6, (uint8_t *)&uart_rx_data, 1);
  PS2_Data_Handle();
}

/**
  * @brief  TIM DMA Period Elapse half complete callback.
  * @param  hdma pointer to DMA handle.
  * @retval None
  */
static void TIM_DMAPeriodElapsedHalfCplt(DMA_HandleTypeDef *hdma)
{
  TIM_HandleTypeDef *htim = (TIM_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
  htim->PeriodElapsedHalfCpltCallback(htim);
#else
  HAL_TIM_PeriodElapsedHalfCpltCallback(htim);
#endif /* USE_HAL_TIM_REGISTER_CALLBACKS */
}

/**
  * @brief  TIM DMA Period Elapse complete callback.
  * @param  hdma pointer to DMA handle.
  * @retval None
  */
static void TIM_DMAPeriodElapsedCplt(DMA_HandleTypeDef *hdma)
{
  TIM_HandleTypeDef *htim = (TIM_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  if (htim->hdma[TIM_DMA_ID_UPDATE]->Init.Mode == DMA_NORMAL)
  {
    htim->State = HAL_TIM_STATE_READY;
  }

#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
  htim->PeriodElapsedCallback(htim);
#else
  HAL_TIM_PeriodElapsedCallback(htim);
#endif /* USE_HAL_TIM_REGISTER_CALLBACKS */
}

/**
  * @brief  Starts the TIM Base generation in DMA mode.
  * @param  htim TIM Base handle
  * @param  pData The source Buffer address.
  * @param  Length The length of data to be transferred from memory to peripheral.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LED_Transmit_Start_DMA(TIM_HandleTypeDef *htim, uint8_t *pData, uint16_t Length)
{
  uint32_t tmpsmcr;

  /* Check the parameters */
  assert_param(IS_TIM_DMA_INSTANCE(htim->Instance));

  /* Set the TIM state */
  if (htim->State == HAL_TIM_STATE_BUSY)
  {
    return HAL_BUSY;
  }
  else if (htim->State == HAL_TIM_STATE_READY)
  {
    if ((pData == NULL) && (Length > 0U))
    {
      return HAL_ERROR;
    }
    else
    {
      htim->State = HAL_TIM_STATE_BUSY;
    }
  }
  else
  {
    return HAL_ERROR;
  }

  /* Set the DMA Period elapsed callbacks */
  htim->hdma[TIM_DMA_ID_UPDATE]->XferCpltCallback = TIM_DMAPeriodElapsedCplt;
  htim->hdma[TIM_DMA_ID_UPDATE]->XferHalfCpltCallback = TIM_DMAPeriodElapsedHalfCplt;

  /* Set the DMA error callback */
  htim->hdma[TIM_DMA_ID_UPDATE]->XferErrorCallback = TIM_DMAError;

  /* Enable the DMA stream */
  if (HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_UPDATE], (uint32_t)pData, (uint32_t)&GPIOB->ODR,
                       Length) != HAL_OK)
  {
    /* Return error status */
    return HAL_ERROR;
  }

  /* Enable the TIM Update DMA request */
  __HAL_TIM_ENABLE_DMA(htim, TIM_DMA_UPDATE);

  /* Enable the Peripheral, except in trigger mode where enable is automatically done with trigger */
  if (IS_TIM_SLAVE_INSTANCE(htim->Instance))
  {
    tmpsmcr = htim->Instance->SMCR & TIM_SMCR_SMS;
    if (!IS_TIM_SLAVEMODE_TRIGGER_ENABLED(tmpsmcr))
    {
      __HAL_TIM_ENABLE(htim);
    }
  }
  else
  {
    __HAL_TIM_ENABLE(htim);
  }

  /* Return function status */
  return HAL_OK;
}

HAL_StatusTypeDef HAL_LED_Transmit_Stop_DMA(TIM_HandleTypeDef *htim)
{
  /* Check the parameters */
  assert_param(IS_TIM_DMA_INSTANCE(htim->Instance));

  /* Disable the TIM Update DMA request */
  __HAL_TIM_DISABLE_DMA(htim, TIM_DMA_UPDATE);

  (void)HAL_DMA_Abort_IT(htim->hdma[TIM_DMA_ID_UPDATE]);

  /* Disable the Peripheral */
  // __HAL_TIM_DISABLE(htim);

  /* Set the TIM state */
  htim->State = HAL_TIM_STATE_READY;

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Starts the TIM Input Capture measurement in DMA mode.
  * @param  htim TIM Input Capture handle
  * @param  Channel TIM Channels to be enabled
  *          This parameter can be one of the following values:
  *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
  *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
  *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
  *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
  * @param  pData The destination Buffer address.
  * @param  Length The length of data to be transferred from TIM peripheral to memory.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PS2_Receive_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, uint8_t *pData, uint16_t Length)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t tmpsmcr;

  HAL_TIM_ChannelStateTypeDef channel_state = TIM_CHANNEL_STATE_GET(htim, Channel);
  HAL_TIM_ChannelStateTypeDef complementary_channel_state = TIM_CHANNEL_N_STATE_GET(htim, Channel);

  /* Check the parameters */
  assert_param(IS_TIM_CCX_INSTANCE(htim->Instance, Channel));
  assert_param(IS_TIM_DMA_CC_INSTANCE(htim->Instance));

  /* Set the TIM channel state */
  if ((channel_state == HAL_TIM_CHANNEL_STATE_BUSY) || (complementary_channel_state == HAL_TIM_CHANNEL_STATE_BUSY))
  {
    return HAL_BUSY;
  }
  else if ((channel_state == HAL_TIM_CHANNEL_STATE_READY) && (complementary_channel_state == HAL_TIM_CHANNEL_STATE_READY))
  {
    if ((pData == NULL) && (Length > 0U))
    {
      return HAL_ERROR;
    }
    else
    {
      TIM_CHANNEL_STATE_SET(htim, Channel, HAL_TIM_CHANNEL_STATE_BUSY);
      TIM_CHANNEL_N_STATE_SET(htim, Channel, HAL_TIM_CHANNEL_STATE_BUSY);
    }
  }
  else
  {
    return HAL_ERROR;
  }

  /* Enable the Input Capture channel */
  TIM_CCxChannelCmd(htim->Instance, Channel, TIM_CCx_ENABLE);

  switch (Channel)
  {
  case TIM_CHANNEL_1:
  {
    /* Set the DMA capture callbacks */
    htim->hdma[TIM_DMA_ID_CC1]->XferCpltCallback = TIM_DMACaptureCplt;
    htim->hdma[TIM_DMA_ID_CC1]->XferHalfCpltCallback = TIM_DMACaptureHalfCplt;

    /* Set the DMA error callback */
    htim->hdma[TIM_DMA_ID_CC1]->XferErrorCallback = TIM_DMAError;

    /* Enable the DMA stream */
    if (HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_CC1], (uint32_t)&GPIOA->IDR, (uint32_t)pData,
                         Length) != HAL_OK)
    {
      /* Return error status */
      return HAL_ERROR;
    }
    /* Enable the TIM Capture/Compare 1 DMA request */
    __HAL_TIM_ENABLE_DMA(htim, TIM_DMA_CC1);
    break;
  }

  case TIM_CHANNEL_2:
  {
    /* Set the DMA capture callbacks */
    htim->hdma[TIM_DMA_ID_CC2]->XferCpltCallback = TIM_DMACaptureCplt;
    htim->hdma[TIM_DMA_ID_CC2]->XferHalfCpltCallback = TIM_DMACaptureHalfCplt;

    /* Set the DMA error callback */
    htim->hdma[TIM_DMA_ID_CC2]->XferErrorCallback = TIM_DMAError;

    /* Enable the DMA stream */
    if (HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_CC2], (uint32_t)&GPIOA->IDR, (uint32_t)pData,
                         Length) != HAL_OK)
    {
      /* Return error status */
      return HAL_ERROR;
    }
    /* Enable the TIM Capture/Compare 2  DMA request */
    __HAL_TIM_ENABLE_DMA(htim, TIM_DMA_CC2);
    break;
  }

  case TIM_CHANNEL_3:
  {
    /* Set the DMA capture callbacks */
    htim->hdma[TIM_DMA_ID_CC3]->XferCpltCallback = TIM_DMACaptureCplt;
    htim->hdma[TIM_DMA_ID_CC3]->XferHalfCpltCallback = TIM_DMACaptureHalfCplt;

    /* Set the DMA error callback */
    htim->hdma[TIM_DMA_ID_CC3]->XferErrorCallback = TIM_DMAError;

    /* Enable the DMA stream */
    if (HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_CC3], (uint32_t)&GPIOA->IDR, (uint32_t)pData,
                         Length) != HAL_OK)
    {
      /* Return error status */
      return HAL_ERROR;
    }
    /* Enable the TIM Capture/Compare 3  DMA request */
    __HAL_TIM_ENABLE_DMA(htim, TIM_DMA_CC3);
    break;
  }

  case TIM_CHANNEL_4:
  {
    /* Set the DMA capture callbacks */
    htim->hdma[TIM_DMA_ID_CC4]->XferCpltCallback = TIM_DMACaptureCplt;
    htim->hdma[TIM_DMA_ID_CC4]->XferHalfCpltCallback = TIM_DMACaptureHalfCplt;

    /* Set the DMA error callback */
    htim->hdma[TIM_DMA_ID_CC4]->XferErrorCallback = TIM_DMAError;

    /* Enable the DMA stream */
    if (HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_CC4], (uint32_t)&GPIOA->IDR, (uint32_t)pData,
                         Length) != HAL_OK)
    {
      /* Return error status */
      return HAL_ERROR;
    }
    /* Enable the TIM Capture/Compare 4  DMA request */
    __HAL_TIM_ENABLE_DMA(htim, TIM_DMA_CC4);
    break;
  }

  default:
    status = HAL_ERROR;
    break;
  }

  /* Enable the Peripheral, except in trigger mode where enable is automatically done with trigger */
  if (IS_TIM_SLAVE_INSTANCE(htim->Instance))
  {
    tmpsmcr = htim->Instance->SMCR & TIM_SMCR_SMS;
    if (!IS_TIM_SLAVEMODE_TRIGGER_ENABLED(tmpsmcr))
    {
      __HAL_TIM_ENABLE(htim);
    }
  }
  else
  {
    __HAL_TIM_ENABLE(htim);
  }

  /* Return function status */
  return status;
}

/**
  * @brief  Stops the TIM Input Capture measurement in DMA mode.
  * @param  htim TIM Input Capture handle
  * @param  Channel TIM Channels to be disabled
  *          This parameter can be one of the following values:
  *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
  *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
  *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
  *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
  * @retval HAL status
  */

HAL_StatusTypeDef HAL_PS2_Receive_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the parameters */
  assert_param(IS_TIM_CCX_INSTANCE(htim->Instance, Channel));
  assert_param(IS_TIM_DMA_CC_INSTANCE(htim->Instance));

  /* Disable the Input Capture channel */
  TIM_CCxChannelCmd(htim->Instance, Channel, TIM_CCx_DISABLE);

  switch (Channel)
  {
  case TIM_CHANNEL_1:
  {
    /* Disable the TIM Capture/Compare 1 DMA request */
    __HAL_TIM_DISABLE_DMA(htim, TIM_DMA_CC1);
    (void)HAL_DMA_Abort_IT(htim->hdma[TIM_DMA_ID_CC1]);
    break;
  }

  case TIM_CHANNEL_2:
  {
    /* Disable the TIM Capture/Compare 2 DMA request */
    __HAL_TIM_DISABLE_DMA(htim, TIM_DMA_CC2);
    (void)HAL_DMA_Abort_IT(htim->hdma[TIM_DMA_ID_CC2]);
    break;
  }

  case TIM_CHANNEL_3:
  {
    /* Disable the TIM Capture/Compare 3  DMA request */
    __HAL_TIM_DISABLE_DMA(htim, TIM_DMA_CC3);
    (void)HAL_DMA_Abort_IT(htim->hdma[TIM_DMA_ID_CC3]);
    break;
  }

  case TIM_CHANNEL_4:
  {
    /* Disable the TIM Capture/Compare 4  DMA request */
    __HAL_TIM_DISABLE_DMA(htim, TIM_DMA_CC4);
    (void)HAL_DMA_Abort_IT(htim->hdma[TIM_DMA_ID_CC4]);
    break;
  }

  default:
    status = HAL_ERROR;
    break;
  }

  if (status == HAL_OK)
  {
    /* Disable the Peripheral */
    // __HAL_TIM_DISABLE(htim);

    /* Set the TIM channel state */
    TIM_CHANNEL_STATE_SET(htim, Channel, HAL_TIM_CHANNEL_STATE_READY);
    TIM_CHANNEL_N_STATE_SET(htim, Channel, HAL_TIM_CHANNEL_STATE_READY);
  }

  /* Return function status */
  return status;
}

uint8_t LED_GRBXY_Value[5] = {0};

struct bit_handler
{
  // uint8_t g7 : 1;
  // uint8_t g6 : 1;
  // uint8_t g5 : 1;
  // uint8_t g4 : 1;
  // uint8_t g3 : 1;
  // uint8_t g2 : 1;
  // uint8_t g1 : 1;
  // uint8_t g0 : 1;
  // uint8_t r7 : 1;
  // uint8_t r6 : 1;
  // uint8_t r5 : 1;
  // uint8_t r4 : 1;
  // uint8_t r3 : 1;
  // uint8_t r2 : 1;
  // uint8_t r1 : 1;
  // uint8_t r0 : 1;
  uint8_t b7 : 1;
  uint8_t b6 : 1;
  uint8_t b5 : 1;
  uint8_t b4 : 1;
  uint8_t b3 : 1;
  uint8_t b2 : 1;
  uint8_t b1 : 1;
  uint8_t b0 : 1;
};

// uint8_t LED_index[2] = {0};

uint8_t LED_Data_Transmit[24 * 4 * LED_num_per_strip + ResetLength] = {0};
struct CHSV
{
  uint8_t hue;
  uint8_t sat;
  uint8_t val;
};

struct CRGB
{
  uint8_t r;
  uint8_t g;
  uint8_t b;
};
struct CHSV LED_HSV[LED_strip_num][1] = {{{0, 0, 0}}};
struct CRGB LED_RGB[LED_strip_num][1] = {{{0, 0, 0}}};
void LED_Data_Init()
{
  memset(LED_Data_Transmit, 0, sizeof(LED_Data_Transmit));
  for (uint32_t i = 0; i < 24 * 4 * LED_num_per_strip; i = i + 4)
  {

    LED_Data_Transmit[i] = 0xFF;
  }
  for (uint8_t i = 0; i < 6; i++)
  {
    LED_HSV[i][0].sat = 255;
  }

  // for (uint32_t i = 0; i < 24 * 4 * LED_num_per_strip; i = i + 4)
  // {

  //   LED_Data_Transmit[i] = 0xFF;
  //   LED_Data_Transmit[i + 1] = 0xFF;

  // }
}
// uint8_t global_tick = 0;

uint8_t grbcolor[3] = {0};

void LED_color()
{
  uint32_t tick = HAL_GetTick();
  for (uint8_t i = 0; i < 3; i++)
  {
    uint16_t a = (tick + i * 128) % (256 * 2);
    if (a < 256)
    {
    }
    else
    {
      a = -a + 511;
    }
    grbcolor[i] = a;
  }

  // return grbcolor;
}
void LED_Data_Generate()
{
  // if ((LED_GRBXY_Value[4] == 0) && (LED_GRBXY_Value[3] == 0))
  // {

  //   if (Key_list[7] || Key_list[8])
  //   {
  //     LED_GRBXY_Value[0] = 255;
  //     LED_GRBXY_Value[1] = 255;
  //     LED_GRBXY_Value[2] = 255;
  //   }
  //   else
  //   {
  //     LED_GRBXY_Value[0] = 255;
  //     LED_GRBXY_Value[1] = 0;
  //     LED_GRBXY_Value[2] = 0;
  //   }

  // }
  if (LED_GRBXY_Value[4] == 0)
  {
    switch (LED_GRBXY_Value[3])
    {
    case 0:
      if (Key_list[0])
      {
        LED_color();
        memcpy(LED_GRBXY_Value, grbcolor, 3);
      }
      else
      {
        memset(LED_GRBXY_Value, 0, 3);
      }
      break;
    case 1:

      break;
    case 2:

      break;
    case 3:

      break;
    case 4:

      break;
    case 5:

      break;

    default:
      break;
    }
  }
}
void LED_Data_Convert()
{
  LED_Data_Init();
  // LED_GRBXY_Value[1] = 0xff;
  // memset(LED_Data_Transmit, 0, sizeof(LED_Data_Transmit));
  // Key_list[7] = 1;
  uint32_t LED_index = 0;
  for (uint8_t y = 0; y < LED_num_per_strip; y++)
  {

    LED_GRBXY_Value[4] = y;

    uint8_t GRB_Values[LED_strip_num * 3] = {0};

    // HAL_UART_Transmit_IT(&huart6, (uint8_t *)GRB_Values, 12);
    // HAL_UART_Transmit_IT(&huart6, (uint8_t *)LED_GRBXY_Value, 5);

    for (uint8_t x = 0; x < LED_strip_num; x++)
    {
      LED_GRBXY_Value[3] = x;

      LED_Data_Generate();

      GRB_Values[x * 3 + 0] = LED_GRBXY_Value[0];
      GRB_Values[x * 3 + 1] = LED_GRBXY_Value[1];
      GRB_Values[x * 3 + 2] = LED_GRBXY_Value[2];
    }

    for (uint8_t x = 0; x < LED_strip_num; x++)
    {
      for (uint8_t GRB_channel = 0; GRB_channel < 3; GRB_channel++)
      {

        LED_index = (y * 3 << 5) + (GRB_channel << 5);

        struct bit_handler *GRB_bithandle = (struct bit_handler *)(GRB_Values + x * 3 + GRB_channel);

        LED_Data_Transmit[LED_index + 1] |= GRB_bithandle->b0 << x;
        LED_Data_Transmit[LED_index + 5] |= GRB_bithandle->b1 << x;
        LED_Data_Transmit[LED_index + 9] |= GRB_bithandle->b2 << x;
        LED_Data_Transmit[LED_index + 13] |= GRB_bithandle->b3 << x;
        LED_Data_Transmit[LED_index + 17] |= GRB_bithandle->b4 << x;
        LED_Data_Transmit[LED_index + 21] |= GRB_bithandle->b5 << x;
        LED_Data_Transmit[LED_index + 25] |= GRB_bithandle->b6 << x;
        LED_Data_Transmit[LED_index + 29] |= GRB_bithandle->b7 << x;

        LED_Data_Transmit[LED_index + 2] |= GRB_bithandle->b0 << x;
        LED_Data_Transmit[LED_index + 6] |= GRB_bithandle->b1 << x;
        LED_Data_Transmit[LED_index + 10] |= GRB_bithandle->b2 << x;
        LED_Data_Transmit[LED_index + 14] |= GRB_bithandle->b3 << x;
        LED_Data_Transmit[LED_index + 18] |= GRB_bithandle->b4 << x;
        LED_Data_Transmit[LED_index + 22] |= GRB_bithandle->b5 << x;
        LED_Data_Transmit[LED_index + 26] |= GRB_bithandle->b6 << x;
        LED_Data_Transmit[LED_index + 30] |= GRB_bithandle->b7 << x;
      }
    }
  }
}

// uint8_t dmaflag = 1;

// #define APPLY_DIMMING(X) (X)
#define HSV_SECTION_6 (0x20)
#define HSV_SECTION_3 (0x40)

void hsv2rgb_raw_C(struct CHSV *hsv, struct CRGB *rgb)
{
  // Convert hue, saturation and brightness ( HSV/HSB ) to RGB
  // "Dimming" is used on saturation and brightness to make
  // the output more visually linear.

  // Apply dimming curves
  uint8_t value = hsv->val;
  uint8_t saturation = hsv->sat;

  // The brightness floor is minimum number that all of
  // R, G, and B will be set to.
  uint8_t invsat = 255 - saturation;
  uint8_t brightness_floor = (value * invsat) / 256;

  // The color amplitude is the maximum amount of R, G, and B
  // that will be added on top of the brightness_floor to
  // create the specific hue desired.
  uint8_t color_amplitude = value - brightness_floor;

  // Figure out which section of the hue wheel we're in,
  // and how far offset we are withing that section
  uint8_t section = hsv->hue / HSV_SECTION_3; // 0..2
  uint8_t offset = hsv->hue % HSV_SECTION_3;  // 0..63

  uint8_t rampup = offset;                         // 0..63
  uint8_t rampdown = (HSV_SECTION_3 - 1) - offset; // 63..0

  // We now scale rampup and rampdown to a 0-255 range -- at least
  // in theory, but here's where architecture-specific decsions
  // come in to play:
  // To scale them up to 0-255, we'd want to multiply by 4.
  // But in the very next step, we multiply the ramps by other
  // values and then divide the resulting product by 256.
  // So which is faster?
  //   ((ramp * 4) * othervalue) / 256
  // or
  //   ((ramp    ) * othervalue) /  64
  // It depends on your processor architecture.
  // On 8-bit AVR, the "/ 256" is just a one-cycle register move,
  // but the "/ 64" might be a multicycle shift process. So on AVR
  // it's faster do multiply the ramp values by four, and then
  // divide by 256.
  // On ARM, the "/ 256" and "/ 64" are one cycle each, so it's
  // faster to NOT multiply the ramp values by four, and just to
  // divide the resulting product by 64 (instead of 256).
  // Moral of the story: trust your profiler, not your insticts.

  // Since there's an AVR assembly version elsewhere, we'll
  // assume what we're on an architecture where any number of
  // bit shifts has roughly the same cost, and we'll remove the
  // redundant math at the source level:

  //  // scale up to 255 range
  //  //rampup *= 4; // 0..252
  //  //rampdown *= 4; // 0..252

  // compute color-amplitude-scaled-down versions of rampup and rampdown
  uint8_t rampup_amp_adj = (rampup * color_amplitude) / (256 / 4);
  uint8_t rampdown_amp_adj = (rampdown * color_amplitude) / (256 / 4);

  // add brightness_floor offset to everything
  uint8_t rampup_adj_with_floor = rampup_amp_adj + brightness_floor;
  uint8_t rampdown_adj_with_floor = rampdown_amp_adj + brightness_floor;

  if (section)
  {
    if (section == 1)
    {
      // section 1: 0x40..0x7F
      rgb->r = brightness_floor;
      rgb->g = rampdown_adj_with_floor;
      rgb->b = rampup_adj_with_floor;
    }
    else
    {
      // section 2; 0x80..0xBF
      rgb->r = rampup_adj_with_floor;
      rgb->g = brightness_floor;
      rgb->b = rampdown_adj_with_floor;
    }
  }
  else
  {
    // section 0: 0x00..0x3F
    rgb->r = rampdown_adj_with_floor;
    rgb->g = rampup_adj_with_floor;
    rgb->b = brightness_floor;
  }
}

uint8_t temp[24 * 4] = {0};

void LED_Send()
{

  for (uint8_t y = 0; y < LED_num_per_strip; y++)
  {
    memcpy(LED_Data_Transmit + y * 24 * 4, temp, 24 * 4);
  }

  while (HAL_DMA_GetState(&hdma_tim1_up) != HAL_DMA_STATE_READY)
  {
  }
  HAL_LED_Transmit_Start_DMA(&htim1, (uint8_t *)LED_Data_Transmit, sizeof(LED_Data_Transmit));
  // {
  //   // HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
  //   // HAL_Delay(20);
  // }
}

// struct CHSV LED_HSV[LED_strip_num][LED_num_per_strip] = {0, 0, 0};
// struct CRGB LED_RGB[LED_strip_num][LED_num_per_strip] = {0, 0, 0};
float base = 0.9925f;
void LED_Process()
{

  uint32_t tick = HAL_GetTick();

  for (uint8_t i = 12; i < 15; i++)
  {
    float base_array[3] = {0.9912f, 0.9925f, 0.9937f};
    uint32_t t = 0;
    if (Key_list[i])
    {
      if (t < Key_list[i])
      {
        t = Key_list[i];
        base = base_array[i - 12];
      }
    }
  }

  for (uint8_t i = 0; i < 3; i++)
  {
    // LED_HSV[i][0].sat = 255;
    // LED_HSV[i + 3][0].sat = 255;

    if (Key_list[i] || Key_list[i + 6] || Key_list[i + 3] || Key_list[i + 9])
    {
      uint32_t offest;
      uint32_t t1;
      uint32_t t2;
      uint8_t value1;
      uint8_t value2;
      // float base;

      if (Key_list[i] < Key_list[i + 3])
      {
        t1 = Key_list[i + 3];
      }
      else
      {
        t1 = Key_list[i];
      }

      offest = tick - t1;

      value1 = powf(base, offest) * 255;

      if (Key_list[i + 6] < Key_list[i + 9])
      {

        t2 = Key_list[i + 9];
      }
      else
      {
        t2 = Key_list[i + 6];
      }

      offest = tick - t2;

      value2 = powf(base + 0.003f, offest) * 255;

      if (value1 < value2)
      {
        LED_HSV[i][0].val = value2;
        LED_HSV[i + 3][0].val = value2;
      }
      else
      {
        LED_HSV[i][0].val = value1;
        LED_HSV[i + 3][0].val = value1;
      }

      uint32_t t = 0;
      for (uint8_t j = i; j < 12; j = j + 3)
      {

        if (t < Key_list[j])
        {
          t = Key_list[j];
        }
      }
      LED_HSV[i][0].hue = t % 192;
      LED_HSV[i + 3][0].hue = t % 192;
    }
    else
    {
      // HAL_UART_Transmit_IT(&huart6, (uint8_t *)&"test", 5);
      LED_HSV[i][0].val = 0;
      LED_HSV[i + 3][0].val = 0;
    }
    // HAL_UART_Transmit_IT(&huart6, (uint8_t *)&LED_HSV[0][0].hue, 1);
    // HAL_Delay(1);
    // HAL_UART_Transmit_IT(&huart6, (uint8_t *)&LED_HSV[0][0].val, 1);
    // HAL_Delay(1);
    // HAL_UART_Transmit_IT(&huart6, (uint8_t *)&LED_HSV[0][0].sat, 1);
    hsv2rgb_raw_C(&LED_HSV[i][0], &LED_RGB[i][0]);
    hsv2rgb_raw_C(&LED_HSV[i + 3][0], &LED_RGB[i + 3][0]);
  }
  // HAL_UART_Transmit_IT(&huart6, (uint8_t *)&LED_RGB[0][0].r, 1);
  // HAL_Delay(1);
  // HAL_UART_Transmit_IT(&huart6, (uint8_t *)&LED_RGB[0][0].g, 1);
  // HAL_Delay(1);
  // HAL_UART_Transmit_IT(&huart6, (uint8_t *)&LED_RGB[0][0].b, 1);
  // HAL_UART_Transmit_IT(&huart6, (uint8_t *)&"test", 5);
  uint8_t GRB_Values[LED_strip_num * 3] = {0};
  memset(temp, 0, sizeof(temp));
  for (uint32_t i = 0; i < 24 * 4; i = i + 4)
  {

    temp[i] = 0xFF;
  }

  for (uint8_t x = 0; x < LED_strip_num; x++)
  {

    GRB_Values[x * 3 + 0] = LED_RGB[x][0].g;
    GRB_Values[x * 3 + 1] = LED_RGB[x][0].r;
    GRB_Values[x * 3 + 2] = LED_RGB[x][0].b;

    for (uint8_t GRB_channel = 0; GRB_channel < 3; GRB_channel++)
    {
      struct bit_handler *GRB_bithandle = (struct bit_handler *)(GRB_Values + x * 3 + GRB_channel);
      uint8_t index = GRB_channel * 8 * 4;
      temp[index + 1] |= GRB_bithandle->b0 << x;
      temp[index + 5] |= GRB_bithandle->b1 << x;
      temp[index + 9] |= GRB_bithandle->b2 << x;
      temp[index + 13] |= GRB_bithandle->b3 << x;
      temp[index + 17] |= GRB_bithandle->b4 << x;
      temp[index + 21] |= GRB_bithandle->b5 << x;
      temp[index + 25] |= GRB_bithandle->b6 << x;
      temp[index + 29] |= GRB_bithandle->b7 << x;

      temp[index + 2] |= GRB_bithandle->b0 << x;
      temp[index + 6] |= GRB_bithandle->b1 << x;
      temp[index + 10] |= GRB_bithandle->b2 << x;
      temp[index + 14] |= GRB_bithandle->b3 << x;
      temp[index + 18] |= GRB_bithandle->b4 << x;
      temp[index + 22] |= GRB_bithandle->b5 << x;
      temp[index + 26] |= GRB_bithandle->b6 << x;
      temp[index + 30] |= GRB_bithandle->b7 << x;
    }
  }
}
void _main()
{

  // dmaflag = 1;

  // HAL_Delay(600);
  // while ((HAL_DMA_GetState(&hdma_tim1_up) != HAL_DMA_STATE_READY) /*&& (HAL_DMA_GetState(&hdma_tim1_ch1) != HAL_DMA_STATE_READY)*/)
  // {
  //   // HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
  //   // HAL_Delay(20);
  // }
  // PS2_Data_Handle();
  // LED_Data_Convert();
  // struct CHSV ledhsv = {100, 255, 255};
  // struct CRGB ledrgb = {0, 0, 0};
  // for (uint32_t i = 0; i < 150 * 8; i++)
  // {
  //   hsv2rgb_raw_C(&ledhsv, &ledrgb);
  // }
  // HAL_LED_Transmit_Start_DMA(&htim1, (uint8_t *)LED_Data_Transmit, sizeof(LED_Data_Transmit));
  LED_Process();
  LED_Send();
  // HAL_Delay(1000);
}

#endif