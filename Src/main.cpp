#include "main.hpp"

using namespace QingKeV4;



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
  interrupt_return;
}