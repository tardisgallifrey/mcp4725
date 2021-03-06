using System;
using System.Device.I2c;
using System.Diagnostics;
using System.Threading;
using System.Device.Gpio;

namespace MCP4725
{
    class Program
    {
        static void Main(string[] args)
        {

            int val;
            int count = 0;
            byte[] writeBuf = new byte[3];

            // set I2C bus ID: 1

            //Create a device with these settings: bus 1, address 0x60
            //This writes the first byte, I think
            I2cConnectionSettings settings = new I2cConnectionSettings(1, 0x60);
            I2cDevice mcp4725 = I2cDevice.Create(settings);

            //control byte
            //0x40 = normal
            //0x60 = write EEPROM
            writeBuf[0] = 0x40;

            //These 2 bytes make write register
            //Just setting up, using later
            writeBuf[1] = 0;        //MSB
            writeBuf[2] = 0;        //LSB
            

            while(count < 4096){
                val = count;

                //val is an int (16bits)
                //writeBuf is a byte (8bits)
                //this method lops off the extra bits
                //so that an overflow error isn't produced
                writeBuf[1] = (byte)(val >> 4);
                writeBuf[2] = (byte)(val << 4);

                try
                {
                    mcp4725.Write(writeBuf);

                }
                catch
                {

                    Console.WriteLine("Error on last Read");
                    Console.WriteLine("Check your wiring");
                    Console.WriteLine("Problem with I2C bus possible");
                    Console.WriteLine("DID YOU RUN THIS AS 'SUDO'?");
                    System.Environment.Exit(0);

                }

                Console.WriteLine($"{val}     {writeBuf[1]}     {writeBuf[2]}");
                count += 100;
                Thread.Sleep(2000);
            }
        
        }
    }
}
