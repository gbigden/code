/*
* Project name:
     UART (Simple usage of UART module library functions)
* Copyright:
     (c) Mikroelektronika, 2011.
* Revision History:
     20120116:
       - initial release (JK);
* Description:
     This code demonstrates how to use uart library routines. Upon receiving
     data via RS232, MCU immediately sends it back to the sender.
* Test configuration:
     MCU:             PIC18F87K22
                      http://ww1.microchip.com/downloads/en/DeviceDoc/39960b.pdf
     dev.board:       easypic pro v7   ac:UART
                      http://www.mikroe.com/easypic-pro/
     Oscillator:      HS-PLL 64.0000 MHz, 16.0000 MHz Crystal
     Ext. Modules:    None.
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
* NOTES:
     - Turn on RX and TX UART switches (SW5.3 and SW5.4).
*/

char *res;
char last_msg_in[32];
char *fatal_err_str = "ERR";
char *fault_msg_0 = "No response required.";
char *fault_msg_1 = "Fatal fault detected!";
char *fault_msg_2 = "Non-fatal fault detected.";

void main() {
  ANCON0 = 0x00;                  // Configure PORTC pins as digital
  ANCON1 = 0x00;                  // Configure PORTC pins as digital
  ANCON2 = 0x00;                  // Configure PORTC pins as digital
  
  TRISF = 0x00;                   // set direction to be output
  LATF = 0x00;                    // turn OFF the LATF leds
  
  UART2_Init(9600);               // Initialize UART module at 9600 bps
  Delay_ms(100);                  // Wait for UART module to stabilize
  
  //UART2_Write_Text("Start");
  //UART2_Write(13);
  //UART2_Write(10);

  while (1)
  {
    if (UART2_Data_Ready())
    {
      // 32 character message frame is being received...
      UART2_Read_Text(last_msg_in, "13", 32);
      res = strstr(last_msg_in, fatal_err_str);

      if (!res)
      {
           // No processing required - can ignore; just repeat message back to source.
          UART2_Write_Text(fault_msg_0);
          //UART2_Write(13);
          //UART2_Write(10);
      }
      else
      {
          // Fatal fault detected.
          UART2_Write_Text(fault_msg_1);
          UART2_Write(13);
          UART2_Write(10);
      }
    }
  }
}
