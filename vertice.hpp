/*!	
	\file    vertice.hpp
	\brief   Declaración del TAD Lado
	\author  Javier Corbacho
	\date    17/05/17
	\version 1.0
*/


#ifndef _VERTICE_HPP_
#define _VERTICE_HPP_
 
#include <iostream>
#include <cassert>
#include "verticeInterfaz.hpp"


// Para la sobrecarga de los operadores de flujo: << y >>
using std::istream;
using std::ostream;

/*!	
	\namespace ed
	\brief Espacio de nombres para la asignatura Estructuras de Datos
*/
namespace ed {

/*!	
  \class Vertice
  \brief Declaración de los atributos y métodos de la clase Vertice
*/
class Vertice:public ed::VerticeInterfaz
{

 	/*!
		\name Atributos privados de la clase Vertice
	*/
   	private: 
		std::string _ciudad;			//!< \brief Nombre de la ciudad que representa el vértice
		int _etiqueta;					//!< \brief Identificador del vértice



	/*! 
		\name Funciones o métodos públicos de la clase Vertice
	*/
	public:


		/*!	
			\name Constructores
		*/

		/*! 
			\brief     Constructor que crea un Vertice a partir de sus coordenadas x e y
			\attention Función sobrecargada        
			\note      Función inline
		 	\warning   Los parámetros tienen valores por defecto
			\param     ciudad: valor que tomará _ciudad
			\param     etiqueta: valor que tomará _etiqueta
			\pre       Ninguna
			\post      Ninguna
			\sa        setCiudad(), setEtiqueta()
		*/
			inline Vertice(std::string ciudad, int etiqueta)
			{
				this->setCiudad(ciudad);
				this->setEtiqueta(etiqueta);
			}


		/*! 
			\brief     Constructor de "copia" que crea un Vertice a partir de otro Vertice
			\attention Función sobrecargada        
			\note      Función inline
			\warning   Se requiere que la funcion de acceso getCiudad y getEtiqueta tenga el modificador const
			\param     q Vertice utilizado para proporcionar los valores iniciales del nuevo Vertice
			\pre       El Vertice q debe existir
			\post      El atributo ciudad debe tener el valor del atributo del Vertice q
			\sa        getCiudad(), setCiudad(), getEtiqueta(), setEtiqueta()
		*/
			inline Vertice(Vertice const &q)
			{
				this->setCiudad( q.getCiudad() );
				this->setEtiqueta( q.getEtiqueta() );
			}



		/*!	
			\name Observadores
		*/

		/*! 
			\brief   Función que devuelve el elemento "_ciudad" de Vertice
			\warning Se utiliza el modificador const en la definición de la función para poder definir el constructor de copia y el operador de asignacion "="
			\note    Función inline
			\return  Componente "_ciudad" del Vertice
			\pre     
			\post    Ninguna
			\sa      getEtiqueta()
		*/
			inline std::string getCiudad() const
			{
				return this->_ciudad;
			}


		/*! 
			\brief   Función que devuelve el elemento "_etiqueta" de Vertice
			\warning Se utiliza el modificador const en la definición de la función para poder definir el constructor de copia y el operador de asignacion "="
			\note    Función inline
			\return  Componente "_etiqueta" del Vertice
			\pre     
			\post    Ninguna
			\sa      getCiudad()
		*/
			inline int getEtiqueta() const
			{
				return this->_etiqueta;
			}



		/*!	
			\name Modificadores
		*/

		/*!	
			\fn     inline void setCiudad(std::string ciudad)
			\brief  Método público que modifica la ciudad de un vertice
			\param  ciudad: valor que se va a introducir en _ciudad
			\post   La ciudad actual debe de ser el parámetro introducido
		  	\return Nada
			\sa		getCiudad()
		*/
			inline void setCiudad(std::string ciudad)
			{
				this->_ciudad = ciudad;

				#ifndef NDEBUG
					// Se comprueba la postcondicion
					assert(this->getCiudad() == ciudad);	
				#endif //NDEBUG
			}


		/*!	
			\fn     inline void setEtiqueta(int etiqueta)
			\brief  Método público que modifica la etiqueta de un vertice
			\param  etiqueta: valor que se va a introducir en _etiqueta
			\post   La etiqueta actual debe de ser el parámetro introducido
		  	\return Nada
			\sa		getEtiqueta()
		*/
			inline void setEtiqueta(int etiqueta)
			{
				this->_etiqueta = etiqueta;

				#ifndef NDEBUG
					// Se comprueba la postcondicion
					assert(this->getEtiqueta() == etiqueta);	
				#endif //NDEBUG
			}



	  	/*! 
			\name Operadores
		*/
	   
		/*! 
			\fn		   inline Vertice & operator=(Vertice const &v)
			\brief     Operador de asignación: operador que "copia" un vertice en otro vertice
			\attention Se sobrecarga el operador de asignación "="
			\note      Función inline
			\param     v vertice pasado como referencia constante
			\pre       El vertice v debe ser diferente del vertice actual
			\post      Ninguna
			\sa        setCiudad(), setEtiqueta(), getCiudad(), getEtiqueta()
		*/
			inline Vertice & operator=(Vertice const &v)
			{
				// Se comprueba que no sean el mismo objeto
				if (this != &v) 
				{
					this->setCiudad( v.getCiudad() );
					this->setEtiqueta( v.getEtiqueta() );
				}

				return *this;
			}


		/*! 
			\fn		   inline bool operator == (Vertice const &v) const
			\brief     Operador de igualdad: compara si un vertice es igual a otro vertice
			\attention Se sobrecarga el operador de asignación "=="
			\note      Función inline
			\param     v vertice pasado como referencia constante
			\post      Ninguna
			\return	   True si los dos vertices son iguales
		*/
			inline bool operator == (Vertice const &v) const
		  	{
				if( (this->_ciudad == v._ciudad) and (this->_etiqueta == v._etiqueta) )
				{
					return true;
				}
				else
				{
					return false;
				}
			}



	   	/*! 
			\name Funciones amigas para poder acceder a la parte privada de Vertice2D.
		*/

		/*!
			\fn        friend ostream &operator<<(ostream &stream, Vertice const &v);
	  		\brief     Sobrecarga del operador de salida o escritura "<<"
			\attention Función amiga de la clase Vertice
			\param     stream Flujo de salida
			\param     v Vertice del cual se van a escribir sus coordenadas en un "flujo de salida"
			\pre        
			\post      Se escriben por pantalla las información del vertice 
			\sa        operator>>
		*/
			friend ostream &operator<<(ostream &stream, Vertice const &v);


		/*!
			\fn         friend istream &operator>>(istream &stream, Vertice &v);
	  		\brief      Sobrecarga del operador de entrada o lectura ">>"
			\attention  Función amiga de la clase Vertice
			\param      stream Flujo de entrada
			\param      v Vertice al que se le van a asignar nuevos valores.
			\pre        
			\post       El vertice v tiene asignadas como ciudad la que se ha leido por el stream
			\sa         operator<<
		*/
			friend istream &operator>>(istream &stream, Vertice &v);



}; // Fin de la definición de la clase Vertice


} // \brief Fin de namespace ed.

//  _VERTICE_HPP_
#endif 

