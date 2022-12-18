#pragma once

#include <cstdint>

#include "risc-v.hpp"

#ifndef WCH_INTERRUPT_FAST
// xpack-riscv-none-elf-gcc toolchain
#define __interrupt extern "C" void __attribute__((naked))
#define interrupt_return riscv::mret()
#else
// MounRiver modified riscv-none-embed-gcc toolchain
#define __interrupt extern "C" void __attribute__((interrupt("WCH-Interrupt-fast")))
#define interrupt_return return
#endif

namespace QingKeV4
{
// ======================================================================
// QingKe V4 microprocessor Programmable Fast Interrupt Controller (PFIC)
// ======================================================================
  struct PFIC_Type
  {
    __I  uint32_t ISR[8];
    __I  uint32_t IPR[8];
    __IO uint32_t ITHRESDR;
    __IO uint32_t RESERVED;
    __IO uint32_t CFGR;
    __I  uint32_t GISR;
    uint8_t VTFIDR[4];
    uint8_t RESERVED0[12];
    __IO uint32_t VTFADDR[4];
    uint8_t RESERVED1[0x90];
    __O  uint32_t IENR[8];
    uint8_t RESERVED2[0x60];
    __O  uint32_t IRER[8];
    uint8_t RESERVED3[0x60];
    __O  uint32_t IPSR[8];
    uint8_t RESERVED4[0x60];
    __O  uint32_t IPRR[8];
    uint8_t RESERVED5[0x60];
    __IO uint32_t IACTR[8];
    uint8_t RESERVED6[0xE0];
    __IO uint8_t IPRIOR[256];
    uint8_t RESERVED7[0x810];
    __IO uint32_t SCTLR;
  };

  /// Memory mapped structure for SysTick
  struct SysTick_Type
  {
    __IO uint32_t CTLR;
    __IO uint32_t SR;
    __IO uint64_t CNT;
    __IO uint64_t CMP;
  };

#define PFIC            ((QingKeV4::PFIC_Type *) 0xE000E000)
#define NVIC            PFIC
#define NVIC_KEY1       ((uint32_t)0xFA050000)
#define NVIC_KEY2       ((uint32_t)0xBCAF0000)
#define NVIC_KEY3       ((uint32_t)0xBEEF0000)
#define SysTick         ((QingKeV4::SysTick_Type *) 0xE000F000)

  enum CSR_REGS : uint16_t
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
//    pmpcfg < i> 0x3A0 + i MRW PMP unit configuration register
//    pmpaddr < i> 0x3B0 + i MRW PMP unit address register
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

  enum class EXCEPTIONS_MODE { UNIFIED_JUMP=0, UNIFIED_ADR=2, VTABLE_JUMPS=1, VTABLE_ADDR=3 };

  static inline void SetMTVEC(const void *padr, EXCEPTIONS_MODE mode)
  {
    auto val = (reinterpret_cast<uint32_t>(padr) & 0xFFFF'FFFC) + static_cast<uint32_t>(mode);
    riscv::CSR<CSR_REGS::mtvec>::write(val);
  }

  static inline void SetMTVEC(riscv::uint_xlen_t value)
  {
    riscv::CSR<CSR_REGS::mtvec>::write(value);
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
    riscv::CSR<CSR_REGS::mstatus>::write(val);
  }

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
    riscv::CSR<CSR_REGS::intsyscr>::write<0x1F>(val);
  }

