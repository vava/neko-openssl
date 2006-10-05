#include "stdafx.h"

#include "neko.h"
#include "stdio.h"
#include "openssl/ssl.h"
#include "openssl/bio.h"
#include "openssl/err.h"

DEFINE_KIND(k_ssl_ctx_pointer);
DEFINE_KIND(k_ssl_method_pointer);
DEFINE_KIND(k_ssl);
DEFINE_KIND(k_ssl_ctx);

//void	SSL_load_error_strings(void );
__declspec(dllexport) value _SSL_load_error_strings() {
	SSL_load_error_strings();
	return VAL_VOID;
}

//void OpenSSL_add_all_algorithms)(void );
__declspec(dllexport) value _OpenSSL_add_all_algorithms() {
	OpenSSL_add_all_algorithms();
	return VAL_VOID;
}

//int SSL_library_init(void );
__declspec(dllexport) value _SSL_library_init(){
	SSL_library_init();
	return VAL_VOID;
}
//SSL_CTX *SSL_CTX_new(SSL_METHOD *meth);
__declspec(dllexport) value _SSL_CTX_new(value meth){
	printf("ssl_ctx_new1 Error %s\n", ERR_error_string(ERR_get_error(), NULL));
	SSL_CTX* ssl_ctx = SSL_CTX_new((SSL_METHOD*)val_data(meth));
	printf("ssl_ctx_new2 Error %s\n", ERR_error_string(ERR_get_error(), NULL));
	return alloc_abstract(k_ssl_ctx_pointer, ssl_ctx);
}
//int SSL_CTX_load_verify_locations(SSL_CTX *ctx, const char *CAfile,
//	const char *CApath);
__declspec(dllexport) value _SSL_CTX_load_verify_locations(value ctx, /*value CAfile, */ value CApath){
	return alloc_int(
		SSL_CTX_load_verify_locations((SSL_CTX*)val_data(ctx),
											/*val_string(CAfile)*/ NULL,
											val_string(CApath))
		);
}
//BIO *BIO_new_ssl_connect(SSL_CTX *ctx);
__declspec(dllexport) value _BIO_new_ssl_connect(value ctx){
	return alloc_abstract(k_ssl_ctx_pointer,BIO_new_ssl_connect((SSL_CTX*)val_data(ctx)));
}
//#define BIO_get_ssl(b,sslp)	BIO_ctrl(b,BIO_C_GET_SSL,0,(char *)sslp)
//long	BIO_ctrl(BIO *bp,int cmd,long larg,void *parg);

__declspec(dllexport) value _BIO_get_ssl(value b/*, value sslp*/){
	SSL* r_ssl = NULL;
	long r_bio_get_ssl = BIO_get_ssl((BIO*)val_data(b), &r_ssl);
	// Debug
	printf("BIO_get_ssl : %d\n", r_bio_get_ssl);
	//
	return alloc_abstract(k_ssl, r_ssl);
	//char* ssl = (char*)val_data(sslp);
	//return alloc_best_int(BIO_get_ssl((BIO*)val_data(b), &ssl));
}

//#define SSL_set_mode(ssl,op) SSL_ctrl((ssl),SSL_CTRL_MODE,(op),NULL)
//long	SSL_ctrl(SSL *ssl,int cmd, long larg, void *parg);

__declspec(dllexport) value _SSL_set_mode(value ssl, value op) {
	long response = SSL_set_mode((SSL*) val_data(ssl), val_int(op));
	printf ("response SSL_set_mode() = %d\n", response);
	return alloc_best_int(response);
}

//#define SSL_MODE_AUTO_RETRY 0x00000004L
__declspec(dllexport) value _SSL_MODE_AUTO_RETRY() {
	return  alloc_best_int(0x00000004L);
}

