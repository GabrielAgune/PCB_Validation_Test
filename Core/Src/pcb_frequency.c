#include "pcb_frequency.h"
#include "tim.h"  // Garante acesso ao handle htim1

/**
 * @brief Inicia o Timer 1 no modo de contagem de pulsos.
 */
void Frequency_Init(void)
{
  // Inicia o timer. Ele vai contar os pulsos do pino PA8 em background.
  HAL_TIM_Base_Start(&htim1);
}

/**
 * @brief Zera o contador de pulsos do timer.
 */
void Frequency_Reset(void)
{
  // __HAL_TIM_SET_COUNTER é uma macro rápida para escrever 0 no contador.
  __HAL_TIM_SET_COUNTER(&htim1, 0);
}

/**
 * @brief Lê o valor atual do contador de pulsos do timer.
 */
uint32_t Frequency_Get_Pulse_Count(void)
{
  // __HAL_TIM_GET_COUNTER é uma macro rápida para ler o contador.
  return __HAL_TIM_GET_COUNTER(&htim1);
}