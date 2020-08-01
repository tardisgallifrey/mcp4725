README.md

MCP4725 DAC project in C, C++, C#

This is part of a project I'm working on with a rasberry pi 
to learn how to utilized and program an MCP4725 12-bit DAC.

I give original credit to Lewis Loflin as he, once again,
was able to figure out the registers and write an initial
C program.  

As opposed to an ADC, this one is  much simpler.  You simply 
load your registers and send them out.  The current C program 
runs a loop to increase the output of the DAC from 0 to 4096 (12-bits).

It is interesting to note that in the program, in order for the 
12 bits loaded in a 16 bit integer, one must shift it right and then
left in order to get the 8-bit MSB and LSB registers to share the 
number. (or, is that shift left and then right?).

The program works as written.  Check there for details.

I am also currently working on porting this same routine to 
other languages.  C# (.NET) will show up soon, followed by C++, 
and maybe Go, in the future.

In addition, I need to function-ize the routine so that it can be 
called as a discrete program in other languages.

Example: MCP4725set 2048

Also, the actual voltage output is determined by VCC of the board.  
For the raspberry pi, that is 3.3VDC.  I'll have to work on something 
to make it do an industry standard of 0-5VDC or 0-10VDC.


