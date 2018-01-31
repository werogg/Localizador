<?php
    // Peparació de les variables per la conexió a la base de dades
    $dbusername = "fbpmf";  // usuari
    $dbpassword = "Werominecon2017";  // contrasenya
    $server = "193.70.86.126"; // servidor
    $My_db = "itemtracker"; // nom de la base de dades
    // Connexió a la base de dades
    $dbconnect = mysql_pconnect($server, $dbusername, $dbpassword);
    $dbselect = mysql_select_db("itemtracker",$dbconnect);
    // Preparació de la declaració SQL
    $sql = "update itemtracker_locators set longitude = '".$_GET["longitude"]."', latitude = '".$_GET["latitude"]."' where secretkey = '".$_GET["key"]."'";
    // Executem la declaració SQL
    mysql_query($sql);
?>
