/******************************************************************************
 *                                                                            *
 *  File:         MCP3208.c                                                   *
 *                                                                            *
 *  Copyright:    (c) Microcontrolandos, 2015.                                *
 *                                                                            *
 *  Author:       Tiago Henrique.                                             *
 *                                                                            *
 *  Description:  Implementacao da biblioteca MCP3208 para o MikroC.          *
 *                MCP3208 e um conversor Analagico para Digital de 12 bits c/ *
 *                8 canais.                                                   *
 *                                                                            *
 *  Requirements: - Requer um MCU com no minino 4 pinos I/O disponiveis.      *
 *                                                                            *
 *  Notes:        Tambem se aplica ao conversor MCP3804.                      *
 *                                                                            *
 *  Datasheet:    http://ww1.microchip.com/downloads/en/DeviceDoc/21298D.pdf  *
 *                                                                            *
 ****************************       CHANGE LOG       **************************
 * Version | ACTION                                           | DATE          *
 * --------|--------------------------------------------------|-------------- *
 *         |                                                  |               *
 *  1.0.0  | - Initial release                                | 060615        *
 *         |                                                  |               *
 *****************************************************************************/

#include "MCP3208.h"

/******************************************************************************
 *                                                                            *
 *  Function:     void MCP3208_Init()                                         *
 *                                                                            *
 *  Description:  Configura a comunicacao com o conversor MCP3208.            *
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
void MCP3208_Init()
{
  //Define os pinos como saida.
  MCP3208_CS_Direction = 0;
  MCP3208_Clk_Direction = 0;
  MCP3208_SDO_Direction = 0;
  //Define o pino como entrada.
  MCP3208_SDI_Direction = 1;
  //Coloca os pinos em nivel logico baixo.
  MCP3208_Clk = 0;  
  MCP3208_SDO = 0;  
}

/******************************************************************************
 *                                                                            *
 *  Function:     unsigned MCP3208_Read( enum MCP3208_INPUT_TYPE channel )    *
 *                                                                            *
 *  Description:  Inicia a conversao.                                         *
 *                Obtem o valor da conversao de um unico canal ou a diferenca *
 *                entre dois canais predeterminados.                          *
 *                                                                            *
 *  Parameters:   channel: Seleciona o canal de entrada.                      *
 *                                                                            *
 *  Return Value: O resultado da conversao.                                   *
 *                                                                            *
 *  Requirements: O MCP3208 deve ser inicializado antes de utilizar esta      *
 *                funcao. Veja a funcao MCP3208_Init.                         *
 *                                                                            *
 *  Notes:       Se a diferenca entre dois canais for negativo, a funcao      *
 *               retornara 0.                                                 *
 *                                                                            *
 *****************************************************************************/
unsigned MCP3208_Read( enum MCP3208_INPUT_TYPE channel )
{
unsigned value = 0;
char i;

  channel.B4 = 1; //Bit de Start.
  
  MCP3208_Clk = 0;  
  MCP3208_CS = 0; //Power-Up.
  
  //Enviamos 5 bits responsaveis pelo controle.
  //Inicia-se a conversao.
  for( i = 0; i < 5; i++ )
  {
    MCP3208_SDO = channel.B4;
    Delay_us( 1 );
    //Pulso de clock.
    MCP3208_Clk = 0;
    Delay_us( 1 );
    MCP3208_Clk = 1;
    channel <<= 1;
  }
  
  //Ignoramos dois bits.
  for( ; i < 7; i++ )
  {
    //Pulso de clock.
    MCP3208_Clk = 0;
    Delay_us( 1 );
    MCP3208_Clk = 1;
  }
  
  //Faz a leitura de 12 bits.
  for( ; i < 19; i++ )
  {
    //Guarda o bit.
    ((char*)&value)[0].B0 = MCP3208_SDI;
    //Pulso de clock.
    MCP3208_Clk = 0;
    Delay_us( 1 );
    MCP3208_Clk = 1;
    //Desloca o valor para esquerda.
    //Movendo o bit MSB para seu devido lugar.
    value <<= 1;
  }
  
  MCP3208_CS = 1; //Power-Down.
  MCP3208_Clk = 0;  
  
  return ( value & 0x0FFF );
}