/*******************************************************************************
  GPIO PLIB

  Company:
    Microchip Technology Inc.

  File Name:
    plib_gpio.h

  Summary:
    GPIO PLIB Header File

  Description:
    This library provides an interface to control and interact with Parallel
    Input/Output controller (GPIO) module.

*******************************************************************************/

/*******************************************************************************
* Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

#ifndef PLIB_GPIO_H
#define PLIB_GPIO_H

#include <device.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Data types and constants
// *****************************************************************************
// *****************************************************************************


/*** Macros for RTDS_PWM pin ***/
#define RTDS_PWM_Get()               ((PORTB >> 6) & 0x1)
#define RTDS_PWM_PIN                  GPIO_PIN_RB6

/*** Macros for K_BREAK_LIGHT pin ***/
#define K_BREAK_LIGHT_Set()               (LATASET = (1<<10))
#define K_BREAK_LIGHT_Clear()             (LATACLR = (1<<10))
#define K_BREAK_LIGHT_Toggle()            (LATAINV= (1<<10))
#define K_BREAK_LIGHT_OutputEnable()      (TRISACLR = (1<<10))
#define K_BREAK_LIGHT_InputEnable()       (TRISASET = (1<<10))
#define K_BREAK_LIGHT_Get()               ((PORTA >> 10) & 0x1)
#define K_BREAK_LIGHT_PIN                  GPIO_PIN_RA10

/*** Macros for K_BMS pin ***/
#define K_BMS_Set()               (LATBSET = (1<<10))
#define K_BMS_Clear()             (LATBCLR = (1<<10))
#define K_BMS_Toggle()            (LATBINV= (1<<10))
#define K_BMS_OutputEnable()      (TRISBCLR = (1<<10))
#define K_BMS_InputEnable()       (TRISBSET = (1<<10))
#define K_BMS_Get()               ((PORTB >> 10) & 0x1)
#define K_BMS_PIN                  GPIO_PIN_RB10

/*** Macros for VOLTAGE_ADC pin ***/
#define VOLTAGE_ADC_Get()               ((PORTB >> 13) & 0x1)
#define VOLTAGE_ADC_PIN                  GPIO_PIN_RB13

/*** Macros for STBY pin ***/
#define STBY_Set()               (LATDSET = (1<<15))
#define STBY_Clear()             (LATDCLR = (1<<15))
#define STBY_Toggle()            (LATDINV= (1<<15))
#define STBY_OutputEnable()      (TRISDCLR = (1<<15))
#define STBY_InputEnable()       (TRISDSET = (1<<15))
#define STBY_Get()               ((PORTD >> 15) & 0x1)
#define STBY_PIN                  GPIO_PIN_RD15

/*** Macros for BOTS_STATUS pin ***/
#define BOTS_STATUS_Set()               (LATCSET = (1<<13))
#define BOTS_STATUS_Clear()             (LATCCLR = (1<<13))
#define BOTS_STATUS_Toggle()            (LATCINV= (1<<13))
#define BOTS_STATUS_OutputEnable()      (TRISCCLR = (1<<13))
#define BOTS_STATUS_InputEnable()       (TRISCSET = (1<<13))
#define BOTS_STATUS_Get()               ((PORTC >> 13) & 0x1)
#define BOTS_STATUS_PIN                  GPIO_PIN_RC13

/*** Macros for COCKPIT_EM_STATUS pin ***/
#define COCKPIT_EM_STATUS_Set()               (LATCSET = (1<<14))
#define COCKPIT_EM_STATUS_Clear()             (LATCCLR = (1<<14))
#define COCKPIT_EM_STATUS_Toggle()            (LATCINV= (1<<14))
#define COCKPIT_EM_STATUS_OutputEnable()      (TRISCCLR = (1<<14))
#define COCKPIT_EM_STATUS_InputEnable()       (TRISCSET = (1<<14))
#define COCKPIT_EM_STATUS_Get()               ((PORTC >> 14) & 0x1)
#define COCKPIT_EM_STATUS_PIN                  GPIO_PIN_RC14

/*** Macros for IMD_STATUS pin ***/
#define IMD_STATUS_Set()               (LATDSET = (1<<1))
#define IMD_STATUS_Clear()             (LATDCLR = (1<<1))
#define IMD_STATUS_Toggle()            (LATDINV= (1<<1))
#define IMD_STATUS_OutputEnable()      (TRISDCLR = (1<<1))
#define IMD_STATUS_InputEnable()       (TRISDSET = (1<<1))
#define IMD_STATUS_Get()               ((PORTD >> 1) & 0x1)
#define IMD_STATUS_PIN                  GPIO_PIN_RD1

