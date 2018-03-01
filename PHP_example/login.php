<?php

require_once('session.php');

if( $logged )
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
	<a href="index.php"><input type="submit" name="submitted" value="Lista Empleados"/></a>
</nav>';

if( isset($_POST['login']) )
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
		//Get the username and password of the login form
		$username = $_POST['username'];
		$password = $_POST['password'];

		//Check if user and password match with the ones in the database
		$checkLogin = $q->login($username, $password);

		if($checkLogin == true)
		{
			$_SESSION['username'] = $username;
			$_SESSION['admin'] = $q->isAdmin($username);

			echo '
			<div align="center">
				<a href="index.php"><img src="Images/volver_inicio.png" alt="volver Icon" style="width:250px;height:75px;"></a>
			</div>';
		}
		else
		{
			echo '
			<div align="center">
				<font color="red" size=4>Usuario o contraseña incorrectos.</font>
				<br></br>
				<a href="index.php"><img src="Images/volver_inicio.png" alt="volver Icon" style="width:250px;height:75px;"></a>
			</div>';
		}
	}
}
elseif( isset($_POST['createUser']) )
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
		//Get the username and password of the login form
		$username = $_POST['username'];
		$password = $_POST['password'];
		$password2 = $_POST['password2'];

		if($password == $password2)
		{
			//Add the new user
			$checkUser = $q->addUser($username, $password, NO);

			if($checkUser)
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
					<font color="red" size=4>No se ha podido agregar el usuario. Nombre ya utilizado.</font>
					<br></br>
					<a href="index.php"><img src="Images/volver_inicio.png" alt="volver Icon" style="width:250px;height:75px;"></a>
				</div>';
			}
		}
		else
		{
			echo '
			<div align="center">
				<font color="red" size=4>Las dos password no coinciden.</font>
				<br></br>
				<a href="index.php"><img src="Images/volver_inicio.png" alt="volver Icon" style="width:250px;height:75px;"></a>
			</div>';
		}
	}
}
else
{
	echo '
	<form method="POST" action="login.php">
		<table align="center" style="margin: 0 auto;">
			<tr align="center" >
				<th colspan="2" ><h2>Login</h2></th>
			</tr>
			<br>
			<tr align="left" >
				<td >Usuario</td>
				<td ><input type="text" name="username"></td>
			</tr>
			<tr align="left" >
				<td >Password</td>
				<td ><input type="password" name="password"></td>
			</tr>

			<tr align="center" >
				<td colspan="2">
					<input type="hidden" name="login" value=true><br>
					<input type="submit" name="submitted" value="Aceptar"/>
					<input type="submit" name="submitted" value="Cancelar"/><br><br>
					<input type="reset"><i class="fa fa-pencil-square-o"></i></input>
				</td>
			</tr>
		</table>
	</form>

	<div align="center">
		<br></br>
		<h3>-----------------------------------------------------------------------------</h3>
	</div>

	<form method="POST" action="login.php">
		<table align="center" style="margin: 0 auto;">
			<tr align="center" >
				<th colspan="2" ><h2>Nuevo Usuario</h2></th>
			</tr>
			<br>
			<tr align="left" >
				<td >Usuario</td>
				<td ><input type="text" name="username"></td>
			</tr>
			<tr align="left" >
				<td >Password</td>
				<td ><input type="password" name="password"></td>
			</tr>
			<tr align="left" >
				<td >Confirmar password</td>
				<td ><input type="password" name="password2"></td>
			</tr>
			<tr align="center" >
				<td colspan="2">
					<input type="hidden" name="createUser" value=true><br>
					<input type="submit" name="submitted" value="Aceptar"/>
					<input type="submit" name="submitted" value="Cancelar"/><br><br>
					<input type="reset"><i class="fa fa-pencil-square-o"></i></input>
				</td>
			</tr>
		</table>
	</form>';
}

?>
