#include "main.hpp"

#ifdef __cplusplus
extern "C" {
#endif

void SystemInit()
{
  using namespace GPIO;

  ConfigList<PinMode::Input_PullUp, PA_0, PA_2,
	         PinMode::OpenDrain_HighSpeed<1>, PB_4, PB_5,
             PinMode::Input, CfgCmd::AllUnusedPins>::pwr_config();
}

#ifdef __cplusplus
}
#endif
