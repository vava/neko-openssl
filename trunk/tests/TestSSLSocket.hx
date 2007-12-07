package tests;

class TestSSLSocket{
	static function main(){
		var tsslsocket : openssl.SSLSocket = new openssl.SSLSocket();
		tsslsocket.connect(openssl.SSLSocket.resolve("activate.microsoft.com"),443);
		tsslsocket.write("get / \n");
		var resp: String = tsslsocket.read();
		trace(resp);
	}
}