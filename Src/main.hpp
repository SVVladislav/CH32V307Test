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
//#include "Hardware/USB/usb_cdc.hpp"
