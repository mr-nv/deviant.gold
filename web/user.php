<?php
if (isset($_GET['useractivate'])){
	include('activatekey.php');
}
?>
<!DOCTYPE html>
<html lang="en" >

<head>
	<meta charset="UTF-8">
	<html lang="en" >

	<head>
		<meta charset="UTF-8">
		<title>User Page</title>
		<meta charset="utf-8">
		<meta http-equiv="X-UA-Compatible" content="IE=edge">
		<!-- Tell the browser to be responsive to screen width -->
		<meta content="width=device-width, initial-scale=1, maximum-scale=1, user-scalable=no" name="viewport">
		<!-- Bootstrap 3.3.6 -->
		<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-beta/css/bootstrap.min.css" integrity="sha384-/Y6pD6FV/Vv2HJnA6t+vslU6fwYXjCFtcEpHbNJ0lyAFsXTsjBbfaDjzALeQsN6M" crossorigin="anonymous">
		<!-- Font Awesome -->
		<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.5.0/css/font-awesome.min.css">

		<link href="https://fonts.googleapis.com/css?family=Roboto" rel="stylesheet"> 

		<link rel='stylesheet prefetch' href='https://cdnjs.cloudflare.com/ajax/libs/twitter-bootstrap/4.0.0-beta/css/bootstrap.min.css'>
		<link rel='stylesheet prefetch' href='https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.5.0/css/font-awesome.min.css'>
		<link rel='stylesheet prefetch' href='https://fonts.googleapis.com/css?family=Roboto'>
		<link rel="stylesheet" href="css/style.css">
	</head>
	<style>
	.hm-gradient {
		background-image: linear-gradient(to top, #f3e7e9 0%, #e3eeff 99%, #e3eeff 100%);
	}
	.darken-grey-text {
		color: #FFF;
	}
	.md-form .prefix~textarea {
		padding-top: 1.6rem; 
	}
</style>
</head>
<body>

	<div class="container mt-4">
		<div class ="text-center darken-grey-text mb-4">
			<h1 class="font-bold mt-4 mb-3 h5">MultiPurpose key activator</h1>
			<a class="btn btn-outline-primary" href="loader.exe" ">Download Loader<i class="fa fa-download pl-2"></i></a>

		</div>
		<div class="login-box">
		<form action="?useractivate" method="post">
			
				<div class="col-lg-12 login-title">Activation</div>
				
			<div class="row ">
				<div class="col-md-6">    
					<div class="md-form">
						<i class="fa fa-key prefix darken-grey-text"></i>
						<label for="form2"  class="darken-grey-text">Key</label>
						<input maxlength="23" type="text" name="key" id="form2" class="form-control">
					</div>
				</div>
				<div class="col-md-6">      
					<div class="md-form">
						<i class="fa fa-lock prefix darken-grey-text"></i>
						<label for="form3" class="darken-grey-text">HardWare ID</label>
						<input maxlength="32" name="hwid" type="text" id="form3" class="form-control">
					</div>

				</div>                
			</div>
			<div class="text-center darken-grey-text mb-4">
				<div class="error"><?= $returnmessage?></div>
				<input  name="sub" class="btn btn-outline-primary" type="submit"  value="Validate"></p>
			</div>
			</form>
		</div>
		   
	</div>
	<script src ='https://cdnjs.cloudflare.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>
	<script src ='https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.11.0/umd/popper.min.js'></script>
	<script src ='https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-beta/js/bootstrap.min.js'></script>
	<script src ='https://cdnjs.cloudflare.com/ajax/libs/mdbootstrap/4.4.1/js/mdb.min.js'></script>
</body>
</html>
