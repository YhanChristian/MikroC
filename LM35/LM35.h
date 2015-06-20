/******************************************************************************
 *                                                                            *
 *  File:         LM35.h                                                      *
 *                                                                            *
 *  Copyright:    (c) Microcontrolandos, 2015.                                *
 *                                                                            *
 *  Author:       Tiago Henrique.                                             *
 *                                                                            *
 *  Description:  Declaracao da biblioteca LM35 para o MikroC.                *
 *                                                                            *
 ****************************       CHANGE LOG       **************************
 * Version | ACTION                                           | DATE          *
 * --------|--------------------------------------------------|-------------- *
 *         |                                                  |               *
 *  1.0.0  | - Initial release                                | 200615        *
 *         |                                                  |               *
 *****************************************************************************/
 
#ifndef _LM35
#define _LM35

extern char LM35_ADC_Channel;

/* public */
float LM35_Read();
char * LM35_Read_String();

#endif