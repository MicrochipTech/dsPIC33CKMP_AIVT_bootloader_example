/**
  @Generated 16-bit Bootloader Source File

  @Company:
    Microchip Technology Inc.

  @File Name: 
    boot_demo.c

  @Summary:
    This is the boot_demo.c file generated using 16-bit Bootloader

  @Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  16-bit Bootloader - 1.23.0
        Device            :  dsPIC33CK256MP508
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.36B
        MPLAB             :  MPLAB X v5.15
*/
/*
Copyright (c) [2012-2023] Microchip Technology Inc.  

    All rights reserved.

    You are permitted to use the accompanying software and its derivatives 
    with Microchip products. See the Microchip license agreement accompanying 
    this software, if any, for additional info regarding your rights and 
    obligations.
    
    MICROCHIP SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT 
    WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT 
    LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT 
    AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP OR ITS
    LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT 
    LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE 
    THEORY FOR ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT 
    LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES, 
    OR OTHER SIMILAR COSTS. 
    
    To the fullest extend allowed by law, Microchip and its licensors 
    liability will not exceed the amount of fees, if any, that you paid 
    directly to Microchip to use this software. 
    
    THIRD PARTY SOFTWARE:  Notwithstanding anything to the contrary, any 
    third party software accompanying this software is subject to the terms 
    and conditions of the third party's license agreement.  To the extent 
    required by third party licenses covering such third party software, 
    the terms of such license will apply in lieu of the terms provided in 
    this notice or applicable license.  To the extent the terms of such 
    third party licenses prohibit any of the restrictions described here, 
    such restrictions will not apply to such third party software.
*/


#include <stdbool.h>
#include <stdint.h>
#include "boot_config.h"
#include "boot_application_header.h"
#include "boot_image.h"
#include "boot_process.h"
#include "../pin_manager.h"

#define DOWNLOADED_IMAGE    0u
#define EXECUTION_IMAGE     0u

static bool inBootloadMode = false;
static bool executionImageRequiresValidation = true;
static bool executionImageValid = false;

static bool EnterBootloadMode(void);

void BOOT_DEMO_Initialize(void)
{    
    
}


void BOOT_DEMO_Tasks(void)
{
    if(inBootloadMode == false)
    {
        if( EnterBootloadMode() == true )
        {
            inBootloadMode = true;
        }
        else
        {
            if( executionImageRequiresValidation == true )
            {
                executionImageValid = BOOT_ImageVerify(EXECUTION_IMAGE);
            }

            if(executionImageValid == false)
            {
                inBootloadMode = true;
            }

            if(inBootloadMode == false)
            {
                /* NOTE: Before starting the application, all interrupts used
                 * by the bootloader must be disabled. Add code here to return
                 * the peripherals/interrupts to the reset state before starting
                 * the application code. */
				 #warning "All interrupt sources and peripherals should be disabled before starting the application.  Add any code required here to disable all interrupts and peripherals used in the bootloader."
				IO_RE13_SetLow();
                __builtin_disable_interrupts();
                BOOT_StartApplication();
                while(1) {                    
                    ;
                }
            }
        }
    }
    
    (void)BOOT_ProcessCommand();
}

static bool EnterBootloadMode(void)
{
    #warning "Update this function to return 'true' when you want to stay in the boot loader, and 'false' when you want to allow a release to the application code"
 
    /* NOTE: This might be a a push button status on power up, a command from a peripheral, 
     * or whatever is specific to your boot loader implementation */    

    return false;
}
