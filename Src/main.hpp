#pragma once

#define CH32V307
#define CPU_FREQ 144'000'000
#define WCH_INTERRUPT_FAST

#include "QingKeV4.hpp"
#include "CH32/ch32v30x.h"


#include "SVVTL/template_lib.hpp"

#include "Hardware/GPIO/Gpio.hpp"
#include "Hardware/led.hpp"
#include "Hardware/key.hpp"

using LED1 = TLed<GPIO::PA_15>;
using LED2 = TLed<GPIO::PB_4>;
using KEY = TKey<GPIO::PB_3, true>;

#define USB_FS_ENABLE
//#define USB_HS_ENABLE
#include "Hardware/USB/usb.hpp"
#include "Hardware/USB/usb_cdc.hpp"


#ifdef USB_FS_ENABLE
using USB_FS_CLASS = TUSB_CDC<CH32_OTG_FS_DEVICE, LED1>;
extern USB_FS_CLASS USB_FS_OBJECT;
#endif

#ifdef USB_HS_ENABLE
using USB_HS_CLASS = USB_CDC<CH32_USB_HS_DEVICE, LED2>;
extern USB_HS_CLASS USB_HS_OBJECT;
#endif

__interrupt SysTick_Handler();
__interrupt EXTI0_IRQHandler();