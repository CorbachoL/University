/*!	
	\file    grafo.hpp
	\brief   Declaración del TAD Grafo, el cual es una estructura compuesta por vertices y lados que los unen
	\author  Javier Corbacho
	\date    17/05/17
	\version 1.0
*/


#ifndef _GRAFO_HPP_
#define _GRAFO_HPP_

#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include <limits>

#include "vertice.hpp"
#include "lado.hpp"


/*!	
	\namespace ed
	\brief Espacio de nombres para la asignatura Estructuras de Datos
*/
namespace ed{

/*!	
  \class Grafo
  \brief Declaración de los atributos y métodos de la clase Grafo
*/
class Grafo
{

	/*!		
		\name Atributos o métodos privados de la clase Grafo
	*/
	private:
		std::vector <ed::Vertice> _vectorVertex;    						//!< \brief Vector de vertices del grafo
		std::vector <ed::Lado> _vectorEdge; 								//!< \brief Vector de lados del grafo
		std::vector < std::vector <int> > _matriz;		  					//!< \brief Matriz de adyacencia del grafo
		bool _esDirigido;													//!< \brief Variable que indica que tipo es el grafo
	


	/*!		
		\name \name Métodos públicos de la clase Grafo
	*/
	public:


		/*!	
			\name Constructores
		*/

		/*!		
			\brief 		Constructor de la clase Grafo
			\attention 	Función sobrecargada 
			\note  		Función inline
			\pre   		Ninguna
			\post  		Crea un nuevo objeto de la clase Grafo
			\sa    		
		*/
			inline Grafo() 
			{
				//_vectorVertex.resize(0);			
			}


		/*!		
			\brief Constructor de copia  
			\note  Función inline
			\param e: objeto de tipo Grafo  
			\pre   Ninguna
			\post  Crea un nuevo objeto de la clase Grafo con los valores de un grafo existente
			\sa    
		*/
			Grafo(const Grafo & e)
			{
				_vectorVertex = e._vectorVertex;
				_vectorEdge = e._vectorEdge;
				_esDirigido = e._esDirigido; 
			}


		/*!		
			\brief 	Constructor para la creación de un grafo no dirigido
			\note  	Función inline
			\pre   	Ninguna
			\sa    	
		*/
			void creaNoDirigido()
			{
				_esDirigido = false;
			}	


		/*!		
			\brief 	Constructor para la creación de un grafo dirigido
			\note  	Función inline
			\pre   	Ninguna
			\sa    	
		*/
			void creaDirigido()
			{
				_esDirigido = true;
			}	



		/*!		
			\brief Destructor  
			\note  Función inline
		*/
			~Grafo()
			{
				_vectorVertex.clear();
				_vectorEdge.clear();
				_matriz.clear();
			}



		/*!	
			\name Observadores
		*/		

		/*!	
			\fn      inline bool isEmpty() const
			\brief   Método público que permite conocer si el grafo está vacio
			\note    Función inline
			\post    Ninguna
			\return  True si los vectores de vertices y de lados del grafo están vacios
			\sa      Funcion empty() de la biblioteca vector
		*/
			inline bool isEmpty() const
			{
				if( _vectorVertex.empty() and _vectorEdge.empty() )
				{
					return true;
				}
				else
				{
					return false;
				}
			}

	
		/*!	
			\fn      inline bool esDirigido() const
			\brief   Método público que permite conocer si el grafo es dirigido
			\note    Función inline
			\post    Ninguna
			\return  _esDirigido
		*/
			inline bool esDirigido() const
			{
				return _esDirigido;
			}


