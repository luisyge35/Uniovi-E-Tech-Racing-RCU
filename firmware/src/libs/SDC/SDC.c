#include "../SDC/SDC.h"
#include "peripheral/gpio/plib_gpio.h"

// Public function
void SDCInit(){
    INERTIA_SWITCH_STATUS_InputEnable();
    HVD_STATUS_InputEnable();
    BSPD_STATUS_InputEnable();
    BOTS_STATUS_InputEnable();
    BMS_STATUS_InputEnable();
    IMD_STATUS_InputEnable();
    RIGHT_EM_STATUS_InputEnable();
    COCKPIT_EM_STATUS_InputEnable();
    LEFT_EM_STATUS_InputEnable();
}

uint16_t SDCGetState(){
    uint16_t state;
    
    state = INERTIA_SWITCH_STATUS_Get() << 9 ||
            HVD_STATUS_Get() << 8 ||
            BSPD_STATUS_Get() << 7 ||
            BOTS_STATUS_Get() << 6 ||
            BMS_STATUS_Get() << 5 ||
            IMD_STATUS_Get() << 4 ||
            RIGHT_EM_STATUS_Get() << 3 ||
            COCKPIT_EM_STATUS_Get() << 2 ||
            LEFT_EM_STATUS_Get();

    return state;
}
