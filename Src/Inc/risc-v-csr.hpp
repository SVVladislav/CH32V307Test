#pragma once

namespace riscv
{

  // Volume I : RISC-V User-Level ISA V2.2
  // 2.8 Control and Status Register Instructions
  template <uint32_t csr>
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

    // RV32I Atomic Write CSR
    static void write(uint_xlen_t new_value)
    {
      __asm volatile ("csrw    %0, %1"
                      : 
                      : "i" (csr),        // input : csr %1
                        "r" (new_value)   // input : register %2
                      :                   // clobbers: none 
                     );
    }

    // RV32I Atomic Write CSR immediate
    static void write_imm(uint_xlen_t new_value)
    {
      __asm volatile ("csrwi    %0, %1"
                      :
                      : "i" (csr),        // input : csr %1
                        "K" (new_value)   // input : immediate %2
                      :                   // clobbers: none 
                     );
    }

    // RV32I Atomic Read and Set Bits in CSR
    static inline uint_xlen_t read_set_bits(uint_xlen_t mask)
    {
      uint_xlen_t prev_value;
      __asm__ volatile ("csrrs    %0, %1, %2"
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
      __asm__ volatile ("csrrsi    %0, %1, %2"
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
      __asm__ volatile ("csrrc    %0, %1, %2"
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
      __asm__ volatile ("csrrci    %0, %1, %2"
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
      __asm__ volatile ("csrs    %0, %1"
                        : 
                        : "i" (csr),        // input : csr %0
                          "r" (mask)        // input : register %1
                        :                   // clobbers: none 
            );
    }

    // RV32I Atomic Set Bits in CSR immediate
    static inline void set_bits_imm(uint_xlen_t mask)
    {
        __asm__ volatile ("csrsi    %0, %1"
                          :
                          : "i" (csr),        // input : csr %0
                            "K" (mask)        // input : immediate %1
                          :                   // clobbers: none 
                         );
    }
    // RV32I Atomic Clear Bits in CSR
    static inline void clear_bits(uint_xlen_t mask)
    {
      __asm__ volatile ("csrc    %0, %1"
                        :
                        : "i" (csr),        // input : csr %0
                          "r" (mask)        // input : register %1
                        :                   // clobbers: none 
                       );
    }

    // RV32I Atomic Clear Bits in CSR immediate
    static inline void clear_bits_imm(uint_xlen_t mask)
    {
      __asm__ volatile ("csrci    %0, %1"
                        :
                        : "i" (csr),        // input : csr %0
                          "K" (mask)        // input : immediate %1
                        :                   // clobbers: none 
                       );
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

  };

} // namespace riscv
