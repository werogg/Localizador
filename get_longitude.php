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
    $sql = "select longitude, latitude from itemtracker_locators where secretkey =  '".$_GET["key"]."'";
    // Executem la declaració SQL
    $result = mysql_query($sql);
    // Seleccionem les dades que necessitem de la base de dades
    $row = mysql_fetch_array($result);
    $longitude = $row[0];
    $latitude = $row[1];
    // Enviem una resposta amb la longitud
    echo($longitude);
    // Tanquem la connexió amb la base de dades
    mysql_close($dbconnect);
?>
