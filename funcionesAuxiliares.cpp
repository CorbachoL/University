/*!
  	\file   funcionesAuxiliares.cpp
  	\brief  Código de las funciones auxiliares del programa principal de la asignatura
  	\author Javier Corbacho
	\date    17/05/17
	\version 1.0
*/


#include <iostream>
#include <vector>
#include <string>

#include "funcionesAuxiliares.hpp"
#include "macros.hpp"

#include "grafo.hpp"
#include "vertice.hpp"

int ed::menu()
{
 	int opcion, posicion;

	// Se muestran las opciones del menú
	posicion=8;

	// Se borra la pantalla
	std::cout << CLEAR_SCREEN;

	LUGAR(5,10);
   	std::cout << BBLUE;
	std::cout << "Programa principal | Opciones del menú   ";
	std::cout << RESET;

	std::cout << BWHITE;

	LUGAR(posicion++,10);
	std::cout << "[1] Comprobar si el grafo está vacío";

	LUGAR(posicion++,10);
	std::cout << "[2] Cargar grafo desde fichero";

	LUGAR(posicion++,10);
	std::cout << "[3] Grabar grafo en un fichero";

	LUGAR(posicion++,10);
	std::cout << "[4] Mostrar grafo por pantalla";

	LUGAR(posicion++,10);
	std::cout << "[5] Aplicar algoritmo de Floyd";

	LUGAR(posicion++,10);
	std::cout << "[6] Camino minimo entre dos ciudades";

	LUGAR(posicion++,10);
	std::cout << "[7] Camino minimo entre las dos ciudades mas lejanas";

	LUGAR(posicion++,10);
	std::cout << "[8] Insertar un nuevo vértice";

	LUGAR(posicion++,10);
	std::cout << "[9] Insertar un nuevo lado";

	std::cout << RESET;

	LUGAR(posicion++,10);
	std::cout << GREEN << "[0] Salir";

	LUGAR(posicion++,20);
	std::cout << IYELLOW;
	std::cout << "Opción: ";
	std::cout << RESET;
	std::cin >> opcion;
    // Se elimina el salto de línea del flujo de entrada
    std::cin.ignore();

	return opcion;
}


void ed::comprobarGrafoVacio(ed::Grafo const &grafo)
{
	LUGAR(8,10);

	if (grafo.isEmpty() == true)
		std::cout << IRED << "El grafo está vacío" << RESET;
	else
		std::cout << BBLUE << "El grafo no está vacío" << RESET;

	return;
}


void ed::cargarGrafo(ed::Grafo & grafo)
{
  	std::string nombreFichero;

	LUGAR(8,10);
	std::cout << BIYELLOW << "Introduce el nombre del archivo: " << RESET;	
	std::cin >> nombreFichero;

	//Se carga el fichero y se comprueba que se abrió correctamente
	if( !grafo.cargarFichero(nombreFichero) )
	{	
		LUGAR(15,10);
		std::cout << IRED << "No se pudo abrir el archivo." << RESET;
		std::cin.ignore();
	}
	else
	{
		LUGAR(15,10);
		std::cout << BIBLUE << "El archivo cargó correctamente." << RESET;	
		std::cin.ignore();
	}
}


void ed::guardarGrafo(ed::Grafo & grafo)
{
  	std::string nombreFichero;

	LUGAR(8,10);
	std::cout << BIYELLOW << "Introduce el nombre del archivo: " << RESET;	
	std::cin >> nombreFichero;

	if( grafo.isEmpty() )
	{	
		LUGAR(15,10);
		std::cout << IRED << "no hay un grafo cargado." << RESET;
		std::cin.ignore();
	}
	else
	{
		grafo.guardarFichero(nombreFichero);		

		LUGAR(15,10);
		std::cout << BIBLUE << "El archivo cargó correctamente." << RESET;	
		std::cin.ignore();
	}
}


