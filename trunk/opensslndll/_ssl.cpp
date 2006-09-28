#include "stdafx.h"

#include "neko.h"
#include "stdio.h"
#include "openssl/ssl.h"
#include "openssl/bio.h"
#include "openssl/err.h"
DEFINE_KIND(k_ssl_ctx_pointer);
DEFINE_KIND(k_ssl_method_pointer);

//void	SSL_load_error_strings(void );
value _SSL_load_error_strings() {
	SSL_load_error_strings();
	return VAL_VOID;
}

//void OpenSSL_add_all_algorithms)(void );
value _OpenSSL_add_all_algorithms() {
	OpenSSL_add_all_algorithms();
	return VAL_VOID;
}

//int SSL_library_init(void );
value _SSL_library_init(){
	SSL_library_init();
	return VAL_VOID;
}
//SSL_CTX *SSL_CTX_new(SSL_METHOD *meth);
value _SSL_CTX_new(value meth){
	return alloc_abstract(k_ssl_ctx_pointer,SSL_CTX_new((SSL_METHOD*)val_data(meth)));
}
//int SSL_CTX_load_verify_locations(SSL_CTX *ctx, const char *CAfile,
//	const char *CApath);
value _SSL_CTX_load_verify_locations(value ctx, /*value CAfile, */ value CApath){
	return alloc_int(
		SSL_CTX_load_verify_locations((SSL_CTX*)val_data(ctx),
											/*val_string(CAfile)*/ NULL,
											val_string(CApath))
		);
}
//BIO *BIO_new_ssl_connect(SSL_CTX *ctx);
value _BIO_new_ssl_connect(value ctx){
	return alloc_abstract(k_ssl_ctx_pointer,BIO_new_ssl_connect((SSL_CTX*)val_data(ctx)));
}
//#define BIO_get_ssl(b,sslp)	BIO_ctrl(b,BIO_C_GET_SSL,0,(char *)sslp)
//long	BIO_ctrl(BIO *bp,int cmd,long larg,void *parg);

value _BIO_get_ssl(value b, value sslp){
	
	int a1234 = 2;
	int b1234 = 3;
	int c________ = a1234+b1234;
	SSL* ssl = (SSL*)val_data(sslp);
	return alloc_best_int(BIO_get_ssl((BIO*)val_data(b), & ssl));
}

//#define SSL_set_mode(ssl,op) SSL_ctrl((ssl),SSL_CTRL_MODE,(op),NULL)
//long	SSL_ctrl(SSL *ssl,int cmd, long larg, void *parg);
value _SSL_set_mode(value ssl, value op) {
	return alloc_best_int(SSL_set_mode((SSL*) val_data(ssl), val_int(op)));
}

//#define SSL_MODE_AUTO_RETRY 0x00000004L
value _SSL_MODE_AUTO_RETRY() {
	return  alloc_best_int(0x00000004L);
}

//SSL_METHOD *SSLv23_client_method(void);
value _SSLv23_client_method() {
	return alloc_abstract(k_ssl_method_pointer, SSLv23_client_method());
}

//Register
DEFINE_PRIM(_BIO_get_ssl,2);
DEFINE_PRIM(_BIO_new_ssl_connect,1);
DEFINE_PRIM(_SSL_CTX_load_verify_locations,2) //!!
DEFINE_PRIM(_SSL_CTX_new,1);
DEFINE_PRIM(_SSL_library_init,0);
DEFINE_PRIM(_SSL_load_error_strings, 0);
DEFINE_PRIM(_OpenSSL_add_all_algorithms, 0);
DEFINE_PRIM(_SSL_set_mode, 2);
DEFINE_PRIM(_SSL_MODE_AUTO_RETRY, 0);
DEFINE_PRIM(_SSLv23_client_method, 0);