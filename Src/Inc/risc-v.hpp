#pragma once

#include <cstdint>

static inline void __NOP() { __asm volatile ("nop"); }

static inline void __enable_irq()
{
    __asm volatile ("csrw 0x800, %0" : : "r" (0x6088));
}

static inline void __disable_irq()
{
    __asm volatile ("csrw 0x800, %0" : : "r" (0x6000));
}

namespace riscv 
{

  static inline void mret() { __asm volatile ("mret"); }

  struct csr
  {
    static inline void Set_MTVEC(uint32_t value)
    {	  
      __asm volatile ("csrw mtvec, %0" : : "r" (value));
	}
  };

} // namespace riscv 