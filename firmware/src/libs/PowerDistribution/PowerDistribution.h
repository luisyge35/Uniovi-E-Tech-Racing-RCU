#ifndef POWER_DISTRIBUTION_H
#define POWER_DISTRIBUTION_H

#include "peripheral/gpio/plib_gpio.h"

typedef enum{
  INIT = 0,
  STARTED,
  START_BMS,
  START_FCU,
  START_SDC,
  START_BOMB_1,
  START_BOMB_2,
  START_BAMOCAR,
  SEQUENCE_FINISHED
} PowerDistributionState;

void PowerDistributionInit(void);
void PowerDistributionTask(void);
void PowerDistributionStartPowerOnSequence(void);
PowerDistributionState PowerDistributionGetState(void);

#endif
