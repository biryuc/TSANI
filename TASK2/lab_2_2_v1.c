//==============================================================================
//
// Title:       lab.2.2.v1
// Purpose:     A short description of the application.
//
// Created on:  15.09.2020 at 9:44:28 by Gennady Kuzin.
// Copyright:   NSU. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include <ansi_c.h>
#include <cvirte.h>     
#include <userint.h>
#include <tsani.h>
#include "lab.2.2.v1.h"
#include "toolbox.h"
#include "avalib.h"
#include "dacad.h"
int address=0;
int subaddress=0;
int val=255;

static int panelHandle;

int main (int argc, char *argv[])
{
    int error = 0;
	avalon_init();
	dac_init();
	adc_init();
    
    /* initialize and load resources */
    nullChk (InitCVIRTE (0, argv, 0));
    errChk (panelHandle = LoadPanel (0, "lab.2.2.v1.uir", PANEL));
	avalon_write(address, subaddress, val);
	//avalon_read(address, subaddress, &val); 
	
    
    /* display the panel and run the user interface */
    errChk (DisplayPanel (panelHandle));
    errChk (RunUserInterface ());

Error:
    /* clean up */
    DiscardPanel (panelHandle);
    return 0;
}

int CVICALLBACK panelCB (int panel, int event, void *callbackData,
        int eventData1, int eventData2)
{
    if (event == EVENT_CLOSE)
        QuitUserInterface (0);
    return 0;
}

int CVICALLBACK write (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2) {
	switch (event) {
		case EVENT_COMMIT:
			{
				GetCtrlVal(panelHandle, PANEL_address_w, &address);
				GetCtrlVal(panelHandle, PANEL_subaddress_w, &subaddress);
				GetCtrlVal(panelHandle, PANEL_val_w, &val);
				avalon_write(address, subaddress, val);
				break;
			}
	

			break;
	}
	return 0;
}

int CVICALLBACK read (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2) {
	switch (event) {
		case EVENT_COMMIT:
			{
				GetCtrlVal(panelHandle, PANEL_address_r, &address);
				GetCtrlVal(panelHandle, PANEL_subaddress_r, &subaddress);
				avalon_read(address, subaddress, &val);
				SetCtrlVal(panelHandle, PANEL_val_r, val);
				break;
			}
		case EVENT_LEFT_CLICK:

		
			break;
	}
	return 0;
}

int CVICALLBACK dac (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2) {
	switch (event) {
		case EVENT_COMMIT:
			{
				int code;
				switch(control)
				{
					case PANEL_DAC_V:
						{
							double data;
							GetCtrlVal(PANEL, PANEL_DAC_V, &data);
							code = dac_voltage_to_code(data);
							SetCtrlVal(PANEL, PANEL_DAC_C, code);
							break;
						}
					case PANEL_DAC_C:
						{
							GetCtrlVal(PANEL, PANEL_DAC_C, &code);
							//code_check(&code,0,255);
							SetCtrlVal(PANEL, PANEL_DAC_V, dac_code_to_voltage(code));
							break;
						};
				}
				dac_out(0x02,code);
				dac_out(0x03,code);
				break;
			}
		case EVENT_LEFT_CLICK:

	
			break;
	}
	return 0;
}

int CVICALLBACK adc (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2) {
	switch (event) {
		case EVENT_COMMIT:
			{
				double data;
				adc_in(0x16,&data);
				SetCtrlVal(PANEL, PANEL_DAC_VIN1_V, data);
				SetCtrlVal(PANEL, PANEL_NUMERIC_4, adc_voltage_to_code(data));
				adc_in(0x17,&data);
				SetCtrlVal(PANEL, PANEL_DAC_VIN2_V, data);
				SetCtrlVal(PANEL, PANEL_NUMERIC_5, adc_voltage_to_code(data));
				break;
			}
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
