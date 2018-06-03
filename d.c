

#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "hc06.h"
#include "usart.h"



void InitUART(void)
{
    BRGH = 1;
    SPBRG = ((_XTAL_FREQ/16)/BAUDRATE) - 1;
    PIND1 = 0; // TX Pin
    PIND0 = 1; // RX Pin
    TXSTA = 0x24;
    RCSTA = 0x90;
    //SPBRG  = 129;
}
void SendByteSerially(unsigned char Byte) // Writes a character to the serial port
{
    while(!TXIF) ; // wait for previous transmission to finish
    TXREG = Byte;
}

unsigned char ReceiveByteSerially(void) // Reads a character from the serial port
{
    while(!RCIF)
        continue;   // Wait for transmission to receive
    return RCREG;
}

void SendStringSerially(const unsigned char* st)
{
    while(*st)
        SendByteSerially(*st++);
}


void main (void)
{
    unsigned char SerialData;
    unsigned int i;
    DDRC=0xFF;
    PORTC=0xFF;
    InitUART(); // Intialize UART
    SendStringSerially("Hello World");
    while(1)
    {
        PORTB=0x00;
        for(i=0; i<100; i++)
            _delay_ms(10);
        PORTB=0x01;
        for(i=0; i<100; i++)
            _delay_ms(10);
        SerialData = ReceiveByteSerially();
        SendByteSerially(SerialData);
    }
}




