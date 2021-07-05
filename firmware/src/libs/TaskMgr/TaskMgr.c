#include "../TaskMgr/TaskMgr.h"
#include "../Tick/Tick.h"
#include "../PowerDistribution/PowerDistribution.h"
#include "../SDC/SDC.h"

#define START_DELAY     (1u)

// Private data types
typedef enum{
    IDLE = 0,
    START_SUBSYSTEMS,
    SDC_CHECK,
    PRECHARGING,
    READY_TO_RACE_BABY
} SMState;

// Private variables
static uint32_t tick = 0;
uint32_t tick2 = 0;
static SMState state;

// Public functions
void TaskMgrInit(){
    
    PowerDistributionInit();
    
    SDCInit();
    
    state = IDLE;
}

void TaskMgr(){
       
    switch(state){
        case IDLE:
          tick2 = TickGet();
          if(TickGet() - tick > START_DELAY * TICK_SECOND){
            tick  = TickGet();
            state = START_SUBSYSTEMS;
            PowerDistributionStartPowerOnSequence();
          }
          break;
        case START_SUBSYSTEMS:
          PowerDistributionTask();
          if(PowerDistributionGetState() == SEQUENCE_FINISHED){
            state = SDC_CHECK;
          }
        case SDC_CHECK:
            break;
        case PRECHARGING:
            break;
        case READY_TO_RACE_BABY:
            break;
    }
}
