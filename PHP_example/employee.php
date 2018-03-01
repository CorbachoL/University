<?php

require_once('session.php');
if( !$logged )
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

?>
<div align="center" style="background-color:PaleTurquoise;">
  <h1>BEST SUPPLIERS</h1>
</div>

<nav>
  <a href="endSession.php">Logout</a> |
  <a href="index.php">Lista libros</a>
</nav>
<?php

$id = $_GET["id"];
$employee = $q->getEmployee($id);

?>

<head>
	<title><?php echo $employee[nombre]?> <?php echo $employee[apellidos]?></title>
	<link rel="stylesheet" href="estilos.css">

	<meta charset="ISO-8859-1">
	<meta name="description" content="Información de <?php echo $employee[nombre]?><?php echo $employee[apellidos]?>">
</head>

<body>

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

	<a href="index.php"><img src="Images/volver_inicio.png" alt="volver Icon" style="width:250px;height:75px;"></a>
</div>


</body>
