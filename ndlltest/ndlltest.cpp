// ndlltest.cpp : Defines the entry point for the console application.
//
#include "stdio.h"
#include "stdafx.h"
#include "../opensslndll/test.h"


int _tmain(int argc, _TCHAR* argv[])
{
	printf ("_tmain()\n Running mcon() :\n");
	printf ("r_mcon = %d\n", mcon());
	return 0;
}