void ed::mostrarGrafo(ed::Grafo & grafo)
{
	std::vector < std::vector <int> > adyacencia;

	if( grafo.isEmpty() )
	{
		LUGAR(15,10);
		std::cout << IRED << "No hay ningún fichero cargado" << RESET;
		std::cin.ignore();
	}

	adyacencia = grafo.getMatrizAdyacencia();
	std::cout << std::endl;

	for(int i=0; i < grafo.getNumeroVertices(); i++)
	{
		std::cout << "\t";

		for(int j=0; j < grafo.getNumeroVertices(); j++)
		{
			if(adyacencia[i][j] == 10000)
			{
				std::cout << "∞";
			}
			else
			{
				std::cout << adyacencia[i][j];
			}
			std::cout << "\t";
		}
		std::cout << "\n";
	}

	std::cout << std::endl;

	for(int i=0; i < grafo.getNumeroVertices(); i++)
	{
		std::cout << IYELLOW << "\t[" << grafo.getVertice(i).getEtiqueta() << "] " << RESET; 
		std::cout << IPURPLE << grafo.getVertice(i) << RESET << std::endl;
	}
}


bool ed::algoritmoFloyd(ed::Grafo & grafo, std::vector < std::vector <int> > & matrizPesos, std::vector < std::vector <int> > & matrizIntermedios)
{
	std::vector < std::vector <int> > adyacencia;

	if( grafo.isEmpty() || grafo.getNumeroLados() ==0 )
	{
		LUGAR(15,10);
		std::cout << IRED << "No hay ningún fichero cargado o no hay suficientes vertices" << RESET;
		std::cin.ignore();
		return false;
	}

	//Inicializar matrizPesos
	matrizPesos.resize( grafo.getNumeroVertices() );
	matrizIntermedios.resize( grafo.getNumeroVertices() );

	for(int i=0; i<grafo.getNumeroVertices(); i++)
	{
		matrizPesos[i].resize( grafo.getNumeroVertices() );
	}

	for(int i=0; i<grafo.getNumeroVertices(); i++)
	{
		matrizIntermedios[i].resize(grafo.getNumeroVertices(),-1);
	}

	//Algoritmo de Floyd
	matrizPesos = grafo.getMatrizAdyacencia();

	for(int k = 0; k < grafo.getNumeroVertices(); k++)
	{
		for(int j = 0; j < grafo.getNumeroVertices(); j++)
		{
			for(int i = 0; i < grafo.getNumeroVertices(); i++)
			{					
				if(matrizPesos[i][j] > matrizPesos[i][k] + matrizPesos[k][j])
				{
					matrizPesos[i][j] = matrizPesos[i][k] + matrizPesos[k][j];
					matrizIntermedios[i][j] = k;
				}
			}
		}
	}

	std::cout << IYELLOW << "\nMATRIZ PESOS\n" << RESET;
	for(int i=0; i < grafo.getNumeroVertices(); i++)
	{
		std::cout << "\t";

		for(int j=0; j < grafo.getNumeroVertices(); j++)
		{
			std::cout << matrizPesos[i][j];
			std::cout << "\t";
		}
		std::cout << "\n";
	}

	std::cout << IYELLOW << "\nMATRIZ INTERMEDIOS\n" << RESET;
	for(int i=0; i < grafo.getNumeroVertices(); i++)
	{
		std::cout << "\t";

		for(int j=0; j < grafo.getNumeroVertices(); j++)
		{
			if(matrizIntermedios[i][j] != -1)
			{
				std::cout << matrizIntermedios[i][j];
			}
			else
			{
				std::cout << "ø";
			}
			std::cout << "\t";
		}
		std::cout << "\n";
	}

	LUGAR(35,10);
	std::cout << BBLUE << "Algoritmo realizado correctamente" << RESET;
	std::cin.ignore();

	return true;
}


