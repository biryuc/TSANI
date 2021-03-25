#include <ansi_c.h>
#include <cvirte.h>     
#include <userint.h>
#include <tsani.h>
#include "Sinus.h"
#include "toolbox.h"

#define datasize 1000

static int panelHandle;

double A = 3;
double freq = 10;
double phi = 0;
double arrSignal[LENGTH], arrPower[LENGTH];
double noise = 0.7;


void CreateSignal()
{
	int i;
	for ( i = 0; i < datasize; i++)
	{
		arrSignal[i] = A * sin(2 * PI * freq * i / 1000 + phi * PI) + Random(-noise, noise);
	}
}


void DrawGraph()
{
	DeleteGraphPlot(PANEL, PANEL_GRAPH, -1, VAL_DELAYED_DRAW);
	SetAxisScalingMode(PANEL, PANEL_GRAPH, VAL_BOTTOM_XAXIS, VAL_MANUAL, 0, datasize);
	SetAxisScalingMode(PANEL, PANEL_GRAPH, VAL_LEFT_YAXIS, VAL_MANUAL, -15, 15);
	PlotY(PANEL, PANEL_GRAPH, arrSignal, LENGTH, VAL_DOUBLE, VAL_THIN_LINE, VAL_CONNECTED_POINTS, VAL_SOLID, 2, VAL_RED);
}

void calculate_module(){
    for(int i = 0; i < 1000; i++)
        module[i] = sqrt(sin_fft_real[i]*sin_fft_real[i] + sin_fft_im[i]*sin_fft_im[i]);
}

void draw_graph_FFT(){
    DeleteGraphPlot(panelHandle, PANEL_GRAPH_2, -1, VAL_DELAYED_DRAW);
    SetAxisScalingMode(panelHandle, PANEL_GRAPH_2, VAL_BOTTOM_XAXIS, VAL_MANUAL, 0, 1000);
    SetAxisScalingMode(panelHandle, PANEL_GRAPH_2, VAL_LEFT_YAXIS, VAL_AUTOSCALE, 0, 0);
    PlotY(panelHandle, PANEL_GRAPH_2, module, 1000, VAL_DOUBLE, VAL_THIN_LINE, VAL_SOLID_SQUARE, VAL_SOLID, 10000, VAL_GREEN);
}

void DrawPower()
{
	int i;
	for ( i = 0; i < LENGTH; i++)
	{
		arrPower[i] = (A * sin(2 * PI * freq * i / 1000 + phi * PI) + Random(-noise, noise))*(A * sin(2 * PI * freq * i / 1000 + phi * PI) + Random(-noise, noise));
	}
	
	DeleteGraphPlot(PANEL, PANEL_GRAPH_POWER, -1, VAL_DELAYED_DRAW);
	SetAxisScalingMode(PANEL, PANEL_GRAPH_POWER, VAL_BOTTOM_XAXIS, VAL_MANUAL, 0, datasize);
	SetAxisScalingMode(PANEL, PANEL_GRAPH_POWER, VAL_LEFT_YAXIS, VAL_MANUAL, 0, 100);
	PlotY(PANEL, PANEL_GRAPH_POWER, arrPower, LENGTH, VAL_DOUBLE, VAL_THIN_LINE, VAL_CONNECTED_POINTS, VAL_SOLID, 2, VAL_GREEN);
	
}	

int main (int argc, char *argv[])
{
    int error = 0;
	int i;
 
    nullChk (InitCVIRTE (0, argv, 0));
    errChk (panelHandle = LoadPanel (0, "Sinus.uir", PANEL));
    
	CreateSignal();
	DrawGraph();
	DrawPower();
    FFT(sin_fft_real, sin_fft_im, 1000);
    calculate_module();
    draw_graph_FFT();
    errChk (DisplayPanel (panelHandle));
    errChk (RunUserInterface ());

Error:
    /* clean up */
    DiscardPanel (panelHandle);
    return 0;
}


int CVICALLBACK panelCB (int panel, int event, void *callbackData, int eventData1, int eventData2)
{
    if (event == EVENT_CLOSE)
        QuitUserInterface (0);
    return 0;
}

int CVICALLBACK Timer1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
	if (event == EVENT_TIMER_TICK)
	{
		CreateSignal();
		DrawGraph();
		DrawPower();
	};
	return 0;
}

int CVICALLBACK EditAmplitude(int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
	if (event == EVENT_COMMIT)
	{
		GetCtrlVal(PANEL, PANEL_Amplitude, &A);
	};
	return 0;
}

int CVICALLBACK EditFrequency(int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
	if (event == EVENT_COMMIT)
	{
		GetCtrlVal(PANEL, PANEL_Frequency, &freq);
	};
	return 0;
}		

int CVICALLBACK EditPhase(int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
	if (event == EVENT_COMMIT)
	{
		GetCtrlVal(PANEL, PANEL_Phase, &phi);
	};
	return 0;
}
		
int CVICALLBACK EditNoise(int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
	if (event == EVENT_COMMIT)
	{
		GetCtrlVal(PANEL, PANEL_Noise, &noise);
	};
	return 0;
}		
		
int CVICALLBACK SaveButton(int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
	int i;
	FILE *pF;
	if (event == EVENT_COMMIT)
	{
		pF = fopen("Data.txt","w");
		for (i=0; i<datasize; i++)
		{
			fprintf(pF, "%i\t%f\n", i, arrSignal[i]);
		}
		fclose(pF);
	};
	return 0;
}		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
