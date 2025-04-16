/*
 * main.c
 *
 *  Created on: Mar 2, 2024
 *      Author: Ahmed
 */

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_register.h"
#include "DIO_interface.h"
#include "GIE_interface.h"
#include "TIMER_interface.h"
#include "TIMER_register.h"
#include "UART_interface.h"
#include "UART_register.h"
#include "StepperMotor_config.h"
#include "StepperMotor_interface.h"
#include "Proximity_Interface.h"
#include "DC_MOTOR_interface.h"
#include "DC_MOTOR_config.h"
#include "LIMIT_SWITCH_config.h"
#include "LIMIT_SWITCH_interface.h"
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define CONVEYOR_DEFAULT_DIR	DIR_CW
#define HH_OPENING_TIME			2250 // MILLI SECONDS
#define HH_STOP_TIME			800 // MILLI SECONDS
#define HH_BREAK_TIME			100
#define VH_OPENING_TIME			800 // MILLI SECONDS
#define VH_STOPPING_TIME		300
#define SHRINKING_PULSES		1200//175       //16cm
#define UART_TRANSMIT_DELAY		15
#define MACHINE_START_CODE		255
#define MACHINE_STOP_CODE		254
#define MACHINE_RUNNING			1
#define MACHINE_STOPPED			0
#define TRUE					1
#define FALSE					0


void Conveyor_voidRun(u8 Copy_u8Speed);

/************** Horizontal Heaters Mechanism *************/
void HH_voidMechanismClose(void);

void HH_voidMechanismOpen(void);

void HH_voidMechanismStop(void);

void HH_voidMechanismRun(void);
/*****************************************************************/

// Motors Running in direction that is away from the funnel bag
// Opening the mechanism to stop sealing the bag
void VH_voidMechanismOpen(void);

// Motors Running in direction that is near the funnel bag
// Closing the mechanism to start sealing the bag
void VH_voidMechanismClose(void);

// Stop the motors from rotating
void VH_voidMechanismStop(void);

// Running the process of sealing (opening then closing then opening and so on...)
void VH_voidMechanismRun(void);

// Shrinking the bag
void Shrink_voidRun(void);

// Millis
void Millis_voidInit();

void Millis_voidCount();

long int string_to_long(const char *str);

void Received_Data(void);

void Machine_voidStop(void);

void Machine_voidRunWithoutProducts(void);

void Machine_voidRun(void);

void Machine_voidDelay_ms(u32 Copy_u32Time);

void Machine_voidCountAndSendProducts(void);

u8 Machine_u8IsStopped(void);

u8 Machine_u8IsConveyorStopped(void);


// Global Variables
extern u8 GlobalUART_u8RXData; // received data
u32 Global_u32Products = 0; // products counter
u32 Global_u32CurrentMillis = 0; // millis
u8 Global_u8ConveyorPercentage = 0; // conveyor speed percentage
u8 Global_u8MachineStatus = MACHINE_STOPPED; // machine status
u8 Global_u8FirstOperation = FALSE; // first operation flag


// Main Function
int main()
{
	// Initialize the system
	GIE_Enable();
	Millis_voidInit();
	Proximity_voidInit();
	MOTOR_voidInit();
	Stepper_voidInit();
	LIMIT_SW_voidInit();
	UART_voidInit();
	UART_u8RXSetCallBack(&Received_Data);

	// Set the conveyor speed to 80 as a default
	MOTOR_voidSetSpeed(80);

	// Stop all Machine dc motors
	Machine_voidStop();

	while(1)
	{
		// check if the machine is running
		if(Global_u8MachineStatus == MACHINE_RUNNING)
		{
			// check if the first operation flag is set, no product will be packed
			if(Global_u8FirstOperation == TRUE)
			{
				// clear the first operation flag
				Global_u8FirstOperation = FALSE;

				// run all machine processes without packing products (conveyor off)
				// and handle the received data continuously for the conveyor speed and machine stop synchronization
				Machine_voidRunWithoutProducts();
			}
			else
			{
				// normal machine operation, products can be packed
				// and handle the received data continuously for the conveyor speed and machine stop synchronization
				Machine_voidRun();
			}
		}
	}

	return 0;
}


void Millis_voidInit()
{
	TCNT2 = 131;
	TIMER2_voidInit();
	TIMER2_u8SetCallBack(Millis_voidCount);
}

void Millis_voidCount()
{
	Global_u32CurrentMillis++; // counting every 1ms
	TCNT2 = 131;
}
/************ Conveyor **********************************/
void Conveyor_voidRun(u8 Copy_u8Speed)
{
	// check if the machine is stopped
	if(Machine_u8IsStopped()) return;

	// check if the conveyor is stopped
	if(Machine_u8IsConveyorStopped()) return;

	// local variables to store the proximity state and the string to send the products counter
	u8 local_u8ProximityState;

	MOTOR_voidSetSpeed(Copy_u8Speed);
	MOTOR_voidRotate(CONVEYOR_MOTOR, DIR_CW);

	do
	{
		// check if the machine is stopped
		if(Machine_u8IsStopped()) return;

		// check if the conveyor is stopped
		if(Machine_u8IsConveyorStopped()) return;

		// check if the object is detected
		local_u8ProximityState = Proximity_u8GetState();

		// debounce delay
		_delay_ms(50);
	}while(local_u8ProximityState==OBJECT_NOT_DETECTED); // wait until the object is detected

	// stopping the conveyor
	MOTOR_voidStop(CONVEYOR_MOTOR);
}
/*********************************************************/

