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
#define  PANEL_address_r                  2
#define  PANEL_subaddress_w               3
#define  PANEL_subaddress_r               4
#define  PANEL_address_w                  5
#define  PANEL_val_w                      6
#define  PANEL_val_r                      7
#define  PANEL_BUTTON_R                   8       /* callback function: read */
#define  PANEL_BUTTON_W                   9       /* callback function: write */
#define  PANEL_DAC_V                      10      /* callback function: dac */
#define  PANEL_DAC_C                      11      /* callback function: dac */
#define  PANEL_ADC                        12      /* callback function: adc */
#define  PANEL_DAC_VIN2_V                 13
#define  PANEL_NUMERIC_5                  14
#define  PANEL_NUMERIC_4                  15
#define  PANEL_DAC_VIN1_V                 16


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK adc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK dac(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK panelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK read(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK write(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
