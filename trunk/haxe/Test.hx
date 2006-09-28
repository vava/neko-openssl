/*
DEFINE_PRIM(_ERR_load_BIO_strings, 0);
DEFINE_PRIM(_BIO_new_connect, 1);
DEFINE_PRIM(_BIO_do_connect, 1);
DEFINE_PRIM(_BIO_read, 3);
	trace ("Starting...\n"); 
	SSL_load_error_strings();
	ERR_load_BIO_strings();
	OpenSSL_add_all_algorithms();
	BIO * bio;
	SSL_library_init();
	SSL_CTX * ctx = SSL_CTX_new(SSLv23_client_method());
	SSL * ssl;

	//Load certificates
	if (!SSL_CTX_load_verify_locations(ctx, NULL,"E:\\openssl-0.9.8c\\certs")){
		trace ("Error in loading trust store file...");
	}

	bio = BIO_new_ssl_connect(ctx);
	BIO_get_ssl(bio, & ssl);
	SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);
	char* host_port = "activate.microsoft.com:443/"; //"https://www.cvsdude.com:443"
	BIO_set_conn_hostname(bio, host_port);
	int r_bio_do_connect = BIO_do_connect(bio);
	trace ("BIO_do_connect = %d\n",r_bio_do_connect);
	if (r_bio_do_connect <= 0) {
		trace ("Connection failed...[%d]\n",r_bio_do_connect);
	}
	char* wbuf="get \ \n"; //"get / \r\n";
	char rbuf [255];
	int r_bio_write =BIO_write(bio, wbuf, 6);
	trace ("BIO_write[%s] = %d\n",wbuf,r_bio_write);
	trace("\n 1 \n");
	int len=254;
	int r_BIO_read = BIO_read ( bio, rbuf, len);
	trace ("BIO_read[%s] = %d\n", rbuf, r_BIO_read);
	BIO_free_all(bio);
	return 0;
*/

class Test {
	static var  SSL_load_error_strings = neko.Lib.load("opensslndll","_SSL_load_error_strings",0);
	static var  ERR_load_BIO_strings = neko.Lib.load("opensslndll","_ERR_load_BIO_strings",0);
	static var  OpenSSL_add_all_algorithms = neko.Lib.load("opensslndll","_OpenSSL_add_all_algorithms",0);
	static var  BIO_new_connect = neko.Lib.load("opensslndll","_BIO_new_connect",1);
	static var  getpointer = neko.Lib.load("opensslndll","getpointer",1);	
	static var  BIO_do_connect = neko.Lib.load("opensslndll","_BIO_do_connect",1);
	static var  BIO_set_conn_port = neko.Lib.load("opensslndll", "_BIO_set_conn_port", 2);
	static var  BIO_set_conn_hostname = neko.Lib.load("opensslndll", "_BIO_set_conn_hostname", 2);	
	static var  SSL_library_init = neko.Lib.load("opensslndll", "_SSL_library_init", 0); 
	static var  SSL_CTX_new = neko.Lib.load("opensslndll", "_SSL_CTX_new", 1);
	static var  SSL_CTX_load_verify_locations = neko.Lib.load("opensslndll", "_SSL_CTX_load_verify_locations", 2);
	static var  BIO_new_ssl_connect = neko.Lib.load("opensslndll","_BIO_new_ssl_connect",1);
	static var  BIO_get_ssl = neko.Lib.load("opensslndll","_BIO_get_ssl",2);
	static var  SSL_set_mode = neko.Lib.load("opensslndll", "_SSL_set_mode",1);
	static var  SSL_MODE_AUTO_RETRY = neko.Lib.load("opensslndll", "_SSL_MODE_AUTO_RETRY",0);
	static var  BIO_free_all = neko.Lib.load("opensslndll","_BIO_free_all",1);
	static var  SSLv23_client_method = neko.Lib.load("opensslndll", "_SSLv23_client_method",0);
	static var  BIO_read = neko.Lib.load("opensslndll", "_BIO_read",3);
	static var  BIO_write = neko.Lib.load("opensslndll", "_BIO_write",3);
	static var  val_of_NULL = neko.Lib.load("opensslndll", "val_of_NULL",0);
	static var  print = neko.Lib.load("opensslndll", "print",2);
	static function main(){
		//try {
			SSL_load_error_strings();
			ERR_load_BIO_strings();
			OpenSSL_add_all_algorithms();
			
			SSL_library_init();
			var ctx = SSL_CTX_new(SSLv23_client_method());
		    var ssl;
			var sclvl : Int = SSL_CTX_load_verify_locations(ctx, 
													neko.Lib.haxeToNeko("E:\\openssl-0.9.8c\\certs"));
			trace ("Answer SSL_CTX_lvl = " + sclvl);
							
			var bio = BIO_new_ssl_connect(ctx);
			var rbgs = BIO_get_ssl(bio, ssl);
			trace ("rbgs = " + rbgs);
			var rssm = SSL_set_mode(ssl/*, SSL_MODE_AUTO_RETRY()*/);
			trace ("rssm = " + rssm);			
			var host_port = "activate.microsoft.com:443/";
			BIO_set_conn_hostname(bio, neko.Lib.haxeToNeko(host_port) );
			
			//print(neko.Lib.haxeToNeko("null="),bio);			
			
			var r_bio_do_connect = BIO_do_connect(bio);
			trace ("BIO_do_connect = " + r_bio_do_connect + "\n");
			/*if (r_bio_do_connect <= 0) {
				trace ("Connection failed..."+r_bio_do_connect);
			}
			var wbuf="get \\ \n";
			var rbuf;
			var r_bio_write = BIO_write(bio, wbuf, 6);
			trace ("BIO_write["+wbuf+"] = "+r_bio_write+"\n");
			var len : Int = 254;
			var r_BIO_read : Int = BIO_read ( bio, rbuf, len);
			trace ("BIO_read["+rbuf+"] = "+r_BIO_read+"\n");
			BIO_free_all(bio); */
		//} catch(e : String) {
		//	trace ("catch: " + e);
		//}
			
	}
}