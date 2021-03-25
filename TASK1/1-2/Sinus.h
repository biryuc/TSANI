/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/* Copyright (c) National Instruments 2009. All Rights Reserved.          */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1       /* callback function: panelCB */
#define  PANEL_GRAPH                      2
#define  PANEL_Amplitude                  3       /* callback function: EditAmplitude */
#define  PANEL_Noise                      4       /* callback function: EditNoise */
#define  PANEL_COMMANDBUTTON              5       /* callback function: SaveButton */
#define  PANEL_Frequency                  6       /* callback function: EditFrequency */
#define  PANEL_Phase                      7       /* callback function: EditPhase */
#define  PANEL_GRAPH_POWER                8
#define  PANEL_TIMER                      9       /* callback function: Timer1 */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK EditAmplitude(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK EditFrequency(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK EditNoise(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK EditPhase(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK panelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SaveButton(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Timer1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
