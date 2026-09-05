
// System Calls Programming IV 

// scp_4a.c

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void list_dir(const char *path) {

    DIR *dir = opendir(path);

    if (dir == NULL) {
        perror("opendir");
        return;
    }

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {

        // Ignore "." and ".."
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        printf("%s/%s\n", path, entry->d_name);

        // Construct complete path
        char new_path[1024];

        snprintf(new_path, sizeof(new_path),
                 "%s/%s", path, entry->d_name);

        struct stat st;

        if (stat(new_path, &st) == -1) {
            perror("stat");
            continue;
        }

        // If it's a directory, recursively enter it
        if (S_ISDIR(st.st_mode)) {
            list_dir(new_path);
        }
    }

    closedir(dir);
}

int main() {

    list_dir(".");

    return 0;
}