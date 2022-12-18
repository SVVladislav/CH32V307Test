#include "main.hpp"

using namespace QingKeV4;

TBlinkingLed<LED2, 50>  bl_led;
KEY key;

int main()
{
  NVIC_EnableIRQ(SysTicK_IRQn);
  
  LED1::On();
  bl_led.On();

  __enable_irq();

  for (;;)
  {
	if(key.isKeyPressed()) LED1::Toggle();
  };
}

__interrupt SysTick_Handler()
{
  SysTick->SR = 0;
  key.Scan();
  bl_led.tic();
  interrupt_return;
}