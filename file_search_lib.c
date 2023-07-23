#include "file_search_lib.h"
#include <dirent.h>
#include <string.h>

// Recursive function for traversing directories and searching for files by name
static void search_files_recursive(const char* dir_path, const char* file_name, int* stop_search, pthread_mutex_t* mutex) {
    DIR* dir = opendir(dir_path);
    if (dir == NULL) {
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        // Skip the "." and ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Form the full path to the current element
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);

        pthread_mutex_lock(mutex); // Lock the mutex before accessing stop_search
        if (*stop_search == 1) {
            pthread_mutex_unlock(mutex); // Unlock the mutex before breaking
            break;
        }
        pthread_mutex_unlock(mutex); // Unlock the mutex after checking stop_search

        // If the desired file is found, we take the necessary actions and stop the search
        if (strcmp(entry->d_name, file_name) == 0) {
            pthread_mutex_lock(mutex); // Lock the mutex before accessing stop_search
            *stop_search = 1;
            pthread_mutex_unlock(mutex); // Unlock the mutex after updating stop_search

            printf("File found: %s\n", full_path);
            break;
        }

#ifdef linux
        // If a subdirectory is found, we recursively search in it (only on Linux)
        if (entry->d_type == DT_DIR) {
            search_files_recursive(full_path, file_name, stop_search, mutex);
        }
#endif
    }

    closedir(dir);
}

void search_files(const char* root_path, const char* file_name, int* stop_search, pthread_mutex_t* mutex) {
    search_files_recursive(root_path, file_name, stop_search, mutex);
}