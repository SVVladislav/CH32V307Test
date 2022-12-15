#include "main.hpp"

#include <cstdint>

#define __interrupt extern "C" void __attribute__((naked))

volatile uint32_t x;

int main()
{

//  __enable_irq();
	LED1::On();
	LED2::On();

  for (;;)
  {

  };
}

__interrupt SysTick_Handler()
{
  for (uint32_t i{}; i < 1000; i++) x = i;
  riscv::mret();
}