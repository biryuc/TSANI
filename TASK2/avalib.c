#include <ansi_c.h>
#include "tsani.h"
#include "avalib.h"
void avalon_init()
{
	ni6251Slot(2);
	portMask(0,0xff);
	portMask(1,0xff); 
	portMask(2,0x07); //ale 1 read 1 write 1
	portOut(0,0x00);
	portOut(1,0x00);
	portOut(2,0x06); //ale 0 read 1 write 1 
}
void avalon_write(int address, int subaddress, int a)
{
	int full_address = (address|(subaddress<<3));
	portMask(0,0xff);
	portMask(1,0xff); 
	portMask(2,0x07);
	portOut(0,full_address);
	portOut(1,full_address>>8);
	portOut(2,0x07);//ale 1 read 1 write 1 
	portOut(2,0x06);//ale 0 read 1 write 1 
	portOut(0,a);
	portOut(1,a>>8);
	portOut(2,0x02);//ale 0 read 1 write 0 
	portOut(2,0x06);//ale 0 read 1 write 1 
	
}
void avalon_read(int address, int subaddress, int *a)
{
	int full_address = (address|(subaddress<<3));
	unsigned char a0, a1;
	portMask(0,0xff);
	portMask(1,0xff); 
	portMask(2,0x07);
	portOut(0,full_address);
	portOut(1,full_address>>8);
	portOut(2,0x07);//ale 1 read 1 write 1 
	portOut(2,0x06);//ale 0 read 1 write 1
	portOut(2,0x04);//ale 0 read 0 write 1
	portMask(0,0x00);
	portMask(1,0x00);
	portIn(0,&a0);
	portIn(1,&a1);
	portOut(2,0x06);//ale 0 read 1 write 1
	*a = a0|(a1<<8);
}



