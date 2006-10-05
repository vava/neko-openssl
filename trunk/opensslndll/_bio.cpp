#include "stdafx.h"
#include "neko.h"
#include "stdio.h"
#include "openssl/bio.h"
#include "openssl/err.h"
#include "string.h"

DEFINE_KIND(k_pointer);
DEFINE_KIND(k_BIO);
DEFINE_KIND(k_BIO_METHOD);
//BIO *BIO_new_connect(char* host_port);

__declspec(dllexport) value _BIO_new_connect(value host_port) {
	// 4Debug
	//printf("Debug: [string:%s][strlen:%d][is_string:%d]",val_string(host_port),
	//										val_strlen(host_port),val_is_string(host_port));
	void* ptr;
	ptr = BIO_new_connect(val_string(host_port));
	return alloc_abstract(k_pointer,ptr);
}

//void ERR_load_BIO_strings(void);

__declspec(dllexport) value _ERR_load_BIO_strings() {
	ERR_load_BIO_strings();
	return VAL_VOID;
}

//long	BIO_ctrl(BIO *bp,int cmd,long larg,void *parg);
//#define BIO_do_connect(b)	BIO_do_handshake(b)
//#define BIO_do_accept(b)	BIO_do_handshake(b)
//#define BIO_do_handshake(b)	BIO_ctrl(b,BIO_C_DO_STATE_MACHINE,0,NULL)

__declspec(dllexport) value _BIO_do_connect(value bp){
	//val_check_kind(bp, k_pointer);	
	BIO* bio_bp = (BIO*)val_data(bp);
	//printf ("bio_bp=[%d]",bio_bp);
	long result = BIO_do_connect(bio_bp);
	if (result < 0)
		printf("Error %s\n", ERR_error_string(ERR_get_error(), NULL));
	return alloc_best_int(result);
}

//int	BIO_read(BIO *b, void *data, int len);
__declspec(dllexport) value _BIO_read(value b, value len) {
	//val_check_kind(b, k_pointer);
	//val_check_kind(data, k_pointer);
	//val_is_int(len);
	int len_ = val_int(len);
	printf ("BIO read len= %d\n",len_);
	char data [255];
	long response = BIO_read((BIO*)val_data(b), data, len_+1);
	printf("Error bio read %s\n", ERR_error_string(ERR_get_error(), NULL));
	printf("BIO_read response= %d \n", response);
	return alloc_string(data);
}

//#define BIO_set_conn_port(b,port) BIO_ctrl(b,BIO_C_SET_CONNECT,1,(char *)port)
__declspec(dllexport) value _BIO_set_conn_port(value b, value port) {
	//val_check_kind(b, k_pointer);
	//val_is_int(port);
	return alloc_best_int(BIO_set_conn_port((BIO*)val_data(b), val_int(port)));
}

//int	BIO_write(BIO *b, const void *data, int len);
__declspec(dllexport) value _BIO_write(value b, value data, value len) {
	//val_check_kind(b, k_pointer);
	//val_check_kind(data, k_pointer);
	//val_is_int(len);
	long response = BIO_write((BIO*)val_data(b), val_string(data), val_int(len));
	printf ("Error bio write: %s\n", ERR_reason_error_string(ERR_get_error()));
	printf ("BIO_write response: %d\n",response);
	return alloc_best_int(response);
}

//#define BIO_set_conn_hostname(b,name) BIO_ctrl(b,BIO_C_SET_CONNECT,0,(char *)name)
__declspec(dllexport) value _BIO_set_conn_hostname(value b, value name) {
	return alloc_best_int(BIO_set_conn_hostname((BIO*) val_data(b), val_string(name)) );
}

//void	BIO_free_all(BIO *a);
__declspec(dllexport) value _BIO_free_all(value a) {
	BIO_free_all((BIO*) val_data(a) );
	return VAL_VOID;
}
#define val_sock(o)  ((int_val)val_data(o))
//BIO *BIO_new_socket(int sock, int close_flag);
__declspec(dllexport) value _BIO_new_socket(value sock, value close_flag){
	printf("bio_new_socket Error1 %s\n", ERR_error_string(ERR_get_error(), NULL));
	int sock_ = ((int_val)val_data(sock));
	BIO* bio = BIO_new_socket(sock_, val_int(close_flag));
	printf ("BIO[%d], socket[%d]\n", bio, sock_);
	printf("bio_new socket Error2 %s\n", ERR_error_string(ERR_get_error(), NULL));
	return alloc_abstract(k_BIO, bio);
}

/*int tcp_connect()
 {
    struct hostent *hp;
    struct sockaddr_in addr;
    int sock;
    
    if(!(hp=gethostbyname(HOST)))
      berr_exit("Couldn't resolve host");
    memset(&addr,0,sizeof(addr));
    addr.sin_addr=*(struct in_addr*)hp->h_addr_list[0];
    addr.sin_family=AF_INET;
    addr.sin_port=htons(PORT);

    if((sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))<0)
      err_exit("Couldn't create socket");
    if(connect(sock,(struct sockaddr *)&addr,sizeof(addr))<0)
      err_exit("Couldn't connect socket");
    
    return sock;
  }*/
//BIO *	BIO_new(BIO_METHOD *type);
value _BIO_new(value type) {
	return alloc_abstract(k_BIO, BIO_new((BIO_METHOD*) val_data(type)));
}
//#define BIO_set_fd(b,fd,c)	BIO_int_ctrl(b,BIO_C_SET_FD,c,fd)
//long	BIO_int_ctrl(BIO *bp,int cmd,long larg,int iarg);
value _BIO_set_fd(value b, value fd, value c){
	return alloc_best_int (BIO_int_ctrl((BIO*) val_data(b), BIO_C_SET_FD, val_int(c),val_int(fd)));
}
//BIO_METHOD *BIO_s_socket(void);
value _BIO_s_socket(){
	return alloc_abstract(k_BIO_METHOD, BIO_s_socket());
}
//Register
DEFINE_PRIM (_BIO_s_socket, 0);
DEFINE_PRIM(_BIO_set_fd, 3);
DEFINE_PRIM(_BIO_new, 1);
DEFINE_PRIM(_BIO_new_socket, 2);
DEFINE_PRIM(_ERR_load_BIO_strings, 0);
DEFINE_PRIM(_BIO_new_connect, 1);
DEFINE_PRIM(_BIO_do_connect, 1);
DEFINE_PRIM(_BIO_read, 2);
DEFINE_PRIM(_BIO_set_conn_port, 2);
DEFINE_PRIM(_BIO_write, 3);
DEFINE_PRIM(_BIO_set_conn_hostname, 2);
DEFINE_PRIM(_BIO_free_all, 1);
