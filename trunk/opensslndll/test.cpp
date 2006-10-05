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

	/*  Unsecure connection
	bio = BIO_new_connect("www.yandex.ru:80");
	*/
	
	SSL_library_init();
	SSL_CTX * ctx = SSL_CTX_new(SSLv23_client_method());
	//printf ("Error: %s\n", ERR_reason_error_string(ERR_get_error()));
	SSL * ssl;

	//Load certificates
	if (!SSL_CTX_load_verify_locations(ctx, NULL,"E:\\openssl-0.9.8c\\certs")){
		printf ("Error in loading trust store file...");
	}

	bio = BIO_new_ssl_connect(ctx);
	BIO_get_ssl(bio, & ssl);
	long rssm = SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);
	printf ("rssm = %d\n",rssm);
	char* host_port = "activate.microsoft.com:443/"; //"https://www.cvsdude.com:443"
	long rbsch = BIO_set_conn_hostname(bio, host_port);
	printf ("rbsch= %d\n",rbsch);

	printf ("Error1: %s\n", ERR_reason_error_string(ERR_get_error()));

	int r_bio_do_connect = BIO_do_connect(bio);
	printf ("Error2: %s\n", ERR_reason_error_string(ERR_get_error()));
	printf ("BIO_do_connect = %d\n",r_bio_do_connect);
	if (r_bio_do_connect <= 0) {
		printf ("Connection failed...[%d]\n",r_bio_do_connect);
	}
	char* wbuf="get \ \n"; //"get / \r\n";
	char rbuf [255];
	int r_bio_write =BIO_write(bio, wbuf, 6);
	printf ("BIO_write[%s] = %d\n",wbuf,r_bio_write);
	printf("\n 1 \n");
	int len=254;
	printf ("Error3: %s\n", ERR_reason_error_string(ERR_get_error()));

	int r_BIO_read = BIO_read ( bio, rbuf, len);

	printf ("Error4: %s\n", ERR_reason_error_string(ERR_get_error()));

	printf ("BIO_read[%s] = %d\n", rbuf, r_BIO_read);

	printf ("Error5: %s\n", ERR_reason_error_string(ERR_get_error()));
	BIO_free_all(bio);
	return 0;
}

__declspec(dllexport) int testsocketssl (){
//	int sock = tcp_connect("activate.microsoft.com", 443);

	return 0;
}