/*!	
	\file    lado.hpp
	\brief   Declaración del TAD Lado
	\author  Javier Corbacho
	\date    17/05/17
	\version 1.0
*/


#ifndef _LADO_HPP_
#define _LADO_HPP_

#include <iostream>
#include "ladoInterfaz.hpp"
#include "vertice.hpp"
#include <cassert>


/*!	
	\namespace ed
	\brief Espacio de nombres para la asignatura Estructuras de Datos
*/
namespace ed{

/*!	
  \class Lado
  \brief Declaración de los atributos y métodos de la clase Lado
*/
class Lado:public LadoInterfaz
{

	/*!		
		\name Atributos o métodos privados de la clase Lado
	*/
	private:
		int _first;    		//!< \brief Etiqueta del primer vertice del lado
		int _second; 		//!< \brief Etiqueta del segundo vertice del lado
		int _distancia;     //!< \brief Distancia entre ciudades
	


	/*!		
		\name Métodos públicos de la clase Lado
	*/
	public:


		/*!	
			\name Constructores
		*/

		/*!		
			\brief Constructor parametrizado con todos los argumentos sin valores por defecto
			\note  Función inline
			\param first: etiqueta del primer vértice
			\param second: etiqueta del segundo vértice
			\param distancia: distancia entre ambas ciudades
			\pre   Ninguna
			\post  Crea un nuevo objeto de la clase Estudiante con los valores de los argumentos
			\sa    setDistancia()
		*/
			Lado(int first, int second, int distancia)
			{
				this->setDistancia(distancia);
				this->_first = first;
				this->_second = second;
			}	

		
		/*!		
			\brief Constructor de copia  
			\note  Función inline
			\param e: objeto de tipo lado  
			\pre   Ninguna
			\post  Crea un nuevo objeto de la clase Lado con los valores de un lado existente
			\sa    setDistancia()
		*/
			Lado(const Lado & e)
			{
				this->setDistancia( e.getDistancia() );
				this->_first = e._first;
				this->_second = e._second;
			}

		/*!		
			\brief Destructor  
			\note  Función inline
			\sa    setDistancia()
		*/
			~Lado()
			{
				this->setDistancia(0);
				this->_first = 0;
				this->_second = 0;
			}



		/*!	
			\name Observadores
		*/		

		/*!	
			\fn     inline int getDistancia() const
			\brief  Método público que permite conocer la distancia
			\note   Función inline
			\pre    Ninguna
			\post   Ninguna
		  	\return Devuelve la distancia entre las dos ciudades
		*/
			inline int getDistancia() const
			{
				return this->_distancia;
			}

		/*!	
			\fn		inline int getFirst() const
			\brief  Método público que permite conocer la etiqueta de la primera ciudad
			\note   Función inline
			\pre    Ninguna
			\post   other( _first ) == _second
		  	\return Devuelve la etiqueta de la primera ciudad
		*/
			inline int getFirst() const
			{
				return this->_first;

				#ifndef NDEBUG
					// Se comprueba la postcondicion
					assert( this->other( _first ) == _second );	
				#endif //NDEBUG
			}


		/*!	
			\fn     inline int getSecond() const
			\brief  Método público que permite conocer la etiqueta de la segunda ciudad
			\note   Función inline
			\pre    Ninguna
			\post   other( _second ) == _first
		  	\return Devuelve la etiqueta de la segunda ciudad
		*/
			inline int getSecond() const
			{
				return this->_second;

				#ifndef NDEBUG
					// Se comprueba la postcondicion
					assert( other( _second ) == _first );	
				#endif //NDEBUG
			}


		/*!	
			\fn     bool has(int etiqueta) const
			\brief  Método público que permite conocer si una etiqueta existe en el lado
			\note   Función inline
			\pre    Ninguna
			\post   Ninguna
		  	\return Devuelve true si existe
		*/
			bool has(int etiqueta) const
			{
				if( (etiqueta == getFirst()) || (etiqueta == getSecond()) )
				{
					return true;
				}
				else
				{
					return false;
				}
			}


		/*!	
			\fn		int other(int etiqueta) const
			\brief  Método público que permite conocer el otro extremo del lado
			\note   Función inline
			\param	etiqueta: identificador de la ciudad de la que se queire conocer el extremo del lado
			\pre    Ninguna
			\post   Ninguna
		  	\return Devuelve la etiqueta de la ciudad a la que está unida
		*/
			int other(int etiqueta) const
			{
				#ifndef NDEBUG
					// Se comprueba la precondicion
					assert( has(etiqueta) );	
				#endif //NDEBUG

				if( etiqueta == getFirst() )
				{
					return getSecond();
				}
				else
				{
					return getFirst();
				}
			}



		/*!	
			\name Modificadores
		*/
		
		/*!	
			\fn     inline void setDistancia(int distancia)
			\brief  Método público que modifica la distancia del lado
			\param  distancia: valor que se va a introducir en _distancia
			\post   La distancia actual debe de ser el parámetro introducido
		  	\return Nada
			\sa		getDistancia()
		*/
			inline void setDistancia(int distancia)
			{
				this->_distancia = distancia;

				#ifndef NDEBUG
					// Se comprueba la postcondicion
					assert(this->getDistancia() == distancia);	
				#endif //NDEBUG
			}



	  	/*! 
			\name Operadores
		*/
	   
		/*! 
			\fn		   inline Lado & operator=(Lado const &v)
			\brief     Operador de asignación: operador que "copia" un Lado en otro Lado
			\attention Se sobrecarga el operador de asignación "="
			\note      Función inline
			\param     v lado pasado como referencia constante
			\pre       El lado v debe ser diferente del lado actual
			\post      Ninguna
			\sa        setDistancia()
		*/
			inline Lado & operator=(Lado const &v)
			{
				// Se comprueba que no sean el mismo objeto
				if (this != &v) 
				{
					this->setDistancia( v.getDistancia() );
					_first = v._first;
					_second = v._second;
				}

				return *this;
			}


		/*! 
			\fn		   inline bool operator == (Lado const &v) const
			\brief     Operador de igualdad: compara si un lado es igual a otro lado
			\attention Se sobrecarga el operador de asignación "=="
			\note      Función inline
			\param     v lado pasado como referencia constante
			\post      Ninguna
			\return	   True si los dos lados son iguales
		*/
			inline bool operator == (Lado const &v) const
		  	{
				if( (_first == v._first) and (_second == v._second) and (_distancia == v._distancia) )
				{
					return true;
				}
				else
				{
					return false;
				}
			}

// Fin de la clase Lado
};

// Fin del espacio de nombres ed
}

// Fin de _LADO_HPP_
#endif

