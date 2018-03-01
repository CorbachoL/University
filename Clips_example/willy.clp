

;====================================MAIN=======================================

	(defrule MAIN::passToMyMain
	=>
		(focus myMAIN)
	)


;===================================myMAIN======================================

;	Módulo que inicia el ciclo de módulos.

(defmodule myMAIN (import MAIN deftemplate ?ALL) (import InternalFunctions deffunction ?ALL) (export deftemplate ?ALL))

	(deffacts inicial
		(direccion)						;Guarda la dirección a la que s emueve willy en ese ciclo
		(posActual 0 0)					;Almacena las coordenadas de la posición actual				
		(visitado 0 0)					;Cada hecho tipo "visitado" representa una casilla recorrida
		(numMovimientos 0)				;Almacena el número de movimientos que ha realizado willy
	)

	(defrule passToProgram
	=>
		(focus Fin_Ciclo)				;Línea 887
		(focus Calculos)				;Línea 826
		(focus IniciarBusqueda)			;Línea 582
		(focus MoverANoVisitada)		;Línea 503
		(focus AfirmarPeligro)			;Línea 402  
		(focus Inconsistencias)			;Línea 254
		(focus Reconocimiento)			;Línea 36
	)


;=============================Reconocimiento====================================

;	Este modulo comprende tanto las reglas para que Willy dispare a la serpiente 
;	(cuando la posición de la serpiente sea segura, como las reglas para insertar 
;	las posiciones seguras pero no visitadas (hechos (no-visitado &?)), como para 
;	insertar hechos de posible-serpiente y posible-temblor

(defmodule Reconocimiento (import MAIN deftemplate ?ALL) (import myMAIN ?ALL) (import InternalFunctions deffunction ?ALL) (export ?ALL))

	(defrule DispararNorte						;	Dispara al norte la flecha si:
		?h<-(seguro-serpiente ?x ?y)			;	-La posición de la serpiente esta asegurada.
		(hasArrow)								;	-Hay fecha.
		(posActual ?x ?z&:(< ?z ?y))			;	-Estamos en la misma columna.

	=>
		(fireArrow north)						;	Se dispara la flecha, eliminamos el hecho
		(retract ?h)							;	"seguro-serpiente", y asertamos un no-visitado.
		(assert (no-visitado ?x ?y))			
	)											;	Se repite este proceso para las otras 3 direcciones.

	(defrule DispararSur
		?h<-(seguro-serpiente ?x ?y)
		(hasArrow)
		(posActual ?x ?z&:(> ?z ?y))

	=>
		(fireArrow south)
		(retract ?h)
		(assert (no-visitado ?x ?y))
	)

	(defrule DispararEste
		?h<-(seguro-serpiente ?x ?y)
		(hasArrow)
		(posActual ?z&:(< ?z ?x) ?y)

	=>
		(fireArrow east)
		(retract ?h)
		(assert (no-visitado ?x ?y))
	)

	(defrule DispararOeste
		?h<-(seguro-serpiente ?x ?y)
		(hasArrow)
		(posActual ?z&:(> ?z ?x) ?y)

	=>
		(fireArrow west)
		(retract ?h)
		(assert (no-visitado ?x ?y))
	)

;-------------------------------------------------------------------------------

	(defrule NoVisitadoNorte					;	Insertar un hecho no-visitado en el norte:
		(posActual ?x ?y)						
												;	Obtenemos la posición actual.
		(not (visitado ?x =(+ ?y 1)))			;	Si no tenemos un hecho "visitado" ni un 
		(not (no-visitado ?x =(+ ?y 1)))		;	"no-visitado", y no percibimos ni un temblor
		(not (percepts $? Tremor $?))			;	ni un sonido, y la dirección norte está
		(not (percepts $? Sound $?))			;	disponible, entonces asertamos el hecho.

		(directions $? north $?)				;	Repetir este proceso para las otras 3 direcciones.
	=>
		(assert (no-visitado ?x =(+ ?y 1)))
	)

	(defrule NoVisitadoSur
		(posActual ?x ?y)

		(not (visitado ?x =(+ ?y -1)))
		(not (no-visitado ?x =(+ ?y -1)))
		(not (percepts $? Tremor $?))
		(not (percepts $? Sound $?))

		(directions $? south $?)
	=>
		(assert (no-visitado ?x =(+ ?y -1)))
	)

	(defrule NoVisitadoEste
		(posActual ?x ?y)

		(not (visitado =(+ ?x 1) ?y))
		(not (no-visitado =(+ ?x 1) ?y))
		(not (percepts $? Tremor $?))
		(not (percepts $? Sound $?))

		(directions $? east $?)
	=>
		(assert (no-visitado =(+ ?x 1) ?y))
	)

	(defrule NoVisitadoOeste
		(posActual ?x ?y)

		(not (visitado =(+ ?x -1) ?y))
		(not (no-visitado =(+ ?x -1) ?y))
		(not (percepts $? Tremor $?))
		(not (percepts $? Sound $?))

		(directions $? west $?)
	=>
		(assert (no-visitado =(+ ?x -1) ?y))
	)

;-------------------------------------------------------------------------------

	(defrule PosiblePeligroNorteSound						;	Insertar un hecho "posible-serpiente" en el norte:
		(posActual ?x ?y)									
															;	Obtenemos la posición actual. Si el hecho 
		(not (seguro-serpiente $?))							;	"seguro-serpiente" no existe, ni un hecho "visitado"
		(not (visitado ?x =(+ ?y 1)))						;	ni un "no-visitado" ni un "posible-serpiente", y
		(not (no-visitado ?x =(+ ?y 1)))					;	percibimos un sonido además de que la posición norte
		(not (posible-serpiente ?x =(+ ?y 1) ?x ?y))		;	esté disponible, entonces podemos asertar.

		(percepts $? Sound $?)								;	Repetir este proceso para las otras 3 direcciones.
		(directions $? north $?)
	=>
		(assert (posible-serpiente ?x =(+ ?y 1) ?x ?y))
	)

	(defrule PosiblePeligroSurSound
		(posActual ?x ?y)

		(not (seguro-serpiente $?))
		(not (visitado ?x =(+ ?y -1)))
		(not (no-visitado ?x =(+ ?y -1)))
		(not (posible-serpiente ?x =(+ ?y -1) ?x ?y))

		(percepts $? Sound $?)
		(directions $? south $?)
	=>
		(assert (posible-serpiente ?x =(+ ?y -1) ?x ?y))
	)

	(defrule PosiblePeligroEsteSound
		(posActual ?x ?y)

		(not (seguro-serpiente $?))
		(not (visitado =(+ ?x 1) ?y))
		(not (no-visitado =(+ ?x 1) ?y))
		(not (posible-serpiente =(+ ?x 1) ?y ?x ?y))

		(percepts $? Sound $?)
		(directions $? east $?)
	=>
		(assert (posible-serpiente =(+ ?x 1) ?y ?x ?y))
	)

	(defrule PosiblePeligroOesteSound
		(posActual ?x ?y)

		(not (seguro-serpiente $?))
		(not (visitado =(+ ?x -1) ?y))
		(not (no-visitado =(+ ?x -1) ?y))
		(not (posible-serpiente =(+ ?x -1) ?y ?x ?y))

		(percepts $? Sound $?)
		(directions $? west $?)
	=>
		(assert (posible-serpiente =(+ ?x -1) ?y ?x ?y))
	)

;-------------------------------------------------------------------------------																		
		
	(defrule PosiblePeligroNorteTremor						;	Insertar un posible temblor se realizaría de la
		(posActual ?x ?y)									;	misma forma que una posible serpiente, pero
															;	adaptándolo.
		(not (visitado ?x =(+ ?y 1)))
		(not (no-visitado ?x =(+ ?y 1)))
		(not (posible-temblor ?x =(+ ?y 1) ?x ?y))

		(percepts $? Tremor $?)
		(directions $? north $?)
	=>
		(assert (posible-temblor ?x =(+ ?y 1) ?x ?y))
	)

	(defrule PosiblePeligroSurTremor
		(posActual ?x ?y)

		(not (visitado ?x =(+ ?y -1)))
		(not (no-visitado ?x =(+ ?y -1)))
		(not (posible-temblor ?x =(+ ?y -1) ?x ?y))

		(percepts $? Tremor $?)
		(directions $? south $?)
	=>
		(assert (posible-temblor ?x =(+ ?y -1) ?x ?y))
	)

	(defrule PosiblePeligroEsteTremor
		(posActual ?x ?y)

		(not (visitado =(+ ?x 1) ?y))
		(not (no-visitado =(+ ?x 1) ?y))
		(not (posible-temblor =(+ ?x 1) ?y ?x ?y))

		(percepts $? Tremor $?)
		(directions $? east $?)
	=>
		(assert (posible-temblor =(+ ?x 1) ?y ?x ?y))
	)

	(defrule PosiblePeligroOesteTremor
		(posActual ?x ?y)

		(not (visitado =(+ ?x -1) ?y))
		(not (no-visitado =(+ ?x -1) ?y))
		(not (posible-temblor =(+ ?x -1) ?y ?x ?y))

		(percepts $? Tremor $?)
		(directions $? west $?)
	=>
		(assert (posible-temblor =(+ ?x -1) ?y ?x ?y))
	)


;==============================Inconsistencias==================================

;	Incluye reglas para resolver cierto tipo de inconsistencias en la base de 
;	hechos (ej: visitado y posible-serpiente en la misma posicion), además de 
;	añadir una regla para parar a Willy si no se ha encontrado a la serpiente y
;	no existe ningun otra casilla segura/no-visitada.
;
;	La explicación sobre cada inconsistencia en general se realiza en el 
;	documento PDF que acompaña este programa.

(defmodule Inconsistencias (import MAIN deftemplate ?ALL) (import myMAIN ?ALL) (import Reconocimiento ?ALL) (import InternalFunctions deffunction ?ALL) (export ?ALL))

	(defrule stop								;	Regla stop, para detener a willy si no
		(not (no-visitado $?))					;	hay ningun hecho "no-visitado", o no
		(not (seguro-serpiente $?))				;	hay indicios de una serpiente.
		(not (posible-serpiente $?))
	=>
		(pop-focus)								;	La función pop-focus saca a los módulos
		(pop-focus)								;	de la pila de módulos, por lo que el 
		(pop-focus)								;	programa para.
		(pop-focus)
		(pop-focus)
		(pop-focus)
	)	

	(defrule inconsistenciaVisitado							;	Si hay un hecho "visitado" y "no-visitado"
		(visitado ?x ?y)									;	haciendo referencia a una misma casilla,
		?v <- (no-visitado ?x ?y)							;	se elimina el "no-visitado".
	=>
		(retract ?v)
	)

	(defrule inconsistenciaVisitadoSound					
		(or (visitado ?x ?y)
			(no-visitado ?x ?y))
		?v <- (posible-serpiente ?x ?y $?)
	=>
		(retract ?v)
	)

	(defrule inconsistenciaVisitadoTemblor
		(or (visitado ?x ?y)
			(no-visitado ?x ?y))
		?v <- (posible-temblor ?x ?y $?)
	=>
		(retract ?v)
	)

	(defrule inconsistenciaPeligros2
		(posActual ?x ?y)
		(percepts Sound)
		?h <- (posible-temblor =(+ ?x 1) ?y ?x2 ?y2)
		(not (posible-serpiente =(+ ?x 1) ?y ?x2 ?y2))
		(not (seguro-serpiente  =(+ ?x 1) ?y))
	=>
		(retract ?h)
		(assert (no-visitado  =(+ ?x 1) ?y))
	)

	(defrule inconsistenciaPeligros3
		(posActual ?x ?y)
		(percepts Tremor)
		?h <- (posible-serpiente =(+ ?x 1) ?y ?x2 ?y2)
		(not (posible-temblor =(+ ?x 1) ?y ?x2 ?y2))
		(not (seguro-temblor =(+ ?x 1) ?y ))
	=>
		(retract ?h)
		(assert (no-visitado  =(+ ?x 1) ?y))
	)

	(defrule inconsistenciaPeligros4
		(posActual ?x ?y)
		(percepts Sound)
		?h <- (posible-temblor =(+ ?x -1) ?y ?x2 ?y2)
		(not (posible-serpiente =(+ ?x -1) ?y ?x2 ?y2))
		(not (seguro-serpiente  =(+ ?x -1) ?y))
	=>
		(retract ?h)
		(assert (no-visitado  =(+ ?x -1) ?y))
	)

	(defrule inconsistenciaPeligros5
		(posActual ?x ?y)
		(percepts Tremor)
		?h <- (posible-serpiente =(+ ?x -1) ?y ?x2 ?y2)
		(not (posible-temblor =(+ ?x -1) ?y ?x2 ?y2))
		(not (seguro-temblor  =(+ ?x -1) ?y))
	=>
		(retract ?h)
		(assert (no-visitado  =(+ ?x -1) ?y))
	)

	(defrule inconsistenciaPeligros6
		(posActual ?x ?y)
		(percepts Sound)
		?h <- (posible-temblor ?x =(+ ?y 1) ?x2 ?y2)
		(not (posible-serpiente ?x =(+ ?y +1) ?x2 ?y2))
		(not (seguro-serpiente ?x =(+ ?y +1)))
	=>
		(retract ?h)
		(assert (no-visitado ?x =(+ ?y 1)))
	)

	(defrule inconsistenciaPeligros7
		(posActual ?x ?y)
		(percepts Tremor)
		?h <- (posible-serpiente ?x =(+ ?y 1) ?x2 ?y2)
		(not (posible-temblor ?x =(+ ?y +1) ?x2 ?y2))
		(not (seguro-temblor ?x =(+ ?y +1)))
	=>
		(retract ?h)
		(assert (no-visitado ?x =(+ ?y 1)))
	)

	(defrule inconsistenciaPeligros8
		(posActual ?x ?y)
		(percepts Sound)
		?h <- (posible-temblor ?x =(+ ?y -1) ?x2 ?y2)
		(not (posible-serpiente ?x =(+ ?y -1) ?x2 ?y2))
		(not (seguro-serpiente ?x =(+ ?y -1)))
	=>
		(retract ?h)
		(assert (no-visitado ?x =(+ ?y -1)))
	)

	(defrule inconsistenciaPeligros9
		(posActual ?x ?y)
		(percepts Tremor)
		?h <- (posible-serpiente ?x =(+ ?y -1) ?x2 ?y2)
		(not (posible-temblor ?x =(+ ?y -1) ?x2 ?y2))
		(not (seguro-temblor ?x =(+ ?y -1)))
	=>
		(retract ?h)
		(assert (no-visitado ?x =(+ ?y -1)))
	)
	
	(defrule inconsistenciaPeligro10
		(seguro-serpiente ?x ?y)
		?v <- (posible-serpiente $?)
	=>
		(retract ?v)	
	)

	(defrule inconsistenciaPeligro11
		(seguro-temblor ?x ?y)
		?v <- (posible-serpiente ?x ?y $?)
	=>
		(retract ?v)	
	)


;===============================AfirmarPeligro==================================

;	Aglutina las funciones para asegurar la posición de una serpiente o de una
; 	arena movediza.
;
;	La explicación sobre cada regla en general se realiza en el documento
;	PDF que acompaña este programa.

(defmodule AfirmarPeligro (import MAIN deftemplate ?ALL) (import myMAIN ?ALL) (import Inconsistencias ?ALL) (import InternalFunctions deffunction ?ALL) (export ?ALL))

	(defrule AsegurarTemblor
		?h <- (posible-temblor ?x ?y ?x2 ?y2)

		(not (posible-temblor  ?a&: (<> ?x ?a) ?y ?x2 ?y2))
		(not (posible-temblor  ?x ?b&: (<> ?y ?b) ?x2 ?y2))
		(not (posible-temblor  ?c&: (<> ?x ?c) ?d&: (<> ?y ?d) ?x2 ?y2))
	=>
		(retract ?h)
		(assert (seguro-temblor ?x ?y))
		(focus Inconsistencias)
	)

	(defrule AsegurarSerpiente1

		?h <- (posible-serpiente ?x ?y ?x2 ?y2)
		?j <- (posible-serpiente ?x ?y =(+ ?x2 2) ?y2 )
	=>
		(assert(seguro-serpiente ?x ?y))
		(retract ?h ?j)
		(focus Inconsistencias)
	)

	(defrule AsegurarSerpiente2

		?h <- (posible-serpiente ?x ?y ?x2 ?y2)
		?j <- (posible-serpiente ?x ?y ?x2 =(+ ?y2 2))
	=>
		(assert(seguro-serpiente ?x ?y))
		(retract ?h ?j)
		(focus Inconsistencias)
	)

	(defrule AsegurarSerpiente3

		?h <- (posible-serpiente ?x ?y ?x2 ?y2)
		?j <- (posible-serpiente ?x ?y =(+ ?x2 1) =(+ ?y2 1))

		(or (visitado ?x2 =(+ ?y2 1))
			(no-visitado ?x2 =(+ ?y2 1) ))
	=>
		(retract ?h ?j)
		(assert (seguro-serpiente ?x ?y))
		(focus Inconsistencias)
	)

	(defrule AsegurarSerpiente4

		?h <- (posible-serpiente ?x ?y ?x2 ?y2)
		?j <- (posible-serpiente ?x ?y =(+ ?x2 1) =(+ ?y2 1))

		(or (visitado =(+ ?x2 1) ?y2)
			(no-visitado =(+ ?x2 1) ?y2))
	=>
		(retract ?h ?j)
		(assert (seguro-serpiente ?x ?y))
		(focus Inconsistencias)
	)

	(defrule AsegurarSerpiente5

		?h <- (posible-serpiente ?x ?y ?x2 ?y2)
		?j <- (posible-serpiente ?x ?y =(+ ?x2 -1) =(- ?y2 -1))

		(or (visitado ?x2 =(+ ?y2 -1))
			(no-visitado ?x2 =(+ ?y2 -1) ))
	=>
		(retract ?h ?j)
		(assert (seguro-serpiente ?x ?y))
		(focus Inconsistencias)
	)

	(defrule AsegurarSerpiente6

		?h <- (posible-serpiente ?x ?y ?x2 ?y2)
		?j <- (posible-serpiente ?x ?y =(+ ?x2 -1) =(+ ?y2 -1))

		(or (visitado =(+ ?x2 1) ?y2)
			(no-visitado =(+ ?x2 1) ?y2))
	=>
		(retract ?h ?j)
		(assert (seguro-serpiente ?x ?y))
		(focus Inconsistencias)
	)

	(defrule AsegurarSerpiente7

		?h <- (posible-serpiente ?x ?y ?x2 ?y2)
		(not (posible-serpiente ?x3&:(<> ?x3 ?x) ?y3&:(<> ?y3 ?y) $?)) 		
	=>
		(retract ?h)
		(assert (seguro-serpiente ?x ?y))
		(focus Inconsistencias)
	)

;=============================MoverANoVisitada==================================

;	Engloba las funciones para visitar una casilla no-visitada y segura. Se 
;	el hecho "hecho" para saber que Willy se ha movido a una casilla segura y
;	que no se vuelva a mover en el siguiente módulo.
;
;	En el caso en el que haya varias posibles opciones, se elegirá 
;	aleatoriamente.

(defmodule MoverANoVisitada (import MAIN deftemplate ?ALL) (import myMAIN ?ALL) (import AfirmarPeligro ?ALL) (import InternalFunctions deffunction ?ALL) (export ?ALL))

	(defrule moverNoVisitadaSur					;	Mover a una casilla "no-visitada" al sur:
		(not (movimiento realizado))			
												;	Si no se ha realizado ningún movimiento, 
		(posActual ?x ?y)						;	ni hay un hecho ir-a (interno del algoritmo
		(or (not (ir-a $?))						;	de busqueda), la casilla tiene un hecho
			(ir-a ?x ?y))						;	"no-visitado", y es posible ir al sur
														
		?f <- (no-visitado ?x =(+ ?y -1))		;	entonces se utiliza la función moveWilly,
	=>											;	se borra el hecho "no-visitado", se inserta
	   	(moveWilly south)						;	la dirección seguida y el hecho
		(retract ?f)							;	"movimiento realizado".
		(assert (direccion south))				
												;	Repetir este proceso para las otras 3 direcciones.
		(assert (movimiento realizado))	
	)

	(defrule moverNoVisitadaNorte
		(not (movimiento realizado))

		(posActual ?x ?y)
		(or (not (ir-a $?))
			(ir-a ?x ?y))

		?f <- (no-visitado ?x =(+ ?y 1))
	=>
	   	(moveWilly north)
		(retract ?f)
		(assert (direccion north))

		(assert (movimiento realizado))
	)

	(defrule moverNoVisitadaEste
		(not (movimiento realizado))

		(posActual ?x ?y)
		(or (not (ir-a $?))
			(ir-a ?x ?y))

		?f <- (no-visitado =(+ ?x 1) ?y)
	=>
	   	(moveWilly east)
		(retract ?f)
		(assert (direccion east))

		(assert (movimiento realizado))
	)

	(defrule moverNoVisitadaOeste
		(not (movimiento realizado))

		(posActual ?x ?y)
		(or (not (ir-a $?))
			(ir-a ?x ?y))

		?f <- (no-visitado =(+ ?x -1) ?y)
	=>
	   	(moveWilly west)
		(retract ?f)
		(assert (direccion west))

		(assert (movimiento realizado))
	)


;==============================IniciarBusqueda==================================

;	Si el anterior módulo no se ha ejecutado, este módulo podrá hacer dos cosas:
;	o iniciar un algoritmo de busqueda en anchura para encontrar un camino 
;	desde la posición actual hasta una casilla de no-visitado; o por otro lado
;	seguir el camino producido por el algoritmo. 

;	También se ocupa de borrar los hechos asertados por el algoritmo al 
;	término de este.

(defmodule IniciarBusqueda (import MAIN deftemplate ?ALL) (import myMAIN ?ALL) (import MoverANoVisitada ?ALL) (import InternalFunctions deffunction ?ALL) (export ?ALL))

	(defrule iniciar-algoritmo					;	Si no se ha realizado un movimiento,
		(posActual ?a ?b)						;	no hay ningún hecho "no-visitado" 
												;	alrededor, y no hay un hecho "ir-a",		
		(not (no-visitado =(+ ?a -1) ?b))		;	entonces se calcula la casilla 
		(not (no-visitado =(+ ?a 1) ?b))		;	"no-visitado" mas proxima con el módulo
		(not (no-visitado ?a =(+ ?b 1)))		;	calcularIr-a.
		(not (no-visitado ?a =(+ ?b -1)))			
												
		(not (movimiento realizado))				
		(not (ir-a $?))							
	=>
		(assert (ir-a 99 99))
		(assert (cadenahijos ?a ?b))

		(focus calcularIr-a)
	)

	(defrule iniciar-algoritmo2					;	Una vez calculada la casilla objetivo
		(ir-a ?x&:(<> ?x 99) ?y&:(<> ?y 99))	;	"ir-a", se incluye en la pila de módulos 
	=>											;	el resto de módulos del algoritmo.
		(assert (cadena-mov ?x ?y))
												;	Se activa cuando la hecho "ir-a" tiene
		(focus SiguienteMovDeBusqueda)			;	valores diferentes a los inicializados
		(focus AlgoritmoBusqueda2)				;	(es decir, 99).
		(focus AlgoritmoBusqueda)
	)

	(defrule seguir-cadena-movimiento			;	Si el algoritmo ya se ha realizado
		(not (movimiento realizado))			;	pero quedan movimientos que seguir,
		(ir-a $?)								;	se activa esta regla.
		(cadena-mov $?)
		(not (cadenahijos $?))
	=>
		(focus SiguienteMovDeBusqueda)
	)

	(defrule borrar-iteracion					;	Borra todas las iteraciones de la 
		(ir-a ?x ?y)							;	base de hechos.
		(posActual ?x ?y)						
		?h <- (iteracion $?)					;	Si el hecho ir-a coincide con la
	=>											;	posición actual, entonces el algoritmo 
		(retract ?h)							;	habrá finalizado y se podrán borrar.
	)	
												;	Del mismo modo se borra la cadena-mov
	(defrule borrar-cadena-mov					;	y por último el hecho "ir-a".
		(ir-a ?x ?y)
		(posActual ?x ?y)
		?h <- (cadena-mov $?)	
	=>
		(retract ?h)
	)

	(defrule borrar-ir-a
		?h <- (ir-a ?x ?y)
		(posActual ?x ?y)
		(not (cadena-mov $?))
		(not (iteracion $?))
	=>
		(retract ?h)
	)


;===============================================================================

;	Módulo encargado de obtener la casilla "no-visitado" mas próximas a la
;	actual.

(defmodule calcularIr-a (import MAIN deftemplate ?ALL) (import myMAIN ?ALL) (import IniciarBusqueda ?ALL) (import InternalFunctions deffunction ?ALL) (export ?ALL))

	(defrule obtener-ir-a					;	Si una casilla cualquiera "no-visitado" 
		(posActual ?x ?y)					;	está mas cerca que la casilla "ir-a", 
		?h <- (ir-a ?x2 ?y2)				;	entonces se sustituye.
		(no-visitado ?a ?b)
	
		(test (< (+ (abs (- ?x ?a)) (abs (- ?y ?b))) (+ (abs (- ?x ?x2)) (abs (- ?y ?y2))) ) )
		
	=>
		(retract ?h)
		(assert (ir-a ?a ?b))
	)

	(defrule ir-a-segura-serpiente
		?h <- (ir-a $?)
		(not (no-visitado $?))
		(seguro-serpiente ?x ?y)
	=>	
		(retract ?h)
		(assert (ir-a ?x ?y))
	)


;=============================AlgoritmoBusqueda=================================

;	En este módulo, el algoritmo produce una cola con casillas alrededor de 
;	de la casilla actual, buscando la casilla objetivo (ir-a).
;
;	Por otro lado va insertando hechos de tipo iteracion, en los que guarda
;	el padre de cada uno de las casillas para poder así encontrar un camino.

(defmodule AlgoritmoBusqueda (import MAIN deftemplate ?ALL) (import myMAIN ?ALL) (import IniciarBusqueda ?ALL) (import InternalFunctions deffunction ?ALL) (export ?ALL))

	(defrule buscarAnchuraNorte									;	Si hay una casilla en el norte adyacente	
																;	a las coordenadas a evaluar de "cadenahijos",
		(ir-a ?a ?b)											;	y dicha casilla no ha sido incluida 
		?h <- (cadenahijos ?x ?y $?cosas)						;	anteriormente además de que sea o una casilla
																;	"visitado" o "no-visitado", dicha casilla
		(not (iteracion ?x =(+ ?y 1) ? ?))						;	se insertará al final de "cadenahijos", además
		(not (iteracion ? ? ?x =(+ ?y 1)))						;	de "iteracion" con el padre de dicha casilla. 
		(or (visitado ?x =(+ ?y 1))
			(no-visitado ?x ?b&:(= ?b (+ ?y 1))))				;	Repetir este proceso para las otras 3 direcciones.
	=>
		(retract ?h)
		(assert (cadenahijos ?x ?y $?cosas ?x =(+ ?y 1)))
		(assert (iteracion ?x =(+ ?y 1) ?x ?y))
	)

	(defrule buscarAnchuraSur

		(ir-a ?a ?b)
		?h <- (cadenahijos ?x ?y $?cosas)

		(not (iteracion ?x =(+ ?y -1) ? ?))
		(not (iteracion ? ? ?x =(+ ?y -1)))
		(or (visitado ?x =(+ ?y -1))
			(no-visitado ?x ?b&:(= ?b (+ ?y -1))))
	=>
		(retract ?h)
		(assert (cadenahijos ?x ?y $?cosas ?x =(+ ?y -1)))
		(assert (iteracion ?x =(+ ?y -1) ?x ?y))
	)

	(defrule buscarAnchuraEste

		(ir-a ?a ?b)
		?h <- (cadenahijos ?x ?y $?cosas)

		(not (iteracion =(+ ?x 1) ?y ? ?))
		(not (iteracion ? ? =(+ ?x 1) ?y))
		(or (visitado =(+ ?x 1) ?y)
			(no-visitado ?a&:(= ?a (+ ?x 1)) ?y))
	=>
		(retract ?h)
		(assert (cadenahijos ?x ?y $?cosas =(+ ?x 1) ?y))
		(assert (iteracion =(+ ?x 1) ?y ?x ?y))
	)

	(defrule buscarAnchuraOeste

		(ir-a ?a ?b)
		?h <- (cadenahijos ?x ?y $?cosas)

		(not (iteracion =(+ ?x -1) ?y ? ?))
		(not (iteracion ? ? =(+ ?x -1) ?y))
		(or (visitado =(+ ?x -1) ?y)
			(no-visitado ?a&:(= ?a (+ ?x -1)) ?y))
	=>
		(retract ?h)
		(assert (cadenahijos ?x ?y $?cosas =(+ ?x -1) ?y))
		(assert (iteracion =(+ ?x -1) ?y ?x ?y))
	)


;=============================AlgoritmoBusqueda2================================

;	En este módulo, se inicia de nuevo el módulo anterior, o por otro lado
;	si el algoritmo ya ha encontrado la casilla objetivo, se forma una cola
;	con coordenadas, desde la casilla objetivo hasta la actual 
;	(cadena-movimientos).

(defmodule AlgoritmoBusqueda2 (import MAIN deftemplate ?ALL) (import myMAIN ?ALL) (import AlgoritmoBusqueda ?ALL) (import InternalFunctions deffunction ?ALL) (export ?ALL))

	(defrule borrar_principio_cadena_hijos					;	Si no se ha encontrado la casilla objetivo,
		?h <- (cadenahijos ?x ?y $?cosas)					;	borrar las coordenadas del principio y repetir
		(not (ir-a ?x ?y))									;	el módulo AlgoritmoBusqueda.
	=>
		(retract ?h)
		(assert (cadenahijos $?cosas))

		(focus AlgoritmoBusqueda)
	)

;-------------------------------------------------------------------------------

	(defrule formar_cadena_mov									;	Si se ha encontrado la casilla objetivo, 
		(cadenahijos ?x ?y $?cosas)								;	se forma la cadena de movimientos que 
		(ir-a ?x ?y)											;	debe realizar willy, desde la casilla actual
																;	hasta la objetivo. 
		?h <- (cadena-mov ?a ?b $?resto)
		?j <- (iteracion ?a ?b ?padreX ?padreY)					;	Al terminar, al final de la cadena estará
		(not (posActual ?padreX ?padreY))						;	la casilla objetivo, y al principio una 
	=>															;	casilla adyacente a la actual.
		(retract ?h ?j)
		(assert (cadena-mov ?padreX ?padreY ?a ?b $?resto))
	)


;==========================SiguienteMovDeBusqueda===============================

;	Este módulo utiliza la cadena de hechos (cadena-mov) para poder obtener
;	la siguiente posición a visitar en el camino hacia la casilla objetivo.

(defmodule SiguienteMovDeBusqueda (import MAIN deftemplate ?ALL) (import myMAIN ?ALL) (import AlgoritmoBusqueda2 ?ALL) (import InternalFunctions deffunction ?ALL) (export ?ALL))

	(defrule eliminar_cadena_hijo					;	Se elimina la cadenahijos si es necesario
		?h <- (cadenahijos $?)
	=>
		(retract ?h)
	)

	(defrule mover_norte							;	Se compará la posición actual con la proxima
		(not (movimiento realizado))				;	casilla en el camino ("cadena-mov"), para 
													;	saber la dirección a seguir.
		(posActual ?x ?y)
		?h <- (cadena-mov ?a ?b $?cosas)			;	Se utiliza la función moveWilly, se inserta 
		(test (= ?b (+ ?y 1)))						;	la dirección obtenida, se borra la casilla 
	=>												;	evaluada, y el hecho "movimiento realizado".
		(retract ?h)	
		(moveWilly north)							;	Repetir este proceso para las otras 3 direcciones.
		(assert (direccion north))
		(assert (cadena-mov $?cosas))

		(assert (movimiento realizado))
	)

	(defrule mover_sur
		(not (movimiento realizado))

		(posActual ?x ?y)
		?h <- (cadena-mov ?a ?b $?cosas)
		(test (= ?b (+ ?y -1)))
	=>
		(retract ?h)	
		(moveWilly south)
		(assert (direccion south))
		(assert (cadena-mov $?cosas))

		(assert (movimiento realizado))
	)

	(defrule mover_este
		(not (movimiento realizado))

		(posActual ?x ?y)
		?h <- (cadena-mov ?a ?b $?cosas)
		(test (= ?a (+ ?x 1)))
	=>
		(retract ?h)	
		(moveWilly east)
		(assert (direccion east))
		(assert (cadena-mov $?cosas))

		(assert (movimiento realizado))
	)

	(defrule mover_oeste
		(not (movimiento realizado))

		(posActual ?x ?y)
		?h <- (cadena-mov ?a ?b $?cosas)
		(test (= ?a (+ ?x -1)))
	=>
		(retract ?h)	
		(moveWilly west)
		(assert (direccion west))
		(assert (cadena-mov $?cosas))

		(assert (movimiento realizado))
	)


;=================================Calculos======================================

; 	Incluye todas las reglas que realizan los cálculos post-movimiento.
;	Actualiza la posición actual, el número de movimientos y las casillas
;	visitadas. 
;	Si Willy ha realizado 999 movimientos, se detendrá.

(defmodule Calculos (import MAIN deftemplate ?ALL) (import myMAIN ?ALL) (import IniciarBusqueda ?ALL) (import InternalFunctions deffunction ?ALL) (export ?ALL))

	(defrule calcularMovimientoEste					;	Si en el módulo de MoverANoVisitada se
		?f <- (direccion east)						;	se ha ejecutado alguna regla, o en el
		?h <- (posActual ?x ?y)						;	SiguienteMovDeBusqueda, se habrá insertado
	=>												;	la dirección a la que se haya dirigido.			
		(retract ?h ?f)								
		(assert (posActual =(+ ?x 1) ?y))			;	Con ella, se calcula la nueva posición
		(assert (visitado =(+ ?x 1) ?y))			;	actual, y se inserta un hecho "visitado".
	)

	(defrule calcularMovimientoOeste
		?f <- (direccion west)
		?h <- (posActual ?x ?y)
	=>
		(retract ?h ?f)
		(assert (posActual =(+ ?x -1) ?y))
		(assert (visitado =(+ ?x -1) ?y))
	)

	(defrule calcularMovimientoNorte
		?f <- (direccion north)
		?h <- (posActual ?x ?y)
	=>
		(retract ?h ?f)
		(assert (posActual ?x =(+ ?y 1)))
		(assert (visitado ?x =(+ ?y 1)))
	)

	(defrule calcularMovimientoSur
		?f <- (direccion south)
		?h <- (posActual ?x ?y)
	=>
		(retract ?h ?f)
		(assert (posActual ?x =(+ ?y -1)))
		(assert (visitado ?x =(+ ?y -1)))
	)

	(defrule aumentarNumMovimientos					;	Se aumenta el número de movimientos
		(not (direccion $?))						;	realizado por willy.
		?v <- (numMovimientos ?m)
	=>
		(retract ?v)
		(assert (numMovimientos =(+ ?m 1)))		
	)

	(defrule stopAl999								;	Si el número de movimientos de willy
		(numMovimientos 998)						;	alcanzado por willy es 999, entonces
	=>												;	se para.
		(pop-focus)
		(pop-focus)
	)


;=================================Fin_Ciclo=====================================

;	Módulo que incluye una única regla para volver a apilar los módulos y 
;	empezar de nuevo el ciclo de Willy

(defmodule Fin_Ciclo (import MAIN deftemplate ?ALL) (import myMAIN ?ALL) (import Calculos ?ALL) (import InternalFunctions deffunction ?ALL) (export ?ALL))

	(defrule volver									;	Por último, se borra el hecho
		?f <- (movimiento realizado)				;	"movimiento realizado", y se vuelve
	=>												;	a insertar en la pila los módulos 
		(retract ?f)								;	y se repite el ciclo.

		(focus Calculos)
		(focus IniciarBusqueda)
		(focus MoverANoVisitada)
		(focus AfirmarPeligro)
		(focus Inconsistencias)
		(focus Reconocimiento)
	)



