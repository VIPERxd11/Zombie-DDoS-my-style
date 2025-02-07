<?php
session_start();
require_once 'functions.php';

if (!isset($_SESSION['user'])) {
    header('Location: login.php');
    exit();
}

$user = $_SESSION['user'];
$bots = getBotsData();
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Bot Command Center</title>
</head>
<body>
    <h1>Welcome, <?php echo htmlspecialchars($user['username']); ?></h1>
    <h2>Bot Control Panel</h2>
    
    <h3>Active Bots</h3>
    <table border="1">
        <thead>
            <tr>
                <th>Bot ID</th>
                <th>Status</th>
                <th>Last Active</th>
                <th>Last Command</th>
                <th>Actions</th>
            </tr>
        </thead>
        <tbody>
            <?php foreach ($bots as $bot): ?>
            <tr>
                <td><?php echo htmlspecialchars($bot['bot_id']); ?></td>
                <td><?php echo htmlspecialchars($bot['status']); ?></td>
                <td><?php echo htmlspecialchars($bot['last_active']); ?></td>
                <td><?php echo htmlspecialchars($bot['last_command']); ?></td>
                <td>
                    <form action="send_command.php" method="POST">
                        <input type="hidden" name="bot_id" value="<?php echo htmlspecialchars($bot['bot_id']); ?>">
                        <button type="submit" name="command" value="attack">Attack</button>
                        <button type="submit" name="command" value="stop">Stop</button>
                    </form>
                </td>
            </tr>
            <?php endforeach; ?>
        </tbody>
    </table>
    
    <a href="logout.php">Logout</a>
</body>
</html>
