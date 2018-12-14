Filename: MOD_6_LINE_SENSOR  
Authors: Marquez Jones, Daniel Olis  
Github: https://github.com/OlisDS/UF_RSLK_LINE_SENSOR.git  

Desc: 
This code will consist of drivers for students to interface the line sensor and their robot  
along with example code for the sensor. Demonstation code will also be included.
This may incorporate additional mod 6 content(TBD).  

Objectives of the Module(from TI document):  
1. Basics of functions, conditionals, loops, and calculations in C (covered by all TAs)  
2. Use GPIO to perform input and output (covered by Brit's code?)  
3. Learning how light is converted to voltage(probably skipped)  
4. Learning how to interface the line sensor to the MCU(our primary purpose)  

Software Notes:  
The TI module instructs students to run TExas(header file included in TI code) 
on the msp432 to use an o-scope feature. Since we'll have DADs in theory, we will 
ignore this part of the instructions.

Hardware Notes:  
The sensor will return 0 if sees white and 1 if sees black.
Based on robot construction guidelines the line sensors is attached to Port 7 on the MCU.
With this pin 7 is the far right while pin 0 is the far left. 
There's also an IR LED attached to P5.3 which is recommended to be turned on 
for each line sensor read operation.

Line Sensor Notes:  
Pololu Info: https://www.pololu.com/product/961  
TI use instructions for line sensor reading(from 6.4.3)  
1) Set P5.3 high (turn on IR LED)  
2) Make P7.7 – P7.0 outputs, and set them high (charging 8 capacitors)   
3)Wait 10 us, Clock_Delay1us(10);  	
4) Make P7.7 – P7.0 input   
5)Wait time us, Clock_Delay1us(time);  
6) Read P7.7 – P7.0 inputs (converts voltages into binary)   
7) Set P5.3 low (turn off IR LED, saving power)   
8) Return 8-bit binary measured in step 6  

Effectively in order to read the sensor status, you must charge an
on board capacitor by setting the P7.7 - 7.0 high then reading the pins. 
For some analog reason we will abstract away, black reflectance causes the 
capactitor to discharge a slower rate which allows us to read high for the IO input.
10us for charge and the variable time for discharge. 
The TI doc says to make time and input variable, but the suggested time is 1000us. 
The student is supposed to use an O-scope to varify that this is correct, but we'll
probably skip over the having them do that and just hard code that in driver.

With the nature of the sensor hardware, an interrupt driven solution to detecting sensor
state changes is not practical. 
