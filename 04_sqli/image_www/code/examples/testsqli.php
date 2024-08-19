<h1>Input Data Here:</h1>
<form action="testsqli.php" method="get">
username: <input type="text" name="username"><br/>
password: <input type="text" name="password"><br/>
          <input type="submit" value="Submit">
</form>
<button onclick="window.location.href='testsqli.php';">Reset</button>

<hr/>
<h1>Check Here:</h1>

<?php
   // original query (before including user params)
   $sqltemplate = "SELECT *
           FROM employee
           WHERE name= '$username' and password='$password'";

   // construct the query
   $username = $_GET['username'];
   $password = $_GET['password'];
   $sql = "SELECT *
           FROM employee
           WHERE name= '$username' and password='$password'";

   printf("username: <b>%s</b> <br/>", $username);
   printf("password: <b>%s</b> <br/>", $password);
   printf("<br/>query string (before): <b>%s</b><br/>", $sqltemplate);
   printf("<br/>query string (after): <b>%s</b><br/>", $sql);

   // -> create a connection
   // -> execute query
   // -> handle results
   // -> close connection
?>
