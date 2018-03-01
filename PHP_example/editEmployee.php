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
<div align="center" style="background-color:PaleTurquoise;">
  <h1>BEST SUPPLIERS</h1>
</div>

<nav>
  <a href="endSession.php">Logout</a> |
  <a href="index.php">Lista libros</a>
</nav>';

if (isset($_POST['modify']))
{
	// Get the old id from the _POST array
	$oldId = $_POST['editId'];

	//Check if cancel button has been selected
	if(strnatcasecmp ( $_POST['submitted'] , "Cancelar") == 0)
	{
		echo '
		<div align="center">
			<a href="index.php"><img src="Images/volver_inicio.png" alt="volver Icon" style="width:250px;height:75px;"></a>
		</div>';
	}
	else
	{
		//Get the new employee values
		$employee['id'] = $_POST['id'];
		$employee['nombre'] = $_POST['nombre'];
		$employee['apellidos'] = $_POST['apellidos'];
		$employee['dni'] = $_POST['dni'];
		$employee['departamento'] = $_POST['departamento'];
		$employee['salario'] = $_POST['salario'];

		$check = $q->checkModifiedEmployee($employee, $oldId);

		if($check)
		{
			$status = $q->editEmployee($employee, $oldId);

			//If correctly updated, go to employees page
			if($status)
			{
				echo '
				<div align="center">
					<a href="index.php"><img src="Images/volver_inicio.png" alt="volver Icon" style="width:250px;height:75px;"></a>
				</div>';
			}
			else
			{
				echo '
	      <div align="center">
	        <font color="red" size=4>Error de modificacion.</font>
	        <br></br>
	        <a href="index.php"><img src="Images/volver_inicio.png" alt="volver Icon" style="width:250px;height:75px;"></a>
	      </div>';
			}
		}else{
			echo '
			<div align="center">
				<font color="red" size=4Error en el check del empleado.</font>
				<br></br>
				<a href="index.php"><img src="Images/volver_inicio.png" alt="volver Icon" style="width:250px;height:75px;"></a>
			</div>';
		}
	}
}
elseif (isset($_GET["id"]))
{
	$id = $_GET["id"];
	$employee = $q->getEmployee($id);

	?>
	<form method="POST" action="editEmployee.php">
		<table align="center" style="margin: 0 auto;">
			<tr align="center" >
				<th colspan="2" ><h3>Modificar empleado</h3></th>
			</tr>
			<br>
			<tr align="left" >
				<td >Nombre</td>
				<td ><input type="text" name=nombre value="<?php echo $employee[nombre]?>"></td>
			</tr>
			<tr align="left" >
				<td >Apellidos</td>
				<td ><input type="text" name=apellidos value="<?php echo $employee[apellidos]?>"></td>
			</tr>
			<tr align="left" >
				<td >Id</td>
				<td ><input type="text" name="id" value="<?php echo $employee[id]?>"></td>
			</tr>
			<tr align="left" >
				<td >DNI</td>
				<td ><input type="text" name="dni" value="<?php echo $employee[dni]?>"></td>
			</tr>
			<tr align="left" >
				<td >Departamento</td>
				<td ><input type="text" name="departamento" value="<?php echo $employee[departamento]?>"></td>
			</tr>
			<tr align="left" >
				<td >Salario</td>
				<td ><input type="text" name="salario" value="<?php echo $employee[salario]?>"></td>
			</tr>

			<tr align="center" >
				<td colspan="2">
					<input type="hidden" name="modify" value=true>
					<input type="hidden" name="editId" value="<?php echo $id?>"><br>

					<input type="submit" name="submitted" value="Aceptar"/>
					<input type="submit" name="submitted" value="Cancelar"/><br>
					<input type="reset">
				</td>
			</tr>
		</table>
	</form>
	<?php
}
else
{
	//Redirect to the list of employees
	echo '
	<div align="center">
		<a href="index.php"><img src="Images/volver_inicio.png" alt="volver Icon" style="width:250px;height:75px;"></a>
	</div>';
}

?>
