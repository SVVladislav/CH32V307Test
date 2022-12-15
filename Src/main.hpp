#pragma once

#define CH32V307

#include "CH32/ch32v30x.h"
#include "risc-v.hpp"

#include "SVVTL/template_lib.hpp"

#include "Hardware/GPIO/Gpio.hpp"
#include "Hardware/led.hpp"

using LED1 = TLed<GPIO::PA_15>;
using LED2 = TLed<GPIO::PB_4>;




