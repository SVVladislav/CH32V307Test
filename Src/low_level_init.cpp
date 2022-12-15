#include "main.hpp"

#ifdef __cplusplus
extern "C" {
#endif

void SystemInit()
{

  RCC->APB2PCENR = (0 ? RCC_APB2Periph_TIM10 : 0U) + (0 ? RCC_APB2Periph_TIM9 : 0U) + (0 ? RCC_APB2Periph_TIM8 : 0U)
	             + (0 ? RCC_APB2Periph_TIM1 : 0U) + (0 ? RCC_APB2Periph_USART1 : 0U) + (0 ? RCC_APB2Periph_SPI1 : 0U)
	             + (0 ? RCC_APB2Periph_ADC2 : 0U) + (0 ? RCC_APB2Periph_ADC1 : 0U) + (0 ? RCC_APB2Periph_GPIOE : 0U)
	             + (0 ? RCC_APB2Periph_GPIOD : 0U) + (0 ? RCC_APB2Periph_GPIOC : 0U) + (1 ? RCC_APB2Periph_GPIOB : 0U)
	             + (1 ? RCC_APB2Periph_GPIOA : 0U) + (0 ? RCC_APB2Periph_AFIO : 0U);

  using namespace GPIO;

  ConfigList<PinMode::Input_PullUp, PA_14, PA_13,  // SWD
	         PinMode::PushPull_LowSpeed<0>, LED1::tpin, LED2::tpin,
             PinMode::Input, CfgCmd::AllUnusedPins>::pwr_config();
}

#ifdef __cplusplus
}
#endif
