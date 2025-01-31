#include <Utility.h>    // Include the header for the Utility class, which provides utility functions for console management

// Function to clear the console screen based on the operating system
void Utility::clearConsole()
{
    // Platform-specific implementation to clear the console screen
    #ifdef _WIN32
        system("cls"); // For Windows OS, use the 'cls' command to clear the screen
    #else
        system("clear"); // For Linux and macOS, use the 'clear' command
    #endif
}

// Function to display a message and wait for the user to press the SPACE key
void Utility::waitForSpace(const string &message)
{
    cout << message << " [Press SPACE to continue]\n";  // Print the message and prompt user to press space
    while (true)
    {
        // Check if the user pressed the spacebar
        if (_getch() == ' ')  // _getch() captures key press (works on Windows, might need alternatives for other platforms)
            break; // Break the loop when the spacebar is pressed
    }
}