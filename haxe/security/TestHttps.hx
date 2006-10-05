
package security;

class TestHttps {
	static function main() {
		var https: Https = new Https("activate.microsoft.com:443");
		https.onData = function(data: String){
			trace("Data :" + data);
		}
		https.onError=function(msg : String) {
			trace ("\n http.Error:"+msg+"\n");
		}
		https.onStatus=function(status : Int){
			trace ("http.Status:"+status);
		}
		trace ("Before http request");			
		https.request(false);
		trace ("After http request");
	}
}