		/*!	
			\fn      inline bool existeCiudad(std::string u) const
			\brief   Método público que permite conocer si una ciudad existe en el grafo
			\param   u: ciudad la cual se comprueba
			\note    Función inline
			\post    Ninguna
			\return  True si la ciudad u está en el vector
			\sa      getNumeroVertices(), getVertice(),  ==
		*/
			inline bool existeCiudad(std::string u) const
			{

				for(int i = 0; i < getNumeroVertices(); i++)
				{
					if( getVertice(i).getCiudad() == u )
					{
						return true;
					}
				}

				return false;
			}

		
		/*!	
			\fn      inline bool existeVertice(ed::Vertice u) const
			\brief   Método público que permite conocer si un vertice existe en el grafo
			\param   u: vertice el cual se comprueba
			\note    Función inline
			\post    Ninguna
			\return  True si el vertice u está en el vector
			\sa      getNumeroVertices(), getVertice(),  ==
		*/
			inline bool existeVertice(ed::Vertice u) const
			{

				for(int i = 0; i < getNumeroVertices(); i++)
				{
					if( getVertice(i).getCiudad() == u.getCiudad() )
					{
						return true;
					}
				}

				return false;
			}


		/*!	
			\fn      inline bool existeLado(ed::Lado u) const
			\brief   Método público que permite conocer si un lado existe en el grafo
			\param   u: lado el cual se comprueba
			\note    Función inline
			\pre     El grafo no está vacio
			\return  True si el lado u está en el vector
			\sa      getNumeroLados(), getLado(), ==
		*/
			inline bool existeLado(ed::Lado u) const
			{
				#ifndef NDEBUG
					//Se comprueba la precondicion
					assert( not isEmpty() );
				#endif 

				for(int i = 0; i < getNumeroLados(); i++)
				{
					if( getLado(i) == u )
					{
						return true;
					}
				}

				return false;
			}

		
		/*!	
			\fn      inline ed::Vertice const & getVertice(int indice) const
			\brief   Método público que devuelve un vertice indicando su indice
			\param   indice: posición que ocupa el vértice devuelto en el vector
			\note    Función inline
			\post    Ninguna
			\return  Vertice que se encuentra en el vector con el indice indicado
			\sa      getNumeroVertices()
		*/
			inline ed::Vertice const & getVertice(int indice) const
			{
				#ifndef NDEBUG
					//Se comprueba la precondicion
					//Se comprueba si el indice esta dentro de los limites del vector de vertices
					assert( (indice>=0) and (indice < this->getNumeroVertices()) );
				#endif  

				return _vectorVertex[indice];
			}


		/*!	
			\fn      inline ed::Vertice getVertice(std::string ciudad) const
			\brief   Método público que devuelve un vertice indicando un string
			\param   ciudad: string que almacena el vertice
			\note    Función inline
			\post    Ninguna
			\return  Vertice que se encuentra en el vector con el string indicado
			\sa      getNumeroVertices(), existeVertice(), getVertice()
		*/
			inline ed::Vertice getVertice(std::string ciudad) const
			{
				ed::Vertice u(ciudad, 0);
				int pos;

				#ifndef NDEBUG
					//Se comprueba la precondicion
					//Se comprueba si el indice esta dentro de los limites del vector de vertices
					assert( existeCiudad(ciudad) );
				#endif 

				for(int i = 0; i < getNumeroVertices(); i++)
				{
					if( getVertice(i).getCiudad() == ciudad)
					{
						pos = i;
						break;
					}
				}
				
				return getVertice(pos);
			}


		/*!	
			\fn      inline ed::Vertice const & getLado(int indice) const
			\brief   Método público que devuelve un lado indicando su indice
			\param   indice: posición que ocupa el lado devuelto en el vector
			\note    Función inline
			\post    Ninguna
			\return  lado que se encuentra en el vector con el indice indicado
			\sa      getNumeroLados()
		*/
			inline ed::Lado const & getLado(int indice) const
			{
				#ifndef NDEBUG
					//Se comprueba la precondicion
					//Se comprueba si el indice esta dentro de los limites del vector de vertices
					assert( (indice>=0) and (indice < this->getNumeroLados()) );
				#endif  

				return _vectorEdge[indice];
			}


