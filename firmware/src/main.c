#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes
#include <sys/kmem.h>

#define ADC_PIN_MAP(pin)

typedef enum{
    IDLE = 0,
    RUNNING = 1,
    ERROR = 2
} SMState;

#define TICKMILISECOND      (CORE_TIMER_FREQUENCY/1000)*50 
#define BAMOCAR_RX_ADDR     (0x201)
#define TORQUE_REGID        (0x31)
#define ACC_1               (ADC_INPUT_POSITIVE_AN23)
#define ACC_2               (ADC_INPUT_POSITIVE_AN27)
#define ADC_VREF            (3.3f)
#define ADC_MAX_COUNT       (1023u)
#define MAX_ACC_ANGLE       (90u)
#define MIN_ACC_ANGLE       (0u)
#define TORQUE_LIMIT_PER    (20)
#define MAX_TORQUE          (32767)

// Private functions
static void SetState(uint8_t newState);
static void HandleCanMessage(void);
void CAN_1_Handler( void );
static uint32_t ADCGet(uint8_t channel);
static uint16_t ParseBamocarTorqueSignal(uint8_t accValue);

// Private variables
volatile uint16_t acceleratorValue;
volatile uint16_t acceleratorValue2;
volatile float Acc1,Acc2;
volatile int8_t Acc1Deg, Acc2Deg;
uint16_t torque;
uint8_t data[8] = {0};
uint32_t tick = 0;
uint32_t tickGet = 0;
volatile uint8_t state = IDLE;
CAN_TX_RX_MSG_BUFFER *rxMessage = NULL;

void __ISR(_CAN_1_VECTOR, ipl1SOFT) CAN_1_Handler (void)
{
    HandleCanMessage();
    CAN1_InterruptHandler();
}

void HandleCanMessage(){
    rxMessage = (CAN_TX_RX_MSG_BUFFER *)PA_TO_KVA1(C1FIFOUA1);
    if (rxMessage->msgData[0] == 0xFF){
        SetState(RUNNING);
    }
}

void SetState(uint8_t newState){
    state = newState;
}
    
uint32_t ADCGet(uint8_t channel){
    ADC_InputSelect(ADC_MUX_A, channel, ADC_INPUT_NEGATIVE_VREFL);
    ADC_SamplingStart();
    CORETIMER_DelayMs(10);
    ADC_ConversionStart();
    while(!ADC_ResultIsReady());
    return ADC_ResultGet(ADC_RESULT_BUFFER_0);
}

int8_t GetAccValue(uint8_t AccIndex){
    volatile uint16_t adcResult;
    float volts;
    
    // Get reading form adc
    adcResult = (uint16_t)ADCGet(AccIndex);
    // Translate to volts
    volts = (float)adcResult * ADC_VREF / ADC_MAX_COUNT;
    // Translate to degrees
    return (int8_t)(68.18*volts-112.5);
}

uint16_t ParseBamocarTorqueSignal(uint8_t accValue){ 
    uint16_t torqueLimit;
    uint16_t torqueReference;
    
    if ((accValue < MIN_ACC_ANGLE) || (accValue > MAX_ACC_ANGLE)){
        return 0;
    }
    
    torqueLimit = (float)MAX_TORQUE * (float)TORQUE_LIMIT_PER/100;
    
    torqueReference = (accValue * torqueLimit / MAX_ACC_ANGLE);
    
    if(torqueReference > torqueLimit){
        return torqueLimit;
    } else {
        return torqueReference;
    }
}

int main ( void )
{
    SYS_Initialize ( NULL );

    while ( true )
    {
        switch(state){
            case IDLE:
                break;
            case RUNNING:
                if (CORETIMER_CounterGet() - tick > TICKMILISECOND){
                    // Update timer
                    tick = CORETIMER_CounterGet();
                    
                    // Read Acc values
                    Acc1Deg = GetAccValue(ACC_1);
                    Acc2Deg = GetAccValue(ACC_2);
                    
                    // TODO: Place APPS algorithm here
                    
                    // Translate accelerator to Bamocar's toque setpoint format
                    torque = ParseBamocarTorqueSignal(Acc2Deg);
                    
                    // Build send buffer
                    //data[0] = Acc1Deg;
                    //data[1] = Acc2Deg;
                    data[0] = (uint8_t)(torque & 0xFF);
                    data[1] = (uint8_t)((torque & 0xFF00) >> 8);

                    // Send buffer
                    CANSendBuffer(BAMOCAR_RX_ADDR, 3, TORQUE_REGID, data);
             
                    // LED_Toggle();
                }
                break;
            default: 
                break;
        }
        SYS_Tasks ( );
    }
    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

