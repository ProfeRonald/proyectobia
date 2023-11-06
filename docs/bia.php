<?php

$ch = curl_init();

    curl_setopt(
      $ch,
      CURLOPT_URL,
      "https://proyecto-bia-default-rtdb.firebaseio.com/bia.json"
    );
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    //curl_setopt($ch, CURLOPT_POST, 1);
    curl_setopt($ch, CURLOPT_CUSTOMREQUEST, 'PATCH');
    curl_setopt(
      $ch,
      CURLOPT_POSTFIELDS,
      "{\"ServoMotorActivo\":".$_GET['ServoMotorActivo']."}"
    );
    curl_setopt($ch, CURLOPT_ENCODING, "gzip, deflate");
    $headers = [];
    $headers[] = "Accept: application/json";
    $headers[] = "Content-Type: application/json";
    curl_setopt($ch, CURLOPT_HTTPHEADER, $headers);

    $calendario = curl_exec($ch);

    curl_close($ch);

    header("HTTP/1.1 200 OK");
    
    print file_get_contents("https://proyecto-bia-default-rtdb.firebaseio.com/bia/ServoMotorActivo.json");

    die();


?>