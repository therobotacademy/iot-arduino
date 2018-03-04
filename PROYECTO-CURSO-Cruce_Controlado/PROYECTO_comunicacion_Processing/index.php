<?php
if($_GET["action"] !="0")
        {
        $myfile = fopen("trafico.txt", "w") or die("Unable to open file!");
        if($_GET["action"] =="punta") {
                fwrite($myfile,"1");
                }
                elseif($_GET["action" ] =="valle"){
                fwrite($myfile,"0");
                }
        fclose($myfile);
        }
?>

<html>
<head>
<title>Interaction Arduino - Processing - web server</title>
</head>

<body>
<h1>Cambia las condiciones de regulacion</h1>
<form method= "get">
<input type="radio" name= "action" value="valle" checked>valle
<br>
<input type="radio" name="action" value="punta" >punta
<br>
<input type="submit">
</form>
</body>

</html>