/*** Macros for HVD_STATUS pin ***/
#define HVD_STATUS_Set()               (LATDSET = (1<<2))
#define HVD_STATUS_Clear()             (LATDCLR = (1<<2))
#define HVD_STATUS_Toggle()            (LATDINV= (1<<2))
#define HVD_STATUS_OutputEnable()      (TRISDCLR = (1<<2))
#define HVD_STATUS_InputEnable()       (TRISDSET = (1<<2))
#define HVD_STATUS_Get()               ((PORTD >> 2) & 0x1)
#define HVD_STATUS_PIN                  GPIO_PIN_RD2

/*** Macros for TSMS_STATUS pin ***/
#define TSMS_STATUS_Set()               (LATDSET = (1<<3))
#define TSMS_STATUS_Clear()             (LATDCLR = (1<<3))
#define TSMS_STATUS_Toggle()            (LATDINV= (1<<3))
#define TSMS_STATUS_OutputEnable()      (TRISDCLR = (1<<3))
#define TSMS_STATUS_InputEnable()       (TRISDSET = (1<<3))
#define TSMS_STATUS_Get()               ((PORTD >> 3) & 0x1)
#define TSMS_STATUS_PIN                  GPIO_PIN_RD3

/*** Macros for INERTIA_SWITCH_STATUS pin ***/
#define INERTIA_SWITCH_STATUS_Set()               (LATDSET = (1<<12))
#define INERTIA_SWITCH_STATUS_Clear()             (LATDCLR = (1<<12))
#define INERTIA_SWITCH_STATUS_Toggle()            (LATDINV= (1<<12))
#define INERTIA_SWITCH_STATUS_OutputEnable()      (TRISDCLR = (1<<12))
#define INERTIA_SWITCH_STATUS_InputEnable()       (TRISDSET = (1<<12))
#define INERTIA_SWITCH_STATUS_Get()               ((PORTD >> 12) & 0x1)
#define INERTIA_SWITCH_STATUS_PIN                  GPIO_PIN_RD12

/*** Macros for RIGHT_EM_STATUS pin ***/
#define RIGHT_EM_STATUS_Set()               (LATESET = (1<<1))
#define RIGHT_EM_STATUS_Clear()             (LATECLR = (1<<1))
#define RIGHT_EM_STATUS_Toggle()            (LATEINV= (1<<1))
#define RIGHT_EM_STATUS_OutputEnable()      (TRISECLR = (1<<1))
#define RIGHT_EM_STATUS_InputEnable()       (TRISESET = (1<<1))
#define RIGHT_EM_STATUS_Get()               ((PORTE >> 1) & 0x1)
#define RIGHT_EM_STATUS_PIN                  GPIO_PIN_RE1

/*** Macros for LEFT_EM_STATUS pin ***/
#define LEFT_EM_STATUS_Set()               (LATGSET = (1<<14))
#define LEFT_EM_STATUS_Clear()             (LATGCLR = (1<<14))
#define LEFT_EM_STATUS_Toggle()            (LATGINV= (1<<14))
#define LEFT_EM_STATUS_OutputEnable()      (TRISGCLR = (1<<14))
#define LEFT_EM_STATUS_InputEnable()       (TRISGSET = (1<<14))
#define LEFT_EM_STATUS_Get()               ((PORTG >> 14) & 0x1)
#define LEFT_EM_STATUS_PIN                  GPIO_PIN_RG14

/*** Macros for INTERLOCKS_STATUS pin ***/
#define INTERLOCKS_STATUS_Set()               (LATGSET = (1<<12))
#define INTERLOCKS_STATUS_Clear()             (LATGCLR = (1<<12))
#define INTERLOCKS_STATUS_Toggle()            (LATGINV= (1<<12))
#define INTERLOCKS_STATUS_OutputEnable()      (TRISGCLR = (1<<12))
#define INTERLOCKS_STATUS_InputEnable()       (TRISGSET = (1<<12))
#define INTERLOCKS_STATUS_Get()               ((PORTG >> 12) & 0x1)
#define INTERLOCKS_STATUS_PIN                  GPIO_PIN_RG12

/*** Macros for K_SDC pin ***/
#define K_SDC_Set()               (LATESET = (1<<2))
#define K_SDC_Clear()             (LATECLR = (1<<2))
#define K_SDC_Toggle()            (LATEINV= (1<<2))
#define K_SDC_OutputEnable()      (TRISECLR = (1<<2))
#define K_SDC_InputEnable()       (TRISESET = (1<<2))
#define K_SDC_Get()               ((PORTE >> 2) & 0x1)
#define K_SDC_PIN                  GPIO_PIN_RE2

