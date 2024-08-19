<?php
    // getdata_encoding.php
    function getDB()
    {
        $dbhost="10.9.0.6";
        $dbuser="seed";
        $dbpass="dees";
        $dbname="sqllab_users";

        // Create a DB connection
        $conn = new mysqli($dbhost, $dbuser, $dbpass, $dbname);
        if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error . "\n");
        }
        return $conn;
    }
    // create a connection
    $conn = getDB();

    $eid = $mysqli->real_escape_string($_GET['EID']);
    $pwd = $mysqli->real_escape_string($_GET['Password'];
    $sql = "SELECT Name, Salary, SSN
            FROM employee
            WHERE eid= '$eid' and password='$pwd'";
?>
