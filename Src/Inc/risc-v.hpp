#pragma once

#include <cstdint>

namespace riscv
{
#if __riscv_xlen==32 
    using uint_xlen_t = std::uint32_t;
    using uint_csr32_t = std::uint32_t;
    using uint_csr64_t = std::uint32_t;
#elif __riscv_xlen==64
    using uint_xlen_t = std::uint64_t;
    using uint_csr32_t = std::uint32_t;
    using uint_csr64_t = std::uint64_t;
#else
    using uint_xlen_t = std::uint32_t;
    using uint_csr32_t = std::uint32_t;
    using uint_csr64_t = std::uint32_t;
#error "riscv::csr: unknown __riscv_xlen"
#endif
}

#include "risc-v-csr.hpp"

static inline void __NOP() { __asm volatile ("nop"); }

static inline void __enable_irq()
{
  //__asm volatile ("csrsi mstatus, 0x8");
  riscv::CSR<0x800>::set_bits<0x08>(); // Vendor defined "gintenr" CSR 
}

static inline void __disable_irq()
{
  //__asm volatile ("csrci mstatus, 0x8");
  riscv::CSR<0x800>::clear_bits<0x08>(); // Vendor defined "gintenr" CSR 
}

namespace riscv 
{
  static inline void SetGP(uint32_t *value)
  {
    __asm volatile (".option push;"
                    ".option norelax;"
                    "la gp, %0;"
                    ".option pop;"
                    : : "" (value));
  }

  static inline void SetSP(uint32_t* value)
  {
      __asm volatile ("la sp, %0;" : : "" (value));
  }

  static inline void mret() { __asm volatile ("mret"); }

  enum class EXCEPTIONS_MODE { UNIFIED_JUMP=0, UNIFIED_ADR=2, VTABLE_JUMPS=1, VTABLE_ADDR=3 };

  struct csr
  {
    static inline void SetMTVEC(const void *padr, EXCEPTIONS_MODE mode)
    {
      SetMTVEC((reinterpret_cast<uint32_t>(padr) & 0xFFFF'FFFC) + static_cast<uint32_t>(mode));
    }

    static inline void SetMSTATUS(uint32_t value)
    {
      __asm volatile ("csrw mstatus, %0" : : "r" (value));
    }

  private:
    static inline void SetMTVEC(uint32_t value)
    {	  
      __asm volatile ("csrw mtvec, %0" : : "r" (value));
	}

  };

} // namespace riscv 