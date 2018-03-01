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
	?><p class="error">ERROR EN LA CONEXION CON LA BD.</p><?php
	die();
}

echo'
<div align="center" style="background-color:PaleTurquoise;">
  <h1>BEST SUPPLIERS</h1>
</div>

<nav>
  <a href="endSession.php">Logout</a> |
  <a href="index.php">Lista libros</a>
</nav>';

if (isset($_POST['deleteId']))
{
	$id = $_POST['deleteId'];
	$employee = $q->getEmployee($id);
}
elseif (isset($_GET["id"]))
{
	$id = $_GET["id"];
	$employee = $q->getEmployee($id);
}
else
{
	//Redirect to the list of employees
	echo '
	<div align="center">
		<a href="index.php"><img src="Images/volver_inicio.png" alt="volver Icon" style="width:250px;height:75px;"></a>
	</div>';
}


/* Check if the book is going to be deleted */
if (isset($_POST['delete']))
{
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
		// Get the isbn from the _POST array and delete
		$q->deleteEmployee($id);
		
		echo '
		<div align="center">
			<a href="index.php"><img src="Images/volver_inicio.png" alt="volver Icon" style="width:250px;height:75px;"></a>
		</div>';

	}
}


if (isset($_GET["id"]))
{
		?>

		<br>
		<div align="center">
			<img src="Images/<?php echo $employee[id]?>.jpg" alt="<?php echo $employee[nombre]?> Icon" style="width:538px;height:300px;">
		</div>

		<div style="background-color:powderblue;">
			<h2 align="center"><?php echo $employee[nombre]?> <?php echo $employee[apellidos]?></h2>
		</div>

		<div align="center">
			<h2>Lista de Empleados</h2>
		   	<ul>
		    	<li><b>ID:</b> <?php echo $employee[id]?></li>
	      	<li><b>Nombre:</b> <?php echo $employee[nombre]?></li>
	      	<li><b>Apellidos:</b> <?php echo $employee[apellidos]?></li>
					<li><b>Nombre:</b> <?php echo $employee[nombre]?></li>
					<li><b>DNI:</b> <?php echo $employee[dni]?></li>
					<li><b>Departamento:</b> <?php echo $employee[departamento]?></li>
					<li><b>Salario:</b> <?php echo $employee[salario]?></li>
		   	</ul>

			<form method="POST" action="/deleteEmployee.php">
				<input type="hidden" name="delete" value=true>
				<input type="hidden" name="deleteId" value="<?php echo $employee[id]?>">
				<input type="submit" name="submitted" value="Eliminar"/>
				<input type="submit" name="submitted" value="Cancelar"/>
			</form>
		</div>

		<?php
}
?>
