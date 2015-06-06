/******************************************************************************
 *                                                                            *
 *  File:         MCP3201.h                                                   *
 *                                                                            *
 *  Copyright:    (c) Microcontrolandos, 2015.                                *
 *                                                                            *
 *  Author:       Tiago Henrique.                                             *
 *                                                                            *
 *  Description:  Declaracao da biblioteca MCP3201 para o MikroC.             *
 *                                                                            *
 ****************************       CHANGE LOG       **************************
 * Version | ACTION                                           | DATE          *
 * --------|--------------------------------------------------|-------------- *
 *         |                                                  |               *
 *  1.0.0  | - Initial release                                | 210515        *
 *  1.0.1  | - Possible bux fixed                             | 280515        *
 *         |                                                  |               *
 *****************************************************************************/

#define MCP3201_MODE 1

extern sfr sbit MCP3201_CS;
extern sfr sbit MCP3201_Clk;
extern sfr sbit MCP3201_Data;
extern sfr sbit MCP3201_CS_Direction;
extern sfr sbit MCP3201_Clk_Direction;
extern sfr sbit MCP3201_Data_Direction;

/* public */
unsigned MCP3201_Read();
void MCP3201_Init();