CC=gcc
CCFLAGS = -g -std=c99 -Wall -Werror
MAINS = pgmEcho.o pgmComp.o pgma2b.o pgmb2a.o pgmReduce.o pgmTile.o pgmAssemble.o
MODULES = openReadFile.o openWriteFile.o pgma2bFunc.o pgmb2aFunc.o pgmStruct.o
TARGETS = pgmEcho pgmComp pgma2b pgmb2a pgmReduce pgmTile pgmAssemble

all:	${TARGETS}



pgmEcho:	pgmEcho.o ${MODULES}
	${CC} 	${CCFLAGS} -o pgmEcho pgmEcho.o ${MODULES}

pgmComp:	pgmComp.o ${MODULES}
	${CC} ${CCFLAGS} -o pgmComp pgmComp.o ${MODULES}

pgma2b:		pgma2b.o ${MODULES}
	${CC} ${CCFLAGS} -o pgma2b pgma2b.o ${MODULES}

pgmb2a:		pgmb2a.o ${MODULES}
	${CC} ${CCFLAGS} -o pgmb2a pgmb2a.o ${MODULES}

pgmReduce:	pgmReduce.o ${MODULES}
	${CC} ${CCFLAGS} -o pgmReduce pgmReduce.o ${MODULES}

pgmTile:	pgmTile.o ${MODULES}
	${CC} ${CCFLAGS} -o pgmTile pgmTile.o ${MODULES}

pgmAssemble:	pgmAssemble.o ${MODULES}
	${CC} ${CCFLAGS} -o pgmAssemble pgmAssemble.o ${MODULES}



pgmEcho.o:	pgmEcho.c	pgmEcho.h	openReadFile.o	openWriteFile.o
	${CC} -c ${CCFLAGS} -o pgmEcho.o pgmEcho.c

pgmComp.o:	pgmComp.c
	${CC} -c ${CCFLAGS} -o pgmComp.o pgmComp.c

pgma2b.o:	pgma2b.c	pgma2b.h	pgma2bFunc.h
	${CC} -c ${CCFLAGS} -o pgma2b.o	pgma2b.c

pgmb2a.o:	pgmb2a.c	pgmb2a.h	pgmb2aFunc.h
	${CC} -c ${CCFLAGS} -o pgmb2a.o	pgmb2a.c

pgmReduce.o:	pgmReduce.c	pgmStruct.h	openReadFile.h	openWriteFile.h 
	${CC} -c ${CCFLAGS} -o pgmReduce.o	pgmReduce.c

pgmTile.o:	pgmTile.c	pgmStruct.h	openReadFile.h	openWriteFile.h 
	${CC} -c ${CCFLAGS} -o pgmTile.o	pgmTile.c

pgmAssemble.o:	pgmAssemble.c	pgmStruct.h	openReadFile.h	openWriteFile.h 
	${CC} -c ${CCFLAGS} -o pgmAssemble.o	pgmAssemble.c



openReadFile.o:		openReadFile.c		pgmStruct.h	errors.h	openReadFile.h
	${CC} -c ${CCFLAGS} -o openReadFile.o	openReadFile.c

openWriteFile.o:	openWriteFile.c		pgmStruct.h	errors.h	openWriteFile.h
	${CC} -c ${CCFLAGS} -o openWriteFile.o	openWriteFile.c

pgma2bFunc.o:	pgma2bFunc.c	pgmStruct.h	errors.h	openWriteFile.h
	${CC} -c ${CCFLAGS} -o pgma2bFunc.o	pgma2bFunc.c	

pgmb2aFunc.o:	pgmb2aFunc.c	pgmStruct.h	errors.h	openWriteFile.h
	${CC} -c ${CCFLAGS} -o pgmb2aFunc.o	pgmb2aFunc.c

pgmStruct.o:	pgmStruct.c	pgmStruct.h
	${CC} -c ${CCFLAGS} -o pgmStruct.o	pgmStruct.c



clean:
	rm ${TARGETS} ${MAINS} ${MODULES}


