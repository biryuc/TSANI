//==============================================================================
//
// Title:       3.1
// Purpose:     A short description of the application.
//
// Created on:  08.10.2019 at 17:13:26 by Gennady Kuzin.
// Copyright:   NSU. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include <ansi_c.h>
#include <cvirte.h>     
#include <userint.h>
#include <tsani.h>
#include "3.1.h"
#include "toolbox.h"
#include "Avalon.h";
#include "DACADC.h"

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
double DAC_LSB=3.3/255;
double Data[256];
double Source[256];
double Error[256];
double DNL[255];
double FixC[256];
double FixErr[256];
//==============================================================================
// Global functions


void CheckDAC(){
	for (int i=0;i<256;i++){
		  Source[i]=i;
		  Dac_Out_D(1,i);
		  analogIn(0,(Data+i));
		  Data[i]/=DAC_LSB;
	}
	PlotY(panelHandle,PANEL_Graph,Data,256,VAL_DOUBLE,VAL_THIN_LINE,VAL_NO_POINT,VAL_SOLID,1,VAL_RED);
	PlotY(panelHandle,PANEL_Graph,Source,256,VAL_DOUBLE,VAL_THIN_LINE,VAL_NO_POINT,VAL_SOLID,1,VAL_GREEN);
}

void FixCurve(){
	double ZeroErr;
	double ScErr;
	GetCtrlVal(panelHandle,PANEL_Zero_Err,&ZeroErr);
	GetCtrlVal(panelHandle,PANEL_Sc_Err,&ScErr);
	for (int i=0;i<256;i++){
		  FixC[i]=(Data[i]-ZeroErr)/(1+((ScErr-ZeroErr)/255));
	}
	PlotY(panelHandle,PANEL_Graph,FixC,256,VAL_DOUBLE,VAL_THIN_LINE,VAL_NO_POINT,VAL_SOLID,1,VAL_YELLOW);
}
void ErrDAC(){
	for (int i=0;i<256;i++){
		  Error[i]=(Data[i]-Source[i]);
	}
}

void FixEr(){
	double ZeroErr;
	GetCtrlVal(panelHandle,PANEL_Zero_Err,&ZeroErr);
	for (int i=0;i<256;i++){
		  FixErr[i]=(FixC[i]-Source[i]);
	}
	PlotY(panelHandle,PANEL_GRAPH_ERR,FixErr,256,VAL_DOUBLE,VAL_THIN_LINE,VAL_NO_POINT,VAL_SOLID,1,VAL_RED);
}

void ErrZero(){
	double ZeroErr=Error[0];
	SetCtrlVal(panelHandle,PANEL_Zero_Err,ZeroErr);
}

void ErrScale(){
	double ScErr=Error[255];
	ScErr=ScErr;
	SetCtrlVal(panelHandle,PANEL_Sc_Err,ScErr);
}															

void IntErr(){
	double max=-3.4;
	for (int i=0;i<256;i++){
		 if (FixErr[i]>max) max = FixErr[i]; 
	}
	max=max;
	SetCtrlVal(panelHandle,PANEL_Int_Err,max);
}

void DNL_Err(){
	for (int i=0;i<255;i++){
		DNL[i]=(Data[i+1]-Data[i]);
		DNL[i]=DNL[i]-1;
	}
	PlotY(panelHandle,PANEL_GRAPH_DNL,DNL,255,VAL_DOUBLE,VAL_THIN_LINE,VAL_NO_POINT,VAL_SOLID,1,VAL_RED);
}

/// HIFN The main entry-point function.
int main (int argc, char *argv[])
{   
    int error = 0;
	
	ni6251Slot(2);
	avalonInit(); 
	DAC_ADC_Init();
	
    /* initialize and load resources */
    nullChk (InitCVIRTE (0, argv, 0));
    errChk (panelHandle = LoadPanel (0, "3.1.uir", PANEL));
    CheckDAC();
	ErrDAC();
	ErrZero();
	ErrScale();
	DNL_Err();
	FixCurve();
	FixEr();
	IntErr();
    /* display the panel and run the user interface */
    errChk (DisplayPanel (panelHandle));
    errChk (RunUserInterface ());

Error:
    /* clean up */
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

int CVICALLBACK GRAPH (int panel, int control, int event,
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

int CVICALLBACK Graph_Err (int panel, int control, int event,
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

int CVICALLBACK ZEROERR (int panel, int control, int event,
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

int CVICALLBACK SCERR (int panel, int control, int event,
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

int CVICALLBACK INT_ERR (int panel, int control, int event,
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

int CVICALLBACK Dnl (int panel, int control, int event,
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
