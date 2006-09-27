#include "stdafx.h"
#include <stdio.h>
#include "openssl/ssl.h"
#include "openssl/bio.h"
#include "openssl/err.h"

__declspec(dllexport) void n_hello(){
	printf ("n_hello()\n");
}

__declspec(dllexport) int mcon () {
	printf ("Starting...\n"); 
	SSL_load_error_strings();
	ERR_load_BIO_strings();
	OpenSSL_add_all_algorithms();
	BIO * bio;
	
	bio = BIO_new_connect("www.yandex.ru:80");
	if (bio == NULL) printf("error");
	int i=100;

	i = BIO_do_connect(bio);
	printf ("i= %d \n",i);
	int* buf = &i;
	int len = 4;
	int x = BIO_read ( bio, &buf, len);
	printf ("x = %d\n", x);
	printf ("buf = %d\n", *buf);
	//int y = BIO_write ( bio, &buf, len);
	//printf ("y = %d\n", y);
	
	/*
	SSL_CTX * ctx = SSL_CTX_new(SSLv23_cclient_mtethod());
	SSL * ssl;

	bio = BIO_new_ssl_connect(ctx);
	BIO_get_ssl(bio, & ssl);
	SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);
	BIO_set_conn_hostname(bio, "localhost:8080");
	*/

	//BIO_free_all(bio);
	return 0;
}