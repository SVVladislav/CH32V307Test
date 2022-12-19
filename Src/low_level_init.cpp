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
  SVVTL::WriteReg32<0x00FF'0000>(&RCC->CTLR, RCC_HSE_ON); //Включим HSE
  //while (!(RCC->CTLR & 0x2'0000));
  while (!(*(pVU8(&RCC->CTLR) + 2) & 0x2));

  RCC->CFGR0 = 0;
  


  RCC->APB2PCENR = (0 ? RCC_APB2Periph_TIM10 : 0U) + (0 ? RCC_APB2Periph_TIM9 : 0U) + (0 ? RCC_APB2Periph_TIM8 : 0U)
                 + (0 ? RCC_APB2Periph_TIM1 : 0U) + (0 ? RCC_APB2Periph_USART1 : 0U) + (0 ? RCC_APB2Periph_SPI1 : 0U)
                 + (0 ? RCC_APB2Periph_ADC2 : 0U) + (0 ? RCC_APB2Periph_ADC1 : 0U) + (0 ? RCC_APB2Periph_GPIOE : 0U)
                 + (0 ? RCC_APB2Periph_GPIOD : 0U) + (0 ? RCC_APB2Periph_GPIOC : 0U) + (1 ? RCC_APB2Periph_GPIOB : 0U)
                 + (1 ? RCC_APB2Periph_GPIOA : 0U) + (0 ? RCC_APB2Periph_AFIO : 0U);

  using namespace GPIO;

  ConfigList<PinMode::Input_PullUp, PA_14, PA_13,  // SWD
             PinMode::PushPull_LowSpeed<0>, LED1::tpin, LED2::tpin,
             PinMode::Input_PullUp, KEY::tpin,
             PinMode::Input, CfgCmd::AllUnusedPins>::pwr_config();

  SysTick->CMP = CPU_FREQ/100;
  SysTick->CTLR = (1 << 5) | (1 << 3) | (1 << 2) | (1 << 1) | (1 << 0);

}

#ifdef __cplusplus
}
#endif
