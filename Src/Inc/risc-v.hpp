#pragma once

#include <cstdint>

namespace riscv
{
#if __riscv_xlen==32 
    using uint_xlen_t = std::uint32_t;
#elif __riscv_xlen==64
    using uint_xlen_t = std::uint64_t;
#else
#error "riscv::csr: unknown __riscv_xlen"
#endif

  enum class CSR_REGS : uint16_t
  {
    marchid = 0xF12,   // Architecture number register
    mimpid = 0xF13,    // MRO Hardware implementation numbering register
    mstatus = 0x300,   // MRW Status register
    misa = 0x301,      // MRW Hardware instruction set register
    mtvec = 0x305,     // MRW Exception base address register
    mscratch = 0x340,  // MRW Machine mode staging register
    mepc = 0x341,      // MRW Exception program pointer register
    mcause = 0x342,    // MRW Exception cause register
    mtval = 0x343,     // MRW Exception value register
//      pmpcfg < i> 0x3A0 + i MRW PMP unit configuration register
//      pmpaddr < i> 0x3B0 + i MRW PMP unit address register
    fflags = 0x001,    // URW Floating - point exception flag register
    frm = 0x002,       // URW Floating - point rounding mode register
    fcsr = 0x003,      // URW Floating - point control and status register
    dcsr = 0x7B0,      // DRW Debug control and status registers
    dpc = 0x7B1,       // DRW Debug mode program pointer register
    dscratch0 = 0x7B2, // DRW Debug mode staging register 0
    dscratch1 = 0x7B3, // DRW Debug mode staging register 1
// Vendordefined CSRs
    gintenr = 0x800,   // URW Global interrupt enable register
    intsyscr = 0x804,  // URW Interrupt system control register
    corecfgr = 0xBC0   // MRW Microprocessor configuration register
  };

} // namespace riscv

#include "risc-v-csr.hpp"

static inline void __NOP() { __asm volatile ("nop"); }

static inline void __enable_irq()
{
  //riscv::CSR<riscv::CSR_REGS::mstatus>::set_bits<0x08>();
  riscv::CSR<riscv::CSR_REGS::gintenr>::set_bits<0x08>(); // Vendor defined "gintenr" CSR
}

static inline void __disable_irq()
{
  //riscv::CSR<riscv::CSR_REGS::mstatus>::clear_bits<0x08>();
  riscv::CSR<riscv::CSR_REGS::gintenr>::clear_bits<0x08>(); // Vendor defined "gintenr" CSR
}

static inline void NVIC_EnableIRQ(IRQn_Type IRQn)
{
  NVIC->IENR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));
}

static inline void NVIC_DisableIRQ(IRQn_Type IRQn)
{
  NVIC->IRER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));
}

static inline uint32_t NVIC_GetStatusIRQ(IRQn_Type IRQn)
{
    return((uint32_t)((NVIC->ISR[(uint32_t)(IRQn) >> 5] & (1 << ((uint32_t)(IRQn) & 0x1F))) ? 1 : 0));
}

namespace riscv 
{
  static inline void SetGP(uint_xlen_t *value)
  {
    __asm volatile (".option push;"
                    ".option norelax;"
                    "la gp, %0;"
                    ".option pop;"
                    : : "" (value));
  }

  static inline void SetSP(uint_xlen_t *value)
  {
    __asm volatile ("la sp, %0;" : : "" (value));
  }

  static inline void mret() { __asm volatile ("mret"); }

  enum class EXCEPTIONS_MODE { UNIFIED_JUMP=0, UNIFIED_ADR=2, VTABLE_JUMPS=1, VTABLE_ADDR=3 };

  static inline void SetMTVEC(const void *padr, EXCEPTIONS_MODE mode)
  {
    auto val = (reinterpret_cast<uint32_t>(padr) & 0xFFFF'FFFC) + static_cast<uint32_t>(mode);
    CSR<CSR_REGS::mtvec>::write(val);
  }

  static inline void SetMTVEC(uint_xlen_t value)
  {
    CSR<CSR_REGS::mtvec>::write(value);
  }

  enum class MSTATUS_FS // Floating-point unit status
  {
	Off = 0,
    Initial = 1<<13,
    Clean = 2<<13,
    Dirty = 3<<13
  };

  enum class MSTATUS_MIE  // Machine mode interrupt enable
  {
	Enable = 8,
    Disable = 0
  };

  static inline void SetMSTATUS(MSTATUS_FS fs, MSTATUS_MIE mie)
  {
    auto val = (riscv::uint_xlen_t)fs + (riscv::uint_xlen_t)mie;
    CSR<CSR_REGS::mstatus>::write(val);
  }

} // namespace riscv 

namespace QingKeV4
{
  // ======= INTSYSCR =======
  enum class HWSTKOVEN // Interrupt enable after HPE overflow
  { 
    Enable = 0x10, // Interrupts are still executable after a hardware stack overflow6
    Disable = 0    // Global interrupts are turned off after a HPE overflow
  };

  enum class PMTCFG // Interrupt nesting depth configuration
  {
    NoNesting = 0, // No nesting, the number of preemption bits is 0
    _2 = 1<<2,     // 2 levels of nesting, with 1 number of preemption bits
    _4 = 2<<2,     // 4 levels of nesting, with 2 number of preemption bits
    _8 = 3<<2      // 8 levels of nesting, with 3 number of preemption bits 
  };

  enum class INESTEN  // Interrupt nesting enable
  {
    Enable = 2, // Interrupt nesting function enabled
    Disable = 0 // Interrupt nesting function off
  };

  enum class HWSTKEN // HPE enable
  {
    Enable = 1, // HPE function enabled
    Disable = 0 // HPE function off
  };

  static inline void SetINTSYSCR(HWSTKOVEN hwstkoven, PMTCFG pmtcfg, INESTEN inesten, HWSTKEN hwstken)
  {
    auto val = (riscv::uint_xlen_t)hwstkoven + (riscv::uint_xlen_t)pmtcfg
             + (riscv::uint_xlen_t)inesten + (riscv::uint_xlen_t)hwstken;
    riscv::CSR<riscv::CSR_REGS::intsyscr>::write<0x1F>(val);
  }



} // namespace QingKeV4
