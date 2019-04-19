#pragma once
#include "ThisComm.h"
#include "afxwin.h"



struct CenterIP
{
	unsigned char my_ip[4];
	unsigned char fw_ip[4];
	unsigned char wg_ip[4];
	unsigned short my_com;
	unsigned short fw_com;
};


int str_to_int(CString buf, int *ints);




class my_config
{
public:
	ThisComm *com=0;
	char my_txt;
	void my_setcom(ThisComm *icom)
	{
		com = icom;
	}
	int my_entercfg(unsigned short);
	int my_esccfg(unsigned short);
	int my_cfgaddr(unsigned short,unsigned short, unsigned char, unsigned char);
	int my_cfgstudy(unsigned short,  unsigned char);
	int my_cfgcenter(unsigned short, unsigned short *, unsigned short,unsigned char *);
	int my_cfgcenterip(unsigned short, CenterIP);
	int my_complitetime(unsigned char *);
	int my_enteriap(unsigned short);
	int my_updataing(unsigned short, unsigned short, unsigned short, unsigned char *);
	int my_reset(unsigned short);
	CString my_geterrtype(short);
};






