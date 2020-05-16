SHELL:=/bin/bash

all: 
	${MAKE} ${objects}

%.${obj_ending}: %.cpp
	${CC} ${INCLUDE} ${CFLAGS} ${DEBUG} $< -o $*.${obj_ending}

clean:
	rm -f *.o
	rm -f *.obj

ol:
	@for file in `ls *.cpp` ; do echo $${file/cpp/$$\{obj_ending}} \\ ; done

tol:
	@for file in `find .|grep \.cpp` ; do echo $${file/cpp/$$\{obj_ending}} \\ ; done

aol:
	@for file in `ls *.cpp` ; do echo $${file/cpp/$$\{obj_ending}} \\ ; done

missing_objects:
	make 2>&1 | egrep -o "\w+\:\:" | sort -u | sed 's/\:\://'

object_list:
	@echo ${objects}

