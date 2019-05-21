
NAUTY_VERSION=nauty26r11

all: nauty_wrapper.so test

nauty26r11.tar.gz :
		wget http://pallini.di.uniroma1.it/${NAUTY_VERSION}.tar.gz
        
nauty/nauty.a : ${NAUTY_VERSION}.tar.gz
		rm -rf nauty && \
		tar xzf ${NAUTY_VERSION}.tar.gz && \
		mv nauty26r11 nauty && \
		cd nauty && \
		CFLAGS="-O3 -fPIC" ./configure && \
		make

test : nauty_wrapper.o
		gcc -Inauty -o test test.c nauty_wrapper.o -Lnauty -l:nauty.a

nauty_wrapper.o : nauty_wrapper.c nauty/nauty.a
		gcc -c -fPIC -Inauty nauty_wrapper.c

nauty_wrapper.so : nauty_wrapper.o
		gcc -shared -o nauty_wrapper.so nauty_wrapper.o  -Lnauty -l:nauty.a

.PHONY: clean

clean:
		rm -r nauty_wrapper.o nauty_wrapper.so nauty nauty26r11.tar.gz

