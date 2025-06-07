#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <atomic>
#include <csignal>

#ifdef _WIN32
#include <windows.h>
void setConsoleTitle(const wchar_t* title) { SetConsoleTitleW(title); }
void clearScreen() { std::system("cls"); }
void flashTrollMessagesInfinite(std::atomic<bool>& keepFlashing, const char* msg1, const char* msg2, const char* msg3) {
    // Windows console color codes (foreground/background)
    const char* colors[] = {
        "1A", "2B", "3C", "4D", "5E", "6F", "A1", "B2", "C3", "D4", "E5", "F6"
    };
    int numColors = sizeof(colors) / sizeof(colors[0]);
    int i = 0;
    while (keepFlashing) {
        std::string cmd = "color ";
        cmd += colors[i % numColors];
        std::system(cmd.c_str());
        clearScreen();
        std::cout << std::endl << msg1 << std::endl;
        std::cout << msg2 << std::endl;
        std::cout << msg3 << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(350));
        i++;
    }
    // Restore original color
    std::system("color 07");
    clearScreen();
}
#else
void setConsoleTitle(const char* title) { std::cout << "\033]0;" << title << "\007"; }
void clearScreen() { std::cout << "\033[2J\033[1;1H"; }
void flashTrollMessagesInfinite(std::atomic<bool>& keepFlashing, const char* msg1, const char* msg2, const char* msg3) {
    // ANSI escape codes for various foreground/background color pairs
    const char* colors[] = {
        "\033[1;31;43m", // bright red on yellow
        "\033[1;32;45m", // bright green on magenta
        "\033[1;33;44m", // bright yellow on blue
        "\033[1;34;41m", // bright blue on red
        "\033[1;35;42m", // bright magenta on green
        "\033[1;36;47m", // bright cyan on white
        "\033[1;37;46m", // bright white on cyan
        "\033[1;30;43m", // black on yellow
        "\033[1;31;47m", // bright red on white
        "\033[1;33;45m", // bright yellow on magenta
        "\033[1;32;44m", // bright green on blue
        "\033[1;36;41m", // bright cyan on red
    };
    int numColors = sizeof(colors) / sizeof(colors[0]);
    int i = 0;
    while (keepFlashing) {
        clearScreen();
        std::cout << colors[i % numColors]
                  << std::endl << msg1 << std::endl
                  << msg2 << std::endl
                  << msg3 << std::endl
                  << "\033[0m" << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(350));
        i++;
    }
    // Reset
    std::cout << "\033[0m";
    clearScreen();
}
#endif

const char* banner = "###### - FREE STEAM CODES - ######";
const char* prompt = "Please type 'start' to start the key generator: ";

const char* steam_codes[] = {
    "6BKB7-6H855-84IRE",
    "BHM58-N7R6R-G9I4K",
    "5P967-996SK-456B4",
    "1EHCG-56R5F-KE71O",
    "87661-D6H6O-3IOT3",
    "BT66I-5733I-L1CSN",
    "4EDGF-GS7LG-48L38",
    "JF7QD-88HJ2-61NBQ",
    "K838Q-CP7H7-66444",
    "S8LB5-75FRN-OR9CF"
};

const char* fake_success =
    "Congratulations! We gained access to the Steam servers and your generated Steam code is: ";

const char* troll_msg1 = "Just Kidding! You are clearly a fucking retard!";
const char* troll_msg2 = "Things aren't just fucking handed to you, dumb bitch! XDDDDDDDD";
const char* troll_msg3 = "Use Indeed.com and look for a fucking job, stupid neet!";

void fakeLoadingBar() {
    std::string bar = "Generating a Steam code - [";
    std::cout << bar;
    for (int i = 0; i < 30; ++i) {
        std::cout << "=" << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    std::cout << ">] 100%" << std::endl;
}

std::atomic<bool> keepFlashing(true);

void handleSignal(int signal) {
    keepFlashing = false;
}

int main() {
#ifdef _WIN32
    setConsoleTitle(L"Free Steam Code Generator");
#else
    setConsoleTitle("Free Steam Code Generator");
#endif
    clearScreen();
    std::cout << banner << std::endl << std::endl;

    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);

    if (input != "start") {
        std::cout << "Aborted." << std::endl;
        return 0;
    }

    clearScreen();

    // Simulate code generation animation
    fakeLoadingBar();

    // Pick a code
    std::srand(std::time(nullptr));
    int code_index = std::rand() % (sizeof(steam_codes)/sizeof(steam_codes[0]));

    std::cout << std::endl << fake_success << steam_codes[code_index] << std::endl << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(800));

    std::cout << "Now flashing the troll messages! (Press Ctrl+C to stop and exit)\n";

#ifndef _WIN32
    std::signal(SIGINT, handleSignal);
#endif

    // Start flashing messages infinitely
    std::thread flasher(flashTrollMessagesInfinite, std::ref(keepFlashing),
                        troll_msg1, troll_msg2, troll_msg3);

#ifdef _WIN32
    // On Windows, wait for Ctrl+C or Enter from user
    while (keepFlashing) {
        if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
            keepFlashing = false;
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
#else
    // On Linux/macOS, wait for Ctrl+C signal
    while (keepFlashing) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
#endif

    if (flasher.joinable()) flasher.join();

    std::cout << std::endl << "Press Enter to exit...";
    std::getline(std::cin, input);
    return 0;
}