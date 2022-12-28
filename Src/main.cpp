#include "main.hpp"

using namespace QingKeV4;

TBlinkingLed<LED2, 50>  bl_led;
KEY key;



int main()
{
  

  SetVTFIRQ(SysTick_Handler, SysTicK_IRQn, 0);
  NVIC_EnableIRQ(SysTicK_IRQn);

  //AFIO->EXTICR[0] = 2;
  //EXTI->INTENR = 1;
  //EXTI->RTENR = 1;
  //SetVTFIRQ((uint32_t)EXTI0_IRQHandler, EXTI0_IRQn, 0);
  //NVIC_EnableIRQ(EXTI0_IRQn);

  LED1::On();
  bl_led.On();

  __enable_irq();

  CH32_OTG_FS_DEVICE::PullUpOn();

  for (;;)
  {
    GPIO::PC_0::toggle();
    GPIO::PC_1::clear();
    //if (key.isKeyPressed())
    //{
    //  LED1::On();
    //}
  };
}

__interrupt SysTick_Handler()
{
  SysTick->SR = 0;
  key.Scan();
  bl_led.tic();
}

/*
void EXTI0_IRQHandler()
{
  GPIO::PC_1::set();
  EXTI->INTFR = 1;
}
*/