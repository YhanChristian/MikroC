/******************************************************************************
 *                                                                            *
 *  File:         MCP41XXX.c                                                  *
 *                                                                            *
 *  Copyright:    (c) Microcontrolandos, 2015.                                *
 *                                                                            *
 *  Author:       Tiago Henrique.                                             *
 *                                                                            *
 *  Description:  Implementacao da biblioteca MCP41XXX para o MikroC.         *
 *                MCP41XXX e um potenciometro digital com 1 canal             *
 *                de 256 posicoes.                                            *
 *                                                                            *
 *  Requirements: - Requer um MCU com no minino 3 pinos I/O disponiveis.      *
 *                                                                            *
 *  Notes:        None.                                                       *
 *                                                                            *
 *  Datasheet:    http://ww1.microchip.com/downloads/en/DeviceDoc/11195c.pdf  *
 *                                                                            *
 ****************************       CHANGE LOG       **************************
 * Version | ACTION                                           | DATE          *
 * --------|--------------------------------------------------|-------------- *
 *         |                                                  |               *
 *  1.0.0  | - Initial release                                | 170615        *
 *         |                                                  |               *
 *****************************************************************************/

#include "MCP41XXX.h"

/******************************************************************************
 *                                                                            *
 *  Function:     void MCP41XXX_Init()                                        *
 *                                                                            *
 *  Description:  Configura e inicializa a comunicacao com o chip MCP41XXX.   *
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
void MCP41XXX_Init()
{
  //Configura os pinos como saida.
  MCP41XXX_Data_Direction = 0;
  MCP41XXX_Data = 0;
  MCP41XXX_Clock_Direction = 0;
  MCP41XXX_Clock = 0;
  MCP41XXX_CS_Direction = 0;
  MCP41XXX_CS = 1;
}

/******************************************************************************
 *                                                                            *
 *  Function:     void MCP41XXX_Write( char valor )                           *
 *                                                                            *
 *  Description:  Escreve um novo valor para o potenciometro.                 *
 *                                                                            *
 *  Parameters:   None.                                                       *
 *                                                                            *
 *  Return Value: None.                                                       *
 *                                                                            *
 *  Requirements: O MCP41XXX deve ser inicializado antes de utilizar esta     *
 *                funcao. Veja a funcao MCP41XXX_Init.                        *
 *                                                                            *
 *  Notes:        None.                                                       *
 *                                                                            *
 *****************************************************************************/
void MCP41XXX_Write( char valor )
{
char i = 0; //Contador de bits.
char cmd = MCP41XXX_CMD_WRITE | MCP41XXX_CH_0; //Comando para enviar.
  
  MCP41XXX_CS = 0; //Power-Up.
  
  //Envia 8 bits do comando. Envia o MSB primeiro.
  for( ; i < 8; i++ )
  {
    //Escreve o bit MSB.
    MCP41XXX_Data = cmd.B7;
    //Pulso de clock.
    MCP41XXX_Clock = 1;
    Delay_us( 1 );
    MCP41XXX_Clock = 0;
    //O bit mais a direita passa a ser o o bit MSB.
    cmd <<= 1;
  }
  
  //Envia 8 bits do novo valor do potenciometro. Envia o MSB primeiro.
  for( ; i < 16; i++ )
  {
    //Escreve o bit MSB.
    MCP41XXX_Data = valor.B7;
    //Pulso de clock.
    MCP41XXX_Clock = 1;
    Delay_us( 1 );
    MCP41XXX_Clock = 0;
    //O bit mais a direita passa a ser o bit MSB.
    valor <<= 1;
  }
    
  MCP41XXX_CS = 1; //Power-Down.
}