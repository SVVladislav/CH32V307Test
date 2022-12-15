#include "main.hpp"

#include <cstdint>

#define __interrupt extern "C" void __attribute__((naked))

int main()
{
  NVIC_EnableIRQ(SysTicK_IRQn);
  __enable_irq();
  LED1::On();
  for (;;)
  {
  };
}

__interrupt SysTick_Handler()
{
  SysTick->SR = 0;
  LED2::Toggle();
  riscv::mret();
}