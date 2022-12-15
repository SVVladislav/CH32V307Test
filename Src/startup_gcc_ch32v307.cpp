#include <cstddef>

#include "CH32/ch32v30x.h"
#include "risc-v.hpp"

#ifdef __cplusplus
extern "C" {
#endif

int main();
void SystemInit();
void Reset_Handler();
void Default_Handler();

void __attribute__((used, naked, section(".init"))) _start(void)
{
  extern uint32_t __global_pointer$;
  extern uint32_t _eusrstack;
  riscv::SetGP(&__global_pointer$);
  riscv::SetSP(&_eusrstack);
  __asm volatile ("j Reset_Handler;");
}

void NMI_Handler()                 __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler()           __attribute__((weak, alias("Default_Handler")));
void Ecall_M_Mode_Handler()        __attribute__((weak, alias("Default_Handler")));
void Ecall_U_Mode_Handler()        __attribute__((weak, alias("Default_Handler")));
void Break_Point_Handler()         __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler()             __attribute__((weak, alias("Default_Handler")));
void SW_handler()                  __attribute__((weak, alias("Default_Handler")));
void WWDG_IRQHandler()             __attribute__((weak, alias("Default_Handler")));
void PVD_IRQHandler()              __attribute__((weak, alias("Default_Handler")));
void TAMPER_IRQHandler()           __attribute__((weak, alias("Default_Handler")));
void RTC_IRQHandler()              __attribute__((weak, alias("Default_Handler")));
void FLASH_IRQHandler()            __attribute__((weak, alias("Default_Handler")));
void RCC_IRQHandler()              __attribute__((weak, alias("Default_Handler")));
void EXTI0_IRQHandler()            __attribute__((weak, alias("Default_Handler")));
void EXTI1_IRQHandler()            __attribute__((weak, alias("Default_Handler")));
void EXTI2_IRQHandler()            __attribute__((weak, alias("Default_Handler")));
void EXTI3_IRQHandler()            __attribute__((weak, alias("Default_Handler")));
void EXTI4_IRQHandler()            __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel1_IRQHandler()    __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel2_IRQHandler()    __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel3_IRQHandler()    __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel4_IRQHandler()    __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel5_IRQHandler()    __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel6_IRQHandler()    __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel7_IRQHandler()    __attribute__((weak, alias("Default_Handler")));
void ADC1_2_IRQHandler()           __attribute__((weak, alias("Default_Handler")));
void USB_HP_CAN1_TX_IRQHandler()   __attribute__((weak, alias("Default_Handler")));
void USB_LP_CAN1_RX0_IRQHandler()  __attribute__((weak, alias("Default_Handler")));
void CAN1_RX1_IRQHandler()         __attribute__((weak, alias("Default_Handler")));
void CAN1_SCE_IRQHandler()         __attribute__((weak, alias("Default_Handler")));
void EXTI9_5_IRQHandler()          __attribute__((weak, alias("Default_Handler")));
void TIM1_BRK_IRQHandler()         __attribute__((weak, alias("Default_Handler")));
void TIM1_UP_IRQHandler()          __attribute__((weak, alias("Default_Handler")));
void TIM1_TRG_COM_IRQHandler()     __attribute__((weak, alias("Default_Handler")));
void TIM1_CC_IRQHandler()          __attribute__((weak, alias("Default_Handler")));
void TIM2_IRQHandler()             __attribute__((weak, alias("Default_Handler")));
void TIM3_IRQHandler()             __attribute__((weak, alias("Default_Handler")));
void TIM4_IRQHandler()             __attribute__((weak, alias("Default_Handler")));
void I2C1_EV_IRQHandler()          __attribute__((weak, alias("Default_Handler")));
void I2C1_ER_IRQHandler()          __attribute__((weak, alias("Default_Handler")));
void I2C2_EV_IRQHandler()          __attribute__((weak, alias("Default_Handler")));
void I2C2_ER_IRQHandler()          __attribute__((weak, alias("Default_Handler")));
void SPI1_IRQHandler()             __attribute__((weak, alias("Default_Handler")));
void SPI2_IRQHandler()             __attribute__((weak, alias("Default_Handler")));
void USART1_IRQHandler()           __attribute__((weak, alias("Default_Handler")));
void USART2_IRQHandler()           __attribute__((weak, alias("Default_Handler")));
void USART3_IRQHandler()           __attribute__((weak, alias("Default_Handler")));
void EXTI15_10_IRQHandler()        __attribute__((weak, alias("Default_Handler")));
void RTCAlarm_IRQHandler()         __attribute__((weak, alias("Default_Handler")));
void USBWakeUp_IRQHandler()        __attribute__((weak, alias("Default_Handler")));
void TIM8_BRK_IRQHandler()         __attribute__((weak, alias("Default_Handler")));
void TIM8_UP_IRQHandler()          __attribute__((weak, alias("Default_Handler")));
void TIM8_TRG_COM_IRQHandler()     __attribute__((weak, alias("Default_Handler")));
void TIM8_CC_IRQHandler()          __attribute__((weak, alias("Default_Handler")));
void RNG_IRQHandler()              __attribute__((weak, alias("Default_Handler")));
void FSMC_IRQHandler()             __attribute__((weak, alias("Default_Handler")));
void SDIO_IRQHandler()             __attribute__((weak, alias("Default_Handler")));
void TIM5_IRQHandler()             __attribute__((weak, alias("Default_Handler")));
void SPI3_IRQHandler()             __attribute__((weak, alias("Default_Handler")));
void UART4_IRQHandler()            __attribute__((weak, alias("Default_Handler")));
void UART5_IRQHandler()            __attribute__((weak, alias("Default_Handler")));
void TIM6_IRQHandler()             __attribute__((weak, alias("Default_Handler")));
void TIM7_IRQHandler()             __attribute__((weak, alias("Default_Handler")));
void DMA2_Channel1_IRQHandler()    __attribute__((weak, alias("Default_Handler")));
void DMA2_Channel2_IRQHandler()    __attribute__((weak, alias("Default_Handler")));
void DMA2_Channel3_IRQHandler()    __attribute__((weak, alias("Default_Handler")));
void DMA2_Channel4_IRQHandler()    __attribute__((weak, alias("Default_Handler")));
void DMA2_Channel5_IRQHandler()    __attribute__((weak, alias("Default_Handler")));
void ETH_IRQHandler()              __attribute__((weak, alias("Default_Handler")));
void ETH_WKUP_IRQHandler()         __attribute__((weak, alias("Default_Handler")));
void CAN2_TX_IRQHandler()          __attribute__((weak, alias("Default_Handler")));
void CAN2_RX0_IRQHandler()         __attribute__((weak, alias("Default_Handler")));
void CAN2_RX1_IRQHandler()         __attribute__((weak, alias("Default_Handler")));
void CAN2_SCE_IRQHandler()         __attribute__((weak, alias("Default_Handler")));
void OTG_FS_IRQHandler()           __attribute__((weak, alias("Default_Handler")));
void USBHSWakeup_IRQHandler()      __attribute__((weak, alias("Default_Handler")));
void USBHS_IRQHandler()            __attribute__((weak, alias("Default_Handler")));
void DVP_IRQHandler()              __attribute__((weak, alias("Default_Handler")));
void UART6_IRQHandler()            __attribute__((weak, alias("Default_Handler")));
void UART7_IRQHandler()            __attribute__((weak, alias("Default_Handler")));
void UART8_IRQHandler()            __attribute__((weak, alias("Default_Handler")));
void TIM9_BRK_IRQHandler()         __attribute__((weak, alias("Default_Handler")));
void TIM9_UP_IRQHandler()          __attribute__((weak, alias("Default_Handler")));
void TIM9_TRG_COM_IRQHandler()     __attribute__((weak, alias("Default_Handler")));
void TIM9_CC_IRQHandler()          __attribute__((weak, alias("Default_Handler")));
void TIM10_BRK_IRQHandler()        __attribute__((weak, alias("Default_Handler")));
void TIM10_UP_IRQHandler()         __attribute__((weak, alias("Default_Handler")));
void TIM10_TRG_COM_IRQHandler()    __attribute__((weak, alias("Default_Handler")));
void TIM10_CC_IRQHandler()         __attribute__((weak, alias("Default_Handler")));
void DMA2_Channel6_IRQHandler()    __attribute__((weak, alias("Default_Handler")));
void DMA2_Channel7_IRQHandler()    __attribute__((weak, alias("Default_Handler")));
void DMA2_Channel8_IRQHandler()    __attribute__((weak, alias("Default_Handler")));
void DMA2_Channel9_IRQHandler()    __attribute__((weak, alias("Default_Handler")));
void DMA2_Channel10_IRQHandler()   __attribute__((weak, alias("Default_Handler")));
void DMA2_Channel11_IRQHandler()   __attribute__((weak, alias("Default_Handler")));

typedef void(*intvec_elem)();

const intvec_elem __vector_table[] __attribute__((used, section(".vectors"))) =
{ //NULL, NULL,
  &NMI_Handler,
  &HardFault_Handler,
  NULL,
  &Ecall_M_Mode_Handler,
  NULL,NULL,
  &Ecall_U_Mode_Handler,
  &Break_Point_Handler,
  NULL,NULL,
  &SysTick_Handler,
  NULL,
  &SW_handler,
  NULL,
  &WWDG_IRQHandler,
  &PVD_IRQHandler,
  &TAMPER_IRQHandler,
  &RTC_IRQHandler,
  &FLASH_IRQHandler,
  &RCC_IRQHandler,
  &EXTI0_IRQHandler,
  &EXTI1_IRQHandler,
  &EXTI2_IRQHandler,
  &EXTI3_IRQHandler,
  &EXTI4_IRQHandler,
  &DMA1_Channel1_IRQHandler,
  &DMA1_Channel2_IRQHandler,
  &DMA1_Channel3_IRQHandler,
  &DMA1_Channel4_IRQHandler,
  &DMA1_Channel5_IRQHandler,
  &DMA1_Channel6_IRQHandler,
  &DMA1_Channel7_IRQHandler,
  &ADC1_2_IRQHandler,
  &USB_HP_CAN1_TX_IRQHandler,
  &USB_LP_CAN1_RX0_IRQHandler,
  &CAN1_RX1_IRQHandler,
  &CAN1_SCE_IRQHandler,
  &EXTI9_5_IRQHandler,
  &TIM1_BRK_IRQHandler,
  &TIM1_UP_IRQHandler,
  &TIM1_TRG_COM_IRQHandler,
  &TIM1_CC_IRQHandler,
  &TIM2_IRQHandler,
  &TIM3_IRQHandler,
  &TIM4_IRQHandler,
  &I2C1_EV_IRQHandler,
  &I2C1_ER_IRQHandler,
  &I2C2_EV_IRQHandler,
  &I2C2_ER_IRQHandler,
  &SPI1_IRQHandler,
  &SPI2_IRQHandler,
  &USART1_IRQHandler,
  &USART2_IRQHandler,
  &USART3_IRQHandler,
  &EXTI15_10_IRQHandler,
  &RTCAlarm_IRQHandler,
  &USBWakeUp_IRQHandler,
  &TIM8_BRK_IRQHandler,
  &TIM8_UP_IRQHandler,
  &TIM8_TRG_COM_IRQHandler,
  &TIM8_CC_IRQHandler,
  &RNG_IRQHandler,
  &FSMC_IRQHandler,
  &SDIO_IRQHandler,
  &TIM5_IRQHandler,
  &SPI3_IRQHandler,
  &UART4_IRQHandler,
  &UART5_IRQHandler,
  &TIM6_IRQHandler,
  &TIM7_IRQHandler,
  &DMA2_Channel1_IRQHandler,
  &DMA2_Channel2_IRQHandler,
  &DMA2_Channel3_IRQHandler,
  &DMA2_Channel4_IRQHandler,
  &DMA2_Channel5_IRQHandler,
  &ETH_IRQHandler,
  &ETH_WKUP_IRQHandler,
  &CAN2_TX_IRQHandler,
  &CAN2_RX0_IRQHandler,
  &CAN2_RX1_IRQHandler,
  &CAN2_SCE_IRQHandler,
  &OTG_FS_IRQHandler,
  &USBHSWakeup_IRQHandler,
  &USBHS_IRQHandler,
  &DVP_IRQHandler,
  &UART6_IRQHandler,
  &UART7_IRQHandler,
  &UART8_IRQHandler,
  &TIM9_BRK_IRQHandler,
  &TIM9_UP_IRQHandler,
  &TIM9_TRG_COM_IRQHandler,
  &TIM9_CC_IRQHandler,
  &TIM10_BRK_IRQHandler,
  &TIM10_UP_IRQHandler,
  &TIM10_TRG_COM_IRQHandler,
  &TIM10_CC_IRQHandler,
  &DMA2_Channel6_IRQHandler,
  &DMA2_Channel7_IRQHandler,
  &DMA2_Channel8_IRQHandler,
  &DMA2_Channel9_IRQHandler,
  &DMA2_Channel10_IRQHandler,
  &DMA2_Channel11_IRQHandler
};

void Default_Handler() { for (;;); }

void __attribute__((used, naked, noreturn)) Reset_Handler()
{
  using namespace riscv;
  using namespace QingKeV4;

	SystemInit();

  extern uint32_t _sidata[], _sdata[], _edata[], _sbss[], _ebss[];
#ifndef __DEBUG_SRAM__
  for (volatile uint32_t* pSrc = _sidata, *pDst = _sdata; pDst != _edata; *pDst++ = *pSrc++);
#endif
  for (volatile uint32_t* pDst = _sbss; pDst != _ebss; *pDst++ = 0); // Zero -> BSS

  // Set Pipeline, instruction prediction and ??? (no documents found)
  CSR<CSR_REGS::corecfgr>::write<0x1F>(0x1F);

  // Enable nested and hardware stack
  SetINTSYSCR(HWSTKOVEN::Enable, PMTCFG::_8, INESTEN::Enable, HWSTKEN::Enable);

  // vector table uses the absolute address of the interrupt function
  SetMTVEC(__vector_table-2, EXCEPTIONS_MODE::VTABLE_ADDR);

  // Enable floating point, interrupts disable
  SetMSTATUS(MSTATUS_FS::Dirty, MSTATUS_MIE::Disable);
  
  main();

}

#ifdef __cplusplus
}
#endif
