/******************************************************************************
 *                                                                            *
 *  File:         MCP3201.c                                                   *
 *                                                                            *
 *  Copyright:    (c) Microcontrolandos, 2015.                                *
 *                                                                            *
 *  Author:       Tiago Henrique.                                             *
 *                                                                            *
 *  Description:  Implementacao da biblioteca MCP3201 para o MikroC.          *
 *                MCP3201 e um conversor Analogico para Digital de 12 bits.   *
 *                                                                            *
 *  Requirements: - Requer um MCU com no minino 3 pinos I/O disponiveis.      *
 *                                                                            *
 *  Notes:        None.                                                       *
 *                                                                            *
 *  Datasheet:    http://ww1.microchip.com/downloads/en/DeviceDoc/21290D.pdf  *
 *                                                                            *
 ****************************       CHANGE LOG       **************************
 * Version | ACTION                                           | DATE          *
 * --------|--------------------------------------------------|-------------- *
 *         |                                                  |               *
 *  1.0.0  | - Initial release                                | 210515        *
 *  1.0.1  | - Possible bux fixed                             | 280515        *
 *         |                                                  |               *
 *****************************************************************************/

#include "MCP3201.h"

/******************************************************************************
 *                                                                            *
 *  Function:     void MCP3201_Init()                                         *
 *                                                                            *
 *  Description:  Configura e inicializa a comunicacao com o sensor MCP3201.  *
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
void MCP3201_Init()
{
  //Define os pinos como saida.
  MCP3201_CS_Direction = 0;
  MCP3201_Clk_Direction = 0;
  //Define o pino como entrada.
  MCP3201_Data_Direction = 1;
  
  MCP3201_Clk = MCP3201_MODE;  
  
  MCP3201_CS = 0; //Power-Up.
  Delay_us( 5 );
  MCP3201_CS = 1; //Power-Down.
}

/******************************************************************************
 *                                                                            *
 *  Function:     unsigned MCP3201_Read()                                     *
 *                                                                            *
 *  Description:  Inicia a conversao.                                         *
                  Obtem o valor da conversao realizada pelo MCP3201.          *
 *                                                                            *
 *  Parameters:   None.                                                       *
 *                                                                            *
 *  Return Value: O resultado da conversao.                                   *
 *                                                                            *
 *  Requirements: O sensor MCP3201 deve ser inicializado antes de utilizar    *
 *                esta funcao. Veja a funcao MCP3201_Init.                    *
 *                                                                            *
 *  Notes:        None.                                                       *
 *                                                                            *
 *****************************************************************************/
unsigned MCP3201_Read()
{
unsigned value = 0;
char i;
  
  MCP3201_Clk = MCP3201_MODE;  
  MCP3201_CS = 0; //Power-Up.
  
  //Ignoramos os 3 primeiros bits.
  //Iniciamos a conversao.
  for( i = 0; i < 3; i++ )
  {
    //Pulso de clock.
    MCP3201_Clk = MCP3201_MODE;
    Delay_us( 1 );
    MCP3201_Clk = !MCP3201_MODE;
  }
  
  //Faz a leitura dos 12 bits.
  for( ; i < 15; i++ )
  {
    //Guarda o bit.
    ( (char*)&value)[0].B0 = MCP3201_Data;
    //Pulso de clock.
    MCP3201_Clk = MCP3201_MODE;
    Delay_us( 1 );
    MCP3201_Clk = !MCP3201_MODE;
    //Desloca o valor para esquerda.
    value <<= 1;
  }
  
  MCP3201_CS = 1; //Power-Down.
  MCP3201_Clk = MCP3201_MODE;  
  
  return ( value & 0x0FFF );
}