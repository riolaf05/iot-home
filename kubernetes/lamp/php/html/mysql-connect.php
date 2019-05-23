<?php
try{
    
    # By Sharon Campbell for Heptio

    # this is a pretty standard MySQL connection script using pdo_mysql
    # http://php.net/manual/en/pdo.construct.php

    # we use environment variables for our MySQL connection
    # the env variables are MYSQL_HOST, MYSQL_USER, and MYSQL_PASSWORD
    # in our example MYSQL_HOST is mysql.default.svc.cluster.local
    # MYSQL_USER is varMyDBUser and MYSQL_PASSWORD is varMyDBPass
    # these env variables are set for our PHP server by Kubernetes when we create the php.yaml file
    # the sensitive data itself is set in a Kubernetes Secret when we create the secrets.yaml file

    # we are using the Sakila sample database https://dev.mysql.com/doc/sakila/en/

    $mysql_host = getenv('MYSQL_HOST');
    $dbh = new pdo( "mysql:host=$mysql_host:3306;dbname=sakila",
                    getenv('MYSQL_USER'),
                    getenv('MYSQL_PASSWORD'),
                    array(PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION));
    $result = $dbh->query("show tables");
    while ($row = $result->fetch(PDO::FETCH_NUM)) {
        echo($row[0]) . "<br />";
    }
    die(json_encode(array('outcome' => true)));
}
catch(PDOException $ex){
    die(json_encode(array('outcome' => false, 'message' => "Unable to connect: $ex")));
}
?>