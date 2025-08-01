#include "pcb_oscillator.h"

/**
  * @brief  Lê o estado lógico atual do pino do sinal CAMARA.
  * @retval GPIO_PIN_RESET (0) ou GPIO_PIN_SET (1).
  */
GPIO_PinState Oscillator_Get_State(void)
{
  return HAL_GPIO_ReadPin(CAMARA_IN_GPIO_Port, CAMARA_IN_Pin);
}