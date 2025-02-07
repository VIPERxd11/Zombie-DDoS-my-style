<?php
// File paths
define('USER_FILE', 'users.json');
define('BOT_FILE', 'bots.json');
define('LOG_FILE', 'command_log.json');

// Helper function to read JSON file and decode it
function read_json($file) {
    if (!file_exists($file)) {
        return [];
    }
    $content = file_get_contents($file);
    return json_decode($content, true);
}

// Helper function to write to JSON file
function write_json($file, $data) {
    file_put_contents($file, json_encode($data, JSON_PRETTY_PRINT));
}

// User Authentication (using password hashing)
function authenticate($username, $password) {
    $users = read_json(USER_FILE);
    foreach ($users as $user) {
        if ($user['username'] === $username && password_verify($password, $user['password'])) {
            return $user;
        }
    }
    return null;
}

// Get Bot Data
function getBotsData() {
    return read_json(BOT_FILE);
}

// Update Bot Status
function updateBotStatus($bot_id, $status, $last_command = null) {
    $bots = getBotsData();
    foreach ($bots as &$bot) {
        if ($bot['bot_id'] === $bot_id) {
            $bot['status'] = $status;
            $bot['last_active'] = date('Y-m-d H:i:s');
            if ($last_command) {
                $bot['last_command'] = $last_command;
            }
        }
    }
    write_json(BOT_FILE, $bots);
}

// Log Command
function logCommand($bot_id, $command, $result) {
    $logs = read_json(LOG_FILE);
    $logs[] = [
        'bot_id' => $bot_id,
        'command' => $command,
        'result' => $result,
        'timestamp' => date('Y-m-d H:i:s')
    ];
    write_json(LOG_FILE, $logs);
}
?>
