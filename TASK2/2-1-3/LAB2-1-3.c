//==============================================================================
//
// Title:       LAB2-1-3
// Purpose:     A short description of the application.
//
// Created on:  11.07.2008 at 17:55:03 by Gennady Kuzin.
// Copyright:   NSU. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include <ansi_c.h>
#include <cvirte.h>     
#include <userint.h>
#include <tsani.h>
#include "LAB2-1-3.h"
#include "toolbox.h"

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

/// HIFN The main entry-point function.
int main (int argc, char *argv[])
{
    int error = 0;
    
	ni6251Slot(2);
	// переводим модуль в режим отображения состояния линий
	portMask(2, 0x07);
	portOut(2, 0x01);
	// гасим все светодиоды
	
	
	portMask(1, 0x0f);
	portOut(1, 0x00);
	
	portMask(0, 0xff);
	portOut(0, 0x00);
    /* initialize and load resources */
    nullChk (InitCVIRTE (0, argv, 0));
    errChk (panelHandle = LoadPanel (0, "LAB2-1-3.uir", PANEL));
    
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

#define BIN(n,v) const int n = v;
#define BIN0(n,v) BIN(n ## O, ((v)<<1)|0) BIN(n ## I, ((v)<<1)|1)
#define BIN1(n,v) BIN(n ## O, ((v)<<1)|0) BIN(n ## I, ((v)<<1)|1)
#define BIN2(n,v) BIN1(n ## O, ((v)<<1)|0) BIN1(n ## I, ((v)<<1)|1)
#define BIN3(n,v) BIN2(n ## O, ((v)<<1)|0) BIN2(n ## I, ((v)<<1)|1)
#define BIN4(n,v) BIN3(n ## O, ((v)<<1)|0) BIN3(n ## I, ((v)<<1)|1)
#define BIN5(n,v) BIN4(n ## O, ((v)<<1)|0) BIN4(n ## I, ((v)<<1)|1)
#define BIN6(n,v) BIN5(n ## O, ((v)<<1)|0) BIN5(n ## I, ((v)<<1)|1)
#define BIN7(n,v) BIN6(n ## O, ((v)<<1)|0) BIN6(n ## I, ((v)<<1)|1)
#define BIN8(n,v) BIN7(n ## O, ((v)<<1)|0) BIN7(n ## I, ((v)<<1)|1)


int run = 0;
int back = 12;

void run_light(unsigned char light) {
	portOut(0, (1<<light));
	portOut(1, (1<<light)>>8);
}

int CVICALLBACK timer (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2) {
	switch (event) {
		case EVENT_TIMER_TICK:
			unsigned char temp,test =240;
		portIn(1,&temp);
			
		
		if(!(temp & (OOOIOOOO))){
		 	portOut(0, (1<<3));
			Delay(1.);
		}
///////////////////////////////////////////
		else if(!(temp & (OOIOOOOO))){
			for(int j=0 ; j<8; j++){
			 portIn(0, &temp);
			temp |= 1<<j;
			portOut(0, temp);
			
			
			Delay(0.25);
			portOut(0, 0x00);
				}
		
		}
/////////////////////////////////////////////		
		portIn(1, &temp); 
		else if (!(temp & (OIOOOOOO))){
		 	for(int j=7 ; j>=0; j--){
			 	portIn(0, &temp);
				temp |= 1<<j;
				portOut(0, temp);
			
			
				Delay(0.25);
				portOut(0, 0x00);
			}
		}
/////////////////////////////////////////////
		
		else if (!(temp&(IOOOOOOO))){
			portMask(0, 0xFF);
			portOut(0, 0x00);
			portMask(1, 0x0F);
			portOut(1, 0x00);
			break;	
		}
			
			
			

			break;
		case EVENT_DISCARD:

			break;
	}
	return 0;
}
