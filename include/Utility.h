#ifndef Utility_H
#define Utility_H

#include <vector>        // For using the std::vector container to store dynamic arrays
#include <cstdlib>       // For general purpose functions, like rand() and srand()
#include <ctime>         // For time-related functions, such as time() to seed the random number generator
#include <string>        // For using the std::string class to manage strings
#include <iostream>      // For input/output operations
#include <conio.h>       // For console input functions
#include <algorithm>     // For algorithms like std::find to search within containers

using namespace std;

class Utility
{
public:
    static void clearConsole();            // Function to clear the console screen
    static void waitForSpace(const string &message);  // Function to display a message and wait for space key press
};

#endif // Utility_H