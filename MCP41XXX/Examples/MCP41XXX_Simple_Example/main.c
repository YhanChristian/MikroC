#include "MCP41XXX.h"

/* Pinos do MCP41XXXX */
sbit MCP41XXX_Data at RA1_bit;
sbit MCP41XXX_Clock at RA0_bit;
sbit MCP41XXX_CS at RA2_bit;
sbit MCP41XXX_Data_Direction at TRISA1_bit;
sbit MCP41XXX_Clock_Direction at TRISA0_bit;
sbit MCP41XXX_CS_Direction at TRISA2_bit;

char value = 0; //valor do potenciometro. 0 até 255.
char flags = 0; //flags.
const BIT_INC_VALUE = 0; //bit que representa o botao INC.
const BIT_DEC_VALUE = 1; //bit que representa o botao DEC.

void main()
{
  CMCON = 7; //Desativa os comparadores analogicos.
  TRISB = 3; //Define os pinos RB0 e RB1 como entrada.

  MCP41XXX_Init(); //Inicializa a comunicao com o chip MCP41XXX.
  
  while( 1 )
  {
    //Botao INC foi pressionado.
    if( PORTB.BIT_INC_VALUE ) flags.BIT_INC_VALUE = 1;
    //Botao DEC foi pressionado.
    else if( PORTB.BIT_DEC_VALUE ) flags.BIT_DEC_VALUE = 1;

    //O botao INC foi solto e anteriormente estava pressionado.
    if( !PORTB.BIT_INC_VALUE && flags.BIT_INC_VALUE )
    {
      //Limpa a flag.
      flags.BIT_INC_VALUE = 0;
      //Incrementa o valor.
      value++;
    }
    //O botao DEC foi solto e anteriormente estava pressionado.
    else if( !PORTB.BIT_DEC_VALUE && flags.BIT_DEC_VALUE )
    {
      //Limpa a flag.
      flags.BIT_DEC_VALUE = 0;
      //Decrementa o valor.
      value--;
    }
    else
    {
      //Caso nao entre em nenhuma das condicoes acima,
      //Volta ao inicio de loop e nao executa as instrucoes abaixo.
      continue;
    }

    //Escreve o novo valor para o potenciometro.
    MCP41XXX_Write( value );
  }
}