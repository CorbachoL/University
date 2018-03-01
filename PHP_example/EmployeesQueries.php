
<?php

class EmployeeQueries
{

	//VARIABLES
	public $user = 'root';
	public $password = '1144';
	public $dbc;

	//FUNCIONES PUBLICAS
	public function __construct()
	{
		$this->dbc = $this->dbconnect();
	}

	public function dbconnect()
	{
		$dbc = null;

		try
		{
			$dbc = new PDO('mysql:host=localhost; dbname=i52coloj', $this->user, $this->password, array(PDO::ATTR_PERSISTENT => true));
		}catch(PDOException $e)
		{
			return null;
		}

		return $dbc;
	}

	/*----------------------------------------------------------------------------

													FUNCIONES DE EMPLEADOS

	----------------------------------------------------------------------------*/

	public function getAllEmployees()
	{
		$employees = array();

		$sentence = $this->dbc->prepare("SELECT * FROM employees");

		if($sentence->execute()) {
			while($row = $sentence->fetch())
			{
				$employees[] = $row;
			}
		}

		return $employees;
	}

	public function getEmployee($id)
	{
		$sentence = $this->dbc->prepare("SELECT * FROM employees WHERE id=$id");

		if($sentence->execute())
		{
			$row = $sentence->fetch();
		}

		return $row;
	}

	public function deleteEmployee($id)
	{
		$sentence = $this->dbc->prepare("DELETE FROM employees WHERE id=$id");
		if($sentence->execute())
		{
			return true;
		}

		return false;
	}

	public function checkModifiedEmployee($employee, $oldId)
	{
		if(strlen($employee['nombre']) <= 0)
		{
			return false;
		}
		if(! $this->checkId($oldId))
		{
			return false;
		}

		if($employee['id'] != $oldId)
		{
			if($this->checkId($employee['id']))
			{
				return false;
			}
		}

		return true;
	}

	public function addEmployee($id, $nombre, $apellidos, $dni, $departamento, $salario)
	{
		$sentence = $this->dbc->prepare("INSERT INTO employees(id, nombre, apellidos, dni, departamento, salario) VALUES('$id', '$nombre', '$apellidos', '$dni', '$departamento', '$salario');");
		if($sentence->execute())
		{
			return true;
		}

		return false;
	}

	public function editEmployee($employee, $oldId)
	{
		if(! $this->deleteEmployee($oldId) )
			return false;

		if(! $this->addEmployee($employee['id'], $employee['nombre'], $employee['apellidos'], $employee['dni'], $employee['departamento'], $employee['salario']) )
			return false;

		return true;
	}

	public function checkId($id)
	{
		$employees = $this->getAllEmployees();

		foreach($employees as $employee)
		{
			if($employee['id'] == $id)
				return true;
		}

		return false;
	}

	/*----------------------------------------------------------------------------

													FUNCIONES DE USUARIOS

	----------------------------------------------------------------------------*/

	public function getAllUsers()
	{
		$users = array();

		$sentence = $this->dbc->prepare("SELECT * FROM usuarios");

		if($sentence->execute()) {
			while($row = $sentence->fetch())
			{
				$users[] = $row;
			}
		}

		return $users;
	}

	public function checkUser($username)
	{
		$users = $this->getAllUsers();

		foreach($users as $user)
		{
			if($user['nombreUsuario'] == $username)
				return true;
		}

		return false;
	}

	public function addUser($username, $password, $admin)
	{
		$salt1 = "*pw*";
		$salt2 = "*mola*";
		$token = hash('ripemd128', "$salt1$password$salt2");

		if( $this->checkUser($username) == true )
		{
			return false;
		}

		$sentence = $this->dbc->prepare("INSERT INTO usuarios(nombreUsuario, password, admin) VALUES('$username', '$token', '$admin');");
		if($sentence->execute())
		{
			return true;
		}

		return false;
	}

	public function login($username, $password)
	{
		if($this->checkUser($username) == false)
			return false;

		$sentence = $this->dbc->prepare("SELECT * FROM usuarios WHERE nombreUsuario='$username'");

		$salt1 = "*pw*";
		$salt2 = "*mola*";
		$token = hash('ripemd128', "$salt1$password$salt2");

		if($sentence->execute())
		{
			$row = $sentence->fetch();

			if( $row['password'] == $token )
				return true;
			else
				return false;
		}
		else
			return false;
	}

	public function isAdmin($username)
	{
		$users = $this->getAllUsers();

		foreach($users as $user)
		{
			if($user['nombreUsuario'] == $username)
				return $user['admin'];
		}
	}

	/*----------------------------------------------------------------------------

																		REQUEST

	----------------------------------------------------------------------------*/

	public function getRequest($id)
	{
		$sentence = $this->dbc->prepare("SELECT * FROM requests WHERE id=$id");

		if($sentence->execute())
		{
			$row = $sentence->fetch();
		}

		return $row;
	}

	public function getAllRequests()
	{
		$requests = array();

		$sentence = $this->dbc->prepare("SELECT * FROM requests");

		if($sentence->execute()) {
			while($row = $sentence->fetch())
			{
				$requests[] = $row;
			}
		}

		return $requests;
	}

	public function modifySalary($id)
	{
		$request = $this->getRequest($id);
		$employee = $this->getEmployee($id);

		try
		{
			//Begin transaction
			$this->dbc->beginTransaction();

			$sentence = $this->dbc->prepare("DELETE FROM requests WHERE id=$id");
			$sentence->execute();

			$sentence = $this->dbc->prepare("DELETE FROM employees WHERE id=$id");
			$sentence->execute();

			$sentence = $this->dbc->prepare("INSERT INTO employees(id, nombre, apellidos, dni, departamento, salario) VALUES('$employee[id]', '$employee[nombre]', '$employee[apellidos]', '$employee[dni]', '$employee[departamento]', '$request[aumento]');");
			$sentence->execute();

			//If all OK, commit the changes
			$this->dbc->commit();
		}
		catch (Exception $e)
		{
			$this->dbc->rollback();
		}
	}

	public function addRequest($id, $aumento)
	{
		$sentence = $this->dbc->prepare("INSERT INTO requests(id, aumento) VALUES('$id', '$aumento');");
		if($sentence->execute())
		{
			return true;
		}

		return false;
	}

	public function deleteRequest($id)
	{
		$sentence = $this->dbc->prepare("DELETE FROM requests WHERE id=$id");
		if($sentence->execute())
		{
			return true;
		}

		return false;
	}
}



?>
