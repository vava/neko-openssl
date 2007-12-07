package openssl;

import neko.net.Socket;
import openssl.SSLSocket.SSL;
import neko.io.Error;
import neko.io.Eof;

class SSLSocketInput extends neko.io.Input {
	var __s : SocketHandle;
	public var ssl: SSL;
	
	public function new(s) {
		__s = s;
	}
	
	public override function readChar() : Int {
		try {
			return socket_recv_char(ssl);
		} catch( e : Dynamic ) {
			if( e == "Blocking" )
				throw Error.Blocked;
			else if( __s == null )
				throw Error.Custom(e);
			else
				throw new Eof();
				return -1;
		}
	}
		
	public override function close() {
		super.close();
		if( __s != null ) socket_close(__s);
	}

	private static var socket_recv = neko.Lib.load("openssl","SSL_recv",4);
	private static var socket_recv_char = neko.Lib.load("openssl", "SSL_recv_char",1);
	private static var socket_close = neko.Lib.load("std","socket_close",1);
	private static var SSL_read = neko.Lib.load("openssl", "_SSL_read", 3);
}
