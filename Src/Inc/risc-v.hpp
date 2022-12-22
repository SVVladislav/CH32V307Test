#pragma once

#include <cstdint>

#ifndef __I
#define     __I     volatile const  // defines 'read only' permissions
#define     __O     volatile        // defines 'write only' permissions (dosn't work)
#define     __IO    volatile        // defines 'read / write' permissions
#endif

namespace riscv
{
  #if __riscv_xlen==32
    using uint_xlen_t = std::uint32_t;
  #elif __riscv_xlen==64
    using uint_xlen_t = std::uint64_t;
  #else
    #error "riscv::csr: unknown __riscv_xlen"
  #endif

  static inline void SetGP(uint_xlen_t* value)
  {
    __asm volatile (".option push;"
    ".option norelax;"
      "la gp, %0;"
      ".option pop;"
      : : "i" (value));
  }

  static inline void SetSP(uint_xlen_t* value)
  {
    __asm volatile ("la sp, %0;" : : "i" (value));
  }

  static inline void mret() { __asm volatile ("mret"); }

  static inline void __NOP() { __asm volatile ("nop"); }

  static inline void __BKPT() { __asm volatile ("ebreak"); }

  // Volume I : RISC-V User-Level ISA V2.2
  // 2.8 Control and Status Register Instructions
  template <uint16_t csr>
  struct CSR
  {
    static_assert(csr <= 0xFFF, "Wrong CSR");

    static constexpr uint_xlen_t CSR_IMM_OP_MASK = 0x01F;

    // RV32I Atomic Read/Write CSR
    static uint_xlen_t read_write(uint_xlen_t new_value)
    {
      uint_xlen_t prev_value;
      __asm volatile ("csrrw    %0, %1, %2"
                      : "=r" (prev_value) // output: register %0
                      : "i" (csr),        // input : csr %1
                        "r" (new_value)   // input : register %2
                      :                   // clobbers: none
                     );
      return prev_value;
    }

    // RV32I Atomic Read/Write CSR immediate
    static uint_xlen_t read_write_imm(uint_xlen_t new_value)
    {
      uint_xlen_t prev_value;
      __asm volatile ("csrrwi    %0, %1, %2"
                      : "=r" (prev_value) // output: register %0
                      : "i" (csr),        // input : csr %1
                        "K" (new_value)   // input : immediate %2
                      :                   // clobbers: none
                     );
      return prev_value;
    }

    // RV32I Atomic Read CSR
    static uint_xlen_t read()
    {
      uint_xlen_t ret_value;
      __asm volatile ("csrr    %0, %1"
                      : "=r" (ret_value) // output: register %0
                      : "i" (csr)         // input : csr %1
                      :                   // clobbers: none
                     );
      return ret_value;
    }

    // RV32I Atomic Write CSR immediate
    static void write_imm(uint_xlen_t value)
    {
      __asm volatile ("csrwi    %0, %1"
                      :
                      : "i" (csr),    // input : csr %1
                        "K" (value)   // input : immediate %2
                      :               // clobbers: none
                     );
    }

    // RV32I Atomic Read and Set Bits in CSR
    static inline uint_xlen_t read_set_bits(uint_xlen_t mask)
    {
      uint_xlen_t prev_value;
      __asm volatile ("csrrs    %0, %1, %2"
                      : "=r" (prev_value) // output: register %0
                      : "i" (csr),        // input : csr %1
                        "r" (mask)        // input : register %2
                      :                   // clobbers: none
                     );
      return prev_value;
    }

    // RV32I Atomic Read and Set Bits in CSR immediate
    static inline uint_xlen_t read_set_bits_imm(uint_xlen_t mask)
    {
      uint_xlen_t prev_value;
      __asm volatile ("csrrsi    %0, %1, %2"
                      : "=r" (prev_value) // output: register %0
                      : "i" (csr),        // input : csr %1
                        "K" (mask)        // input : immediate %2
                      :                   // clobbers: none
                     );
      return prev_value;
    }

    // RV32I Atomic Read and Clear Bits in CSR
    static inline uint_xlen_t read_clear_bits(uint_xlen_t mask)
    {
      uint_xlen_t prev_value;
      __asm volatile ("csrrc    %0, %1, %2"
                      : "=r" (prev_value) // output: register %0
                      : "i" (csr),        // input : csr %1
                        "r" (mask)        // input : register %2
                      :                   // clobbers: none
                     );
      return prev_value;
    }

    // RV32I Atomic Read and Clear Bits in CSR immediate
    static inline uint_xlen_t read_clear_bits_imm(uint_xlen_t mask)
    {
      uint_xlen_t prev_value;
      __asm volatile ("csrrci    %0, %1, %2"
                      : "=r" (prev_value) // output: register %0
                      : "i" (csr),        // input : csr %1
                        "K" (mask)        // input : immediate %2
                      :                   // clobbers: none
                     );
      return prev_value;
    }

    // RV32I Atomic Set Bits in CSR
    static inline void set_bits(uint_xlen_t mask)
    {
      __asm volatile ("csrs    %0, %1"
                      :
                      : "i" (csr),        // input : csr %0
                        "r" (mask)        // input : register %1
                      :                   // clobbers: none
                     );
    }

    // RV32I Atomic Set Bits in CSR immediate
    static inline void set_bits_imm(uint_xlen_t mask)
    {
        __asm volatile ("csrsi    %0, %1"
                        :
                        : "i" (csr),        // input : csr %0
                          "K" (mask)        // input : immediate %1
                        :                   // clobbers: none
                       );
    }
    // RV32I Atomic Clear Bits in CSR
    static inline void clear_bits(uint_xlen_t mask)
    {
      __asm volatile ("csrc    %0, %1"
                      :
                      : "i" (csr),        // input : csr %0
                        "r" (mask)        // input : register %1
                      :                   // clobbers: none
                     );
    }

    // RV32I Atomic Clear Bits in CSR immediate
    static inline void clear_bits_imm(uint_xlen_t mask)
    {
      __asm volatile ("csrci    %0, %1"
                      :
                      : "i" (csr),        // input : csr %0
                        "K" (mask)        // input : immediate %1
                      :                   // clobbers: none
                     );
    }

    template <uint_xlen_t MASK=0xFFFF'FFFF>
    static void write(uint_xlen_t value)
    {
        if constexpr ((MASK & ~CSR_IMM_OP_MASK) == 0)
          write_imm(value);
        else
          write_(value);
    }

    template <uint_xlen_t MASK>
    static inline void set_bits()
    {
      if constexpr ((MASK & CSR_IMM_OP_MASK) == MASK)
        set_bits_imm(MASK);
      else
        set_bits(MASK);
    }

    template <uint_xlen_t MASK>
    static inline void clear_bits()
    {
      if constexpr ((MASK & CSR_IMM_OP_MASK) == MASK)
        clear_bits_imm(MASK);
      else
        clear_bits(MASK);
    }

  private:
    // RV32I Atomic Write CSR
    static void write_(uint_xlen_t value)
    {
      __asm volatile ("csrw    %0, %1"
                      :
                      : "i" (csr),    // input : csr %1
                        "r" (value)   // input : register %2
                      :               // clobbers: none
                     );
    }

  };

} // namespace riscv
