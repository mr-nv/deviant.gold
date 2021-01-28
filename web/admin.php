<?php
include('validate.php');
if (isset($_GET['generatekeys'])){
	include('admintools.php');
}
?>

<html>
<head>
	<meta charset="UTF-8">
	<html lang="en" >

	<head>
		<meta charset="UTF-8">
		<title>Admin Panel</title>
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
	<div class="container">
		<div class="row">
			<div class="col-lg-3 col-md-2"></div>
			<div class="col-lg-6 col-md-8 login-box">
				<div class="col-lg-12 login-key">
                    <i class="fa fa-key" aria-hidden="true"></i>
                </div>
				<div class="col-lg-12 login-title">ADMIN PANEL</div>
				
				<form action="?generatekeys" method="post">
					<label class="form-control-label">Keys count</label><br /><input type="text" name="keys_count" /><br />
					<label class="form-control-label">Days count</label><br /><input type="text" name="days_count" /><br />
					<label class="form-control-label">Cheat id</label><br /><input type="text" name="cheat_id" /><br />
					<input type="submit"  class="btn btn-outline-primary" value="Generate keyz"></p>
				</form>
			</div>
		</div>
	</div>
</body>
</html>