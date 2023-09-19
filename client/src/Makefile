CC=g++
CPPFLAGS= -I../../common/inc -I../inc -L../../common/lib -fPIC -g -O0 
LDFLAGS = -lcommon -ldl -lpthread -lssl -lcrypto

BINSOURCES = UpdateClient.cpp UdpClient.cpp ClientHandler.cpp FunctionalHandler.cpp
BINARY = UpdateClient 
BINPATH = ../bin/


build:  $(BINARY)

$(BINARY) : $(BINSOURCES)
	$(CC) $(CPPFLAGS) $(BINSOURCES)  $(LDFLAGS) -o $(BINPATH)/$@ 


.PHONY: clean

clean: 
	rm -f  $(BINARY)
