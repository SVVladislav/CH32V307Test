#pragma once
/********************************** (C) COPYRIGHT  *******************************
* File Name          : core_riscv.h
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/06/06
* Description        : RISC-V Core Peripheral Access Layer Header File for CH32V30x
*******************************************************************************/
#ifndef __CORE_RISCV_H__
#define __CORE_RISCV_H__

/* IO definitions */
#ifdef __cplusplus
  #define     __I     volatile                /* defines 'read only' permissions */
#else
  #define     __I     volatile const          /* defines 'read only' permissions */
#endif
#define     __O     volatile                  /* defines 'write only' permissions */
#define     __IO    volatile                  /* defines 'read / write' permissions */

/* Standard Peripheral Library old types (maintained for legacy purpose) */
typedef __I uint64_t vuc64;  /* Read Only */
typedef __I uint32_t vuc32;  /* Read Only */
typedef __I uint16_t vuc16;  /* Read Only */
typedef __I uint8_t vuc8;   /* Read Only */

typedef const uint64_t uc64;  /* Read Only */
typedef const uint32_t uc32;  /* Read Only */
typedef const uint16_t uc16;  /* Read Only */
typedef const uint8_t uc8;   /* Read Only */

typedef __I int64_t vsc64;  /* Read Only */
typedef __I int32_t vsc32;  /* Read Only */
typedef __I int16_t vsc16;  /* Read Only */
typedef __I int8_t vsc8;   /* Read Only */

typedef const int64_t sc64;  /* Read Only */
typedef const int32_t sc32;  /* Read Only */
typedef const int16_t sc16;  /* Read Only */
typedef const int8_t sc8;   /* Read Only */

typedef __IO uint64_t  vu64;
typedef __IO uint32_t  vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;

typedef uint64_t  u64;
typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef __IO int64_t  vs64;
typedef __IO int32_t  vs32;
typedef __IO int16_t  vs16;
typedef __IO int8_t   vs8;

typedef int64_t  s64;
typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;

//#define   RV_STATIC_INLINE  static  inline

/* Core_Exported_Functions */  
extern uint32_t __get_FFLAGS(void);
extern void __set_FFLAGS(uint32_t value);
extern uint32_t __get_FRM(void);
extern void __set_FRM(uint32_t value);
extern uint32_t __get_FCSR(void);
extern void __set_FCSR(uint32_t value);
extern uint32_t __get_MSTATUS(void);
extern void __set_MSTATUS(uint32_t value);
extern uint32_t __get_MISA(void);
extern void __set_MISA(uint32_t value);
extern uint32_t __get_MIE(void);
extern void __set_MIE(uint32_t value);
extern uint32_t __get_MTVEC(void);
//extern void __set_MTVEC(uint32_t value);
extern uint32_t __get_MSCRATCH(void);
extern void __set_MSCRATCH(uint32_t value);
extern uint32_t __get_MEPC(void);
extern void __set_MEPC(uint32_t value);
extern uint32_t __get_MCAUSE(void);
extern void __set_MCAUSE(uint32_t value);
extern uint32_t __get_MTVAL(void);
extern void __set_MTVAL(uint32_t value);
extern uint32_t __get_MIP(void);
extern void __set_MIP(uint32_t value);
extern uint32_t __get_MCYCLE(void);
extern void __set_MCYCLE(uint32_t value);
extern uint32_t __get_MCYCLEH(void);
extern void __set_MCYCLEH(uint32_t value);
extern uint32_t __get_MINSTRET(void);
extern void __set_MINSTRET(uint32_t value);
extern uint32_t __get_MINSTRETH(void);
extern void __set_MINSTRETH(uint32_t value);
extern uint32_t __get_MVENDORID(void);
extern uint32_t __get_MARCHID(void);
extern uint32_t __get_MIMPID(void);
extern uint32_t __get_MHARTID(void);

#endif // __CORE_RISCV_H__