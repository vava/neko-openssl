package security;
class TestSecureSocket {
	static function main(){
		var s: SecureSocket = new SecureSocket();
		var host: String = "activate.microsoft.com";
		var port: Int = 443;
		s.connect(neko.io.Socket.resolve(host), port);
		s.write("get \n");
		var res: String;
		res = s.read(254);
		trace(res);
	}
}