<?php
include('validate.php');
$keyscount = htmlspecialchars($_POST["keys_count"]);
$dayscount = htmlspecialchars($_POST["days_count"]);
$cheatid = htmlspecialchars($_POST["cheat_id"]);
$keyscount = check_input($_POST["keys_count"], "Input Keys count!");
$dayscount = check_input($_POST["days_count"], "Input days count!");
$cheatid = check_input($_POST["cheat_id"], "Input cheat id!");
function generate_key_string() {
$tokens = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789';
$segment_chars = 5;
$num_segments = 4;
$key_string = '';
for ($i = 0; $i < $num_segments; $i++) {
$segment = '';
for ($j = 0; $j < $segment_chars; $j++) {
$segment .= $tokens[rand(0, 35)];
}
$key_string .= $segment;
if ($i < ($num_segments - 1)) {
$key_string .= '-';
}
}
return $key_string;
}
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
function addkeystomysql($countreq,$days,$cheat)
{
require_once "config.php";
try {
    $conn = new PDO("mysql:host=$mysql_host;dbname=$mysql_database", $mysql_user, $mysql_pass);
    $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
echo nl2br("Your keyz: \r\n", false);
for ($i = 0; ; ) {
    if ($i == $countreq) {

        break;
    }
$key = generate_key_string();
    $sql = "INSERT INTO licensekeys (activationkey, day, cheat)
    VALUES ('$key', '$days', '$cheat')";
    $conn->exec($sql);
echo nl2br("$key\r\n", false);
    $i++;
}
    }
catch(PDOException $e)
    {
    echo $sql . "<br>" . $e->getMessage();
    }
$conn = null;

}
addkeystomysql($keyscount,$dayscount,$cheatid);
?>