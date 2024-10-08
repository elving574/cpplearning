#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <windows.h>
#include <algorithm>
#include <tlhelp32.h>
#include <ctime>

using namespace std;

bool TerminateProcessByID(DWORD processID) {
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, processID);
    if (hProcess != NULL) {
        if (TerminateProcess(hProcess, 0)) {
            cout << "Successfully terminated process with PID:" << processID << endl;
            CloseHandle(hProcess);
            return true;
        } else {
            cerr << "Failed to terminate process with PID: " << processID << endl;
        }
        CloseHandle(hProcess);
    } else {
        cerr << "Failed to open process with PID: " << processID << endl;
    }
    return false;
}

vector<DWORD> GetBrowserProcessIDs() {
    vector<DWORD> processIDs;
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        cerr << "Failed to create process snapshot" << endl;
        return processIDs;
    }
    if (!Process32First(hSnapshot, &pe32)) {
        cerr << "Failed to retrieve first process" << endl;
        CloseHandle(hSnapshot);
        return processIDs;
    }
    do {
        if (strcmp(pe32.szExeFile, "Google Chrome.exe") == 0 ||
            strcmp(pe32.szExeFile, "firefox.exe") == 0 ||
            strcmp(pe32.szExeFile, "msedge.exe") == 0 ||
            strcmp(pe32.szExeFile, "opera.exe") == 0) {
            processIDs.push_back(pe32.th32ProcessID);
        }
    } while (Process32Next(hSnapshot, &pe32));
    CloseHandle(hSnapshot);
    return processIDs;
}

BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam) {
    vector<string>* websites = reinterpret_cast<vector<string>*>(lParam);
    if (websites) {
        DWORD windowPID;
        GetWindowThreadProcessId(hWnd, &windowPID);
        char windowTitle[256];
        GetWindowTextA(hWnd, windowTitle, sizeof(windowTitle));
        string title(windowTitle);
        for (const string& website : *websites) {
            if (title.find(website) != string::npos) {
                PostMessage(hWnd, WM_CLOSE, 0, 0);
                return FALSE; // Stop enumerating windows
            }
        }
    }
    return TRUE;
}

void FindAndCloseWebsites(vector<string>& websites) {
    if (!websites.empty()) {
        EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(&websites));
    }
}

bool TryCloseProgram(const string& correctPassword) {
    string enteredPassword;
    sf::RenderWindow passwordWindow(sf::VideoMode(300, 100), "Enter Password", sf::Style::None);
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return false;
    }
    sf::Text promptText("Enter password:", font, 20);
    promptText.setPosition(20, 20);

    while (passwordWindow.isOpen()) {
        sf::Event event;
        while (passwordWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                passwordWindow.close();
                return false; // User closed the password window without entering password
            }
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128 && event.text.unicode != '\r') {
                    if (event.text.unicode == '\b' && !enteredPassword.empty()) {
                        enteredPassword.pop_back();
                    } else if (enteredPassword.size() < 20) { // Maximum password length
                        enteredPassword += static_cast<char>(event.text.unicode);
                    }
                }
            }
        }

        passwordWindow.clear(sf::Color::White);
        passwordWindow.draw(promptText);
        sf::Text enteredPasswordText(enteredPassword, font, 20);
        enteredPasswordText.setPosition(20, 50);
        passwordWindow.draw(enteredPasswordText);
        passwordWindow.display();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            if (enteredPassword == correctPassword) {
                passwordWindow.close();
                return true; // Password correct, close the program
            } else {
                enteredPassword.clear(); // Clear entered password if wrong
            }
        }
    }
    return false;
}

