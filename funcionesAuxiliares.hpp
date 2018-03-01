/*!
  	\file    funcionesAuxiliares.hpp
  	\brief   Prototipos de las funciones auxiliares de principalGrafo.cpp
	\author  Javier Corbacho
	\date    17/05/17
	\version 1.0
*/


#ifndef _FUNCIONESAUXILIARES_HPP_
#define _FUNCIONESAUXILIARES_HPP_

#include <string>

#include "grafo.hpp"

namespace ed
{
	
	/*! 
		\brief   Muestra el menú del programa principal 
		\return  Devuelve el número de opción elegido
	*/
  	int menu();

	/*! 
		\brief   Comrpueba si el grafo está vacio
		\param   grafo con vertices y lados
		\return  void
	*/
	void comprobarGrafoVacio(ed::Grafo const &grafo);

	/*! 
		\brief   Muestra la matriz de adyacencia del grafo
		\param   grafo con vertices y lados
		\return  void
	*/
	void mostrarGrafo(ed::Grafo & grafo);

	/*! 
		\brief   Cargar un grafo de un fichero
		\param   grafo con vertices y lados
		\return  void
	*/
	void cargarGrafo(ed::Grafo & grafo); 

	/*! 
		\brief   Guardar un grafo de un fichero
		\param   grafo con vertices y lados
		\return  void
	*/
	void guardarGrafo(ed::Grafo & grafo);

	/*! 
		\brief   Realiza el algoritmo de Floyd sobre el grafo
		\param   grafo con vertices y lados  
		\param   matrizPesos de la matriz con todas las distancias mínimas entre nodos
		\param   matrizIntermedios con los nodos intermedios entre dos cualesquiera
		\return  True si se ha realizado correctamente
	*/
	bool algoritmoFloyd(ed::Grafo & grafo, std::vector < std::vector <int> > & matrizPesos, std::vector < std::vector <int> > & matrizIntermedios);


	/*! 
		\brief   Muestra por pantalla el camino mínimo entre dos nodos del grafo
		\param	 aux será el peso total del camino
		\param   grafo con vertices y lados  
		\param   matrizPesos de la matriz con todas las distancias mínimas entre nodos
		\param   matrizIntermedios con los nodos intermedios entre dos cualesquiera
		\param   origen con el vertice inicial del camino
		\param	 destino con el vertice final del camino
		\return  void
	*/
	bool mostrarCaminoMinimo(int &aux, ed::Grafo const & grafo, std::vector < std::vector <int> > matrizPesos, std::vector < std::vector <int> > matrizIntermedios, ed::Vertice origen, ed::Vertice destino);


	/*! 
		\brief   Muestra el camino mínimo entre los dos vertices mas lejanos
		\param   grafo con vertices y lados  
		\param   matrizPesos de la matriz con todas las distancias mínimas entre nodos
		\param   matrizIntermedios con los nodos intermedios entre dos cualesquiera
		\return  void
	 	\sa      mostrarCaminoMinimo
	*/
	void caminoMinimoCiudadesDistantes(ed::Grafo const &grafo, std::vector < std::vector <int> > matrizPesos, std::vector < std::vector <int> > matrizIntermedios);


	/*! 
		\brief   Inserta un vertice en el grafo
		\param   grafo con vertices y lados  
		\return  void
	 	\sa      insertarLado
	*/
	void insertarVertice(ed::Grafo & grafo);


	/*! 
		\brief   Inserta un lado en el grafo
		\param   grafo con vertices y lados  
		\return  void
	 	\sa      insertarVertice
	*/
	void insertarLado(ed::Grafo & grafo);

}

// Fin de _FUNCIONESAUXILIARES_HPP_
#endif

