#include <unistd.h>
#include <dirent.h>
#include <iostream>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <cstring>

using namespace std;

void remove_directory(const char* path) {
    DIR* dir = opendir(path);
    if (!dir) 
    {
        // Path is a file, remove it
        unlink(path);
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }

        char child_path[1024];
        snprintf(child_path, sizeof(child_path), "%s/%s", path, entry->d_name);
        remove_directory(child_path);
    }
    closedir(dir);
    rmdir(path);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Usage: rm-r <directory>" << endl;
        return 1;
    }

    remove_directory(argv[1]);
    return 0;
}