  // Enable Interrupt
  // IRQn : Interrupt Numbers
  static inline void NVIC_EnableIRQ(uint32_t IRQn)
  {
    NVIC->IENR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));
  }

  // Disable Interrupt
  // IRQn : Interrupt Numbers
  static inline void NVIC_DisableIRQ(uint32_t IRQn)
  {
    NVIC->IRER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));
  }

  // Get Interrupt Enable State
  // IRQn : Interrupt Numbers
  // return  1 - Interrupt Enable
  //         0 - Interrupt Disable
  static inline uint32_t NVIC_GetStatusIRQ(uint32_t IRQn)
  {
    return((uint32_t)((NVIC->ISR[(uint32_t)(IRQn) >> 5] & (1 << ((uint32_t)(IRQn) & 0x1F))) ? 1 : 0));
  }

  // Get Interrupt Pending State
  // IRQn: Interrupt Numbers
  // return  1 - Interrupt Pending Enable
  //         0 - Interrupt Pending Disable
  static inline uint32_t NVIC_GetPendingIRQ(uint32_t IRQn)
  {
    return((uint32_t)((NVIC->IPR[(uint32_t)(IRQn) >> 5] & (1 << ((uint32_t)(IRQn) & 0x1F))) ? 1 : 0));
  }

  // Set Interrupt Pending
  // IRQn: Interrupt Numbers
  static inline void NVIC_SetPendingIRQ(uint32_t IRQn)
  {
    NVIC->IPSR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));
  }

  // Clear Interrupt Pending
  // IRQn: Interrupt Numbers
  static inline void NVIC_ClearPendingIRQ(uint32_t IRQn)
  {
    NVIC->IPRR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));
  }

  // Get Interrupt Active State
  // IRQn: Interrupt Numbers
  // return  1 - Interrupt Active
  //         0 - Interrupt No Active
  static inline uint32_t NVIC_GetActive(uint32_t IRQn)
  {
    return((uint32_t)((NVIC->IACTR[(uint32_t)(IRQn) >> 5] & (1 << ((uint32_t)(IRQn) & 0x1F))) ? 1 : 0));
  }

  // Set Interrupt Priority
  // IRQn - Interrupt Numbers
  // priority -
  //            bit7 - pre-emption priority
  //            bit6~bit4 - subpriority
  static inline void NVIC_SetPriority(uint32_t IRQn, uint8_t priority)
  {
    NVIC->IPRIOR[(uint32_t)(IRQn)] = priority;
  }

  // Wait for Interrupt
  __attribute__((always_inline)) static inline void __WFI(void)
  {
    NVIC->SCTLR &= ~(1 << 3);   // wfi
    asm volatile ("wfi");
  }

  // Wait for Events
  __attribute__((always_inline)) static inline void __WFE(void)
  {
    uint32_t t = NVIC->SCTLR;
    NVIC->SCTLR |= (1 << 3) | (1 << 5);     // (wfi->wfe)+(__sev)
    NVIC->SCTLR = (NVIC->SCTLR & ~(1 << 5)) | (t & (1 << 5));
    asm volatile ("wfi");
    asm volatile ("wfi");
  }

  // Initiate a system reset request
  static inline void NVIC_SystemReset(void)
  {
    NVIC->CFGR = NVIC_KEY3 | (1 << 7);
  }

  // Set VTF Interrupt
  //   addr - VTF interrupt service function base address.
  //   IRQn -Interrupt Numbers
  //   num - VTF Interrupt Numbers
  //   NewState - DISABLE or ENABLE
  static inline void SetVTFIRQ(uint32_t addr, uint32_t IRQn, uint8_t num, bool NewState = true)
  {
    if (num > 3)  return;
    if (NewState)
    {
      NVIC->VTFIDR[num] = IRQn;
      NVIC->VTFADDR[num] = ((addr & 0xF00FFFFE) | 0x1);
    }
    else
    {
      NVIC->VTFIDR[num] = IRQn;
      NVIC->VTFADDR[num] = ((addr & 0xF00FFFFE) & (~0x1));
    }
  }

  static inline void EnableVTFIRQ(uint8_t num)
  {
    NVIC->VTFADDR[num] |= 0x1;
  }

  static inline void DisableVTFIRQ(uint8_t num)
  {
    NVIC->VTFADDR[num] &= ~0x1;
  }

} // namespace QingKeV4


// Enable Global Interrupt
static inline void __enable_irq()
{
  riscv::CSR<QingKeV4::CSR_REGS::gintenr>::set_bits<0x08>();
}

// Disable Global Interrupt
static inline void __disable_irq()
{
  riscv::CSR<QingKeV4::CSR_REGS::gintenr>::clear_bits<0x08>();
}