		/*!	
			\fn     std::vector < std::vector <int> > getMatrizAdyacencia()
			\brief  Método público que devuelve la matriz de adyacencia
			\note   Función inline
			\pre    Ninguna
			\post   Ninguna
		  	\return Devuelve la matriz de adyacencia
		*/
			std::vector < std::vector <int> > getMatrizAdyacencia()
			{
				hacerMatrizAdyacencia();

				return _matriz;
			}


		/*!	
			\fn     inline int getNumeroVertices() const
			\brief  Método público que devuelve el número de vertices del grafo
			\note   Función inline
			\pre    Ninguna
			\post   Ninguna
		  	\return Devuelve el número de vertices
			\sa		Funcion size() de la biblioteca vector
		*/
			inline int getNumeroVertices() const
			{
				return (int)_vectorVertex.size();
			}


		/*!	
			\fn     inline int getNumeroLados() const
			\brief  Método público que devuelve el número de lados del grafo
			\note   Función inline
			\pre    Ninguna
			\post   Ninguna
		  	\return Devuelve el número de lados
			\sa		Funcion size() de la biblioteca vector
		*/
			inline int getNumeroLados() const
			{
				return (int)_vectorEdge.size();
			}



		/*!	
			\name Modificadores
		*/

		/*!	
			\fn     void hacerMatrizAdyacencia();
			\brief  Método público que actualiza la matriz de adyacencia
			\pre    El grafo no está vacio
			\post   Ninguna
		  	\return Nada
			\sa		Funcion size() y resize() de la biblioteca vector, getLado()
		*/
			void hacerMatrizAdyacencia();


		/*!	
			\fn     inline void addVertex(std::string ciudad, int etiqueta)
			\brief  Método público que añade un vértice al vector del grafo
			\param  etiqueta: identificador del vértice
			\param	ciudad: valor que almacena el vértice
			\pre    El vértice no existe en el vector
			\post   El vértice existe en el vector
		  	\return Nada
			\sa		Funcion push_back() de la biblioteca vector, existeVertice()
		*/
			inline void addVertex(std::string ciudad, int etiqueta)
			{
				ed::Vertice nuevo(ciudad, etiqueta);

				#ifndef NDEBUG
					//Se comprueba la precondicion
					assert( not existeVertice(nuevo) );
				#endif

				_vectorVertex.push_back(nuevo);

				#ifndef NDEBUG
					//Se comprueba la postcondicion
					assert( existeVertice(nuevo) );
				#endif
			}


		/*!	
			\fn     inline void addEdge(int u, int v, int distancia)
			\brief  Método público que añade un lado al vector del grafo
			\param  u: identificador del primer vértice del lado
			\param  v: identificador del segundo vértice del lado
			\param	distancia: valor que almacena el lado
			\pre    El lado no existe en el vector
			\post   El lado existe en el vector
		  	\return Nada
			\sa		Funcion push_back() de la biblioteca vector, existeLado()
		*/
			inline void addEdge(int u, int v, int distancia)
			{
				ed::Lado nuevo(u, v, distancia);

				#ifndef NDEBUG
					//Se comprueba la precondicion
					assert( not existeLado(nuevo) );
				#endif

				_vectorEdge.push_back(nuevo);

				#ifndef NDEBUG
					//Se comprueba la precondicion
					assert( existeLado(nuevo) );
				#endif
			}

			
		/*!	
			\fn     bool cargarFichero(std::string const &nombreFichero);
			\brief  Método público que carga un grafo desde un fichero
			\param  nombreFichero: nombre del fichero
			\post   El grafo no está vacio
		  	\return True si se ha cargado correctamente
		*/
			bool cargarFichero(std::string const &nombreFichero);


		/*!	
			\fn     void guardarFichero(std::string const &nombreFichero)
			\brief  Método público que guardar un grafo a un fichero
			\param  nombreFichero: nombre del fichero
			\pre    El grafo no está vacio
		  	\return Nada
		*/
			void guardarFichero(std::string const &nombreFichero);

// Fin de la clase Grafo
};

// Fin del espacio de nombres ed
}


// Fin de _GRAFO_HPP_
#endif

