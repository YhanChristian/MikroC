/******************************************************************************
 *                                                                            *
 *  File:         AD5206.h                                                    *
 *                                                                            *
 *  Copyright:    (c) Microcontrolandos, 2015.                                *
 *                                                                            *
 *  Author:       Tiago Henrique.                                             *
 *                                                                            *
 *  Description:  Declaracao da biblioteca AD5206 para o MikroC.              *
 *                                                                            *
 ****************************       CHANGE LOG       **************************
 * Version | ACTION                                           | DATE          *
 * --------|--------------------------------------------------|-------------- *
 *         |                                                  |               *
 *  1.0.0  | - Initial release                                | 170615        *
 *         |                                                  |               *
 *****************************************************************************/

#ifndef __AD5206
#define __AD5206

extern sfr sbit AD5206_Data;
extern sfr sbit AD5206_Clock;
extern sfr sbit AD5206_CS;
extern sfr sbit AD5206_Data_Direction;
extern sfr sbit AD5206_Clock_Direction;
extern sfr sbit AD5206_CS_Direction;

/* public */
void AD5206_Init();
void AD5206_Write( char channel, char valor );

#endif