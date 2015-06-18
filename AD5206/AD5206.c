/******************************************************************************
 *                                                                            *
 *  File:         AD5206.c                                                    *
 *                                                                            *
 *  Copyright:    (c) Microcontrolandos, 2015.                                *
 *                                                                            *
 *  Author:       Tiago Henrique.                                             *
 *                                                                            *
 *  Description:  Implementacao da biblioteca AD5206 para o MikroC.           *
 *                AD5206 e um potenciometro digital de 6 canais e             *
 *                256 posicoes.                                               *
 *                                                                            *
 *  Requirements: - Requer um MCU com no minino 3 pinos I/O disponiveis.      *
 *                                                                            *
 *  Notes:        Tambem se aplica ao chip AD5204.                            *
 *                                                                            *
 *  Datasheet:    http://www.analog.com/media/en/technical-documentation/     *
 *                data-sheets/AD5204_5206.pdf                                 *
 *                                                                            *
 ****************************       CHANGE LOG       **************************
 * Version | ACTION                                           | DATE          *
 * --------|--------------------------------------------------|-------------- *
 *         |                                                  |               *
 *  1.0.0  | - Initial release                                | 170615        *
 *  1.0.1  | - Improved performance                           | 170615        *
 *         |                                                  |               *
 *****************************************************************************/

#include "AD5206.h"

/******************************************************************************
 *                                                                            *
 *  Function:     void AD5206_Init()                                          *
 *                                                                            *
 *  Description:  Configura a comunicacao com o chip AD5206.                  *
 *                                                                            *
 *  Parameters:   None.                                                       *
 *                                                                            *
 *  Return Value: None.                                                       *
 *                                                                            *
 *  Requirements: None.                                                       *
 *                                                                            *
 *  Notes:        None.                                                       *
 *                                                                            *
 *****************************************************************************/
void AD5206_Init()
{
  AD5206_Data_Direction = 0;
  AD5206_Data = 0;
  AD5206_Clock_Direction = 0;
  AD5206_Clock = 0;
  AD5206_CS_Direction = 0;
  AD5206_CS = 1;
}

/******************************************************************************
 *                                                                            *
 *  Function:     void AD5206_Write( char channel, char valor )               *
 *                                                                            *
 *  Description:  Define um valor para o potenciometro selecionado.           *
 *                                                                            *
 *  Parameters:   channel: seleciona um potenciometro.                        *
 *                value: o valor a ser definido para o potenciometro.         *
 *                                                                            *
 *  Return Value: None.                                                       *
 *                                                                            *
 *  Requirements: O AD5206 deve ser inicializado antes de utilizar esta       *
 *                funcao. Veja a funcao AD5206_Init.                          *
 *                                                                            *
 *  Notes:        None.                                                       *
 *                                                                            *
 *****************************************************************************/
void AD5206_Write( char channel, char valor )
{
char i = 0; //Contador de bits.
  
  AD5206_CS = 0; //Power-Up.
  
  //Envia 3 bits do canal selecionado. Envia o MSB primeiro.
  for( ; i < 3; i++ )
  {
    //Escreve o bit 2.
    AD5206_Data = channel.B2;
    //Pulso de clock.
    AD5206_Clock = 1;
    Delay_us( 1 );
    AD5206_Clock = 0;
    //O bit mais a direita passa a ser o o bit 2.
    channel <<= 1;
  }
  
  //Envia 8 bits do valor do potenciometro. Envia o MSB primeiro.
  for( ; i < 11; i++ )
  {
    //Escreve o bit MSB.
    AD5206_Data = valor.B7;
    //Pulso de clock.
    AD5206_Clock = 1;
    Delay_us( 1 );
    AD5206_Clock = 0;
    //O bit mais a direita passa a ser o o bit MSB.
    valor <<= 1;
  }
    
  AD5206_CS = 1; //Power-Down.
}