//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "siren.h"

#include "smart_home_system.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============
Ticker sirenTicker;     //NUEVO
DigitalOut sirenPin(PE_10);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static bool sirenState = OFF;

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void sirenInit()
{
    sirenPin = ON;
}

bool sirenStateRead() //NO BLOQUEANTE
{
    return sirenState;
}

void sirenStateWrite( bool state ) //NO BLOQUEANTE
{
    sirenState = state;
}

void sirenUpdateVieja( int strobeTime ) 
{
    static int accumulatedTimeAlarm = 0;
    accumulatedTimeAlarm = accumulatedTimeAlarm + SYSTEM_TIME_INCREMENT_MS;
    
    if( sirenState ) { 
        if( accumulatedTimeAlarm >= strobeTime ) {
                accumulatedTimeAlarm = 0;
                sirenPin= !sirenPin;
        }
    } else {
        sirenPin = ON;
    }
}

void toggleSiren() { //NUEVO
    sirenState = !sirenState;  
    sirenPin = sirenState; 
}

void sirenUpdate( int strobeTime )  //NUEVO
{
sirenTicker.attach(toggleSiren, strobeTime);
}

//=====[Implementations of private functions]==================================

