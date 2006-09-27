#include "stdafx.h"
#include "neko.h"
#include "stdio.h"
#include "openssl/bio.h"
#include "openssl/err.h"
#include "string.h"
DEFINE_KIND(k_pointer);

//BIO *BIO_new_connect(char* host_port);

value _BIO_new_connect(value host_port) {
	printf("[string:%s][strlen:%d][is_string:%d]",val_string(host_port),
											val_strlen(host_port),val_is_string(host_port));
	void* ptr;
	//try {
		ptr = BIO_new_connect(val_string(host_port));
	//} catch (...) {
	//  printf("in except");
	//}
	return alloc_abstract(k_pointer,ptr);
}

//void ERR_load_BIO_strings(void);

value _ERR_load_BIO_strings() {
	ERR_load_BIO_strings();
	return VAL_VOID;
}

//long	BIO_ctrl(BIO *bp,int cmd,long larg,void *parg);
//#define BIO_do_connect(b)	BIO_do_handshake(b)
//#define BIO_do_accept(b)	BIO_do_handshake(b)
//#define BIO_do_handshake(b)	BIO_ctrl(b,BIO_C_DO_STATE_MACHINE,0,NULL)

value _BIO_do_connect(value bp){
	val_check_kind(bp, k_pointer);	
	long result = BIO_do_connect((BIO*)val_data(bp));
	if (result ==-1)
		printf("%s\n", ERR_error_string(ERR_get_error(), NULL));
	else
		return alloc_best_int(result);
	//	return VAL_VOID;
}

//int	BIO_read(BIO *b, void *data, int len);
value _BIO_read(value b, value data, value len) {
	val_check_kind(b, k_pointer);
	val_check_kind(data, k_pointer);
	val_is_int(len);
	return alloc_int(BIO_read((BIO*)val_data(b), val_data(data), val_int(len)));
}

//#define BIO_set_conn_port(b,port) BIO_ctrl(b,BIO_C_SET_CONNECT,1,(char *)port)
value _BIO_set_conn_port(value b, value port) {
	val_check_kind(b, k_pointer);
	val_is_int(port);
	return alloc_best_int(BIO_set_conn_port((BIO*)val_data(b), val_int(port)));
}

//int	BIO_write(BIO *b, const void *data, int len);
value _BIO_write(value b, value data, value len) {
	val_check_kind(b, k_pointer);
	val_check_kind(data, k_pointer);
	val_is_int(len);
	return alloc_int(BIO_write( (BIO*)val_data(b), val_data(data), val_int(len) ));
}

//Register
DEFINE_PRIM(_ERR_load_BIO_strings, 0);
DEFINE_PRIM(_BIO_new_connect, 1);
DEFINE_PRIM(_BIO_do_connect, 1);
DEFINE_PRIM(_BIO_read, 3);
DEFINE_PRIM(_BIO_set_conn_port, 2);
DEFINE_PRIM(_BIO_write, 3);
