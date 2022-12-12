#include "main.hpp"

#include <cstdint>

#define __interrupt extern "C" void __attribute__((naked))

int main()
{
  __enable_irq();
  for (;;);
}

volatile uint32_t x;

__interrupt SysTick_Handler()
{
  for (uint32_t i{}; i < 1000; i++) x = i;
  riscv::mret();
}