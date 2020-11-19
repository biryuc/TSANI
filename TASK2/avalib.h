#ifndef __avalib_H__
#define __avalib_H__

#ifdef __cplusplus
    extern "C" {
#endif

#include "cvidef.h"
//#include "avalib.c"		

//int Declare_Your_Functions_Here (int x);
void avalon_init(void);
void avalon_write(int address, int subaddress, int a);
void avalon_read(int address, int subaddress, int *a);



#ifdef __cplusplus
    }
#endif

#endif  /* ndef __avalib_H__ */
