/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/* Copyright (c) National Instruments 2020. All Rights Reserved.          */
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
#define  PANEL_READ_2                     2       /* callback function: read_2_cb */
#define  PANEL_READ_1                     3       /* callback function: read_1_cb */
#define  PANEL_READ_0                     4       /* callback function: read_0_cb */
#define  PANEL_WRITE                      5       /* callback function: write_cb */
#define  PANEL_LED_1                      6       /* callback function: L */
#define  PANEL_LED_2                      7       /* callback function: L */
#define  PANEL_LED_3                      8       /* callback function: L */
#define  PANEL_LED_4                      9       /* callback function: L */
#define  PANEL_TIMER                      10      /* callback function: timer_cb */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK L(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK panelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK read_0_cb(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK read_1_cb(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK read_2_cb(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK timer_cb(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK write_cb(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
