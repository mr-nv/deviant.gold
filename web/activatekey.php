<?php
$userhwid = htmlspecialchars($_POST["hwid"]);
$keyuff = htmlspecialchars($_POST["key"]);
$userhwid = check_input($_POST["hwid"], "Input hwid!");
$keyuff = check_input($_POST["key"], "Input key!");
$returnmessage = "";
$globaldayz = getdaysfromrow($keyuff);
function check_input($data, $problem = "")
{
$data = trim($data);
$data = stripslashes($data);
$data = htmlspecialchars($data);
if ($problem && strlen($data) == 0)
{
show_error($problem);
}
return $data;
}
function show_error($myError)
{
?>
<html>
<body>
<p>Please fix error.</p>
<?php echo $myError; ?>
</body>
</html>
<?php
exit();
}
function removekey($itttkey)
{
	require( "config.php" );
$conn = new mysqli($mysql_host, $mysql_user, $mysql_pass , $mysql_database);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

// sql to delete a record
$sql = "DELETE FROM licensekeys WHERE activationkey='$itttkey'";

if ($conn->query($sql) === TRUE) {
} else {
}

$conn->close();
}
function getdaysfromrow($ittkey)
{
	require( "config.php" );
mysql_connect($mysql_host, $mysql_user, $mysql_pass , $mysql_database); //Создаём и открываем соединение с MySQL
mysql_select_db($mysql_database); //Указываем базу данных для работы
$command = "SELECT * FROM licensekeys WHERE activationkey='$ittkey'"; //Объявлем комманду
$response = mysql_query($command); //Выполняем комманду и получаем ответ
$count = mysql_num_rows($response); //Выводим количество полученных рядков с ответа
$row=mysql_fetch_array($response); //Преобразовываем рядки в массив
if ($count == 1) //Если число рядков равно 1
{

return $row['day'];

}
else if ($count == 0)
{
return "0";
}
else 
{
return "0";
}
}
function validationkey($itkey,$hwidd)
{
	require( "config.php" );
mysql_connect($mysql_host, $mysql_user, $mysql_pass , $mysql_database);
mysql_select_db($mysql_database);
$command = "SELECT * FROM auth WHERE hwid='$hwidd'";
$response = mysql_query($command);
$count = mysql_num_rows($response);
$row=mysql_fetch_array($response);
$days = getdaysfromrow($itkey);
$addtime=Date('d-m-Y', strtotime("+$days days"));
$subscribtiontime = $row['csgo_time'];	
if ($days == 0)
{
die();
}
$globaldayz = $days;
if ($count == 1) //Если число рядков равно 1
{

if ($subscribtiontime == NULL || $subscribtiontime == "0" || strtotime($subscribtiontime) <= strtotime(date("d-m-Y")))
{
$updatereq = mysql_query("UPDATE auth SET csgo_time='$addtime' WHERE hwid='$hwidd'");
mysql_query($updatereq);
}
else if (strtotime($subscribtiontime) > strtotime(date("d-m-Y")))
{
$subtimeeksde = date('d-m-Y', strtotime("$subscribtiontime +$days days")); //date("d-m-Y", strtotime("$subscribtiontime")); // пизц
//$addtimeexits= strtotime("$subtimeeksde +$days days"); //$subscribtiontime 
$updatereqnew = mysql_query("UPDATE auth SET csgo_time='$subtimeeksde' WHERE hwid='$hwidd'");
mysql_query($updatereqnew);
}
}
else if ($count == 0)
{
$insertreq = mysql_query("INSERT INTO `auth` (hwid,csgo_time,idk_time,banned) VALUES ('$hwidd','$addtime','0','no')");
mysql_query($insertreq);
}
removekey($itkey);
}
validationkey($keyuff,$userhwid);
$returnmessage = "Your key activated for $globaldayz days.";
?>