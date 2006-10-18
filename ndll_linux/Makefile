
objects := _bio.o _evp.o _hmac.o opensslndll.o _ssl.o test.o
nekoobjects := $(wildcard /home/berje/buildup/neko-1.4/vm/*.o)

.PHONY: clean all install

CC=gcc
INCLUDE_PATH_OPENSSL=/usr/local/ssl/include

# Change /home/berje/buildup/neko-1.4/vm to your correct path to neko.h
INCLUDE_PATH_NEKO=/home/berje/buildup/neko-1.4/vm
SSL_PATH=/usr/local/ssl/lib/

all: libsossl.ndll test

libsossl.ndll: $(objects)
	$(CC) -I $(INCLUDE_PATH_OPENSSL) -I$(INCLUDE_PATH_NEKO) -L /usr/lib/ -L $(SSL_PATH) -shared -o libsossl.ndll -lstdc++ -ldl -lgc -lssl -lcrypto $(objects) $(nekoobjects) $(SSL_PATH)libcrypto.a $(SSL_PATH)libssl.a

%.o: %.cpp
	$(CC) -I ${INCLUDE_PATH_NEKO} -I ${INCLUDE_PATH_OPENSSL}  -fPIC -fpermissive -c $< -o $@

test: libsossl.ndll openssltest.cpp
	$(CC) -c -I . -I ${INCLUDE_PATH_NEKO} openssltest.cpp -o openssltest.o
	$(CC) -o test -L . openssltest.o libsossl.ndll
	./test

clean:
	rm *.o
	rm *.ndll
	rm test

install: libsossl.ndll
	cp libsossl.ndll /usr/lib/libsossl.ndll

