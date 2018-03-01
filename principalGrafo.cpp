/*!

	\file 	 principalGrafo.cpp
	\brief   Programa principal de la practica 4 de ED, grafo de vertices
	\author  Javier Corbacho
	\date 	 17/05/17
	\version 1.0
*/

/*!
 \mainpage Implementación de un TAD Grafo utilizando dos TADs Vertice y Lado
 \author   Javier Corbacho
 \date     17/05/17
 \version  1.0
*/

#include <iostream>
#include <vector>
#include <string>

#include "vertice.hpp"
#include "grafo.hpp"
#include "funcionesAuxiliares.hpp"
#include "macros.hpp"

/*!	
  	\brief Programa principal de la práctica 4 de ED
*/
int main()
{
	std::vector < std::vector <int> > matrizPesos;
	std::vector < std::vector <int> > matrizIntermedios;
	ed::Vertice origen("",0), destino("",0);
	std::string ciudadOrigen, ciudadDestino;
	ed::Grafo grafo;
	bool algoritmoHecho=false;
	int opcion, aux=0;

	do{
		// Se elige la opción del menún
		opcion = ed::menu();		

		std::cout << CLEAR_SCREEN;
		LUGAR(5,1);

		// Se ejecuta la opción del menú elegida
		switch(opcion)
		{
			case 0: 
					std::cout << INVERSE;
					std::cout << "Fin del programa" << std::endl;
					std::cout << RESET;
					break;

			case 1: 
				  	std::cout << BIWHITE << "[1] Comprobar si el grafo está vacio" << RESET << std::endl;
					ed::comprobarGrafoVacio(grafo);
					break;

			case 2: 
				  	std::cout << BIWHITE << "[2] Cargar grafo" << RESET << std::endl;
					ed::cargarGrafo(grafo);
					algoritmoHecho = false;
					break;

			case 3: 
				  	std::cout << BIWHITE << "[3] Guardar grafo" << RESET << std::endl;
					ed::guardarGrafo(grafo);
					break;

			case 4: 
				  	std::cout << BIWHITE << "[4] Mostrar grafo por pantalla" << RESET << std::endl;
					ed::mostrarGrafo(grafo);
					break;

			case 5: 
				  	std::cout << BIWHITE << "[5] Aplicar algoritmo de Floyd" << RESET << std::endl;
					algoritmoHecho = ed::algoritmoFloyd(grafo, matrizPesos, matrizIntermedios);
					break;	

			case 6: 
			  		std::cout << BIWHITE << "[6] Camino minimo entre dos ciudades\n" << RESET << std::endl;
	
					if(algoritmoHecho == true)
					{
						std::cout << std::endl << IYELLOW << "Introduce el nombre de la ciudad origen: " << RESET;
						std::cin >> ciudadOrigen;
						std::cout << std::endl << IYELLOW << "Introduce el nombre de la ciudad destino: " << RESET;
						std::cin >> ciudadDestino;

						origen.setCiudad(ciudadOrigen);
						destino.setCiudad(ciudadDestino);

						if( not ed::mostrarCaminoMinimo(aux, grafo, matrizPesos, matrizIntermedios, origen, destino) )
						{
								LUGAR(15,10);
								std::cout << IRED << "No existen las ciudades en el grafo." << RESET;
								std::cin.ignore();
						}
						else
						{
							std::cout << std::endl << std::endl;
							std::cout << BBLUE << "\tLa distancia total es: " << aux << RESET;
							std::cin.ignore();
						}
					}
					else
					{
						LUGAR(15,10);
						std::cout << IRED << "Se necesita realizar el algoritmo primero" << RESET;
						std::cin.ignore();
					}
					break;

			case 7: 
					std::cout << BIWHITE << "[7] Camino minimo entre las dos ciudades mas lejanas\n" << RESET << std::endl;
					if(algoritmoHecho == true)
					{
						ed::caminoMinimoCiudadesDistantes(grafo, matrizPesos, matrizIntermedios);
						std::cin.ignore();
					}
					else
					{
						LUGAR(15,10);
						std::cout << IRED << "Se necesita realizar el algoritmo primero" << RESET;
						std::cin.ignore();
					}
					break;

			case 8: 
					std::cout << BIWHITE << "[8] Insertar un vértice nuevo\n" << RESET << std::endl;

					insertarVertice(grafo);
					algoritmoHecho = false;

					break;

			case 9: 
					std::cout << BIWHITE << "[9] Insertar un lado nuevo\n" << RESET << std::endl;

					insertarLado(grafo);
					algoritmoHecho = false;

					break;

			default:
			    	LUGAR(25,25);
					std::cout << INVERSE;
					std::cout << "Opción incorrecta ";
					std::cout << RESET;
			  		std::cout << RED;
					std::cout << " --> " << opcion << std::endl;
					std::cout << RESET;
     }
  
    if (opcion !=0)
    {
		 LUGAR(30,10);
		 std::cout << "pulse ";
		 std::cout << UNDERLINE;
		 std::cout << IYELLOW;
		 std::cout << "ENTER";
		 std::cout << RESET;
		 std::cout << " para ";
		 std::cout << INVERSE;
		 std::cout << "continuar"; 
		 std::cout << RESET;
		 getchar();
		 std::cout << CLEAR_SCREEN;
    }
	  }while(opcion!=0);

	return 0;
}


