<?php
   //getdata.php
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

   $eid = $_GET['EID'];
   $pwd = $_GET['Password'];

   // create a connection
   $conn = getDB();
   $sql = "SELECT Name, Salary, SSN
           FROM employee
           WHERE eid= '$eid' and password='$pwd'";

   $result = $conn->query($sql);
   if ($result) {
       // Print out the result
       while ($row = $result->fetch_assoc()) {
           printf(
               "Name: %s -- Salary: %s -- SSN: %s\n",
               $row["Name"],
               $row["Salary"],
               $row['SSN']
        );
       }
       $result->free();
   }
   $conn->close();
?>
