/*
 * Author: Marquez Jones
 * Project: Module 6 Line Sensor Read Demo
 * Desc: This demo will read from the line sensor and output the results
 * to an LED array
 *
 * Hardware Notes: By TI instructions the light sensor is on port 7
 * which is what the students will use in the final robot design.
 *
 * For demo purposes I set port 4 to outputs
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

	    //continually read sensor and output results

	    //read sensor
	    line_state = line_read();

	    //output result to LED
	    led_write(line_state);

	}

}

/***********************FUNCTION PROTOTYPES***********************************/

// sets all pins on port 4 to output
void led_init(void){

    // set all pins on port 4 as IO
    P4->SEL0 &= 0x00;
    P4->SEL1 &= 0x00;

    //set all pins as output
    P4->DIR |= 0xFF;

    //initialize LEDs as off
    P4->OUT &= 0x00;
}

//writes 8 bit value to LEDs on port 4
void led_write(uint8_t data){

    //set LED outputs to line results
    /*
     * with the sensor convention of 0 = white and 1 = blackj
     * on LEDs will represent bits that are on the line
     */
    P4->OUT = data;

}
