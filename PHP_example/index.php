<?php

require_once('session.php');
require_once('EmployeesQueries.php');

$q = new EmployeeQueries();

if(empty($q->dbc))
{
	echo "ERROR EN LA CONEXION CON LA BD";
	die();
}

?>
<head>
   <title>Practica 5</title>
   <link rel="stylesheet" href="estilos.css">

   <meta charset="ISO-8859-1">
   <meta name="description" content="Aplicación web para mostrar información de los empleados de una empresa">
</head>

<body>

<div align="center" style="background-color:PaleTurquoise;">
	<br><img src="Images/logo.jpg" alt="logo Icon" style="width:374px;height:188px;"></br>
	<br></br>
</div>

<div align="center" style="background-color:PaleTurquoise;">
	<h1>BEST SUPPLIERS</h1>
</div>

<nav>
	<?php
	if( $admin == SI )
	{
		echo '<a href="createUserAdmin.php"><input type="submit" name="submitted" value="Agregar usuario"/></a> ';
		echo '<a href="aceptarPeticiones.php"><input type="submit" name="submitted" value="Peticiones"/></a> ';
	}
	if($admin == NO and $logged)
	{
		echo '<a href="pedirAumento.php"><input type="submit" name="submitted" value="Pedir aumento"/></a> ';
	}

	if( !$logged )
	{
		echo '<a href="login.php"><input type="submit" name="submitted" value="Login"/></a> ';
	}
	else
	{
		echo '<a href="endSession.php"><input type="submit" name="submitted" value="Logout"/></a>';
	}
	?>

</nav>

<h1 align="center" >Lista de Empleados</h1>

<table align="center" border=1>
	<tr>
		<th>Id</th>
		<th>Apellidos</th>
		<th>Nombre</th>
	</tr>

	<?php

	$employees = $q->getAllEmployees();

	foreach($employees as $employee)
	{
		if($admin == SI)
		{
			echo '<tr>
				<td>'.$employee[id].'</td>
				<td>'.$employee[apellidos].'</td>
				<td>'.$employee[nombre].'</td>
				<td><a href="employee.php?id='.urlencode($employee[id]).'"><img src="Images/mas.jpeg" alt="logo Icon" style="width:27px;height:27px;"></a></td>
				<td><a href="deleteEmployee.php?id='.urlencode($employee[id]).'"><img src="Images/borrar.jpg" alt="logo Icon" style="width:27px;height:27px;"></a></td>
				<td><a href="editEmployee.php?id='.urlencode($employee[id]).'"><img src="Images/lapiz.png" alt="logo Icon" style="width:27px;height:27px;"></a></td>
			</tr>';
		}
		elseif($logged == true)
		{
			echo '<tr>
					<td>'.$employee[id].'</td>
					<td>'.$employee[apellidos].'</td>
					<td>'.$employee[nombre].'</td>
					<td><a href="employee.php?id='.urlencode($employee[id]).'"><img src="Images/mas.jpeg" alt="logo Icon" style="width:27px;height:27px;"></a></td>
			</tr>';
		}
		else
		{
			echo '<tr>
					<td>'.$employee[id].'</td>
					<td>'.$employee[apellidos].'</td>
					<td>'.$employee[nombre].'</td>
			</tr>';
		}
	}

	?>

</table>

<?php
	if($admin == SI)
	{
		echo '
		<div align="center">
			<br>
			<a href="addEmployee.php" align="center"><input type="submit" name="submitted" value="Agregar empleado"/></a>
			<br>
		</div>';
	}
?>
