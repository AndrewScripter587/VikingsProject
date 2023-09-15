#include <cstdlib>
#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
bool IsWindowsVersionOrLater(DWORD majorVersion, DWORD minorVersion) {
    OSVERSIONINFOEX osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    osvi.dwMajorVersion = majorVersion;
    osvi.dwMinorVersion = minorVersion;

    DWORDLONG conditionMask = 0;
    VER_SET_CONDITION(conditionMask, VER_MAJORVERSION, VER_GREATER_EQUAL);
    VER_SET_CONDITION(conditionMask, VER_MINORVERSION, VER_GREATER_EQUAL);

    return VerifyVersionInfo(&osvi, VER_MAJORVERSION | VER_MINORVERSION, conditionMask) != 0;
}

int main() {
    

    int result = system("python --version"); // Try running Python --version

    if (result == 0) {
        std::cout << "Python is installed." << std::endl;
    }
    else {
        std::cerr << "Python is not installed. Please install Python and run the file again." << std::endl;
        std::cout << "Press Enter to exit..." << std::endl;
        std::cin.get(); // Wait for Enter key press
        return 1;
    }
    const char* pythonScript = "pythonsegment.py";

    // Run the Python script using the Python interpreter
    int exitCode = system(("python " + std::string(pythonScript)).c_str());

    if (exitCode == 0) {
        std::cout << "Python script executed successfully." << std::endl;
    }
    else {
        std::cerr << "Error executing Python script." << std::endl;
    }


    // Use _dupenv_s to get the user's desktop folder path
    char* userProfile = nullptr;
    size_t len;
    if (_dupenv_s(&userProfile, &len, "userprofile") == 0 && userProfile != nullptr) {
        // Construct the full path to the batch script on the desktop
        std::string batchScriptPath = userProfile;
        batchScriptPath += "\\Desktop\\vikings.bat"; // Change "vikings.bat" to your batch script's filename

        // Execute the batch script
        int result2 = system(batchScriptPath.c_str());

        if (result2 == 0) {
            std::cout << "Batch script executed successfully!" << std::endl;
        }
        else {
            std::cerr << "Error executing batch script" << std::endl;
        }

        // Free the allocated memory
        free(userProfile);
    }
    else {
        std::cerr << "Error: Could not get the user's desktop folder path." << std::endl;
        return 1;
    }
    // Replace "your_script.py" with the name of your Python script
    return 0;
}
