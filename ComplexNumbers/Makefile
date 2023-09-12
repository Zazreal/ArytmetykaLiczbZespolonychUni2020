#
#  To sa opcje dla kompilacji
#
CPPFLAGS= -c -g -Iinc -Wall -pedantic

__start__: system_of_equations
	./system_of_equations

system_of_equations: obj/main.o obj/SystemOfLinearEquations.o obj/Matrix.o obj/Vector.o
	g++ -Wall -pedantic -o system_of_equations obj/main.o obj/Vector.o\
                                   obj/Matrix.o obj/SystemOfLinearEquations.o

obj/main.o: src/main.cpp inc/SystemOfLinearEquations.hh inc/Matrix.hh inc/Vector.hh\
        inc/Size.hh
	g++ ${CPPFLAGS} -o obj/main.o src/main.cpp

obj/SystemOfLinearEquations.o: src/SystemOfLinearEquations.cpp inc/SystemOfLinearEquations.hh
	g++ ${CPPFLAGS} -o obj/SystemOfLinearEquations.o src/SystemOfLinearEquations.cpp

obj/Matrix.o: src/Matrix.cpp inc/Matrix.hh 
	g++ ${CPPFLAGS} -o obj/Matrix.o src/Matrix.cpp

obj/Vector.o: src/Vector.cpp inc/Vector.hh inc/Size.hh
	g++ ${CPPFLAGS} -o obj/Vector.o src/Vector.cpp

clean:
	rm -f obj/*.o system_of_equations