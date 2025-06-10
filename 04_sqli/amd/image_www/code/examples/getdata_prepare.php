<?php
    // getdata_prepare.php
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
    $sql = "SELECT Name, Salary, SSN
            FROM employee
            WHERE eid= ? and password=?";
    if ($stmt = $conn->prepare($sql)) {
        $stmt->bind_param("ss", $eid, $pwd);
        $stmt->execute();
        $stmt->bind_result($name, $salary, $ssn);
        while ($stmt->fetch()) {
            printf("%s %s %s\n", $name, $salary, $ssn);
        }
    }
?>
