#ifdef WIN32
	#include "stdafx.h"
#endif

#include "neko.h"
#include "stdio.h"

DEFINE_KIND(kpointer);

value getpointer(value x){
	return alloc_abstract(kpointer, val_kind(&val_data(x)));
}

//value getval(value x){
//	return val_data(x);
//}

value val_of_NULL(){
	return val_null;
}

value print(value help,value x){
	void* ptr = val_kind(x);
	printf("%s",val_string(help));
	if (ptr == NULL) printf ("NULL\n"); else printf ("NOT NULL\n");
	return VAL_VOID;
}

DEFINE_PRIM(print,2);
DEFINE_PRIM(getpointer,1);
DEFINE_PRIM(val_of_NULL,0);