/*
 * Filename: LineSensor.c
 * Author: Marquez Jones
 * Desc: This contains drivers necessary to interface the MSP432 launchpad with the
 * Line Sensor board
 *
 * Hardware Notes: The line sensor is attached for Port 7 pins 7 to 0.
 * Pin 7 - far left
 * Pin 0 - far right
 */

/************************INCLUDES*****************************/
#include<stdint.h>
#include"msp.h"
#include"Clock.h"
#include "LineSensor.h"

/*
 * Desc: Initializes pins in use of the line sensor
 * Port 7:
 * All pins initialized as I/O and inputs
 *
 * Port 5:
 * Pin 3 initialized as I/O and set to output
 * Pin set low(turns off IR LED)
 *
 * Inputs: None
 * Outputs: None
 * Assumptions: None
 */
void line_sensor_init(void){

    //we can go through and add bitmasks later
    P5->SEL0 &= ~0x08;
    P5->SEL1 &= ~0x08;    // configure P5.3 as GPIO
    P5->DIR |= 0x08;      // make P5.3 out
    P5->OUT &= ~0x08;     // turn off LEDs
    P7->SEL0 = 0x00;
    P7->SEL1 = 0x00;      // configure P7.7-P7.0 as GPIO
    P7->DIR = 0x00;       // make P7.7-P7.0 in

}

/*
 * Desc: Reads line sensor
 * TI use instructions(from 6.4.3)
 *   1) Set P5.3 high (turn on IR LED)
 *   2) Make P7.7 – P7.0 outputs, and set them high (charging 8 capacitors)
 *   3)Wait 10 us, Clock_Delay1us(10);
 *   4) Make P7.7 – P7.0 input
 *   5)Wait time us, Clock_Delay1us(time);
 *   6) Read P7.7 – P7.0 inputs (converts voltages into binary)
 *   7) Set P5.3 low (turn off IR LED, saving power)
 *   8) Return 8-bit binary measured in step 6
 * Inputs: None
 * Outputs: sensor status as an 8 bit value
 * Assumptions:
 * That line_sensor_init() was called
 * The clock is set to 48 MHz
 */
uint8_t line_read(void){
    uint8_t result;
    P5->OUT |= 0x08;      // turn on 8 IR LEDs
    P7->DIR = 0xFF;       // make P7.7-P7.0 out
    P7->OUT = 0xFF;       // prime for measurement
    Clock_Delay1us(10);   // wait 10 us
    P7->DIR = 0x00;       // make P7.7-P7.0 in

    /*
     * as advised in the TI lab document,
     * the student should wait 1000 before
     * reading the state of the line sensor
     */
    Clock_Delay1us(1000); // wait 1000 us
    result = P7->IN;      // 1 means black, 0 means white
    P5->OUT &= ~0x08;     // turn off 8 IR LEDs
    return result;
}

/*
 * Desc: outputs a distance(in 0.1 mm) between center of robot and line
 *       if the line is not within range of the, the function will output an
 *       error code
 *
 * Hardware Notes:
 * Assuming the robot is constructed with P7.7 being far left
 * and P7.0 being on the far right,
 *
 * A negative value should mean the line is on the left side of the robot
 * while a positive value means the line is right of the robot's center
 *
 * Inputs: data from line read
 * Outputs: signed distance from center or error
 * Assumes: the data comes from a line sensor mounted to the robot
 */

/*
 * modified from reflectance position in solution code reflectance.c
 * Based on formula in 6.4.4 in TI lab manual
 */

const int32_t Weight[8] = {332, 237, 142, 47, -47, -142, -237, -332}; // Weights provided TI
const int32_t Mask[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};    // Bit masks
int32_t line_position(uint8_t data){

    /*
     * relating back to the formula in 6.4.4
     * count is the sum of the bits which whose values can only be 1 or 0
     */
    uint32_t i; int32_t sum,count;
     if(data){ // calculate only if some active
       sum = 0; count=0;
       for(i=0;i<8;i++){

         if(data&Mask[i]){

           sum += Weight[i];
           count++;

         }
       }
       return sum/count; //distance measurement
     }

     // no sensors see black line if data = 0
     else{

         //original code returned Weight[0] + 1 (333)
         //code was to guess and see if the line was on the right
         //added the error code for external decision making
         return NO_LINE_ERROR;

     }

}

