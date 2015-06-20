#include "LM35.h"

/* Pinos do LCD */
sbit LCD_RS at RC0_bit;
sbit LCD_EN at RC1_bit;
sbit LCD_D4 at RC2_bit;
sbit LCD_D5 at RC3_bit;
sbit LCD_D6 at RC4_bit;
sbit LCD_D7 at RC5_bit;
sbit LCD_RS_Direction at TRISC0_bit;
sbit LCD_EN_Direction at TRISC1_bit;
sbit LCD_D4_Direction at TRISC2_bit;
sbit LCD_D5_Direction at TRISC3_bit;
sbit LCD_D6_Direction at TRISC4_bit;
sbit LCD_D7_Direction at TRISC5_bit;

/* Textos que serao exibidos no LCD */
char celsius[] = { ' ', 223, 'C', 0 };
char device[][7] = { "LM35: ", "LM45: " };

void main() 
{
  CMCON = 7; //Desativa o comparador analogico.
  ADC_Init(); //Inicializa o canal analogico com os valores padroes.
  TRISA.B1 = 1; //Pino RB1 configurado como entrada.
  TRISA.B2 = 1; //Pino RB2 configurado como entrada.

  Lcd_Init(); //Inicializa o display LCD.
  Lcd_Cmd( _LCD_CURSOR_OFF ); //desativa o cursor do LCD.
  Lcd_Cmd( _LCD_CLEAR ); //limpa a tela do display.

  while( 1 )
  {
    LM35_ADC_Channel = 1; //Define o canal analogico para realizar a leitura do chip LM35.
    Lcd_Out( 1, 1, device[0] ); //Escreve um texto no LCD.
    Lcd_Out_CP( LM35_Read_String() ); //Escreve o texto retornado pela funcao LM35_Read_String().
    Lcd_Out_CP( celsius ); //Escreve um texto no LCD.
    
    LM35_ADC_Channel = 2; //Define o canal analogico para realizar a leitura do chip LM35.
    Lcd_Out( 2, 1, device[1] ); //Escreve um texto no LCD.
    Lcd_Out_CP( LM35_Read_String() ); //Escreve o texto retornado pela funcao LM35_Read_String().
    Lcd_Out_CP( celsius ); //Escreve um texto no LCD.

    Delay_ms( 500 ); //Aguarda 500ms.
  }
}