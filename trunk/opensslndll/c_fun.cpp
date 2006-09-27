#include "stdafx.h"
#include "neko.h"

DEFINE_KIND(kpointer);

value getpointer(value x){
	return alloc_abstract(kpointer, val_kind(&val_data(x)));
}

//value getval(value x){
//	return val_data(x);
//}
DEFINE_PRIM(getpointer,1);