/*** Macros for K_FCU pin ***/
#define K_FCU_Set()               (LATESET = (1<<3))
#define K_FCU_Clear()             (LATECLR = (1<<3))
#define K_FCU_Toggle()            (LATEINV= (1<<3))
#define K_FCU_OutputEnable()      (TRISECLR = (1<<3))
#define K_FCU_InputEnable()       (TRISESET = (1<<3))
#define K_FCU_Get()               ((PORTE >> 3) & 0x1)
#define K_FCU_PIN                  GPIO_PIN_RE3

/*** Macros for K_BOMB_1 pin ***/
#define K_BOMB_1_Set()               (LATESET = (1<<4))
#define K_BOMB_1_Clear()             (LATECLR = (1<<4))
#define K_BOMB_1_Toggle()            (LATEINV= (1<<4))
#define K_BOMB_1_OutputEnable()      (TRISECLR = (1<<4))
#define K_BOMB_1_InputEnable()       (TRISESET = (1<<4))
#define K_BOMB_1_Get()               ((PORTE >> 4) & 0x1)
#define K_BOMB_1_PIN                  GPIO_PIN_RE4


// *****************************************************************************
/* GPIO Port

  Summary:
    Identifies the available GPIO Ports.

  Description:
    This enumeration identifies the available GPIO Ports.

  Remarks:
    The caller should not rely on the specific numbers assigned to any of
    these values as they may change from one processor to the next.

    Not all ports are available on all devices.  Refer to the specific
    device data sheet to determine which ports are supported.
*/

typedef enum
{
    GPIO_PORT_A = 0,
    GPIO_PORT_B = 1,
    GPIO_PORT_C = 2,
    GPIO_PORT_D = 3,
    GPIO_PORT_E = 4,
    GPIO_PORT_F = 5,
    GPIO_PORT_G = 6,
} GPIO_PORT;

// *****************************************************************************
/* GPIO Port Pins

  Summary:
    Identifies the available GPIO port pins.

  Description:
    This enumeration identifies the available GPIO port pins.

  Remarks:
    The caller should not rely on the specific numbers assigned to any of
    these values as they may change from one processor to the next.

    Not all pins are available on all devices.  Refer to the specific
    device data sheet to determine which pins are supported.
*/

typedef enum
{
    GPIO_PIN_RA0 = 0,
    GPIO_PIN_RA1 = 1,
    GPIO_PIN_RA2 = 2,
    GPIO_PIN_RA3 = 3,
    GPIO_PIN_RA4 = 4,
    GPIO_PIN_RA5 = 5,
    GPIO_PIN_RA6 = 6,
    GPIO_PIN_RA7 = 7,
    GPIO_PIN_RA9 = 9,
    GPIO_PIN_RA10 = 10,
    GPIO_PIN_RA14 = 14,
    GPIO_PIN_RA15 = 15,
    GPIO_PIN_RB0 = 16,
    GPIO_PIN_RB1 = 17,
    GPIO_PIN_RB2 = 18,
    GPIO_PIN_RB3 = 19,
    GPIO_PIN_RB4 = 20,
    GPIO_PIN_RB5 = 21,
    GPIO_PIN_RB6 = 22,
    GPIO_PIN_RB7 = 23,
    GPIO_PIN_RB8 = 24,
    GPIO_PIN_RB9 = 25,
    GPIO_PIN_RB10 = 26,
    GPIO_PIN_RB11 = 27,
    GPIO_PIN_RB12 = 28,
    GPIO_PIN_RB13 = 29,
    GPIO_PIN_RB14 = 30,
    GPIO_PIN_RB15 = 31,
    GPIO_PIN_RC1 = 33,
    GPIO_PIN_RC2 = 34,
    GPIO_PIN_RC3 = 35,
    GPIO_PIN_RC4 = 36,
    GPIO_PIN_RC12 = 44,
    GPIO_PIN_RC13 = 45,
    GPIO_PIN_RC14 = 46,
    GPIO_PIN_RC15 = 47,
    GPIO_PIN_RD0 = 48,
    GPIO_PIN_RD1 = 49,
    GPIO_PIN_RD2 = 50,
    GPIO_PIN_RD3 = 51,
    GPIO_PIN_RD4 = 52,
    GPIO_PIN_RD5 = 53,
    GPIO_PIN_RD6 = 54,
    GPIO_PIN_RD7 = 55,
    GPIO_PIN_RD8 = 56,
    GPIO_PIN_RD9 = 57,
    GPIO_PIN_RD10 = 58,
    GPIO_PIN_RD11 = 59,
    GPIO_PIN_RD12 = 60,
    GPIO_PIN_RD13 = 61,
    GPIO_PIN_RD14 = 62,
    GPIO_PIN_RD15 = 63,
    GPIO_PIN_RE0 = 64,
    GPIO_PIN_RE1 = 65,
    GPIO_PIN_RE2 = 66,
    GPIO_PIN_RE3 = 67,
    GPIO_PIN_RE4 = 68,
    GPIO_PIN_RE5 = 69,
    GPIO_PIN_RE6 = 70,
    GPIO_PIN_RE7 = 71,
    GPIO_PIN_RE8 = 72,
    GPIO_PIN_RE9 = 73,
    GPIO_PIN_RF0 = 80,
    GPIO_PIN_RF1 = 81,
    GPIO_PIN_RF2 = 82,
    GPIO_PIN_RF3 = 83,
    GPIO_PIN_RF4 = 84,
    GPIO_PIN_RF5 = 85,
    GPIO_PIN_RF8 = 88,
    GPIO_PIN_RF12 = 92,
    GPIO_PIN_RF13 = 93,
    GPIO_PIN_RG0 = 96,
    GPIO_PIN_RG1 = 97,
    GPIO_PIN_RG6 = 102,
    GPIO_PIN_RG7 = 103,
    GPIO_PIN_RG8 = 104,
    GPIO_PIN_RG9 = 105,
    GPIO_PIN_RG12 = 108,
    GPIO_PIN_RG13 = 109,
    GPIO_PIN_RG14 = 110,
    GPIO_PIN_RG15 = 111,

    /* This element should not be used in any of the GPIO APIs.
       It will be used by other modules or application to denote that none of the GPIO Pin is used */
    GPIO_PIN_NONE = -1

} GPIO_PIN;


