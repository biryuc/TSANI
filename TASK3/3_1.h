/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/* Copyright (c) National Instruments 2019. All Rights Reserved.          */
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
#define  PANEL_Graph                      2       /* callback function: GRAPH */
#define  PANEL_GRAPH_ERR                  3       /* callback function: Graph_Err */
#define  PANEL_Zero_Err                   4       /* callback function: ZEROERR */
#define  PANEL_Sc_Err                     5       /* callback function: SCERR */
#define  PANEL_Int_Err                    6       /* callback function: INT_ERR */
#define  PANEL_GRAPH_DNL                  7       /* callback function: Dnl */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK Dnl(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK GRAPH(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Graph_Err(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK INT_ERR(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK panelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SCERR(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ZEROERR(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