/************** Horizontal Heaters Mechanism *************/
void HH_voidMechanismClose(void)
{
	MOTOR_voidRotate(HH_MOTOR, DIR_CCW);
}

void HH_voidMechanismOpen(void)
{
	//Open mechanism
	MOTOR_voidRotate(HH_MOTOR, DIR_CW);
}

void HH_voidMechanismStop(void)
{
	//Stop the mechanism
	MOTOR_voidStop(HH_MOTOR);
}


void HH_voidMechanismRun(void)
{
	// check if the machine is stopped
	if(Machine_u8IsStopped()) return;

	// Local variable to store the limit switch state
	u8 Local_u8LimitSWState = LIMIT_SW_NOT_REACHED;

	// Close the mechanism to start sealing the bag
	HH_voidMechanismClose();

	// Wait until the limit switch is reached/pressed
	do
	{
		// check if the machine is stopped
		if(Machine_u8IsStopped()) return;

		// reading the limit switch state
		Local_u8LimitSWState = LIMIT_SW_u8GetState(HH_LIMIT_SW);
		// debouncing delay
		_delay_ms(50);
	}
	while(Local_u8LimitSWState == LIMIT_SW_NOT_REACHED); // waiting until the limit switch is reached

	// Stop the mechanism for some time to ensure that the bag is sealed
	HH_voidMechanismStop();
	Machine_voidDelay_ms(HH_STOP_TIME);

	// check if the machine is stopped
	if(Machine_u8IsStopped()) return;

	// return the jaws to the initial position
	HH_voidMechanismOpen();
	Machine_voidDelay_ms(HH_OPENING_TIME);

	// Stop the mechanism
	HH_voidMechanismStop();
}
/*****************************************************************/

/***************** Vertical Heaters Mechanism*********************/
void VH_voidMechanismOpen(void)
{
	/*Right Motor Mechanism is Opening*/
	MOTOR_voidRotate(VH_R_MOTOR, DIR_CW);

	/*Left Motor Mechanism is Opening*/
	MOTOR_voidRotate(VH_L_MOTOR, DIR_CCW);
}

void VH_voidMechanismClose(void)
{
	/*Right Motor Mechanism is Closing*/
	MOTOR_voidRotate(VH_R_MOTOR, DIR_CCW);

	/*Left Motor Mechanism is Closing*/
	MOTOR_voidRotate(VH_L_MOTOR, DIR_CW);
}

void VH_voidMechanismStop(void)
{
	/*Stopping Right Motor*/
	MOTOR_voidStop(VH_R_MOTOR);

	/*Stopping Left Motor*/
	MOTOR_voidStop(VH_L_MOTOR);
}

void VH_voidMechanismRun(void)
{
    // Check if machine is stopped, return if true
    if (Machine_u8IsStopped()) return;

    // Variables to track limit switch states and motor statuses
    u8 leftLimitSwitch = LIMIT_SW_NOT_REACHED, rightLimitSwitch = LIMIT_SW_NOT_REACHED;
    u8 leftMotorStopped = FALSE, rightMotorStopped = FALSE;

    // Close the mechanism
    VH_voidMechanismClose();

    // Wait until both motors reach their limit switches
    while (!leftMotorStopped || !rightMotorStopped)
    {
        // Check if machine is stopped, return if true
        if (Machine_u8IsStopped()) return;

        // Read limit switches
        leftLimitSwitch = LIMIT_SW_u8GetState(VH_L_LIMIT_SW);
        rightLimitSwitch = LIMIT_SW_u8GetState(VH_R_LIMIT_SW);

        // Stop left motor if limit switch is reached
        if (!leftMotorStopped && leftLimitSwitch == LIMIT_SW_REACHED)
        {
            MOTOR_voidStop(VH_L_MOTOR);
            leftMotorStopped = TRUE;
        }

        // Stop right motor if limit switch is reached
        if (!rightMotorStopped && rightLimitSwitch == LIMIT_SW_REACHED)
        {
            MOTOR_voidStop(VH_R_MOTOR);
            rightMotorStopped = TRUE;
        }

        // Debounce delay for limit switches
        _delay_ms(50);
    }

    // Stop the mechanism for some time
    VH_voidMechanismStop();
	Machine_voidDelay_ms(VH_STOPPING_TIME);

    // Check if machine is stopped, return if true
    if (Machine_u8IsStopped()) return;

    // Open the mechanism for some time
    VH_voidMechanismOpen();
	Machine_voidDelay_ms(VH_OPENING_TIME);

    // Stop the mechanism
    VH_voidMechanismStop();
}
/*****************************************************************/

