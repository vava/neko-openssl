// ndlltest.cpp : Defines the entry point for the console application.
//
#include "stdio.h"
#include "stdafx.h"
#include "../opensslndll/test.h"


int _tmain(int argc, _TCHAR* argv[])
{
	printf ("_tmain()\n");
	int x = mcon();
	printf ("mcon = %d", x);
	return 0;
}

