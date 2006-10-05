class TestSSLSocket{
	static function main(){
		var sslsocket : SSLSocket = new SSLSocket();
		sslsocket.connect(SSLSocket.resolve("activate.microsoft.com"),443);
		sslsocket.write("get / \n");
		var resp: String = sslsocket.read();
		trace(resp);
	}
}