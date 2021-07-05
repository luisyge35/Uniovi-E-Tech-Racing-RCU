#include "../PowerDistribution/PowerDistribution.h"
#include "../Tick/Tick.h"

#define START_SEQUENCE_TIMEOUT      (2u)

// Private variables
PowerDistributionState state;
uint32_t tick;

// Private function declaration
void SMTask(void);
void StartFCU(void);
void StartBMS(void);
void StartSDC(void);
void StartBamocar(void);
void StartBomb1(void);
void StartBomb2(void);

//Public functions
void PowerDistributionInit(){
    K_BMS_OutputEnable();
    K_SDC_OutputEnable();
    K_FCU_OutputEnable();
    K_BOMB_1_OutputEnable();
    K_BOMB_2_OutputEnable();
    K_INVERTER_OutputEnable();

    state = INIT;
}

void PowerDistributionTask(){
    SMTask();
}

void PowerDistributionStartPowerOnSequence(){
    state = STARTED;
}

PowerDistributionState PowerDistributionGetState(){
    return state;
}

// Private functions
void SMTask(){
    switch(state){
    case INIT:
            break;
    case STARTED:
        state = START_BMS;
        break;
    case START_BMS:
        if(TickGet() - tick > TICK_SECOND * START_SEQUENCE_TIMEOUT){
            tick = TickGet();
            state = START_FCU;
            StartBMS();
          }
          break;
    case START_FCU:
          if(TickGet() - tick > TICK_SECOND * START_SEQUENCE_TIMEOUT){
            tick = TickGet();
            state = START_SDC;
            StartFCU();
          }
          break;
    case START_SDC:
          if(TickGet() - tick > TICK_SECOND * START_SEQUENCE_TIMEOUT){
            tick = TickGet();
            state = START_BOMB_1;
            StartSDC();
          }
          break;
    case START_BOMB_1:
          if(TickGet() - tick > TICK_SECOND * START_SEQUENCE_TIMEOUT){
            tick = TickGet();
            state = START_BOMB_2;
            StartBomb1();
          }
          break;
    case START_BOMB_2:
          if(TickGet() - tick > TICK_SECOND * START_SEQUENCE_TIMEOUT){
            tick = TickGet();
            state = START_BAMOCAR;
            StartBomb2();
          }
          break;
    case START_BAMOCAR:
          if(TickGet() - tick > TICK_SECOND * START_SEQUENCE_TIMEOUT){
            tick = TickGet();
            state = SEQUENCE_FINISHED;
            StartBamocar();
          }
          break;
    case SEQUENCE_FINISHED:
            break;
    }
}

void StartFCU(){
    K_FCU_Set();
}

void StartBMS(){
    K_BMS_Set();
}

void StartSDC(){
    K_SDC_Set();
}

void StartBamocar(){
    K_INVERTER_Set();
}

void StartBomb1(){
    K_BOMB_1_Set();
}

void StartBomb2(){
    K_BOMB_2_Set();
}
