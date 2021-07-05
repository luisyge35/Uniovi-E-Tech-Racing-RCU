#ifndef TICK_H
#define TICK_H

#include "peripheral/coretimer/plib_coretimer.h"

#define TICKMILISECOND    (CORE_TIMER_FREQUENCY/1000)
#define TICK_SECOND       (TICKMILISECOND * 1000)

#define TickGet() CORETIMER_CounterGet()

#endif
