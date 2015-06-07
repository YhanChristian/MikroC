/******************************************************************************
 *                                                                            *
 *  File:         MCP3208.h                                                   *
 *                                                                            *
 *  Copyright:    (c) Microcontrolandos, 2015.                                *
 *                                                                            *
 *  Author:       Tiago Henrique.                                             *
 *                                                                            *
 *  Description:  Declaracao da biblioteca MCP3208 para o MikroC.             *
 *                                                                            *
 ****************************       CHANGE LOG       **************************
 * Version | ACTION                                           | DATE          *
 * --------|--------------------------------------------------|-------------- *
 *         |                                                  |               *
 *  1.0.0  | - Initial release                                | 060615        *
 *         |                                                  |               *
 *****************************************************************************/
 
extern sfr sbit MCP3208_CS;
extern sfr sbit MCP3208_Clk;
extern sfr sbit MCP3208_SDO;
extern sfr sbit MCP3208_SDI;
extern sfr sbit MCP3208_CS_Direction;
extern sfr sbit MCP3208_Clk_Direction;
extern sfr sbit MCP3208_SDO_Direction;
extern sfr sbit MCP3208_SDI_Direction;

enum MCP3208_INPUT_TYPE
{
  CH0_CH1,
  CH1_CH0,
  CH2_CH3,
  CH3_CH2,
  CH4_CH5,
  CH5_CH4,
  CH6_CH7,
  CH7_CH6, 
  CH0,
  CH1,
  CH2,
  CH3,
  CH4,
  CH5,
  CH6,
  CH7   
};

/* public */
unsigned MCP3208_Read( enum MCP3208_INPUT_TYPE );
void MCP3208_Init();