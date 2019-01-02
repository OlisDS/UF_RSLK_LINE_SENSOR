/*
 * Author: Student
 * Project: Line Sensor Lab
 * Desc: Write a program that reads the line sensor
 * and outputs the result to an LED array.
 *
 * Hardware Notes: By TI instructions the light sensor is on port 7
 * which is what the students will use in the final robot design.
 *
 * For demo purposes I set port 4 to outputs for LEDs
 */


/*********************************INCLUDES***********************************/

//From CCS
#include "msp.h"

//From TI Robotics kit
#include "Clock.h"

//Made for Workshop
#include "LineSensor.h"

/***********************FUNCTION PROTOTYPES***********************************/

// sets all pins on port 4 to output
void led_init(void);

//writes 8 bit value to LEDs on port 4
void led_write(uint8_t data);

/***********************************MAIN**************************************/

void main(void)
{
  //variables
  uint8_t line_state; //results from line sensor read

	//initialize clock
	Clock_Init48MHz();

	//initialize line sensor
	line_sensor_init();

	//initialize LED pins
	led_init();



	while(1){

	   //insert your code here

	}

}

/***********************FUNCTION PROTOTYPES***********************************/

// sets all pins on port 4 to output
void led_init(void){

  //insert your code here
  
}

//writes 8 bit value to LEDs on port 4
void led_write(uint8_t data){

   //inser your code here

}
