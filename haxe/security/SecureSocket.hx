package security;

import neko.io.Socket.Host;

class SecureSocket /*extends neko.io.Socket*/ {

	static var  SSL_load_error_strings = neko.Lib.load("opensslndll","_SSL_load_error_strings",0);
	static var  ERR_load_BIO_strings = neko.Lib.load("opensslndll","_ERR_load_BIO_strings",0);
	static var  OpenSSL_add_all_algorithms = neko.Lib.load("opensslndll","_OpenSSL_add_all_algorithms",0);
	static var  SSL_library_init = neko.Lib.load("opensslndll", "_SSL_library_init", 0); 
	static var  SSL_CTX_new = neko.Lib.load("opensslndll", "_SSL_CTX_new", 1);
	static var  SSL_CTX_load_verify_locations = neko.Lib.load("opensslndll", "_SSL_CTX_load_verify_locations", 2);
	static var  BIO_new_ssl_connect = neko.Lib.load("opensslndll","_BIO_new_ssl_connect",1);
	static var  BIO_get_ssl = neko.Lib.load("opensslndll","_BIO_get_ssl",1);
	static var  SSL_set_mode = neko.Lib.load("opensslndll", "_SSL_set_mode",2);
	static var  SSL_MODE_AUTO_RETRY = neko.Lib.load("opensslndll", "_SSL_MODE_AUTO_RETRY",0);
	static var  SSLv23_client_method = neko.Lib.load("opensslndll", "_SSLv23_client_method",0);
	static var  BIO_do_connect = neko.Lib.load("opensslndll","_BIO_do_connect",1);	
	static var  BIO_set_conn_port = neko.Lib.load("opensslndll", "_BIO_set_conn_port", 2);
	static var  BIO_set_conn_hostname = neko.Lib.load("opensslndll", "_BIO_set_conn_hostname", 2);	

	
	static var ctx;
	static var bio;
	static var ssl;

	public var input(default,null) : neko.io.SocketInput;
	public var output(default,null) : neko.io.SocketOutput;
	
	public function new() {
		SSL_load_error_strings();
		ERR_load_BIO_strings();
		OpenSSL_add_all_algorithms();
		SSL_library_init();
		
		ctx = SSL_CTX_new(SSLv23_client_method());
		var rsclvl : Int = SSL_CTX_load_verify_locations(ctx, 
												neko.Lib.haxeToNeko("E:\\openssl-0.9.8c\\certs"));
		//trace ("rsclvl = " + rsclvl);
		bio = BIO_new_ssl_connect(ctx);
		ssl = BIO_get_ssl(bio);
		var rssm : Int = SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY());
		//trace ("rssm = " + rssm);			
		input = new SecureSocketInput(bio);
		output = new SecureSocketOutput(bio);
	}
	
	public  function write(content: String){
		output.write(content);
	}
	
	public function read(nbytes: Int) : String{
		return input.read(nbytes);
	}
		
	public  function connect(host : Host, port : Int){
		var host_port = neko.io.Socket.hostToString(host) + ":" + port;
		//var host_port = "activate.microsoft.com:443/";
		var rbsch : Int= BIO_set_conn_hostname(bio, neko.Lib.haxeToNeko(host_port) );
		//trace ("rbsch= " + rbsch);
		var r_bio_do_connect : Int = BIO_do_connect(bio);
		trace ("BIO_do_connect = " + r_bio_do_connect + "\n");
		if (r_bio_do_connect <= 0) {
			trace ("Connection failed..."+r_bio_do_connect);
		}
	}
}