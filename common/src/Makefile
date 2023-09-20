CC=g++
CPPFLAGS= -I../inc -fPIC -g -O0 -DDEBUG
LDFLAGS = -shared -ldl -lpthread
LIBPATH = ../lib/

SOURCES= UdpSocket.cpp FileReader.cpp FileWriter.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = libcommon.so

LIBVER1_SOURCES = ActionHandler56.cpp
LIBVER1 = libversion_1_0.so

LIBVER2_SOURCES = ActionHandler86.cpp
LIBVER2 = libversion_2_0.so

build: $(TARGET) $(LIBVER1) $(LIBVER2)

$(TARGET): $(SOURCES)
	$(CC) $(CPPFLAGS) $(SOURCES) $(LDFLAGS) -o $(LIBPATH)/$@ $(LDFLAGS)

$(LIBVER1): $(LIBVER1_SOURCES)
	$(CC) $(CPPFLAGS) $(LIBVER1_SOURCES) $(LDFLAGS) -o $(LIBPATH)/$@ $(LDFLAGS)
		
$(LIBVER2): $(LIBVER2_SOURCES)
	$(CC) $(CPPFLAGS) $(LIBVER2_SOURCES) $(LDFLAGS) -o $(LIBPATH)/$@ $(LDFLAGS)

.PHONY: clean

clean: 
	rm -f $(LIBPATH)/$(TARGET) $(LIBPATH)/$(LIBVER1) $(LIBPATH)/$(LIBVER2)
