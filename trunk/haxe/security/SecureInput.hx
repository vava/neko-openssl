package security;

class SecureInput extends neko.io.Input {
	var bio : Dynamic;
	static var BIO_read = neko.Lib.load("opensslndll", "_BIO_read",2);

	public override function readChar() : Int {
		return  Std.parseInt((BIO_read(bio,1)));
	}
	
	public override function read(nbytes: Int) : String {
		trace(bio);
		var rbuf: String = BIO_read(bio, nbytes);
		return rbuf;
	}
	
	public function new(bio){
		this.bio = bio;
	}

}