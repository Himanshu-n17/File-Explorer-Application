#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

string currentPath;

void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

string getInput(const string& prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

void listFiles() {
    cout << "\n--- Contents of: " << currentPath << " ---\n\n";

    DIR* dir = opendir(currentPath.c_str());
    if (dir == nullptr) {
        cerr << "Error: Cannot open directory.\n";
        pauseScreen();
        return;
    }

    struct dirent* entry;
    vector<string> directories;
    vector<string> files;

    while ((entry = readdir(dir)) != nullptr) {
        string name = entry->d_name;
        if (name == "." || name == "..") continue;

        string fullPath = currentPath + "/" + name;
        struct stat info;

        if (stat(fullPath.c_str(), &info) == 0) {
            if (S_ISDIR(info.st_mode)) {
                directories.push_back(name);
            } else {
                files.push_back(name);
            }
        }
    }
    closedir(dir);

    sort(directories.begin(), directories.end());
    sort(files.begin(), files.end());

    cout << "Directories:\n";
    for (const auto& dir : directories) {
        cout << "  [DIR]  " << dir << "\n";
    }

    cout << "\nFiles:\n";
    for (const auto& file : files) {
        cout << "  [FILE] " << file << "\n";
    }

    cout << "\nTotal: " << directories.size() << " directories, "
         << files.size() << " files\n";
    pauseScreen();
}

void changeDirectory() {
    string newPath = getInput("\nEnter directory path: ");

    if (newPath.empty()) {
        cout << "Invalid path.\n";
        pauseScreen();
        return;
    }

    string targetPath;
    if (newPath[0] == '/') {
        targetPath = newPath;
    } else {
        targetPath = currentPath + "/" + newPath;
    }

    struct stat info;
    if (stat(targetPath.c_str(), &info) == 0 && S_ISDIR(info.st_mode)) {
        currentPath = targetPath;
        cout << "Changed to: " << currentPath << "\n";
    } else {
        cout << "Error: Invalid directory path.\n";
    }
    pauseScreen();
}

void navigateUp() {
    if (currentPath == "/") {
        cout << "\nAlready at root directory.\n";
        pauseScreen();
        return;
    }

    size_t lastSlash = currentPath.find_last_of('/');
    if (lastSlash == 0) {
        currentPath = "/";
    } else if (lastSlash != string::npos) {
        currentPath = currentPath.substr(0, lastSlash);
    }

    cout << "\nNavigated to: " << currentPath << "\n";
    pauseScreen();
}

void goToHome() {
    const char* homeDir = getenv("HOME");
    if (homeDir != nullptr) {
        currentPath = homeDir;
        cout << "\nNavigated to home: " << currentPath << "\n";
    } else {
        cout << "\nError: Cannot determine home directory.\n";
    }
    pauseScreen();
}

void createFile() {
    string filename = getInput("\nEnter file name: ");

    if (filename.empty()) {
        cout << "Invalid filename.\n";
        pauseScreen();
        return;
    }

    string fullPath = currentPath + "/" + filename;

    ofstream file(fullPath);
    if (file.is_open()) {
        file.close();
        cout << "File created successfully: " << filename << "\n";
    } else {
        cout << "Error: Cannot create file.\n";
    }
    pauseScreen();
}

void createDirectory() {
    string dirname = getInput("\nEnter directory name: ");

    if (dirname.empty()) {
        cout << "Invalid directory name.\n";
        pauseScreen();
        return;
    }

    string fullPath = currentPath + "/" + dirname;

    if (mkdir(fullPath.c_str(), 0755) == 0) {
        cout << "Directory created successfully: " << dirname << "\n";
    } else {
        cout << "Error: Cannot create directory.\n";
    }
    pauseScreen();
}

void deleteFileOrDirectory() {
    string name = getInput("\nEnter file/directory name to delete: ");

    if (name.empty()) {
        cout << "Invalid name.\n";
        pauseScreen();
        return;
    }

    string fullPath = currentPath + "/" + name;

    cout << "Are you sure you want to delete '" << name << "'? (y/n): ";
    char confirm;
    cin >> confirm;
    cin.ignore();

    if (confirm != 'y' && confirm != 'Y') {
        cout << "Deletion cancelled.\n";
        pauseScreen();
        return;
    }

    struct stat info;
    if (stat(fullPath.c_str(), &info) == 0) {
        if (S_ISDIR(info.st_mode)) {
            if (rmdir(fullPath.c_str()) == 0) {
                cout << "Directory deleted successfully.\n";
            } else {
                cout << "Error: Cannot delete directory (may not be empty).\n";
            }
        } else {
            if (remove(fullPath.c_str()) == 0) {
                cout << "File deleted successfully.\n";
            } else {
                cout << "Error: Cannot delete file.\n";
            }
        }
    } else {
        cout << "Error: File/Directory not found.\n";
    }
    pauseScreen();
}

void copyFile() {
    string source = getInput("\nEnter source file name: ");
    string dest = getInput("Enter destination file name: ");

    if (source.empty() || dest.empty()) {
        cout << "Invalid file names.\n";
        pauseScreen();
        return;
    }

    string sourcePath = currentPath + "/" + source;
    string destPath = currentPath + "/" + dest;

    ifstream sourceFile(sourcePath, ios::binary);
    if (!sourceFile.is_open()) {
        cout << "Error: Cannot open source file.\n";
        pauseScreen();
        return;
    }

    ofstream destFile(destPath, ios::binary);
    if (!destFile.is_open()) {
        cout << "Error: Cannot create destination file.\n";
        sourceFile.close();
        pauseScreen();
        return;
    }

    destFile << sourceFile.rdbuf();
    sourceFile.close();
    destFile.close();

    cout << "File copied successfully.\n";
    pauseScreen();
}

void moveFile() {
    string source = getInput("\nEnter source file name: ");
    string dest = getInput("Enter destination file name: ");

    if (source.empty() || dest.empty()) {
        cout << "Invalid file names.\n";
        pauseScreen();
        return;
    }

    string sourcePath = currentPath + "/" + source;
    string destPath = currentPath + "/" + dest;

    if (rename(sourcePath.c_str(), destPath.c_str()) == 0) {
        cout << "File moved/renamed successfully.\n";
    } else {
        cout << "Error: Cannot move/rename file.\n";
    }
    pauseScreen();
}

void searchFiles() {
    string searchTerm = getInput("\nEnter search term: ");

    if (searchTerm.empty()) {
        cout << "Invalid search term.\n";
        pauseScreen();
        return;
    }

    cout << "\nSearching for files containing '" << searchTerm << "'...\n\n";

    DIR* dir = opendir(currentPath.c_str());
    if (dir == nullptr) {
        cerr << "Error: Cannot open directory.\n";
        pauseScreen();
        return;
    }

    struct dirent* entry;
    vector<string> matches;

    while ((entry = readdir(dir)) != nullptr) {
        string name = entry->d_name;
        if (name == "." || name == "..") continue;

        if (name.find(searchTerm) != string::npos) {
            matches.push_back(name);
        }
    }
    closedir(dir);

    if (matches.empty()) {
        cout << "No files found matching '" << searchTerm << "'.\n";
    } else {
        cout << "Found " << matches.size() << " match(es):\n";
        for (const auto& match : matches) {
            cout << "  - " << match << "\n";
        }
    }
    pauseScreen();
}

void changePermissions() {
    string filename = getInput("\nEnter file/directory name: ");

    if (filename.empty()) {
        cout << "Invalid name.\n";
        pauseScreen();
        return;
    }

    string fullPath = currentPath + "/" + filename;

    struct stat info;
    if (stat(fullPath.c_str(), &info) != 0) {
        cout << "Error: File/Directory not found.\n";
        pauseScreen();
        return;
    }

    string permStr = getInput("Enter permissions in octal format (e.g., 755): ");

    try {
        int perm = stoi(permStr, nullptr, 8);

        if (chmod(fullPath.c_str(), perm) == 0) {
            cout << "Permissions changed successfully.\n";
        } else {
            cout << "Error: Cannot change permissions.\n";
        }
    } catch (...) {
        cout << "Error: Invalid permission format.\n";
    }
    pauseScreen();
}

void displayPermissions() {
    string filename = getInput("\nEnter file/directory name: ");

    if (filename.empty()) {
        cout << "Invalid name.\n";
        pauseScreen();
        return;
    }

    string fullPath = currentPath + "/" + filename;

    struct stat info;
    if (stat(fullPath.c_str(), &info) != 0) {
        cout << "Error: File/Directory not found.\n";
        pauseScreen();
        return;
    }

    cout << "\nPermissions for: " << filename << "\n";
    cout << "Octal: " << oct << (info.st_mode & 0777) << dec << "\n";
    cout << "String: ";
    cout << (S_ISDIR(info.st_mode) ? "d" : "-");
    cout << ((info.st_mode & S_IRUSR) ? "r" : "-");
    cout << ((info.st_mode & S_IWUSR) ? "w" : "-");
    cout << ((info.st_mode & S_IXUSR) ? "x" : "-");
    cout << ((info.st_mode & S_IRGRP) ? "r" : "-");
    cout << ((info.st_mode & S_IWGRP) ? "w" : "-");
    cout << ((info.st_mode & S_IXGRP) ? "x" : "-");
    cout << ((info.st_mode & S_IROTH) ? "r" : "-");
    cout << ((info.st_mode & S_IWOTH) ? "w" : "-");
    cout << ((info.st_mode & S_IXOTH) ? "x" : "-");
    cout << "\n";
    pauseScreen();
}

void displayMenu() {
    clearScreen();
    cout << "========================================\n";
    cout << "    LINUX FILE EXPLORER APPLICATION    \n";
    cout << "========================================\n";
    cout << "Current Directory: " << currentPath << "\n";
    cout << "========================================\n\n";
    cout << "File Operations:\n";
    cout << "  1. List files and directories\n";
    cout << "  2. Change directory\n";
    cout << "  3. Navigate to parent directory\n";
    cout << "  4. Go to home directory\n\n";
    cout << "File Manipulation:\n";
    cout << "  5. Create new file\n";
    cout << "  6. Create new directory\n";
    cout << "  7. Delete file/directory\n";
    cout << "  8. Copy file\n";
    cout << "  9. Move/Rename file\n\n";
    cout << "Search:\n";
    cout << "  10. Search files\n\n";
    cout << "Permissions:\n";
    cout << "  11. Change permissions\n";
    cout << "  12. Display permissions\n\n";
    cout << "  0. Exit\n";
    cout << "========================================\n";
}

int main() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != nullptr) {
        currentPath = string(cwd);
    } else {
        currentPath = "/";
    }

    int choice;

    while (true) {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                listFiles();
                break;
            case 2:
                changeDirectory();
                break;
            case 3:
                navigateUp();
                break;
            case 4:
                goToHome();
                break;
            case 5:
                createFile();
                break;
            case 6:
                createDirectory();
                break;
            case 7:
                deleteFileOrDirectory();
                break;
            case 8:
                copyFile();
                break;
            case 9:
                moveFile();
                break;
            case 10:
                searchFiles();
                break;
            case 11:
                changePermissions();
                break;
            case 12:
                displayPermissions();
                break;
            case 0:
                cout << "\nExiting File Explorer. Goodbye!\n";
                return 0;
            default:
                cout << "\nInvalid choice. Please try again.\n";
                pauseScreen();
        }
    }

    return 0;
}