//SSL_METHOD *SSLv23_client_method(void);
__declspec(dllexport) value _SSLv23_client_method() {
	return alloc_abstract(k_ssl_method_pointer, SSLv23_client_method());
}
//SSL *	SSL_new(SSL_CTX *ctx);
__declspec(dllexport) value _SSL_new(value ssl_ctx){
	printf("ssl_new1 Error %s\n", ERR_error_string(ERR_get_error(), NULL));
	SSL* ssl = SSL_new((SSL_CTX*)val_data(ssl_ctx));
	printf("SSL[%d]\n", ssl);
	printf("ssl_new2 Error %s\n", ERR_error_string(ERR_get_error(), NULL));
	return alloc_abstract(k_ssl_ctx, ssl);
}
//void	SSL_set_bio(SSL *s, BIO *rbio,BIO *wbio);
__declspec(dllexport) value _SSL_set_bio(value s, value rbio, value wbio){
	printf("s[%d], rbio[%d], wbio[%d]\n", val_data(s), val_data(rbio), val_data(wbio));
	printf("Error %s\n", ERR_error_string(ERR_get_error(), NULL));
	SSL_set_bio((SSL*)val_data(s), (BIO*)val_data(rbio),(BIO*)val_data(wbio));
	printf("s[%d], rbio[%d], wbio[%d]\n", val_data(s), val_data(rbio), val_data(wbio));
	printf("Error %s\n", ERR_error_string(ERR_get_error(), NULL));
	return VAL_VOID;
}

__declspec(dllexport) value _BIO_NOCLOSE(){
	return alloc_int(BIO_NOCLOSE);
}

//int 	SSL_connect(SSL *ssl);
__declspec(dllexport) value _SSL_connect(value ssl){
	int rsc = SSL_connect((SSL*) val_data(ssl));
	printf("[%d]Error %s\n", rsc, ERR_error_string(ERR_get_error(), NULL));
	//
	printf ("Sock errors: %d\n", GetLastError());
	//
	return alloc_int(rsc);
}
//void SSL_CTX_set_verify(SSL_CTX *ctx,int mode,
//											int (*callback)(int, X509_STORE_CTX *));
__declspec(dllexport) value _SSL_CTX_set_verify(value ctx, value mode,
												value (*callback)(value, value)){
	//SSL_CTX_set_verify((SSL_CTX*) val_data(ctx), val_int(mode), );
	return VAL_VOID;
}
//int	SSL_set_fd(SSL *s, int fd);
__declspec(dllexport) value _SSL_set_fd(value s, value fd){
	return alloc_int(SSL_set_fd((SSL*) val_data(s), val_int(fd)));
}
//void SSL_CTX_set_verify_depth(SSL_CTX *ctx,int depth);
__declspec(dllexport) value _SSL_CTX_set_verify_depth(value ctx, value depth) {
	SSL_CTX_set_verify_depth((SSL_CTX*) val_data(ctx), val_int(depth));
	return VAL_VOID;
}
//int 	SSL_read(SSL *ssl,void *buf,int num);
value _SSL_read(value ssl, value buf, value num){
	return alloc_int(SSL_read((SSL*) val_data(ssl), val_data(buf), val_int(num)));
}
//int 	SSL_write(SSL *ssl,const void *buf,int num);
value _SSL_write(value ssl, const value buf, value num){
	return alloc_int(SSL_write((SSL*) val_data(ssl), val_data(buf), val_int(num)));
}
//Register
DEFINE_PRIM(_SSL_read,  3);
DEFINE_PRIM(_SSL_write, 3);
DEFINE_PRIM(_SSL_CTX_set_verify_depth, 2);
DEFINE_PRIM(_SSL_set_fd, 2);
DEFINE_PRIM(_SSL_connect, 1);
DEFINE_PRIM(_BIO_NOCLOSE, 0);
DEFINE_PRIM(_SSL_set_bio, 3);
DEFINE_PRIM(_SSL_new, 1);
DEFINE_PRIM(_BIO_get_ssl,1);
DEFINE_PRIM(_BIO_new_ssl_connect,1);
DEFINE_PRIM(_SSL_CTX_load_verify_locations,2) //!!
DEFINE_PRIM(_SSL_CTX_new,1);
DEFINE_PRIM(_SSL_library_init,0);
DEFINE_PRIM(_SSL_load_error_strings, 0);
DEFINE_PRIM(_OpenSSL_add_all_algorithms, 0);
DEFINE_PRIM(_SSL_set_mode, 2);
DEFINE_PRIM(_SSL_MODE_AUTO_RETRY, 0);
DEFINE_PRIM(_SSLv23_client_method, 0);