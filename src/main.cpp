#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
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
  DDRB &=~(1<<PD2 );//defined the digital pin 2 dreaction of the  as inpu put
  DDRB |= (1 << PB3);//defined the digital pin 3 dreaction of the  as out put
  DDRB |= (1 << PB4);//defined the digital pin 3 dreaction of the  as out put


  while(1)//continuously working 
  {
    if ( PIND & (1<<PD2)){// check the actual (current value of  the pd2)
      UART_sendString("detected live  objecte\r\n");
      _delay_ms(1000);
      

      



    }
    else{
      UART_sendString("not detected live  objecte\r\n");
      _delay_ms(1000);
    }
  }


 }