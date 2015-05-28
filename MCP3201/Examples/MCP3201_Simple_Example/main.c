#include "MCP3201.h"

/* Pinos do LCD */
sbit LCD_RS at RB0_bit;
sbit LCD_EN at RB1_bit;
sbit LCD_D4 at RB2_bit;
sbit LCD_D5 at RB3_bit;
sbit LCD_D6 at RB4_bit;
sbit LCD_D7 at RB5_bit;
sbit LCD_RS_Direction at TRISB0_bit;
sbit LCD_EN_Direction at TRISB1_bit;
sbit LCD_D4_Direction at TRISB2_bit;
sbit LCD_D5_Direction at TRISB3_bit;
sbit LCD_D6_Direction at TRISB4_bit;
sbit LCD_D7_Direction at TRISB5_bit;

/* Pinos do MCP3201 */
sbit MCP3201_CS at RA2_bit;
sbit MCP3201_Clk at RA0_bit;
sbit MCP3201_Data at RA1_bit;
sbit MCP3201_CS_Direction at TRISA2_bit;
sbit MCP3201_Clk_Direction at TRISA0_bit;
sbit MCP3201_Data_Direction at TRISA1_bit;

char text[12];  //variavel que armazena a conversao de um número em string.

void main() 
{
   Lcd_Init(); //Inicializa o display LCD.
   Lcd_Cmd( _LCD_CURSOR_OFF ); //desativa o cursor do LCD.
   Lcd_Cmd( _LCD_CLEAR ); //limpa a tela do display.
   
   MCP3201_Init(); //Inicializa a comunicacao com o sensor MCP3201.
   
   Lcd_Out( 1, 5, "MCP3201" ); //Escreve um texto no LCD.
   
   while( 1 )
   {
      unsigned adc_value = MCP3201_Read(); //Realiza a leitura do sensor.
      WordToStr( adc_value, text ); //Converte o valor para string.
      Lcd_Out( 2, 1, "VALOR: " ); //Escreve um texto no LCD.
      Lcd_Out_CP( text ); //Escreve um texto no LCD.
      
      Delay_ms( 500 ); //Aguarda 500ms
   }
}