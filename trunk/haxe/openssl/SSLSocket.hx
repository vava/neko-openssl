package openssl;

import neko.net.Socket;
import neko.net.Host;

enum CTX {
}

enum SSL {
}

class SSLSocket {
	public static var certFolder : String = "E:\\openssl-0.9.8c\\certs";
	private var __s : SocketHandle;
	private var ctx: CTX;
	private var ssl: SSL;
	public var input(default,null) : SSLSocketInput;
	public var output(default,null) : SSLSocketOutput;
	
	private function initializeOpenSSL(){
		SSL_library_init();						
		SSL_load_error_strings();
		ctx = SSL_CTX_new(SSLv23_client_method());
		var rsclvl : Int = SSL_CTX_load_verify_locations(
				ctx, neko.Lib.haxeToNeko(certFolder));
	}
	
	public function new( ?s ) {
		initializeOpenSSL();
		__s = if( s == null ) socket_new(false) else s;
		input = new SSLSocketInput(__s);
		output = new SSLSocketOutput(__s);
	}

	public function close() : Void {
		socket_close(__s);
		untyped {
			input.__s = null;
			output.__s = null;
		}
		input.close();
		output.close();
	}
	
	public function read() : String {
		return socket_read(ssl);		
	}

	public function write( content : String ) {
		socket_write(ssl, neko.Lib.haxeToNeko(content));
		
	}
	
	public function connect(host : Host, port : Int) {
		try {
			
			socket_connect(__s, host, port);
			ssl = SSL_new(ctx);
			
			input.ssl = ssl;
			output.ssl = ssl;
			
			var sbio = BIO_new_socket(__s, BIO_NOCLOSE());
			SSL_set_bio(ssl, sbio, sbio);
			var rsc : Int = SSL_connect(ssl);
		} catch( s : String ) {
			if( s == "std@socket_connect" )
				throw "Failed to connect on "+(try reverse(host) catch( e : Dynamic ) hostToString(host))+":"+port;
			else
				neko.Lib.rethrow(s);
		}
	}

	public function listen(connections : Int) {
		socket_listen(__s, connections);
	}

	public function shutdown( read : Bool, write : Bool ){
		SSL_shutdown(ssl);
		socket_shutdown(__s,read,write);
	}

	public function bind(host : Host, port : Int) {
		socket_bind(__s, host, port);
	}

	public function accept() : SSLSocket {
		return new SSLSocket(socket_accept(__s));
	}

	public function peer() : { host : Host, port : Int } {
		var a : Dynamic = socket_peer(__s);
		return { host : a[0], port : a[1] };
	}

	public function host() : { host : Host, port : Int } {
		var a : Dynamic = socket_host(__s);
		return { host : a[0], port : a[1] };
	}

	public function setTimeout( timeout : Float ) {
		socket_set_timeout(__s, timeout);
	}

	public function waitForRead() {
		select([this],null,null,null);
	}

	public function setBlocking( b : Bool ) {
		socket_set_blocking(__s,b);
	}

	// STATICS
	public static function select(read : Array<SSLSocket>, write : Array<SSLSocket>, others : Array<SSLSocket>, timeout : Float) : {read: Array<SSLSocket>,write: Array<SSLSocket>,others: Array<SSLSocket>} {
		var c = untyped __dollar__hnew( 1 );
		var f = function( a : Array<SSLSocket> ){
			if( a == null ) return null;
			untyped {
				var r = __dollar__amake(a.length);
				var i = 0;
				while( i < a.length ){
					r[i] = a[i].__s;
					__dollar__hadd(c,a[i].__s,a[i]);
					i += 1;
				}
				return r;
			}
		}
		var neko_array = socket_select(f(read),f(write),f(others), timeout);

		var g = function( a ) : Array<SSLSocket> {
			if( a == null ) return null;

			var r = new Array();
			var i = 0;
			while( i < untyped __dollar__asize(a) ){
				var t = untyped __dollar__hget(c,a[i],null);
				if( t == null ) throw "SSLSocket object not found.";
				r[i] = t;
				i += 1;
			}
			return r;
		}

		return {
			read: g(neko_array[0]),
			write: g(neko_array[1]),
			others: g(neko_array[2])
		};
	}

