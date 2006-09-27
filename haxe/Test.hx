/*
DEFINE_PRIM(_ERR_load_BIO_strings, 0);
DEFINE_PRIM(_BIO_new_connect, 1);
DEFINE_PRIM(_BIO_do_connect, 1);
DEFINE_PRIM(_BIO_read, 3);


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

*/
class Test {
	static var  SSL_load_error_strings = neko.Lib.load("opensslndll","_SSL_load_error_strings",0);
	static var  ERR_load_BIO_strings = neko.Lib.load("opensslndll","_ERR_load_BIO_strings",0);
	static var  OpenSSL_add_all_algorithms = neko.Lib.load("opensslndll","_OpenSSL_add_all_algorithms",0);
	static var  BIO_new_connect = neko.Lib.load("opensslndll","_BIO_new_connect",1);
	static var  getpointer = neko.Lib.load("opensslndll","getpointer",1);	
	static var  BIO_do_connect = neko.Lib.load("opensslndll","_BIO_do_connect",1);
	static var  BIO_set_conn_port = neko.Lib.load("opensslndll", "_BIO_set_conn_port", 2);
	
	static function main(){
		SSL_load_error_strings();
		ERR_load_BIO_strings();
		OpenSSL_add_all_algorithms();
		try {
			var bio = BIO_new_connect(neko.Lib.haxeToNeko("www.yandex.ru:80"));
			var answer = BIO_do_connect(bio);
			trace ("answer="+answer);
		} catch(e : String) {
			trace ("catch: " + e);
		}
		
	}
}