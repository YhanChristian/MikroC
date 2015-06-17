#include "AD5206.h"

/* Pinos do AD5206 */
sbit AD5206_Data at RA1_bit;
sbit AD5206_Clock at RA0_bit;
sbit AD5206_CS at RA2_bit;
sbit AD5206_Data_Direction at TRISA1_bit;
sbit AD5206_Clock_Direction at TRISA0_bit;
sbit AD5206_CS_Direction at TRISA2_bit;

char value[6] = { 0, 0, 0, 0, 0, 0 }; //Valor dos 6 potenciometros.
char channel = 0; //Seleciona um potenciometro.
char flags = 0; //flags.
const BIT_TOGGLE_CHANNEL = 0; //Bit que representa o botao CHANNEL.
const BIT_INC_VALUE = 1; //Bit que representa o botao INC.
const BIT_DEC_VALUE = 2; //Bit que representa o botao DEC.

void main() 
{
  CMCON = 7; //Desativa os compadores analogicos.
  TRISB = 7; //Define os pinos RB0, RB1, RB2 como entrada.

  AD5206_Init(); //Inicializa a comunicao com o chip AD5206.
  
  while(1)
  {
    //Botao CHANNEL foi pressionado.
    if( PORTB.BIT_TOGGLE_CHANNEL ) flags.BIT_TOGGLE_CHANNEL = 1;
    //Botao INC foi pressionado.
    else if( PORTB.BIT_INC_VALUE ) flags.BIT_INC_VALUE = 1;
    //Botao DEC foi pressionado.
    else if( PORTB.BIT_DEC_VALUE ) flags.BIT_DEC_VALUE = 1;

    //O botao CHANNEL foi solto e anteriormente estava pressionado.
    if( !PORTB.BIT_TOGGLE_CHANNEL && flags.BIT_TOGGLE_CHANNEL )
    {
      //Limpa a flag.
      flags.BIT_TOGGLE_CHANNEL = 0;
      //Incrementa o canal selecionado ate 5. ( No caso do AD5204, vai até 3 ).
      if( ++channel > 5 )
        channel = 0;
    }
    //O botao INC foi solto e anteriormente estava pressionado.
    else if( !PORTB.BIT_INC_VALUE && flags.BIT_INC_VALUE )
    {
      //Limpa a flag.
      flags.BIT_INC_VALUE = 0;
      //Incrementa o valor do canal selecionado.
      value[channel]++;
    }
    //O botao DEC foi solto e anteriormente estava pressionado.
    else if( !PORTB.BIT_DEC_VALUE && flags.BIT_DEC_VALUE )
    {
      //Limpa a flag.
      flags.BIT_DEC_VALUE = 0;
      //Decrementa o valor do potenciometro selecionado.
      value[channel]--;
    }
    else
    {
      //Caso nao entre em nenhuma das condicoes acima,
      //Volta ao inicio de loop e nao executa as instrucoes abaixo.
      continue;
    }

    //Escreve o novo valor para o potenciometro selecionado.
    AD5206_Write( channel, value[channel] );
  }
}