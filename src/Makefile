G++ = g++
STD = c++11

DEBUG = -g -pg -O0
PERF = -O3

#Choix de l'option finale 
OPT = ${PERF}

exec : main.o
	${G++} ${OPT} -std=${STD} -o $@ $^

%.o : %.cpp
	${G++} ${OPT} -std=${STD} -c $^

clean : 
	rm *.o

cleanall :
	rm -r sortie.mesh sortie.sol html *.o 