#pragma once

#define CH32V307
#define CPU_FREQ 72'000'000

#include "CH32/ch32v30x.h"
#include "QingKeV4.hpp"

#include "SVVTL/template_lib.hpp"

#include "Hardware/GPIO/Gpio.hpp"
#include "Hardware/led.hpp"
#include "Hardware/key.hpp"

using LED1 = TLed<GPIO::PA_15>;
using LED2 = TLed<GPIO::PB_4>;
using KEY = TKey<GPIO::PB_3, true>;

#include "Hardware/USB/usb.hpp"
#include "Hardware/USB/usb_cdc.hpp"

#define USB_FS_ENABLE
#ifdef USB_FS_ENABLE
using USB_FS_CLASS = USB_CDC<CH32_OTG_FS_DEVICE, LED1>;
extern USB_FS_CLASS USB_FS_OBJECT;
#define USB_FS_ENABLE
#endif

//#define USB_HS_ENABLE
#ifdef USB_HS_ENABLE
using USB_HS_CLASS = USB_CDC<CH32_OTG_HS_DEVICE, LED2>;
extern USB_HS_CLASS USB_HS_OBJECT;
#endif
