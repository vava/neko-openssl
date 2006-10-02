package security;
class SecureSocketInput extends neko.io.SocketInput {
	var bio : Dynamic;
	var delegate: SecureInput;
    
	public override function readChar() : Int {
		return delegate.readChar();
	}	
	
	public override function read(nbytes : Int) : String{
		return delegate.read(nbytes);
	}
	
	public function new(bio){
	    super(__s);
		this.bio = bio;
		delegate = new SecureInput(bio);
	}
}
