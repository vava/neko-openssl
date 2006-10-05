package security;
class SecureSocketInput {//extends neko.io.SocketInput {
	var bio : Dynamic;
	var delegate: SecureInput;
    
	public override function readChar() : Int {
		return delegate.readChar();
		//return delegate.read(1);
	}	
	
	public override function read(nbytes : Int) : String{
		return delegate.read(nbytes);
	}
	
	public function readBytes( s : String, p : Int, len : Int ) : Int {
		var k = len;
		while( k > 0 ) {
			var c = readChar();
			untyped __dollar__sset(s.__s,p,c);
			p += 1;
			k -= 1;
		}
		return len;
	}

	public function new(bio){
	    //super(__s);
		this.bio = bio;
		delegate = new SecureInput(bio);
	}
}
