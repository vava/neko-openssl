package security;
class SecureSocketOutput extends neko.io.SocketOutput {
	var bio : Dynamic;
	var delegate: SecureOutput;
    
	public override function writeChar( c : Int ) {
		delegate.writeChar(c);
	}
	
	public override function write(str : String){
		delegate.writeString(str);
	}

	public function new(bio){
		super(__s);
		this.bio = bio;
		delegate = new SecureOutput(bio);
	}
	
	public override function close() {
		delegate.close;
	}
}