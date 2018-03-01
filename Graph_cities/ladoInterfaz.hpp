/*! 
   \file ladoInterfaz.hpp
   \brief Fichero de la clase ladoInterfaz: clase de interfaz del lado de un grafo 
*/


#ifndef _LADOINTERFAZ_HPP_
#define _LADOINTERFAZ_HPP_


/*!	
	\namespace ed
	\brief Espacio de nombres para la asignatura Estructuras de Datos
*/
namespace ed {

/*!
	Definición de la clase lado
*/
class LadoInterfaz 
{

 	/*!
		\name Atributos públicos de la clase LadoInterfaz
	*/
   	public:

		/*!
			\name Observadores
		*/

		/*! 
			\fn      virtual int getDistancia()const = 0;
			\brief   Función que devuelve el elemento distancia de un LadoInterfaz
			\warning Se utiliza el modificador const en la definición de la función para poder definir el constructor de copia y el operador de asignacion "="
			\note    Función virtual pura que deberá ser redefinida por la clase heredera
			\return  Componente "distancia" del LadoInterfaz
			\pre     El LadoInterfaz debe existir
			\post    Ninguna
			\sa      setDistancia()
		*/
			virtual int getDistancia()const = 0;



		/*! 
			\name Funciones de modificación de verticeInterfaz
		*/

		/*! 
			\fn    virtual void setDistancia(int v) = 0;
			\brief Función que asigna un valor "v" a la coordenada "distancia" de un LadoInterfaz
			\note  Función virtual pura que deberá ser redefinida por la clase heredera
			\param v Nuevo valor de la ciudad del LadoInterfaz
			\pre   El LadoInterfaz debe existir
			\post  El atributo _distancia de LadoInterfaz debe tener el valor "v"
			\sa    getDistancia()
		*/
			virtual void setDistancia(int v) = 0;


}; // Fin de la definición de la clase ladoInterfaz


}//  _LADOINTERFAZ_HPP_
#endif 

