<?php

require_once('session.php');
if( !$logged or ($admin==NO) )
{
	header ("Location: /index.php");
}

require_once('EmployeesQueries.php');

$q = new EmployeeQueries();

if(empty($q->dbc))
{
	echo "ERROR EN LA CONEXION CON LA BD";
	die();
}

echo '
	<head>
		 <title>Practica 5</title>
		 <link rel="stylesheet" href="estilos.css">

		 <meta charset="ISO-8859-1">
		 <meta name="description" content="Aplicación web para mostrar información de los empleados de una empresa">
	</head>

  <div align="center" style="background-color:PaleTurquoise;">
    <h1>BEST SUPPLIERS</h1>
  </div>

  <nav>
  	<a href="index.php"><input type="submit" name="submitted" value="Volver a inicio"/></a>
  </nav>';

if( !isset($_GET['id']) )
{
	echo '
		<h1 align="center" >Peticiones de aumento</h1>

		<table align="center" border=1>
			<tr>
				<th>Id</th>
				<th>Nombre</th>
				<th>Apellido</th>
				<th>DNI</th>
				<th>Departamento</th>
				<th>Salario Actual</th>
				<th>Salario Pedido</th>
			</tr>';

	$requests = $q->getAllRequests();

	foreach($requests as $request)
	{
			$employee = $q->getEmployee($request[id]);
			echo '<tr>
				<td>'.$employee[id].'</td>
				<td>'.$employee[nombre].'</td>
				<td>'.$employee[apellidos].'</td>
				<td>'.$employee[dni].'</td>
				<td>'.$employee[departamento].'</td>
				<td>'.$employee[salario].'</td>
				<td>'.$request[aumento].'</td>
				<td><a href="aceptarPeticiones.php?id='.urlencode($employee[id]).'&valor='.urlencode(SI).'"><img src="Images/aceptar.png" alt="logo Icon" style="width:27px;height:27px;"></a></td>
				<td><a href="aceptarPeticiones.php?id='.urlencode($employee[id]).'&valor='.urlencode(NO).'"><img src="Images/denegar.jpeg" alt="logo Icon" style="width:27px;height:27px;"></a></td>
			</tr>';
	}

	echo '</table>';
}
else
{
	$id = $_GET['id'];
	if(strnatcasecmp ( $_GET['valor'] , "SI") == 0)
	{
		$q->modifySalary($id);
	}
	else
	{
		$q->deleteRequest($id);
	}

	echo '
	<div align="center">
		<a href="index.php"><img src="Images/volver_inicio.png" alt="volver Icon" style="width:250px;height:75px;"></a>
	</div>';
}

?>
