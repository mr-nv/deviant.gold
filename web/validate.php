<?php
session_start();
$errorMsg = "";
$validUser = $_SESSION["login"] === true;
if(!$validUser)
die();
?>
