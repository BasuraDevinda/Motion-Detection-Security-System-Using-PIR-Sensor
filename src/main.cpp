#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include<stdbool.h>

void UART_init()
{
    UBRR0 = 103;

    UCSR0B = (1 << TXEN0);

    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void UART_sendChar(char data)
{
    while (!(UCSR0A & (1 << UDRE0)));

    UDR0 = data;
}

void UART_sendString(char *str)
{
    while(*str)
    {
        UART_sendChar(*str);
        str++;
    }
}
int main( void){
  UART_init();
  DDRD &=~(1<<PD2 );//defined the digital pin 2 dreaction of the  as inpu put
  DDRD |= (1 << PD3);//defined the digital pin 3 dreaction of the  as out put
  DDRD |= (1 << PD4);//defined the digital pin 3 dreaction of the  as out put
  bool onLed=false;
  int alarmTime = 5000; // milliseconds


  while(1)//continuously working 
  {
    //this runs continously 
    PORTD |= (1 << PD3);//green led on when detected 
    _delay_ms(1000);
    if ( PIND & (1<<PD2)){// check the actual (current value of  the pd2)
      UART_sendString("detected live  objecte\r\n");
      onLed=true;


      
      
     



    }
    else{
      UART_sendString("not detected live  objecte\r\n");
      onLed=false;

      

    }
    
    PORTD &= ~(1 << PD3);//green led on when detected 
    _delay_ms(1000);

    if (onLed){
      PORTD |= (1 << PD4);//red led on when detected 
      _delay_ms(alarmTime);
    }
    else{
      PORTD &= ~(1 << PD4);//red led off when detected 
    }
  }


 }