<?php

	//Iniciar la sesión para poder acceder al array $_SESSION
	session_start();

	//Inicializar $_SESSION a un array vacío
	$_SESSION = array();

	//Finalizar la sesión
	session_destroy();

	header ("Location: /index.php");
?>
