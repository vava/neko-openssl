#objects := $(patsubst %.cpp,%.o,$(wildcard *.cpp))
objects := _bio.o _evp.o _hmac.o opensslndll.o _ssl.o test.o
nekoobjects := $(wildcard /home/berje/buildup/neko-1.4/vm/*.o)
sslobj := #$(wildcard /home/berje/buildup/openssl-0.9.8d/crypto/pem/*.o)
.PHONY: clean mexport

CC=gcc
INCLUDE_PATH_OPENSSL=/home/berje/buildup/openssl-0.9.8d/include
INCLUDE_PATH_NEKO=/home/berje/buildup/neko-1.4/vm
SSL_PATH=/usr/local/ssl/lib/


libsossl.so: $(objects) mexport
	$(CC) -I $(INCLUDE_PATH_OPENSSL) -I$(INCLUDE_PATH_NEKO) -L /usr/lib/ -L $(SSL_PATH) -shared -o libsossl.so -lstdc++ -ldl -lgc -lssl -lcrypto $(objects) $(nekoobjects) $(SSL_PATH)libcrypto.a $(SSL_PATH)libssl.a
%.o: %.cpp
	$(CC) -I ${INCLUDE_PATH_NEKO} -I ${INCLUDE_PATH_OPENSSL}  -fPIC -fpermissive -c $< -o $@
mexport:
#	export CPLUS_INCLUDE_PATH=/home/berje/buildup/openssl-0.9.8d/include:/home/berje/buildup/neko-1.4/vm
#	export LD_LIBRARY_PATH=/usr/local/ssl/lib:${LD_LIBRARY_PATH}
#	echo "LD:"${LD_LIBRARY_PATH}
#	echo "CPLUS:"${CPLUS_INCLUDE_PATH}
try: libsossl.so try.cpp
	$(CC) -c -I . -I ${INCLUDE_PATH_NEKO} try.cpp -o try.o
	$(CC) -o try -L . -lsossl try.o
clean:
	rm *.o
	rm *.so

