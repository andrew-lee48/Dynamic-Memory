COMPILER = gcc
CCFLAGS  = -Wall -g
all: test1 test2 test3 test4

test1: testmain1.c libsl.a
	$(COMPILER) $(CCFLAGS) -o test1 testmain1.c
test2: testmain2.c libsl.a
	$(COMPILER) $(CCFLAGS) -o test2 testmain2.c
test3: testmain3.c libsl.a
	$(COMPILER) $(CCFLAGS) -o test3 testmain3.c
test4: testmain4.c libsl.a
	$(COMPILER) $(CCFLAGS) -o test4 testmain4.c
libsl.a: DynMem.o
	ar rv libsl.a DynMem.o

DynMem.o: DynMem.c DynMem.h
	$(COMPILER) $(CCFLAGS) -c DynMem.c

clean:
	rm -f DynMem.o
