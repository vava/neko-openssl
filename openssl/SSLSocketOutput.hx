package openssl;

import neko.net.Socket;
import openssl.SSLSocket.SSL;
import neko.io.Error;
import neko.io.Eof;

class SSLSocketOutput extends neko.io.Output {

	var __s : SocketHandle;
	public var ssl : SSL;
	public function new(s) {
		__s = s;
	}

	public override function writeChar( c : Int ) {
		try {
			socket_send_char(ssl, c);
		} catch( e : Dynamic ) {
			if( e == "Blocking" )
				throw Error.Blocked;
			else
				throw Error.Custom(e);
		}
	}

	public override function close() {
		super.close();
		if( __s != null ) socket_close(__s);
	}

	private static var socket_close = neko.Lib.load("std","socket_close",1);
	private static var socket_send_char = neko.Lib.load("openssl","SSL_send_char",2);
	private static var socket_send = neko.Lib.load("openssl", "SSL_send", 4);
}
