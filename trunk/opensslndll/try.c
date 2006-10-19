#include "test.h"
#include "neko.h"
#include "stdio.h"
#include "_hmac.h"

int main() {
	n_hello();
	int x = mcon();
	printf ("mcon response = [%d]", x);
		
	return 0;
}
