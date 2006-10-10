package sslsocket;
class TestHttps {
	static function main() {
		//var https: Https = new Https("www.megafonnw.ru:443/ifon/userdata/personal");
		//var https: Https = new Https("activate.microsoft.com:443");
		
		var https: Https = new Https("www.google.com:443/accounts/AuthSubTokenInfo");
		https.setHeader("Authorization", " AuthSub token=\"" + "CN-NgcC7BRDMi8Sd-P____8B" + "\"");
		https.onData=function(data : String) {
			trace ("<hr>Data:"+data+"<hr>");			
			//OnResult(data != null);
			trace ("\n   Result    \n");
		}
		https.onError=function(msg : String) {
			trace ("<br> https.Error:"+msg+"<br>");
		}
		https.onStatus=function(status : Int){
			trace ("<br>https.Status:"+status+"<br>");
		}
		trace ("<br> Before https req<hr>");			
		https.request(false);
		trace ("<hr> After https req<br>");

		/*
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
		*/
	}
}