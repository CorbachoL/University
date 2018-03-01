/*!	
	\file     grafo.cpp
	\brief    Código auxiliar de las funciones de la clase Grafo
	\author   Javier Corbacho
	\date    17/05/17
	\version 1.0
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdio>
#include <limits>

#include "grafo.hpp"
#include "lado.hpp"
#include "vertice.hpp"


void ed::Grafo::hacerMatrizAdyacencia()
{
	int first, second;

	#ifndef NDEBUG
		//Se comprueba la precondicion
		assert( not isEmpty() );
	#endif

	_matriz.resize( _vectorVertex.size() );
	for(int i=0; i<(int)_vectorVertex.size(); i++)
	{
		_matriz[i].resize( _vectorVertex.size() );
	}

	for(int i=0; i < (int)_vectorVertex.size(); i++)
	{
		for(int j=0; j < (int)_vectorVertex.size(); j++)
		{
			if(i == j)
				_matriz[i][j] = 0;
			else
				_matriz[i][j] = 10000;
		}
	}

	for(int i=0; i < (int)_vectorEdge.size(); i++)
	{
		first = getLado(i).getFirst();
		second = getLado(i).getSecond();

		_matriz[ first ][ second ] = getLado(i).getDistancia();
		_matriz[ second ][ first ] = getLado(i).getDistancia();
	}
}


bool ed::Grafo::cargarFichero(std::string const &nombreFichero)
{
	std::ifstream f(nombreFichero.c_str());
	int numVertices, esDirigido, distancia;
	ed::Vertice auxVertice("", 0);
	std::string aux1, aux2;

	_vectorVertex.clear();
	_vectorEdge.clear();
	_matriz.clear();

	if(!f)
	{
		return false;
	}

	f >> numVertices;
	f >> esDirigido;

	if(esDirigido == 0)
	{
		_esDirigido = false;
	}
	else
	{	
		_esDirigido = true;
	}

	for(int i=0; i < numVertices; i++)
	{
		f >> auxVertice;
		addVertex(auxVertice.getCiudad(), i);
	}

	while( f >> aux1 >> aux2 >> distancia )
	{	
		addEdge(getVertice(aux1).getEtiqueta(), getVertice(aux2).getEtiqueta(), distancia);
	}

	f.close();	

	#ifndef NDEBUG
		//Se comprueba la precondicion
		assert( not isEmpty() );
	#endif	

	return true;
}

void ed::Grafo::guardarFichero(std::string const &nombreFichero)
{
	#ifndef NDEBUG
		//Se comprueba la precondicion
		assert( not isEmpty() );
	#endif

	std::ofstream f(nombreFichero.c_str());

	f << getNumeroVertices() << "\n";
	
	if( esDirigido() )
	{
		f << 1 << "\n";
	}
	else
	{
		f << 0 << "\n";
	}

	for(int i = 0; i < getNumeroVertices(); i++)	
	{
		f << getVertice(i) << "\n";
	}
	
	for(int i = 0; i < getNumeroLados(); i++)	
	{	
		f << getVertice(getLado(i).getFirst()) <<  " " << getVertice(getLado(i).getSecond()) << " " << getLado(i).getDistancia() << "\n";
	}

	f.close();

}



