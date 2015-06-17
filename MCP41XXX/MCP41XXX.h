/******************************************************************************
 *                                                                            *
 *  File:         MCP41XXX.h                                                  *
 *                                                                            *
 *  Copyright:    (c) Microcontrolandos, 2015.                                *
 *                                                                            *
 *  Author:       Tiago Henrique.                                             *
 *                                                                            *
 *  Description:  Declaracao da biblioteca MCP41XXX para o MikroC.            *
 *                                                                            *
 ****************************       CHANGE LOG       **************************
 * Version | ACTION                                           | DATE          *
 * --------|--------------------------------------------------|-------------- *
 *         |                                                  |               *
 *  1.0.0  | - Initial release                                | 170615        *
 *         |                                                  |               *
 *****************************************************************************/

#ifndef __MCP41XXX
#define __MCP41XXX
 
#define MCP41XXX_CMD_NONE ( 0 << 4 )
#define MCP41XXX_CMD_WRITE ( 1 << 4 )
#define MCP41XXX_CMD_SHUTDOWN ( 2 << 4 )

#define MCP41XXX_CH_0 1

extern sfr sbit MCP41XXX_Data;
extern sfr sbit MCP41XXX_Clock;
extern sfr sbit MCP41XXX_CS;
extern sfr sbit MCP41XXX_Data_Direction;
extern sfr sbit MCP41XXX_Clock_Direction;
extern sfr sbit MCP41XXX_CS_Direction;

/* public */
void MCP41XXX_Init();
void MCP41XXX_Write( char valor );

#endif