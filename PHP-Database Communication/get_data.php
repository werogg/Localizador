<?php
    // Prepare variables for database connection
    $dbusername = "fbpmf";  // enter database username, I used "arduino" in step 2.2
    $dbpassword = "Werominecon2017";  // enter database password, I used "arduinotest" in step 2.2
    $server = "193.70.86.126"; // IMPORTANT: if you are using XAMPP enter "localhost", but if you have an online website enter its address, ie."www.yourwebsite.com"
    $My_db = "itemtracker";
    // Connect to your database
    $dbconnect = mysql_pconnect($server, $dbusername, $dbpassword);
    $dbselect = mysql_select_db("itemtracker",$dbconnect);
    // Prepare the SQL statement
    $sql = "select longitude, latitude from itemtracker_locators where secretkey =  '".$_GET["key"]."'";
    // Execute SQL statement
    $result = mysql_query($sql);
	$row = mysql_fetch_array($result);
	$longitude = $row[0];
	$latitude = $row[1];
	print (json_encode($latitude));
	print(json_encode($longitude));
	
	mysql_close($dbconnect);
	
	if($resultset=getSQLResultSet("select longitude, latitude from itemtracker_locators where secretkey =  '".$_GET["key"]."'")){
	while ($row = $resultset->fetch_array(MYSQLI_NUM)){
		echo json_encode($row);
	}
	
	mysql_close($dbconnect);
}
?>