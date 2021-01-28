<?php
    $key = '48160653375770156294656980818014'; // 32 bytes
    $iv  = '9727089038717736'; // 16 bytes
    $method = 'aes-256-cfb';
   // Checking if there is a GET request.
    if (isset($_GET['hwid']) && isset($_GET['cheat'])){
require_once "config.php";
mysql_connect($mysql_host, $mysql_user, $mysql_pass , $mysql_database); //Создаём и открываем соединение с MySQL
mysql_select_db($mysql_database); //Указываем базу данных для работы
$auth =  $_GET['hwid'];
$cheat = $_GET['cheat'];
$command = "SELECT * FROM auth WHERE  hwid='$auth'"; //Объявлем комманду
$response = mysql_query($command); //Выполняем комманду и получаем ответ
$count = mysql_num_rows($response); //Выводим количество полученных рядков с ответа
$row=mysql_fetch_array($response); //Преобразовываем рядки в массив

$output; //Переменная, в которую будем добавлять информацию

if ($count == 1) //Если число рядков равно 1
{
$today = date("d-m-Y");
if ($cheat == "1")
$end = strtotime($row['csgo_time']);
else if ($cheat == "2") 
$end = strtotime($row['idk_time']); 
$userdate = date("d-m-Y", $end); 
$todayend = strtotime($today);
$userdateend = strtotime($userdate);

if ($row['banned'] == "yes")
{
	$output  .= base64_encode( openssl_encrypt ('user-active-banned', $method, $key, true, $iv)); //Добавляем к переменной значение license=0
}
else
{
if ($userdateend > $todayend)
{
$output  .= base64_encode( openssl_encrypt ('user-active-true', $method, $key, true, $iv)); //Добавляем к переменной значение license=0
}
else
	$output  .=base64_encode( openssl_encrypt ('user-active-false', $method, $key, true, $iv)); //Добавляем к переменной значение license=0
}
}
else if ($count == 0) //Тогда если число рядков равно 0
{
$output  .=base64_encode( openssl_encrypt ('user-active-false', $method, $key, true, $iv)); //Добавляем к переменной значение license=0
}
echo $output;

	}
?>
