
objects := _bio.o _evp.o _hmac.o opensslndll.o _ssl.o test.o
nekoobjects := $(wildcard /home/berje/buildup/neko-1.4/vm/*.o)

.PHONY: clean all install

CC=gcc
INCLUDE_PATH_OPENSSL=/usr/local/ssl/include

# Change /home/berje/buildup/neko-1.4/vm to your correct path to neko.h
INCLUDE_PATH_NEKO=/home/berje/buildup/neko-1.4/vm
SSL_PATH=/usr/local/ssl/lib/

all: openssl.ndll test

%.o: ../opensslndll/%.c
	$(CC) -I ${INCLUDE_PATH_NEKO} -I ${INCLUDE_PATH_OPENSSL}  -fPIC  -c $< -o $@

openssl.ndll: $(objects)
	$(CC) -I $(INCLUDE_PATH_OPENSSL) -I$(INCLUDE_PATH_NEKO) -L /usr/lib/ -L $(SSL_PATH) -shared -o openssl.ndll -lstdc++ -ldl -lgc -lssl -lcrypto $(objects) $(nekoobjects) $(SSL_PATH)libcrypto.a $(SSL_PATH)libssl.a

test: openssl.ndll ../opensslndll/try.c
	$(CC) -c -I ../opensslndll/.  -I ${INCLUDE_PATH_NEKO} ../opensslndll/try.c -o try.o
	$(CC) -o test -L . try.o openssl.ndll
	./test

clean:
	rm *.o
	rm *.ndll
	rm test

install: openssl.ndll
	cp openssl.ndll /usr/lib/openssl.ndll

