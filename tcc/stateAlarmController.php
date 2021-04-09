<?php
// header('Content-Type: application/json');
class stateAlarmController{
    /*
   * Verify current state of the alarm and modify its state, and create a file with the new value 
   * @author  SGV
   * @version 20201111 1.1 initial release
   * @param   <int> 
   * @return  <bool>  true in case of success
   *           OR
   *           <string> with the description of the error
   */
  function newStateOfAlarm(){ 
    // $currentState = getParam('state');   
    $currentState = [ 'teste','vamos ver'];
    return(json_encode(['success' => true , 'content'=> $currentState]));
    
  }



}