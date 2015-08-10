ifneq (DEBUG, "-g")
	DEBUG += -O2
else
	DEBUG += -Wa,-adhln
endif
CC=gcc
CXX=g++
FLAGS= -lpthread -lrt -Wall
CFLAGS = -std=gnu11 $(FLAGS) $(DEBUG)
LDFLAGS = $(DEBUG)
CXXFLAGS = -std=c++11 $(FLAGS)

EXEC = peterson peterson_c11 sc multithread

all: $(EXEC)

.PHONY: all


$(EXEC): % : %.o qsim_magic.h
	$(CC) $< -o $@ $(CXXFLAGS) 

$(OBJ): %.o : %.c 
	$(CC) -o $@ -c $< $(CXXFLAGS)

.PHONY: debug

debug: clean
	$(MAKE) $(MAKEFILE) all DEBUG="-g"

.PHONY: lst

lst: clean
	$(MAKE) $(MAKEFILE) all DEBUG="-Wa,-adhln -g" > file.lst

.PHONY: clean

clean:
	rm -f *.o *~ relaxed peterson peterson_c11 *.lst
