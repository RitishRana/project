<?php
/*
*	Name	    :	Ritish
*	Assignment  :	Layout of the start page of Assignment
*	Date	    :	13-June-2015
*/
if(isset($_POST['Sub']))
{
	if($_POST['frm_city']!="" && $_POST['to_city']!="")
	    {	
		$date = new DateTime(date());
		$date->modify('+1 day');
		$str="Location: ci/index.php/redis/search/".$_POST['frm_city']."/".$_POST['to_city']."/".$date->format('d-m-Y');
		header($str);
	    }

}


?>
<html>
<title>Routofy</title>
<head><h2>Assignment</h2></head>
<form method="post">
From City/Source City:
<input type="text" name="frm_city">
Destination City:
<input type="text" name="to_city">
<input type="submit" value="Submit" name="Sub">

</form>
</html>
