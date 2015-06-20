/******************************************************************************
 *                                                                            *
 *  File:         LM35.c                                                      *
 *                                                                            *
 *  Copyright:    (c) Microcontrolandos, 2015.                                *
 *                                                                            *
 *  Author:       Tiago Henrique.                                             *
 *                                                                            *
 *  Description:  Implementacao da biblioteca LM35 para o MikroC.             *
 *                LM35 e um sensor de temperatura.                            *
 *                                                                            *
 *  Requirements: - Requer um MCU com modulo Converor Analogico para Digital. *
 *                                                                            *
 *  Notes:        Tambem se aplica ao chip LM45.                              *
 *                                                                            *
 *  Datasheet:    http://www.ti.com/lit/ds/symlink/lm35.pdf                   *
 *                http://www.ti.com/lit/ds/symlink/lm45.pdf                   *
 *                                                                            *
 ****************************       CHANGE LOG       **************************
 * Version | ACTION                                           | DATE          *
 * --------|--------------------------------------------------|-------------- *
 *         |                                                  |               *
 *  1.0.0  | - Initial release                                | 200615        *
 *         |                                                  |               *
 *****************************************************************************/

#include "LM35.h"
/******************************************************************************
 *                                                                            *
 *  Description: Define o canal analogico utilizado na leitura do chip LM35.  *
 *                                                                            *
 *  Notes:       None.                                                        *
 *                                                                            *
 ******************************************************************************/
char LM35_ADC_Channel;

/******************************************************************************
 *                                                                            *
 *  Function:     float LM35_Read()                                           *
 *                                                                            *
 *  Description:  Realiza a leitura da temperatura do chip LM35.              *
 *                                                                            *
 *  Parameters:   None.                                                       *
 *                                                                            *
 *  Return Value: Retorna o valor da temperatura em ponto flutuante.          *
 *                                                                            *
 *  Requirements: - O modulo ADC deve estar ativado. Veja a funcao ADC_Init.  *
 *                - O pino utlizado na leitura, deve estar configurado como   *
 *                  entrada.                                                  *
 *                                                                            *
 *  Notes:        None.                                                       *
 *                                                                            *
 *****************************************************************************/
float LM35_Read()
{
  //Le o canal analogico e converte para um valor de temperatura em ponto flutuante.
  return ADC_Get_Sample( LM35_ADC_Channel ) * 0.48875855327468230694037145650049;
}

/******************************************************************************
 *                                                                            *
 *  Function:     char * LM35_Read_String()                                   *
 *                                                                            *
 *  Description:  Realiza a leitura da temperatura do chip LM35.              *
 *                                                                            *
 *  Parameters:   None.                                                       *
 *                                                                            *
 *  Return Value: Retorna o valor da temperatura em string.                   *
 *                                                                            *
 *  Requirements: - O modulo ADC deve estar ativado. Veja a funcao ADC_Init.  *
 *                - O pino utlizado na leitura, deve estar configurado como   *
 *                  entrada.                                                  *
 *                                                                            *
 *  Notes:        None.                                                       *
 *                                                                            *
 *****************************************************************************/
char * LM35_Read_String()
{
unsigned temp;
char i;
static char output[6];

  //Le o canal analogico e converte para um valor de temperatura com uma casa decimal.
  temp = ( (unsigned long)ADC_Get_Sample( LM35_ADC_Channel ) * 1250UL ) >> 8;
  //Final da string.
  output[5] = 0;
  //Converte a casa decimal do valor em caracter.
  output[4] = ( temp % 10 ) + '0';
  //Desloca o valor da temperatura uma digito para direita.
  temp /= 10;
  //Insere o ponto decimal.
  output[3] = '.';
  //Converte os valores da unidade, dezena e centena em caracter.
  for( i = 2; !i.B7; i--, temp /= 10 )
    output[i] = ( temp % 10 ) + '0';
  //Retorna a string que representa o valor da temperatura.
  return output;
}