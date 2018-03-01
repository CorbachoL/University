/*!	
	\file     vertice.cpp
	\brief    Código auxiliar de las funciones de la clase Vertice
	\author   Javier Corbacho
	\date     17/05/17
	\version  1.0
*/


#include <iostream>
#include "vertice.hpp"


// Se incluyen los operadores sobrecargados dentro del espacio de nombres de ed

namespace ed{

//! \name Funciones amigas para poder acceder a la parte privada de Vertice2D.

// Sobrecarga del operador de salida
ostream &operator<<(ostream &stream, ed::Vertice const &v)
{
  	stream << v._ciudad;

  	return stream;
}

// Sobrecarga del operador de entrada
istream &operator>>(istream &stream, ed::Vertice &v)
{
	stream >> v._ciudad;

  	return stream;
} 

} // Fin del espacio de nombres ed

