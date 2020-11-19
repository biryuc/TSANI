//==============================================================================
// Include files

#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "Task_1_2.h"
#include "toolbox.h"

//==============================================================================
// Constants
const int data_size = 1000;

//==============================================================================
// Types

//==============================================================================
// Static global variables

static int panelHandle = 0;

//==============================================================================
// Static functions

//==============================================================================
// Global variables
double data[data_size];

//==============================================================================
// Global functions
void create_signal(double frequence, double amplitude, double initial_phase, double noise_level, double *container, int size, double time_size) {
	for(int i = 0; i < size; i++)
		container[i] = amplitude * sin(initial_phase + frequence * time_size / size * i) + noise_level * Random(-1, 1);
	
	return;
}

void set_plot(int panel_handle, int control_id) {
	SetAxisScalingMode(panel_handle, control_id, VAL_BOTTOM_XAXIS, VAL_MANUAL, 0, data_size);
	SetAxisScalingMode(panel_handle, control_id, VAL_LEFT_YAXIS, VAL_MANUAL, -15, 15);
	return;
}

void draw_graph(int panel_handle, int control_id, double *data, int size_of_data) {
	DeleteGraphPlot(panel_handle, control_id, -1, VAL_IMMEDIATE_DRAW);
	PlotY(panel_handle, control_id, data, size_of_data, VAL_DOUBLE, VAL_FAT_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_RED);
	return;
}

int main (int argc, char *argv[]) {
	int error = 0;
	
	/* initialize and load resources */
	nullChk (InitCVIRTE (0, argv, 0));
	errChk (panelHandle = LoadPanel (0, "Task_1_2.uir", PANEL));
		
	/* display the panel and run the user interface */
	errChk (DisplayPanel (panelHandle));
	errChk (RunUserInterface ());

Error:
	/* clean up */
	if (panelHandle > 0)
		DiscardPanel (panelHandle);
	
	return 0;
}

//==============================================================================
// UI callback function prototypes

int CVICALLBACK panelCB (int panel, int event, void *callbackData,
		int eventData1, int eventData2) {
	if (event == EVENT_CLOSE)
		QuitUserInterface (0);
	return 0;
}

int CVICALLBACK save_callback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2) {
	switch (event)
	{
		case EVENT_COMMIT:
			FILE *save_file;
			save_file = fopen("F:\\Занятия\\ТСАНИ\\1\\Files\\graph.dat", "w");
			for(int i = 0; i < data_size; i++)
				fprintf(save_file, "%e\n", data[i]);
			fclose(save_file);
			break;
	}
	return 0;
}

int CVICALLBACK update_callback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2) {
	switch (event)
	{
		case EVENT_TIMER_TICK:
			double amplitude = 0;
			double frequence = 0;
			double init_phase = 0;
			double noise_level = 0;
			
			GetCtrlVal(panelHandle, PANEL_NOISE, &noise_level);
			GetCtrlVal(panelHandle, PANEL_PHASE, &init_phase);
			GetCtrlVal(panelHandle, PANEL_FREQ, &frequence);
			GetCtrlVal(panelHandle, PANEL_AMPL, &amplitude);
			create_signal(frequence, amplitude, init_phase, noise_level, data, data_size, 1000);
			set_plot(panelHandle, PANEL_GRAPH);
			draw_graph(panelHandle, PANEL_GRAPH, data, data_size);
			break;
	}
	return 0;
}