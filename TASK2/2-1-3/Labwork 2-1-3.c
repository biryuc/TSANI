//==============================================================================
//
// Title:       Labwork 2-1-3
// Purpose:     A short description of the application.
//
// Created on:  14.10.2020 at 16:21:59 by Gennady Kuzin.
// Copyright:   NSU. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include <ansi_c.h>
#include <cvirte.h>     
#include <userint.h>
#include <tsani.h>
#include "Labwork 2-1-3.h"
#include "toolbox.h"

unsigned char read0, read1, read2;

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

static int panelHandle;

//==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Global functions

int LEDupdate()
{
	portIn(1, &read1);
	SetCtrlVal(PANEL, PANEL_LED_1, !(0x01 & (read1 >> 4)));
	SetCtrlVal(PANEL, PANEL_LED_2, !(0x01 & (read1 >> 5)));
	SetCtrlVal(PANEL, PANEL_LED_3, !(0x01 & (read1 >> 6)));
	SetCtrlVal(PANEL, PANEL_LED_4, !(0x01 & (read1 >> 7)));
	
	return 0;
}

/// HIFN The main entry-point function.
int main (int argc, char *argv[])
{
    int error = 0;
    
	ni6251Slot(2); 	
	portMask(2, 7);
	portOut(2, 1);  //¬ключаем авалошку(D12-D15)      
    /* initialize and load resources */
    nullChk (InitCVIRTE (0, argv, 0));
    errChk (panelHandle = LoadPanel (0, "Labwork 2-1-3.uir", PANEL));
	

    
    /* display the panel and run the user interface */
    errChk (DisplayPanel (panelHandle));
    errChk (RunUserInterface ());
	

Error:
    /* clean up */
	ni6251Close();
    DiscardPanel (panelHandle);
    return 0;
}

//==============================================================================
// UI callback function prototypes

/// HIFN Exit when the user dismisses the panel.
int CVICALLBACK panelCB (int panel, int event, void *callbackData,
        int eventData1, int eventData2)
{
    if (event == EVENT_CLOSE)
        QuitUserInterface (0);
    return 0;
}

int CVICALLBACK timer_cb (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2) {
	int data;
	switch (event) {
		case EVENT_TIMER_TICK:
			 
			GetCtrlVal(panelHandle,PANEL_WRITE, &data);
			portMask(0, 0xff);
			portMask(1, 0x0f);
			portOut(0, data & 0xff);
			portOut(1, (data >> 8) & 0xff);
			
			//portMask(0,0x00); // порт 0 - чтение
			//portMask(1,0x00); // порт 1 - чтение
			//portMask(2,0x00); // порт 2 - чтение
			portIn(0, &read0); 
			portIn(1, &read1); 
			portIn(2, &read2);
			
			
			
			SetCtrlVal(panelHandle, PANEL_READ_0, read0);
			SetCtrlVal(panelHandle, PANEL_READ_1, read1);
			SetCtrlVal(panelHandle, PANEL_READ_2, read2);
			
			
			LEDupdate(); 
			
			break;
		case EVENT_DISCARD:

			break;
	}
	return 0;
}

int CVICALLBACK write_cb (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2) {
	int data;
	switch (event) {
		case EVENT_COMMIT:
			/*
			GetCtrlVal(panelHandle,PANEL_WRITE, &data);
			portMask(0, 0xff);
			portMask(1, 0x0f);
			portOut(0, data & 0xff);
			portOut(1, (data >> 8) & 0xff);
			
			portMask(0,0x00); // порт 0 - чтение
			portMask(1,0x00); // порт 1 - чтение
			//portMask(2,0x00); // порт 2 - чтение
			portIn(0, &read0); 
			portIn(1, &read1); 
			//portIn(2, &read2);
			
			SetCtrlVal(panelHandle, PANEL_READ_0, read0);
			SetCtrlVal(panelHandle, PANEL_READ_1, read1);
			Delay(2.); 
			//SetCtrlVal(panelHandle, PANEL_READ_2, read2); */ 
		case EVENT_LEFT_CLICK:

			break;
		case EVENT_RIGHT_CLICK:

			break;
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_DISCARD:

			break;
	}
	return 0;
}

int CVICALLBACK read_0_cb (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2) {
	switch (event) {
		case EVENT_COMMIT:

			break;
		case EVENT_LEFT_CLICK:

			break;
		case EVENT_RIGHT_CLICK:

			break;
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_DISCARD:

			break;
	}
	return 0;
}

int CVICALLBACK read_1_cb (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2) {
	switch (event) {
		case EVENT_COMMIT:

			break;
		case EVENT_LEFT_CLICK:

			break;
		case EVENT_RIGHT_CLICK:

			break;
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_DISCARD:

			break;
	}
	return 0;
}

int CVICALLBACK read_2_cb (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2) {
	switch (event) {
		case EVENT_COMMIT:

			break;
		case EVENT_LEFT_CLICK:

			break;
		case EVENT_RIGHT_CLICK:

			break;
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_DISCARD:

			break;
	}
	return 0;
}


int CVICALLBACK L (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2) {
	switch (event) {
		case EVENT_COMMIT:

			break;
		case EVENT_LEFT_CLICK:

			break;
		case EVENT_RIGHT_CLICK:

			break;
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_DISCARD:

			break;
	}
	return 0;
}
