OBJETOS = vertice.o lado.o grafo.o funcionesAuxiliares.o principalGrafo.o

CPPFLAGS = -c -g -Wall -ansi

objetivo: principalGrafo.exe

#Opciones para NO depurar
ndebug: CPPFLAGS += -DNDEBUG 
ndebug: objetivo

#Para general a documentacion
doc: Doxyfile 
	doxygen
	
principalGrafo.exe: $(OBJETOS)
	g++ $(OBJETOS) -o principalGrafo.exe 	 

principalGrafo.o: principalGrafo.cpp funcionesAuxiliares.o grafo.o $(INCLUDES)
	g++ $(CPPFLAGS) principalGrafo.cpp

funcionesAuxiliares.o: funcionesAuxiliares.cpp funcionesAuxiliares.hpp grafo.o $(INCLUDES)
	g++ $(CPPFLAGS) funcionesAuxiliares.cpp

grafo.o: grafo.cpp grafo.hpp vertice.o lado.o $(INCLUDES)
	g++ $(CPPFLAGS) grafo.cpp

lado.o: lado.cpp lado.hpp ladoInterfaz.hpp $(INCLUDES)
	g++ $(CPPFLAGS) lado.cpp

vertice.o: vertice.cpp vertice.hpp verticeInterfaz.hpp $(INCLUDES)
	g++ $(CPPFLAGS) vertice.cpp

clean:
	rm -rf *~ $(OBJETOS)



