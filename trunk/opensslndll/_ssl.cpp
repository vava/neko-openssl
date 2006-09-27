#include "stdafx.h"

#include "neko.h"
#include "stdio.h"
#include "openssl/ssl.h"
#include "openssl/bio.h"
#include "openssl/err.h"



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

//Register

DEFINE_PRIM(_SSL_load_error_strings, 0);
DEFINE_PRIM(_OpenSSL_add_all_algorithms, 0);