	public static function resolve(host : String) : Host {
		return host_resolve(neko.Lib.haxeToNeko(host));
	}

	public static function hostToString(host : Host) : String {
		return new String(host_to_string(host));
	}

	public static function reverse( host : Host ) : String {
		return new String(host_reverse(host));
	}

	public static function localhost() : String {
		return new String(host_local());
	}

	static function __init__() {
		neko.Lib.load("std","socket_init",0)();
	}

	private static var socket_new = neko.Lib.load("std","socket_new",1);
	private static var socket_close = neko.Lib.load("std","socket_close",1);
	private static var socket_write = neko.Lib.load("openssl","__SSL_write",2);
	private static var socket_read = neko.Lib.load("openssl","__SSL_read",1);
	private static var host_resolve = neko.Lib.load("std","host_resolve",1);
	private static var host_reverse = neko.Lib.load("std","host_reverse",1);
	private static var host_to_string = neko.Lib.load("std","host_to_string",1);
	private static var host_local = neko.Lib.load("std","host_local",0);
	private static var socket_connect = neko.Lib.load("std","socket_connect",3);
	private static var socket_listen = neko.Lib.load("std","socket_listen",2);
	private static var socket_select = neko.Lib.load("std","socket_select",4);
	private static var socket_bind = neko.Lib.load("std","socket_bind",3);
	private static var socket_accept = neko.Lib.load("std","socket_accept",1);
	private static var socket_peer = neko.Lib.load("std","socket_peer",1);
	private static var socket_host = neko.Lib.load("std","socket_host",1);
	private static var socket_set_timeout = neko.Lib.load("std","socket_set_timeout",2);
	private static var socket_shutdown = neko.Lib.load("std","socket_shutdown",3);
	private static var SSL_shutdown = neko.Lib.load("openssl","_SSL_shutdown",1);	
	private static var socket_set_blocking = neko.Lib.load("std","socket_set_blocking",2);
	
	private static var SSL_load_error_strings = neko.Lib.load("openssl","_SSL_load_error_strings",0);
	private static var ERR_load_BIO_strings = neko.Lib.load("openssl","_ERR_load_BIO_strings",0);
	private static var OpenSSL_add_all_algorithms = neko.Lib.load("openssl","_OpenSSL_add_all_algorithms",0);
	private static var SSL_library_init = neko.Lib.load("openssl", "_SSL_library_init", 0); 	
	private static var SSL_CTX_new = neko.Lib.load("openssl", "_SSL_CTX_new", 1);
	private static var SSL_CTX_load_verify_locations = neko.Lib.load("openssl", "_SSL_CTX_load_verify_locations", 2);
	private static var SSLv23_client_method = neko.Lib.load("openssl", "_SSLv23_client_method",0);
	private static var SSL_new = neko.Lib.load("openssl", "_SSL_new", 1);
	private static var BIO_new_socket = neko.Lib.load("openssl", "_BIO_new_socket", 2);
	private static var SSL_set_bio = neko.Lib.load("openssl", "_SSL_set_bio", 3);
	private static var BIO_NOCLOSE = neko.Lib.load("openssl", "_BIO_NOCLOSE", 0);
	private static var SSL_connect = neko.Lib.load("openssl", "_SSL_connect", 1);
	private static var SSL_set_fd = neko.Lib.load ("openssl", "_SSL_set_fd", 2);
	private static var SSL_CTX_set_verify_depth = neko.Lib.load("openssl", 
													"_SSL_CTX_set_verify_depth", 2);
	private static var BIO_new = neko.Lib.load("openssl", "_BIO_new", 1);
	private static var BIO_set_fd = neko.Lib.load("openssl", "_BIO_set_fd", 3);
	private static var BIO_s_socket = neko.Lib.load("openssl", "_BIO_s_socket", 0);
}
