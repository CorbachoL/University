<?php

require_once('session.php');
if( $admin == NO )
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
	<div align="center" style="background-color:PaleTurquoise;">
	  <h1>BEST SUPPLIERS</h1>
	</div>

	<nav>
	  <a href="endSession.php">Logout</a> |
	  <a href="index.php">Lista libros</a>
	</nav>';

/* Check if the employee is going to be add */
if (isset($_POST['add']))
{
	//Check if cancel button has been selected
	if(strnatcasecmp ( $_POST['submitted'] , "Cancelar") != 0)
	{
		// Get the data of the new employee from the _POST array and add
		$id = $_POST['id'];
		$nombre = $_POST['nombre'];
		$apellido = $_POST['apellido'];
		$dni = $_POST['dni'];
		$departamento = $_POST['departamento'];
		$salario = $_POST['salario'];

		if($q->checkId($id))
		{
			echo '
			<div align="center">
				<font color="red" size=4>El ID ya existia.</font>
				<br></br>
				<a href="index.php"><img src="Images/volver_inicio.png" alt="volver Icon" style="width:250px;height:75px;"></a>
			</div>';
		}
		else
		{
			$q->addEmployee($id, $nombre, $apellido, $dni, $departamento, $salario);
			echo '
			<div align="center">
				<a href="index.php"><img src="Images/volver_inicio.png" alt="volver Icon" style="width:250px;height:75px;"></a>
			</div>';
		}
	}
	else
	{
		echo '
		<div align="center">
			<a href="index.php"><img src="Images/volver_inicio.png" alt="volver Icon" style="width:250px;height:75px;"></a>
		</div>';
	}
}
elseif(! isset($_POST['add']))
{
	echo '
	<form method="POST" action="addEmployee.php">
		<table align="center" style="margin: 0 auto;">
			<tr align="center" >
				<th colspan="2" ><h3>Agregar empleado</h3></th>
			</tr>
			<br>
			<tr align="left" >
				<td >Nombre</td>
				<td ><input type="text" name="nombre"></td>
			</tr>
			<tr align="left" >
				<td >Apellido</td>
				<td ><input type="text" name="apellido"></td>
			</tr>
			<tr align="left" >
				<td >Id</td>
				<td ><input type="text" name="id"></td>
			</tr>
			<tr align="left" >
				<td >DNI</td>
				<td ><input type="text" name="dni"></td>
			</tr>
			<tr align="left" >
				<td >Departamento</td>
				<td ><input type="text" name="departamento"></td>
			</tr>
			<tr align="left" >
				<td >Salario</td>
				<td ><input type="text" name="salario"></td>
			</tr>

			<tr align="center" >
				<td colspan="2">
					<input type="hidden" name="add" value=true><br>
					<input type="submit" name="submitted" value="Aceptar"/>
					<input type="submit" name="submitted" value="Cancelar"/><br><br>
					<input type="reset"><i class="fa fa-pencil-square-o"></i></input>
				</td>
			</tr>
		</table>
	</form>';
}
else
{
	echo '
	<div align="center">
		<a href="index.php"><img src="Images/volver_inicio.png" alt="volver Icon" style="width:250px;height:75px;"></a>
	</div>';
}

?>