void GPIO_Initialize(void);

// *****************************************************************************
// *****************************************************************************
// Section: GPIO Functions which operates on multiple pins of a port
// *****************************************************************************
// *****************************************************************************

uint32_t GPIO_PortRead(GPIO_PORT port);

void GPIO_PortWrite(GPIO_PORT port, uint32_t mask, uint32_t value);

uint32_t GPIO_PortLatchRead ( GPIO_PORT port );

void GPIO_PortSet(GPIO_PORT port, uint32_t mask);

void GPIO_PortClear(GPIO_PORT port, uint32_t mask);

void GPIO_PortToggle(GPIO_PORT port, uint32_t mask);

void GPIO_PortInputEnable(GPIO_PORT port, uint32_t mask);

void GPIO_PortOutputEnable(GPIO_PORT port, uint32_t mask);

// *****************************************************************************
// *****************************************************************************
// Section: GPIO Functions which operates on one pin at a time
// *****************************************************************************
// *****************************************************************************

static inline void GPIO_PinWrite(GPIO_PIN pin, bool value)
{
    GPIO_PortWrite((GPIO_PORT)(pin>>4), (uint32_t)(0x1) << (pin & 0xF), (uint32_t)(value) << (pin & 0xF));
}

static inline bool GPIO_PinRead(GPIO_PIN pin)
{
    return (bool)(((GPIO_PortRead((GPIO_PORT)(pin>>4))) >> (pin & 0xF)) & 0x1);
}

static inline bool GPIO_PinLatchRead(GPIO_PIN pin)
{
    return (bool)((GPIO_PortLatchRead((GPIO_PORT)(pin>>4)) >> (pin & 0xF)) & 0x1);
}

static inline void GPIO_PinToggle(GPIO_PIN pin)
{
    GPIO_PortToggle((GPIO_PORT)(pin>>4), 0x1 << (pin & 0xF));
}

static inline void GPIO_PinSet(GPIO_PIN pin)
{
    GPIO_PortSet((GPIO_PORT)(pin>>4), 0x1 << (pin & 0xF));
}

static inline void GPIO_PinClear(GPIO_PIN pin)
{
    GPIO_PortClear((GPIO_PORT)(pin>>4), 0x1 << (pin & 0xF));
}

static inline void GPIO_PinInputEnable(GPIO_PIN pin)
{
    GPIO_PortInputEnable((GPIO_PORT)(pin>>4), 0x1 << (pin & 0xF));
}

static inline void GPIO_PinOutputEnable(GPIO_PIN pin)
{
    GPIO_PortOutputEnable((GPIO_PORT)(pin>>4), 0x1 << (pin & 0xF));
}


// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif
// DOM-IGNORE-END
#endif // PLIB_GPIO_H
