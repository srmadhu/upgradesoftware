CC=g++
CPPFLAGS= -I../../common/inc -I../inc/ -L../../common/lib -fPIC -g -O0 
LDFLAGS = -lcommon -ldl -lpthread
BINDIR = ../bin/

BINSOURCES = UpdateServer.cpp UdpServer.cpp
TARGET = UpdateServer 


build: $(TARGET)

$(TARGET) : $(BINSOURCES)
	$(CC) $(CPPFLAGS) $(BINSOURCES)  $(LDFLAGS) -o $(BINDIR)/$@ 


.PHONY: clean

clean: 
	rm -f $(BINDIR)/$(TARGET)
