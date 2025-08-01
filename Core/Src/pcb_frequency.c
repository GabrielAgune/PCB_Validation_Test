#include "pcb_frequency.h"
#include "tim.h" 

// Variável para contar quantas vezes o timer transbordou
static volatile uint32_t overflow_count = 0;

/**
 * @brief Inicia o Timer 1 com interrupção de update (overflow).
 */
void Frequency_Init(void)
{
  // Inicia o timer em modo de contagem e HABILITA a interrupção de update/overflow
  HAL_TIM_Base_Start_IT(&htim1);
}

/**
 * @brief Zera ambos os contadores (o do timer e o de overflows).
 */
void Frequency_Reset(void)
{
  __HAL_TIM_SET_COUNTER(&htim1, 0);
  overflow_count = 0;
}

/**
 * @brief Lê o valor atual do contador de pulsos do timer.
 */
uint32_t Frequency_Get_Pulse_Count(void)
{
  return __HAL_TIM_GET_COUNTER(&htim1);
}

/**
 * @brief Retorna o número de overflows que ocorreram.
 */
uint32_t Frequency_Get_Overflow_Count(void)
{
  return overflow_count;
}

/**
  * @brief  Callback: chamado pela HAL toda vez que o timer transborda (overflow).
  * @note   Esta função é chamada pela TIM1_UP_IRQHandler.
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  // Verifica se a interrupção veio do TIM1
  if (htim->Instance == TIM1)
  {
    overflow_count++; // Incrementa nosso contador de overflows
  }
}