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

  enum class EXCEPTIONS_MODE { UNIFIED_JUMP=0, UNIFIED_ADR=2, VTABLE_JUMPS=1, VTABLE_ADDR=3 };

  struct csr
  {
    static inline void SetMTVEC(const void *padr, EXCEPTIONS_MODE mode)
    {
      SetMTVEC((reinterpret_cast<uint32_t>(padr) & 0xFFFF'FFFC) + static_cast<uint32_t>(mode));
    }
  private:
    static inline void SetMTVEC(uint32_t value)
    {	  
      __asm volatile ("csrw mtvec, %0" : : "r" (value));
	}

  };

} // namespace riscv 