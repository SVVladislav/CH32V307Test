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
  using namespace REMAP;

  riscv::__NOP();

  Remap< SWCFG::Enable,
         USART1_RM::CK_PA8_TX_PA9_RX_PA10_CTS_PA11_RTS_PA12,
         USART2_RM::CK_PA4_TX_PA2_RX_PA3_CTS_PA0_RTS_PA1,
         USART3_RM::CK_PB12_TX_PB10_RX_PB11_CTS_PB13_RTS_PB14,
         UART4_RM::TX_PC10_RX_PC11,
         UART5_RM::TX_PC12_RX_PD2,
         UART6_RM::TX_PC0_RX_PC1,
         UART7_RM::TX_PC2_RX_PC3,
         UART8_RM::TX_PC4_RX_PC5,
         TIM1_RM::ETR_PA12_CH1_PA8_CH2_PA9_CH3_PA10_CH4_PA11_BKIN_PB12_CH1N_PB13_CH2N_PB14_CH3N_PB15,
         TIM2_RM::CH1_ETR_PA0_CH2_PA1_CH3_PA2_CH4_PA3,
         TIM2_ITR1_RM::Ethernet_PTP,
         TIM3_RM::CH1_PA6_CH2_PA7_CH3_PB0_CH4_PB1,
         TIM4_RM::CH1_PB6_CH2_PB7_CH3_PB8_CH4_PB9,
         TIM5_CH4_RM::TIM5_CH4,
         TIM8_RM::ETR_PA0_CH1_PC6_CH2_PC7_CH3_PC8_CH4_PC9_BKIN_PA6_CH1N_PA7_CH2N_PB0_CH3N_PB1,
         TIM9_RM::ETR_PA2_CH1_PA2_CH2_PA3_CH3_PA4_CH4_PC4_BKIN_PC5_CH1N_PC0_CH2N_PC1_CH3N_PC2,
         TIM10_RM::ETR_PC10_CH1_PB8_CH2_PB9_CH3_PC3_CH4_PC11_BKIN_PC12_CH1N_PA12_CH2N_PA13_CH3N_PA14,
         CAN1_RM::RX_PA11_TX_PA12,
         CAN2_RM::RX_PB12_TX_PB13,
         ADC1_ETRG_INJ::EXTI15,
         ADC2_ETRG_INJ::EXTI15,
         ADC1_ETRG_REG::EXTI11,
         ADC2_ETRG_REG::EXTI11,
         PD0_PD1_RM::PD0_PD1,
         ETH_RM::RX_DV_PA7_RXD0_PC4_RXD1_PC5_RXD2_PB0_RXD3_PB1,
         MII_RMII_SEL::MII_PHY,
         PTP_PPSP_RM::Disable,
         SPI1_RM::NSS_PA4_SCK_PA5_MISO_PA6_MOSI_PA7,
         SPI3_RM::NSSP_PA15_SCK_PB3_MISO_PB4_MOSI_PB5,
         I2C1_RM::SCL_PB6_SDA_PB7,
         FSMC_NADV::PB7 >();

  riscv::__NOP();

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

