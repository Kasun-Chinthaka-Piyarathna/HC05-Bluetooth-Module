//Micricontroller		:All 8-bit AVR Micricontrollers with Similar Register Configuration with ATmega16
//System Clock			:8 MHz
//Header File Version 		:1.1

/*The functions and macros defined in this header file are for HC-06 Bluetooth Module*/

#ifndef	_HC06_H_
#define	_HC06_H_ 	1



#include<avr/io.h>
#include<util/delay.h>
#include<usart.h>

char hc_06_buffer1[3], hc_06_buffer2[15];

void hc_06_bluetooth_transmit_byte(char data_byte);
char hc_06_bluetooth_receive_byte(void);
void hc_06_bluetooth_transmit_string(char *transmit_string);
char *hc_06_bluetooth_receive_string(char *receive_string, unsigned char terminating_character);
unsigned char hc_06_bluetooth_at_command_mode_test(void);
unsigned char hc_06_bluetooth_device_name_change(char *device_name);
unsigned char hc_06_bluetooth_get_version(void);
unsigned  char hc_06_bluetooth_change_baud_rate(long int baud_rate);
unsigned  char hc_06_bluetooth_pin_change(char *new_pin);


void hc_06_bluetooth_transmit_byte(char data_byte)
{
	usart_data_transmit(data_byte);
}
char hc_06_bluetooth_receive_byte(void)
{
	return usart_data_receive();
}
void hc_06_bluetooth_transmit_string(char *transmit_string)
{
	usart_string_transmit(transmit_string);
}
char *hc_06_bluetooth_receive_string(char *receive_string, unsigned char terminating_character)
{
	unsigned char temp=0x00;
	for(unsigned char i=0;;i++)
	{
		*(receive_string+i)=usart_data_receive();
		if(*(receive_string+i)==terminating_character)
			break;
		else
			temp++;
	}
	*(receive_string+temp)='\0';
	return receive_string;
}
unsigned char hc_06_bluetooth_at_command_mode_test(void)
{
	usart_string_transmit("AT");
	for(unsigned char i=0; i<2;i++)
	{
		hc_06_buffer1[i]=usart_data_receive();
	}
	hc_06_buffer1[2]=0;
	if(!(strcmp(hc_06_buffer1,"OK")))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
unsigned char hc_06_bluetooth_device_name_change(char *device_name)
{
	usart_string_transmit("AT+NAME");
	usart_string_transmit(device_name);
	for(unsigned char i=0; i<9;i++)
	{
		hc_06_buffer2[i]=usart_data_receive();
	}
	hc_06_buffer2[9]=0;	
	if(!(strcmp(hc_06_buffer2,"OKsetname")))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
unsigned char hc_06_bluetooth_get_version(void)
{
	usart_string_transmit("AT+VERSION");
	for(unsigned char i=0; i<2;i++)
	{
		hc_06_buffer1[i]=usart_data_receive();
	}
	hc_06_buffer1[2]=0;
	for(unsigned char i=0; i<10;i++)
	{
		hc_06_buffer2[i]=usart_data_receive();
	}
	hc_06_buffer2[10]=0;
	if(!(strcmp(hc_06_buffer1,"OK")))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
unsigned  char hc_06_bluetooth_change_baud_rate(long int baud_rate)
{
	if(baud_rate==1200)
	{
		usart_string_transmit("AT+BAUD1");
	}
	else if(baud_rate==2400)
	{
		usart_string_transmit("AT+BAUD2");
	}
	else if(baud_rate==4800)
	{
		usart_string_transmit("AT+BAUD3");
	}
	else if(baud_rate==9600)
	{
		usart_string_transmit("AT+BAUD4");
	}
	else if(baud_rate==19200)
	{
		usart_string_transmit("AT+BAUD5");
	}
	else if(baud_rate==38400)
	{
		usart_string_transmit("AT+BAUD6");
	}
	else if(baud_rate==57600)
	{
		usart_string_transmit("AT+BAUD7");
	}
	else if(baud_rate==115200)
	{
		usart_string_transmit("AT+BAUD8");
	}
	else if(baud_rate==230400)
	{
		usart_string_transmit("AT+BAUD9");
	}
	else if(baud_rate==460800)
	{
		usart_string_transmit("AT+BAUDA");
	}
	else if(baud_rate==921600)
	{
		usart_string_transmit("AT+BAUDB");
	}
	else if(baud_rate==1382400)
	{
		usart_string_transmit("AT+BAUDC");
	}
	else
	{
		;
	}
	for(unsigned char i=0; i<2;i++)
	{
		hc_06_buffer1[i]=usart_data_receive();
	}
	hc_06_buffer1[2]=0;
	
	if(baud_rate<=9600)
	{
		for(unsigned char i=0; i<4;i++)
		{
			hc_06_buffer2[i]=usart_data_receive();
		}
		hc_06_buffer2[4]=0;
	}
	else if(baud_rate<=57600)
	{
		for(unsigned char i=0; i<5;i++)
		{
			hc_06_buffer2[i]=usart_data_receive();
		}
		hc_06_buffer2[5]=0;
	}
	else if(baud_rate<=921600)
	{
		for(unsigned char i=0; i<6;i++)
		{
			hc_06_buffer2[i]=usart_data_receive();
		}
		hc_06_buffer2[6]=0;
	}
	else if(baud_rate==1382400)
	{
		for(unsigned char i=0; i<7;i++)
		{
			hc_06_buffer2[i]=usart_data_receive();
		}
		hc_06_buffer2[7]=0;
	}
	if(!(strcmp(hc_06_buffer1,"OK")))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
unsigned  char hc_06_bluetooth_pin_change(char *new_pin)
{
	usart_string_transmit("AT+PIN");
	usart_string_transmit(new_pin);
	for(unsigned char i=0; i<2;i++)
	{
		hc_06_buffer1[i]=usart_data_receive();
	}
	hc_06_buffer1[2]=0;
	for(unsigned char i=0; i<6;i++)
	{
		hc_06_buffer2[i]=usart_data_receive();
	}
	hc_06_buffer2[6]=0;
	if(!(strcmp(hc_06_buffer1,"OK")))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

#endif










