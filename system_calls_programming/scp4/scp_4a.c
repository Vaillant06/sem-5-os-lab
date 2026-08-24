
// scp_4a.c

// System Calls Programming IV

#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>

int main() {

    DIR *dir;
    struct dirent *entry;
    struct stat; // use this 
    
    dir = opendir(".");
    // dir = opendir("/home");

    if(dir == NULL) {
        perror("Error opening the directory");
        return 1;

    } else {
        while((entry = readdir(dir)) != NULL) {
            printf("Filename: %s\nType: %u\nSize: %d\n", 
                entry -> d_name, 
                entry -> d_type, 
                entry -> d_reclen
            );       
        }

        closedir(dir);
    }

    return 0;
}