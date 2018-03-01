<?php

require_once('session.php');
if( !$logged or $admin==SI )
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
	<a href="index.php"><input type="submit" name="submitted" value="Volver a inicio"/></a>
</nav>';

if( !isset($_POST['request']) )
{
	echo '
	<form method="POST" action="pedirAumento.php">
		<table align="center" style="margin: 0 auto;">
			<tr align="center" >
				<th colspan="2" ><h2>Peticion de aumento</h2></th>
			</tr>
			<br>
			<tr align="left" >
				<td >ID</td>
				<td ><input type="text" name="id"></td>
			</tr>
			<tr align="left" >
				<td >Aumento (euros)</td>
				<td ><input type="text" name="aumento" value"1000"></td>
			</tr>

			<tr align="center" >
				<td colspan="2">
					<input type="hidden" name="request" value=true><br>
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
  if(strnatcasecmp ( $_POST['submitted'] , "Cancelar") == 0)
	{
		echo '
		<div align="center">
			<a href="index.php"><img src="Images/volver_inicio.png" alt="volver Icon" style="width:250px;height:75px;"></a>
		</div>';
	}
  else
  {
    $id = $_POST['id'];
    $aumento = $_POST['aumento'];
		$empleado = $q->getEmployee($id);

		if($aumento <= $empleado[salario])
		{
			echo '
			<div align="center">
				<font color="red" size=4>El salario introducido es menor del actual.</font>
				<br></br>
				<a href="index.php"><img src="Images/volver_inicio.png" alt="volver Icon" style="width:250px;height:75px;"></a>
			</div>';
		}
		else
		{
			if($q->checkId($id) == true)
			{
				$q->addRequest($id, $aumento);

		    echo '
		    <div align="center">
		      <a href="index.php"><img src="Images/volver_inicio.png" alt="volver Icon" style="width:250px;height:75px;"></a>
		    </div>';
			}
			else
			{
				echo '
		    <div align="center">
					<font color="red" size=4>El ID no existe.</font>
					<br></br>
		      <a href="index.php"><img src="Images/volver_inicio.png" alt="volver Icon" style="width:250px;height:75px;"></a>
		    </div>';
			}
		}

  }
}


?>
