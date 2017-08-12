CC=mpicc
INC_DIR = ./
CFLAGS=-g -Wall -Wstrict-prototypes -c -I$(INC_DIR)
LDFLAGS=-o 

all: serial_sa para_sa dislike_Mat print_mat readobj readop

serial_sa:	serial_sa.o functions.o
	${CC} ${LDFLAGS} serial_sa serial_sa.o functions.o

serial_sa.o:	serial_sa.c header.h
	$(CC) ${CFLAGS} serial_sa.c -I${INC_DIR}

para_sa:	para_sa.o functions.o
	${CC} ${LDFLAGS} para_sa para_sa.o functions.o

para_sa.o:	para_sa.c header.h
	$(CC) ${CFLAGS} para_sa.c -I${INC_DIR}

functions.o:	functions.c header.h
	$(CC) ${CFLAGS} functions.c -I${INC_DIR}

dislike_Mat:	dislike_Mat.o 
	${CC} ${LDFLAGS} dislike_Mat dislike_Mat.o 

dislike_Mat.o:	dislike_Mat.c 
	$(CC) ${CFLAGS} dislike_Mat.c -I${INC_DIR}

print_mat:	print_mat.o 
	${CC} ${LDFLAGS} print_mat print_mat.o 

print_mat.o:	print_mat.c 
	$(CC) ${CFLAGS} print_mat.c -I${INC_DIR}

readobj:	readobj.o 
	${CC} ${LDFLAGS} readobj readobj.o 

readobj.o:	readobj.c 
	$(CC) ${CFLAGS} readobj.c -I${INC_DIR}

readop:	readop.o 
	${CC} ${LDFLAGS} readop readop.o 

readop.o:	readop.c 
	$(CC) ${CFLAGS} readop.c -I${INC_DIR}

clean:
	rm -rf *.o
	rm -rf *~
	rm -rf serial_sa para_sa dislike_Mat print_mat readobj readop