int main() {
    cout << "Starting to monitor for YouTube in popular browsers..." << endl;

    sf::RenderWindow window(sf::VideoMode(400, 600), "Website blocker");

    vector<string> websites = {"YouTube", "Netflix", "Discord", "Roblox", "kizigames", "a10games"};
    bool blockingEnabled = true;

    // Password setup
    const string correctPassword = "12345"; // Change to your desired password
    string enteredPassword;
    bool passwordEntered = false;
    bool pendingAction = false;
    enum class PendingActionType { None, Add, Clear, Toggle, Delete };
    PendingActionType pendingActionType = PendingActionType::None;
    int deleteIndex = -1;
    time_t lastPasswordEntryTime = time(nullptr);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return EXIT_FAILURE;
    }

    sf::Text inputText("", font);
    inputText.setCharacterSize(24);
    inputText.setFillColor(sf::Color::Black);
    inputText.setPosition(20, 20);

    sf::RectangleShape addButton(sf::Vector2f(100, 40));
    addButton.setFillColor(sf::Color::Green);
    addButton.setPosition(240, 15);
    sf::Text addButtonText("Add", font);
    addButtonText.setCharacterSize(24);
    addButtonText.setFillColor(sf::Color::White);
    addButtonText.setPosition(255, 20);

    sf::RectangleShape clearButton(sf::Vector2f(100, 40));
    clearButton.setFillColor(sf::Color::Red);
    clearButton.setPosition(240, 70);
    sf::Text clearButtonText("Clear", font);
    clearButtonText.setCharacterSize(24);
    clearButtonText.setFillColor(sf::Color::White);
    clearButtonText.setPosition(250, 75);

    sf::RectangleShape toggleButton(sf::Vector2f(100, 40));
    toggleButton.setFillColor(sf::Color::Blue);
    toggleButton.setPosition(240, 125);
    sf::Text toggleButtonText("On/Off", font);
    toggleButtonText.setCharacterSize(24);
    toggleButtonText.setFillColor(sf::Color::White);
    toggleButtonText.setPosition(250, 130);

    sf::Text statusText("Blocking: On", font);
    statusText.setCharacterSize(24);
    statusText.setFillColor(sf::Color::Black);
    statusText.setPosition(20, 80);

    sf::Text passwordPrompt("Enter password:", font);
    passwordPrompt.setCharacterSize(24);
    passwordPrompt.setFillColor(sf::Color::Black);
    passwordPrompt.setPosition(20, 180);

    sf::Text enteredPasswordText("", font);
    enteredPasswordText.setCharacterSize(24);
    enteredPasswordText.setFillColor(sf::Color::Black);
    enteredPasswordText.setPosition(20, 220);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                if (TryCloseProgram(correctPassword)) {
                    window.close(); // Close the program if password is correct
                }
            }
            if (!passwordEntered) {
                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode < 128) {
                        if (event.text.unicode == '\b') {
                            if (!enteredPassword.empty()) {
                                enteredPassword.pop_back();
                                enteredPasswordText.setString(string(enteredPassword.length(), '*'));
                            }
                        } else if (event.text.unicode == '\r') {
                            // Check password
                            if (enteredPassword == correctPassword) {
                                passwordEntered = true;
                                pendingAction = true;
                                enteredPassword.clear();
                                enteredPasswordText.setString("");
                                lastPasswordEntryTime = time(nullptr);
                            } else {
                                enteredPassword.clear();
                                enteredPasswordText.setString("");
                            }
                        } else {
                            enteredPassword += static_cast<char>(event.text.unicode);
                            enteredPasswordText.setString(string(enteredPassword.length(), '*'));
                        }
                    }
                }
            } else {
                // Handle other events when password is entered
                if (event.type == sf::Event::TextEntered) {
                    if (!inputText.getString().isEmpty()) {
                        if (event.text.unicode == '\b') {
                            inputText.setString(inputText.getString().substring(0, inputText.getString().getSize() - 1));
                        } else {
                            inputText.setString(inputText.getString() + static_cast<char>(event.text.unicode));
                        }
                    }
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                        if (addButton.getGlobalBounds().contains(mousePos)) {
                            pendingActionType = PendingActionType::Add;
                            passwordEntered = false;
                            enteredPassword.clear();
                            enteredPasswordText.setString("");
                        }
                        if (clearButton.getGlobalBounds().contains(mousePos)) {
                            pendingActionType = PendingActionType::Clear;
                            passwordEntered = false;
                            enteredPassword.clear();
                            enteredPasswordText.setString("");
                        }
                        if (toggleButton.getGlobalBounds().contains(mousePos)) {
                            pendingActionType = PendingActionType::Toggle;
                            passwordEntered = false;
                            enteredPassword.clear();
                            enteredPasswordText.setString("");
                        }
                        for (size_t i = 0; i < websites.size(); ++i) {
                            sf::Text websiteText(websites[i], font);
                            websiteText.setCharacterSize(24);
                            websiteText.setFillColor(sf::Color::Black);
                            websiteText.setPosition(20, 240 + i * 30);
                            if (websiteText.getGlobalBounds().contains(mousePos)) {
                                pendingActionType = PendingActionType::Delete;
                                deleteIndex = i;
                                passwordEntered = false;
                                enteredPassword.clear();
                                enteredPasswordText.setString("");
                            }
                        }
                    }
                }
            }
        }

        window.clear(sf::Color::White);

        if (!passwordEntered) {
            // Display password input mode
            window.draw(passwordPrompt);
            window.draw(enteredPasswordText);
        } else {
            // Execute pending action
            if (pendingAction) {
                switch (pendingActionType) {
                    case PendingActionType::Add:
                        websites.push_back(inputText.getString().toAnsiString());
                        inputText.setString("");
                        break;
                    case PendingActionType::Clear:
                        websites.clear();
                        break;
                    case PendingActionType::Toggle:
                        blockingEnabled = !blockingEnabled;
                        statusText.setString(blockingEnabled ? "Blocking: On" : "Blocking: Off");
                        break;
                    case PendingActionType::Delete:
                        if (deleteIndex >= 0 && deleteIndex < websites.size()) {
                            websites.erase(websites.begin() + deleteIndex);
                            deleteIndex = -1;
                        }
                        break;
                    case PendingActionType::None:
                        break;
                }
                pendingAction = false;
                pendingActionType = PendingActionType::None;
            }

            // Display website input mode
            window.draw(inputText);
            window.draw(addButton);
            window.draw(addButtonText);
            window.draw(clearButton);
            window.draw(clearButtonText);
            window.draw(toggleButton);
            window.draw(toggleButtonText);
            window.draw(statusText);
            for (size_t i = 0; i < websites.size(); ++i) {
                sf::Text websiteText(websites[i], font);
                websiteText.setCharacterSize(24);
                websiteText.setFillColor(sf::Color::Black);
                websiteText.setPosition(20, 240 + i * 30);
                window.draw(websiteText);
            }
        }

        window.display();

        if (blockingEnabled && passwordEntered && difftime(time(nullptr), lastPasswordEntryTime) <= 60) {
            FindAndCloseWebsites(websites);
        }
    }

    return 0;
}