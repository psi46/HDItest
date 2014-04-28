#
# Makefile for libljacklm
#
#

UNAME = $(shell uname -s)

VERSION = 1.20.2
DESTINATION = /usr/local/lib
HEADER = ljacklm.h
HEADER_DESTINATION = /usr/local/include
LIBFLAGS = -llabjackusb -lm -lc

ifeq ($(UNAME),Darwin)
	#Mac OS X operating system macros
	TARGET = libljacklm.dylib
	# Build for multiple architectures
	#ARCHFLAGS = -arch i386 -arch x86_64 -arch ppc
	# Build for 32- and 64-bit Intel architectures
	#ARCHFLAGS = -arch i386 -arch x86_64
	# Build for only the host architecture
	ARCHFLAGS =
	COMPILE = libtool -dynamic -o $(TARGET) -install_name $(TARGET) -current_version $(VERSION) -compatibility_version $(VERSION) ljacklm.o $(LIBFLAGS)
else
	#Linux operating system macros
	TARGET = libljacklm.so.$(VERSION)
	# Build for only the host architecture
	ARCHFLAGS =
	COMPILE = $(CC) -shared -Wl,-soname,libljacklm.so -o $(TARGET) ljacklm.o $(LIBFLAGS)
endif

CFLAGS += -fPIC -g -Wall $(ARCHFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

all: $(TARGET)

$(TARGET): ljacklm.o $(HEADER)
	$(COMPILE)

install: $(TARGET)
	test -z $(DESTINATION) || mkdir -p $(DESTINATION)
	install $(TARGET) $(DESTINATION)
	test -z $(HEADER_DESTINATION) || mkdir -p $(HEADER_DESTINATION)
	install $(HEADER) $(HEADER_DESTINATION)
ifeq ($(UNAME),Linux)
	/sbin/ldconfig $(DESTINATION)
endif

clean:
	rm -f $(TARGET) *.o *~ libljacklm.*
