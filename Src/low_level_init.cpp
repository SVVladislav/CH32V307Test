#include "main.hpp"

#ifdef __cplusplus
extern "C" {
#endif

using pVU8 = volatile uint8_t*;
using pVU16 = volatile uint16_t*;
using pVU32 = volatile uint32_t*;

void SystemInit()
{
  // HSE On
  SVVTL::WriteReg32<0x00FF'0000>(&RCC->CTLR, RCC_HSEON);

  // Whait HSE
  while (!(SVVTL::ReadReg32<0x00FF'0000>(&RCC->CTLR) & (RCC_HSERDY>>16)));

  RCC->CFGR0 = RCC_CFGR0_MCO_PLL | RCC_USBPRE | RCC_PLLMULL18_EXTEN | CFGR0_PLLSRC_HSE | RCC_ADCPRE_DIV8
             | RCC_PPRE2_DIV2 | RCC_PPRE1_DIV1 | RCC_HPRE_DIV1 | RCC_SW_HSI;

  // PLL On
  SVVTL::WriteReg32<0xFF00'0000>(&RCC->CTLR, RCC_PLLON);

  // Whait PLL
  while (!(SVVTL::ReadReg32<0xFF00'0000>(&RCC->CTLR) & (RCC_PLLRDY >> 24)));

  // Switch to PLL
  SVVTL::WriteReg32<0x0000'00FF>(&RCC->CFGR0, RCC_SW_PLL);

  RCC->AHBPCENR = (0 ? RCC_AHBPeriph_DMA1       : 0) + (0 ? RCC_AHBPeriph_DMA2    : 0) + (1 ? RCC_AHBPeriph_SRAM       : 0)
                + (0 ? RCC_AHBPeriph_CRC        : 0) + (0 ? RCC_AHBPeriph_FSMC    : 0) + (0 ? RCC_AHBPeriph_RNG        : 0)
                + (0 ? RCC_AHBPeriph_SDIO       : 0) + (0 ? RCC_AHBPeriph_DVP     : 0) + (0 ? RCC_AHBPeriph_ETH_MAC    : 0)
#ifdef USB_HS_ENABLE
                + (1 ? RCC_AHBPeriph_USBHS      : 0)
#endif
#ifdef USB_FS_ENABLE
                + (1 ? RCC_AHBPeriph_OTG_FS     : 0)
#endif
                + (0 ? RCC_AHBPeriph_ETH_MAC_Tx : 0) + (0 ? RCC_AHBPeriph_ETH_MAC_Rx : 0);

  RCC->APB2PCENR = (0 ? RCC_APB1Periph_TIM2   : 0) + (0 ? RCC_APB1Periph_TIM3   : 0) + (0 ? RCC_APB1Periph_TIM4  : 0)
                 + (0 ? RCC_APB1Periph_TIM5   : 0) + (0 ? RCC_APB1Periph_TIM6   : 0) + (0 ? RCC_APB1Periph_TIM7  : 0)
                 + (0 ? RCC_APB1Periph_UART6  : 0) + (0 ? RCC_APB1Periph_UART7  : 0) + (0 ? RCC_APB1Periph_UART8 : 0)
                 + (0 ? RCC_APB1Periph_WWDG   : 0) + (0 ? RCC_APB1Periph_SPI2   : 0) + (0 ? RCC_APB1Periph_SPI3  : 0)
                 + (0 ? RCC_APB1Periph_USART2 : 0) + (0 ? RCC_APB1Periph_USART3 : 0) + (0 ? RCC_APB1Periph_UART4 : 0)
                 + (0 ? RCC_APB1Periph_UART5  : 0) + (0 ? RCC_APB1Periph_I2C1   : 0) + (0 ? RCC_APB1Periph_I2C2  : 0)
                 + (0 ? RCC_APB1Periph_USB    : 0) + (0 ? RCC_APB1Periph_CAN1   : 0) + (0 ? RCC_APB1Periph_CAN2  : 0)
                 + (0 ? RCC_APB1Periph_BKP    : 0) + (0 ? RCC_APB1Periph_PWR    : 0) + (0 ? RCC_APB1Periph_DAC   : 0);

  RCC->APB2PCENR = (0 ? RCC_APB2Periph_TIM10 : 0U) + (0 ? RCC_APB2Periph_TIM9   : 0U) + (0 ? RCC_APB2Periph_TIM8  : 0U)
                 + (0 ? RCC_APB2Periph_TIM1  : 0U) + (0 ? RCC_APB2Periph_USART1 : 0U) + (0 ? RCC_APB2Periph_SPI1  : 0U)
                 + (0 ? RCC_APB2Periph_ADC2  : 0U) + (0 ? RCC_APB2Periph_ADC1   : 0U) + (0 ? RCC_APB2Periph_GPIOE : 0U)
                 + (0 ? RCC_APB2Periph_GPIOD : 0U) + (1 ? RCC_APB2Periph_GPIOC  : 0U) + (1 ? RCC_APB2Periph_GPIOB : 0U)
                 + (1 ? RCC_APB2Periph_GPIOA : 0U) + (1 ? RCC_APB2Periph_AFIO   : 0U);

  using namespace GPIO;

  ConfigList<PinMode::Input_PullUp, PA_14, PA_13,  // SWD
             PinMode::PushPull_LowSpeed<0>, LED1::tpin, LED2::tpin,
             PinMode::Input_PullUp, KEY::tpin,
             PinMode::AF_PushPull_HighSpeed, PA_8,
             //PinMode::PushPull_HighSpeed<>, PC_0, PC_1,
             PinMode::Input, CfgCmd::AllUnusedPins>::pwr_config();

  SysTick->CMP = CPU_FREQ/100;
  SysTick->CTLR = (1 << 5) | (1 << 3) | (1 << 2) | (1 << 1) | (1 << 0);

#ifdef USB_FS_ENABLE
  CH32_OTG_FS_DEVICE::Init();
#endif

#ifdef USB_HS_ENABLE
  CH32_USB_HS_DEVICE::Init();
#endif

}

#ifdef __cplusplus
}
#endif
