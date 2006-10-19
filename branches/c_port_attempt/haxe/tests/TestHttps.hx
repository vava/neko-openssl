package tests;

class TestHttps {
	static function main() {
		var https: haxe.Http = new haxe.Http("www.megafonnw.ru:443/ifon/userdata/personal");
		//var https: haxe.Http = new haxe.Http("activate.microsoft.com:443");
		var output  = new neko.io.StringOutput();
		output.close = function() {
			https.onData(output.toString());
		};
		https.onData=function(data : String) {
			trace ("https.Data:\n"+data+"\n");			
		}
		https.onError=function(msg : String) {
			trace ("https.Error:"+msg+"\n");
		}
		https.onStatus=function(status : Int){
			trace ("https.Status:"+status+"\n");
		}
		trace("Before async request");
		https.asyncRequest(false, output, new openssl.SSLSocket());
		trace("After async request");		
	}
}