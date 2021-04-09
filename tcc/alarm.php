<?php
// header('Content-Type: application/json');
// require'holidayDayController.php';
// require'stateAlarmController.php';
// $stateAlarmWk = new stateAlarmController();
// exit($stateAlarmWk);
  // 1 check if it is a holiday

?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <link rel="stylesheet" href="stylebtn.css">
</head>
<body>
    <!-- SGV 20201201 Reports the alarm status -->
    <div id='alarm-status'> </div>
    <!-- SGV 20201201 Btn alarm for mode on or off  -->
    <div id='content-btn'>
    <div id="toggles">
        <input type="checkbox" name="checkbox1" id="checkbox1" class="ios-toggle" checked/>
        <label for="checkbox1" class="checkbox-label" data-off="off" data-on="on"></label>
    </div>
    <script src="jquery-3.5.1.min.js"></script>
    <script src="jquery-ui-1.12.1.custom/jquery-ui.js"></script>
   
    <script>
        

        // // SGV 20201208 Show statu of btn
        $('#checkbox1').on('click', function(){
            var stateAlarm = $('#checkbox1')[0].checked;
        });


    </script>
</body>
</html>