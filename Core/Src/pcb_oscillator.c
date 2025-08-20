#include "pcb_oscillator.h"

/**
  * @brief  Lê o estado lógico atual do pino do sinal CAMARA.
  * @retval GPIO_PIN_RESET (0) ou GPIO_PIN_SET (1).
  */
GPIO_PinState Oscillator_Get_State(void)
{
  // A leitura de GPIO não funciona em um pino configurado para Alternate Function (Timer).
  // Esta função não é mais útil. O comando "osc frec" é o correto.
  return GPIO_PIN_RESET;
}