/********* Shrinking Process *********************/
void Shrink_voidRun(void)
{
	// Keep this directions as they are, rotating stepper in opposite direction will cause the plastic film to be pulled downards
	DIO_u8SetPinValue(SL_DIR_PORT, SL_DIR_PIN, DIO_u8PIN_LOW);
	DIO_u8SetPinValue(SR_DIR_PORT, SR_DIR_PIN, DIO_u8PIN_HIGH);

	// Calibrate the required pulses for shrinking the required length
	for(int i = 0; i < SHRINKING_PULSES; i++)
	{
		// check if machine is stopped
		if(Machine_u8IsStopped()) return;

		// Pulse the stepper motors
		DIO_u8SetPinValue(SL_PULSE_PORT, SL_PULSE_PIN, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(SR_PULSE_PORT, SR_PULSE_PIN, DIO_u8PIN_HIGH);
		_delay_ms(2);
		DIO_u8SetPinValue(SL_PULSE_PORT, SL_PULSE_PIN, DIO_u8PIN_LOW);
		DIO_u8SetPinValue(SR_PULSE_PORT, SR_PULSE_PIN, DIO_u8PIN_LOW);
		_delay_ms(2);
	}
}
/*****************************************************************/

/************Converting a tring to long number******************* */
long int string_to_long(const char *str) 
{
    char *endptr;

    // Convert string to long integer
    long int result = strtol(str, &endptr, 10);

    // return the result
    return result;
}
/*****************************************************************/

/************Callback function for the received data**************/
void Received_Data(void)
{
    // Use switch-case for more efficient branching
    switch (GlobalUART_u8RXData)
    {
        case MACHINE_START_CODE:
            // Start the machine
            Global_u8MachineStatus = MACHINE_RUNNING;
            Global_u8FirstOperation = TRUE;
            break;

        case MACHINE_STOP_CODE:
            // Stop the machine
            Global_u8MachineStatus = MACHINE_STOPPED;
            break;

        default:
            // Set the conveyor speed
            Global_u8ConveyorPercentage = GlobalUART_u8RXData;
            break;
    }
}
/******************************************************************/

/****************MFlowpack Machine app functions************/
void Machine_voidStop(void)
{
	MOTOR_voidStop(HH_MOTOR);
	MOTOR_voidStop(VH_L_MOTOR);
	MOTOR_voidStop(VH_R_MOTOR);
	MOTOR_voidStop(CONVEYOR_MOTOR);
}

// Run the machine without products
// this function is used for ensuring that first seal is done and the plastic film is seal from bottom and products can fall inside the bag
// the conveyor will be off and the machine will run the processes without packing products
// the machine will stop when the stop code is received
void Machine_voidRunWithoutProducts(void)
{
	// Vertical heaters mechanism Run
	VH_voidMechanismRun();

	// Shrinking the plastic film
	Shrink_voidRun();

	// Horizontal heaters mechanism Run
	HH_voidMechanismRun();
}

// Run the machine with products
// this function is used for running the machine in normal mode
// the conveyor will be on and the machine will run the processes with packing products
// the machine will stop when the stop code is received
void Machine_voidRun(void)
{
	// Vertical heaters mechanism Run
	VH_voidMechanismRun();

	// Shrinking the plastic film
	Shrink_voidRun();

	// Run the conveyor
	Conveyor_voidRun(Global_u8ConveyorPercentage);

	// Horizontal heaters mechanism Run
	HH_voidMechanismRun();

	// Count the products and send the counter to the second micro
	Machine_voidCountAndSendProducts();
}

void Machine_voidDelay_ms(u32 Copy_u32Time)
{
	// local variable to store the current millis count
	u32 Local_u32StartMillis = Global_u32CurrentMillis;
	do
	{
		// this algorithm is used to handle machine stop while waiting
		// check if the machine is stopped
		if(Machine_u8IsStopped())
			return;

	}while(Global_u32CurrentMillis - Local_u32StartMillis < Copy_u32Time); // wait for the required time as a delay
}

u8 Machine_u8IsStopped(void)
{
	// check if the machine is stopped
	if(Global_u8MachineStatus == MACHINE_STOPPED)
	{
		// stop the machine
		Machine_voidStop();

		// return true
		return TRUE;
	}

	// return false
	return FALSE;
}

u8 Machine_u8IsConveyorStopped(void)
{
	// check if the conveyor is stopped
	if(Global_u8ConveyorPercentage == 0)
	{
		// stop the conveyor
		MOTOR_voidStop(CONVEYOR_MOTOR);

		// return true
		return TRUE;
	}

	// return false
	return FALSE;
}

void Machine_voidCountAndSendProducts(void)
{
	// local variables to store the string to send the products counter
	u8 Local_u8String[10], i = 0;

	// increment the products counter
	Global_u32Products++;
	
	// sending the products to second micro as a string
	sprintf(Local_u8String, "%u", Global_u32Products);
	
	while (Local_u8String[i]) 
	{
		UART_voidSendData(Local_u8String[i]);
		i++;
		_delay_ms(UART_TRANSMIT_DELAY);

    }
    UART_voidSendData('\0');
}
/*******************************************************************/

