#define F_CPU 16000000UL
#define D4 eS_PORTB4
#define D5 eS_PORTB5
#define D6 eS_PORTB6
#define D7 eS_PORTB7
#define RS eS_PORTB2
#define EN eS_PORTB3

#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include <stdlib.h>
#include <stdio.h>

char keypad_digit[4][4]= {{1,2,3,4},
						  {5,6,7,8},
						  {9,10,11,12},
						  {13,14,15,16}};
							
int d = 0;
int h= 0;
int x= 0;

unsigned char keypad(void);
unsigned char key_Digit(void);

int main(void)
{
	
	DDRB= 0xFF;
	Lcd4_Init();
	DDRD=0xF0;
	PORTD=0x0F;
	
	char lcd_string1[20]= {}, lcd_string2[20]= {}, lcd_string3[20]= {};
	char a1=0, a2=0, a3=0;
	
	int i=0;
	for(i=0; i<3; i++){
		
		char enter[20]= "Enter 3 digits: ";
		Lcd4_Set_Cursor(1,1);
		Lcd4_Write_String(enter);
		
		if(i==0){
		a1= key_Digit();
		itoa(a1, lcd_string1, 10);
		Lcd4_Set_Cursor(2,1);
		Lcd4_Write_String(lcd_string1);
		_delay_ms(500);
		}
		
		if(i==1){
		a2= key_Digit();
		itoa(a2, lcd_string2, 10);
		Lcd4_Set_Cursor(2,4);
		Lcd4_Write_String(lcd_string2);
		_delay_ms(500);
		}
		
		if(i==2){
		a3= key_Digit();
		itoa(a3, lcd_string3, 10);
		Lcd4_Set_Cursor(2,7);
		Lcd4_Write_String(lcd_string3);
		_delay_ms(500);
		}
	}
	
	_delay_ms(1000);
	Lcd4_Clear();
	
	char string1[20]= {'*'};
	char correct[20]= "CORRECT !!";
	char incorrect[20]= "INCORRECT";
	
	while(1)
	{
		
		char enter2[20]= "Guess 3 digits: ";
		Lcd4_Set_Cursor(1,1);
		Lcd4_Write_String(enter2);
		
		
		char b1=0,b2=0,b3=0;
		int i=0;
		for(i=0; i<3; i++){
			
			if(i==0){
				b1= key_Digit();
				Lcd4_Set_Cursor(2,1);
				Lcd4_Write_String(string1);
				_delay_ms(500);
			}
			if(i==1){
				b2= key_Digit();
				Lcd4_Set_Cursor(2,3);
				Lcd4_Write_String(string1);
				_delay_ms(500);
			}
			if(i==2){
				b3= key_Digit();
				Lcd4_Set_Cursor(2,5);
				Lcd4_Write_String(string1);
				_delay_ms(500);
			}
		}
		
		_delay_ms(500);
		Lcd4_Clear();
		
		if(b1==a1 && b2==a2 && b3==a3){
			Lcd4_Set_Cursor(1,1);
			Lcd4_Write_String(correct);
			_delay_ms(2000);
			Lcd4_Clear();
		}
		else{
			Lcd4_Set_Cursor(1,1);
			Lcd4_Write_String(incorrect);
			_delay_ms(2000);
			Lcd4_Clear();
		}
	}
	
}

unsigned char keypad(void)
{
	unsigned char num;
	
	x= x & 0x0F;
	if(x==0x0E)
	num= keypad_digit[d][0];
	
	if(x==0x0D)
	num= keypad_digit[d][1];
	
	if(x==0x0B)
	num= keypad_digit[d][2];
	
	if(x==0x07)
	num= keypad_digit[d][3];
	
	return num;
}

unsigned char key_Digit(void)
{
	char out;
	
	while(1)
	{
		x=PIND;
		if(x!=0x0f){
			break;
		}
	}
	
	PORTD=0xEF;
	x=PIND;
	if(x!=0xEF){
		d=0;
		out=keypad();
	}
	
	PORTD=0xDF;
	x=PIND;
	if(x!=0xDF){
		d=1;
		out=keypad();
	}
	
	PORTD=0xBF;
	x=PIND;
	if(x!=0xBF){
		d=2;
		out=keypad();
	}
	
	PORTD=0x7F;
	x=PIND;
	if(x!=0x7F){
		d=3;
		out=keypad();
	}
	PORTD=0x0F;
	
	return out;
}