bool ed::mostrarCaminoMinimo(int &aux, ed::Grafo const &grafo, std::vector < std::vector <int> > matrizPesos, std::vector < std::vector <int> > matrizIntermedios, ed::Vertice origen, ed::Vertice destino)
{
	int k, peso;
	ed::Vertice aux1(" ",1), aux2(" ",1);

	if( grafo.existeCiudad( origen.getCiudad() ) and grafo.existeCiudad( destino.getCiudad() ) )
	{

		aux1 = grafo.getVertice( origen.getCiudad() );
		aux2 = grafo.getVertice( destino.getCiudad() );

		k = matrizIntermedios[ aux1.getEtiqueta() ][ aux2.getEtiqueta() ];
		peso =  matrizPesos[ aux1.getEtiqueta() ][ aux2.getEtiqueta() ];
	
		if(k != -1)
		{
			mostrarCaminoMinimo(aux, grafo, matrizPesos, matrizIntermedios, aux1, grafo.getVertice(k));

			mostrarCaminoMinimo(aux, grafo, matrizPesos, matrizIntermedios, grafo.getVertice(k), aux2);
		}
		else
		{
			std::cout << BBLUE << "\n\t" << aux1.getCiudad() << "(" << aux1.getEtiqueta() << ") -> " << peso << " -> " << aux2.getCiudad() << "(" << aux2.getEtiqueta() << ")" << std::endl << RESET;
	
			aux += peso;
		}

		return true;
	}
	else
	{
		return false;
	}
}


void ed::caminoMinimoCiudadesDistantes(ed::Grafo const &grafo, std::vector < std::vector <int> > matrizPesos, std::vector < std::vector <int> > matrizIntermedios)
{
	int distancia=0;
	int etiqueta1=0, etiqueta2=0, aux=0;

	for(int i = 0; i < grafo.getNumeroVertices(); i++)
	{
		for(int j = 0; j < grafo.getNumeroVertices(); j++)
		{					
			if(matrizPesos[i][j] > distancia)
			{
				etiqueta1 = i;
				etiqueta2 = j;
				distancia = matrizPesos[i][j];
			}
		}
	}

	mostrarCaminoMinimo(aux, grafo, matrizPesos, matrizIntermedios, grafo.getVertice(etiqueta1), grafo.getVertice(etiqueta2));

	std::cout << std::endl << std::endl;
	std::cout << BBLUE << "\tLa distancia total es: " << aux << RESET;
}

void ed::insertarVertice(ed::Grafo & grafo)
{
	std::string ciudad;

	LUGAR(8,10);
	std::cout << BIYELLOW << "Introduce el nombre de la ciudad: " << RESET;	
	getline(std::cin, ciudad);

	if(grafo.existeCiudad(ciudad))
	{
		LUGAR(20,10);
		std::cout << IRED << "La ciudad YA existe" << RESET;

		return;
	}
	else
	{
		grafo.addVertex( ciudad, grafo.getNumeroVertices() );

		LUGAR(20,10);
		std::cout << BBLUE << "El vertice ha sido insertado correctamente" << RESET;
		
		return;
	}

}

void ed::insertarLado(ed::Grafo & grafo)
{
	std::string ciudad1, ciudad2;
	int distancia;

	LUGAR(8,10);
	std::cout << BIYELLOW << "Introduce el nombre de la primera ciudad: " << RESET;	
	getline(std::cin, ciudad1);

	LUGAR(10,10);
	std::cout << BIYELLOW << "Introduce el nombre de la segunda ciudad: " << RESET;	
	getline(std::cin, ciudad2);

	LUGAR(12,10);
	std::cout << BIYELLOW << "Introduce la distancia entre ciudades: " << RESET;	
	std::cin >> distancia;

	if (grafo.existeCiudad(ciudad1) and grafo.existeCiudad(ciudad2) )
	{
		grafo.addEdge(grafo.getVertice(ciudad1).getEtiqueta(), grafo.getVertice(ciudad2).getEtiqueta(), distancia);
		
		LUGAR(20,10);
		std::cout << BBLUE << "El lado ha sido insertado correctamente" << RESET;
		std::cin.ignore();
	}
	else
	{
		LUGAR(20,10);
		std::cout << IRED << "No existen las ciudades" << RESET;
		std::cin.ignore();

	}
}












