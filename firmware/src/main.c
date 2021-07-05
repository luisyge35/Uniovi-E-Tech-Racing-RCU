#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes
#include <sys/kmem.h>
#include "libs/TaskMgr/TaskMgr.h"

// Definitons
#define ADC_VREF                    (3.3f)
#define ADC_MAX_COUNT               (1023u)
#undef NHAPAS

// CAN-Bus IDS
#define BAMOCAR_CAN_ID                  (0x01)
#define FCU_STATUS_REQUEST_CAN_ID       (0x29)
#define FCU_STATUS_RESPONSE_CAN_ID      (0x30)
#define PRECHARGE_REQUEST_CAN_ID        (0x31)
#define PRECHARGE_RESPONSE_CAN_ID       (0x32)
#define PRECHARGE_READY_CAN_ID          (0x33)
#define FCU_SENSOR_VALUES_CAN_ID        (0x34)
#define RTD_REQUEST_CAN_ID              (0x35)
#define RTD_RESPONSE_CAN_ID             (0x36)
#define DASHBOARD_AWAKE_CAN_ID          (0x37)
#define FCU_AWAKE_CAN_ID                (0x38)
#define SDC_STATUS_CAN_ID               (0x50)

// Custom Data types
typedef enum{
    UNKNOWN = 0,
    STARTED,
    ERROR
} ECUState;

// Private function declaration
void HandleCanMessage(void);
uint32_t ADCGet(uint8_t channel);

/////////////////////////////////////////////////////////////////
// Interrupt
void CAN_1_Handler( void );

void __ISR(_CAN_1_VECTOR, ipl1SOFT) CAN_1_Handler (void)
{
    HandleCanMessage();
    CAN1_InterruptHandler();
}
/////////////////////////////////////////////////////////////////


// Private variables
uint8_t canSendBuffer[8] = {0};
static uint32_t tick = 0;
CAN_TX_RX_MSG_BUFFER *rxMessage = NULL;

// Main task
int main ( void )
{
    SYS_Initialize ( NULL );
    
    TaskMgrInit();

    while ( true )
    {
        TaskMgr();
        
        SYS_Tasks ( );
    }

    return ( EXIT_FAILURE );
}


// Private function definition
void HandleCanMessage(){
    rxMessage = (CAN_TX_RX_MSG_BUFFER *)PA_TO_KVA1(C1FIFOUA1);

    switch(rxMessage->msgSID){

    }
}

uint32_t ADCGet(uint8_t channel){
    ADC_InputSelect(ADC_MUX_A, channel, ADC_INPUT_NEGATIVE_VREFL);
    ADC_SamplingStart();
    CORETIMER_DelayMs(10);
    ADC_ConversionStart();
    while(!ADC_ResultIsReady());
    return ADC_ResultGet(ADC_RESULT_BUFFER_0);
}
