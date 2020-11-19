#include <ansi_c.h>
#include <cvirte.h>     
#include <userint.h>
//#include <tsani.h>
#include "3.2.h"
#include "toolbox.h"
//#include "avalib.h"
//#include "dacad.h"

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
double ADC_LSB=2.56/1023;
double Input[8192];
double Error[8192];
double FixC[8192];
double FixErr[8192];

double Theory[8192];
double X[8192];
double Data[8192];
double Source[8192];
double ZeroErr;
double ScErr;
	//==============================================================================
// Global functions



void WriteADC(){  
	FILE* pF1;
	FILE* pF2;
	pF1=fopen("Input.txt","r"); // perfect adc
	pF2=fopen("Data.txt","r"); // real adc
	for (int i=0;i<8192;i++){
		float temp;
		fscanf(pF1,"%f",&temp);
		Input[i]=temp;
		fscanf(pF2,"%f",&temp);
		Data[i]=temp;
		Theory[i]=i*1.0*1024/8192; // input code
		X[i]=i*ADC_LSB/8; //volt
	}
	
} 

void PlotADC(){
	PlotXY(panelHandle,PANEL_GRAPH,X,Data,8192,VAL_DOUBLE,VAL_DOUBLE,VAL_THIN_LINE,VAL_NO_POINT,VAL_SOLID,1,VAL_RED);
	PlotXY(panelHandle,PANEL_GRAPH,X,Input,8192,VAL_DOUBLE,VAL_DOUBLE,VAL_THIN_LINE,VAL_NO_POINT,VAL_SOLID,1,VAL_GREEN);
	PlotXY(panelHandle,PANEL_GRAPH,X,Theory,8192,VAL_DOUBLE,VAL_DOUBLE,VAL_THIN_LINE,VAL_NO_POINT,VAL_SOLID,1,VAL_YELLOW);
}   

/*void ADC_inp()
{
	for (int i=0;i<8192;i++){
		X[i]=ADC_LSB*i/8; //volt
		Source[i]=i/8;
		analogOut(0, X[i]); //DAC PXI
		adc_in(0x16, &Data[i]);// volt ACD AVALON
		//avalon_write(2, 0x16, Source[i]);
		//analogOut(0, Data[i]); //code
		//Data[i]*=ADC_LSB; // acd volt
		Data_code[i]=adc_voltage_to_code(Data[i]);
		
	}
	PlotXY(panelHandle,PANEL_GRAPH, X, Source, 8192,VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE,VAL_NO_POINT,VAL_SOLID,1,VAL_RED);
	PlotXY(panelHandle,PANEL_GRAPH, X, Data_code,8192,VAL_DOUBLE, VAL_INTEGER, VAL_THIN_LINE,VAL_NO_POINT,VAL_SOLID,1,VAL_GREEN);
	
}  */

void ErrADC()
{
	for (int i=0;i<8192;i++){
		  Error[i]=(Input[i]-Data[i]);	  // perfect-real 
	}
}

void ErrZero(){
	for(int i=0;Data[i]==0;i++) 
	ZeroErr=(-i+4)/8;
	SetCtrlVal(panelHandle,PANEL_ZEROERR_LSB,ZeroErr);
	SetCtrlVal(panelHandle,PANEL_ZEROERR_V,ZeroErr*ADC_LSB);
}

void ErrScale(){
	
	int l,k;
	for (int k=8191; Input[k]==1023; k--)
	for (int l=8191; Data[l]==1023; l--)
	ScErr=k-l+ZeroErr;
	SetCtrlVal(panelHandle,PANEL_SCERR_LSB,ScErr);
	SetCtrlVal(panelHandle,PANEL_SCERR_V,ScErr*ADC_LSB);
}

void FixCurve(){
	for (int i=0;i<8191+ZeroErr*8;i++){
		FixC[i]=Data[i-(int)ZeroErr*8]/(2.56-ScErr*ADC_LSB)*2.56; //rotate and remove offset
	}
	PlotXY(panelHandle,PANEL_GRAPH,X,FixC,8191+ZeroErr*8,VAL_DOUBLE, VAL_DOUBLE,VAL_THIN_LINE,VAL_NO_POINT,VAL_SOLID,1,VAL_BLUE);
}

void FixEr(){
	int p=0;
	for (int i=0;i<8191+ZeroErr*8;i++){  
		FixErr[i]=Input[i]-FixC[i];
	}
	PlotXY(panelHandle,PANEL_ERR_GRAPH,X, FixErr,8191+ZeroErr*8,VAL_DOUBLE,VAL_DOUBLE,VAL_THIN_LINE,VAL_NO_POINT,VAL_SOLID,1,VAL_RED);
}

void IntegErr(){
	double max=-1023;
	for (int i=0;i<8191+ZeroErr*8;i++){
		 if (abs(FixErr[i])>max) max = abs(FixErr[i]); 
	}

	SetCtrlVal(panelHandle,PANEL_INTERR,max);
}				  

/// HIFN The main entry-point function.
int main (int argc, char *argv[])
{
    int error = 0;
    //ni6251Slot(2);
	//avalon_init(); 
	//dac_init();
	//adc_init();
    /* initialize and load resources */
    nullChk (InitCVIRTE (0, argv, 0));
    errChk (panelHandle = LoadPanel (0, "3.2.uir", PANEL));
    WriteADC();
	PlotADC();
	ErrADC();
	ErrZero();
	ErrScale();
	FixCurve();
	FixEr();
	IntegErr(); 
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

