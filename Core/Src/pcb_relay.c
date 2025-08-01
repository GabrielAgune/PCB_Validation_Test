#include "pcb_relay.h"

/**
  * @brief  Liga o rel� da PCB.
  */
void Relay_On(void)
{
  HAL_GPIO_WritePin(RELAY_CTRL_GPIO_Port, RELAY_CTRL_Pin, GPIO_PIN_SET);
}

/**
  * @brief  Desliga o rel� da PCB.
  */
void Relay_Off(void)
{
  HAL_GPIO_WritePin(RELAY_CTRL_GPIO_Port, RELAY_CTRL_Pin, GPIO_PIN_RESET);
}