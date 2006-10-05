package security;
class SecureOutput extends neko.io.Output {
	var bio : Dynamic;
	var writeResult: Int;
	static var  BIO_write = neko.Lib.load("opensslndll", "_BIO_write",3);
	static var  BIO_free_all = neko.Lib.load("opensslndll","_BIO_free_all",1);
	
	public override function writeChar(c : Int) : Void{
		var a : String = Std.string(c);
		writeResult = BIO_write(bio, neko.Lib.haxeToNeko(a), 1);
	}
	
	public function writeString(str : String){	
		writeResult = BIO_write(bio, neko.Lib.haxeToNeko(str), str.length);		
	}
	
	public override function close() {
		//super.close();
		BIO_free_all(bio); 
	}	
	
	public function new(bio){
		this.bio = bio;
	}

}