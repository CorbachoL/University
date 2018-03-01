/*! 
   \file verticeInterfaz.hpp
   \brief Fichero de la clase verticeInterfaz: clase de interfaz del vértice de un grafo
*/


#ifndef _VERTICEINTERFAZ_HPP_
#define _VERTICEINTERFAZ_HPP_

#include <string>


/*!	
	\namespace ed
	\brief Espacio de nombres para la asignatura Estructuras de Datos
*/
namespace ed {

/*!
	Definición de la clase verticeInterfaz
*/
class VerticeInterfaz 
{

 	/*!
		\name Atributos públicos de la clase VerticeInterfaz
	*/
   	public:

		/*!
			\name Observadores
		*/

		/*! 
			\fn      virtual std::string getCiudad()const = 0;
			\brief   Función que devuelve el elemento ciudad de un VerticeInterfaz
			\warning Se utiliza el modificador const en la definición de la función para poder definir el constructor de copia y el operador de asignacion "="
			\note    Función virtual pura que deberá ser redefinida por la clase heredera
			\return  Componente "ciudad" del verticeInterfaz
			\pre     El verticeInterfaz debe existir
			\post    Ninguna
			\sa      setCiudad()
		*/
			virtual std::string getCiudad() const = 0;



		/*! 
			\name Funciones de modificación de verticeInterfaz
		*/

		/*! 
			\fn    virtual void setCiudad(std::string v) = 0;
			\brief Función que asigna un valor "v" a la coordenada "ciudad" de un verticeInterfaz
			\note  Función virtual pura que deberá ser redefinida por la clase heredera
			\param v Nuevo valor de la ciudad del verticeInterfaz
			\pre   El verticeInterfaz debe existir
			\post  El atributo _ciudad de Vertice debe tener el valor "v"
			\sa    getCiudad()
		*/
			virtual void setCiudad(std::string v) = 0;


}; // Fin de la definición de la clase VerticeInterfaz


}//  _VERTICEINTERFAZ_HPP_
#endif 

