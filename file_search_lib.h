// File: file_search_lib.h (Static library for file search)

#ifndef FILE_SEARCH_LIB_H
#define FILE_SEARCH_LIB_H

#include <stdio.h>
#include <pthread.h>

// Function for searching files in a directory and its subdirectories by name
// Parameters:
//   - root_path: the path to the root directory to start the search from
//   - file_name: the name of the file we are looking for
//   - stop_search: a pointer to the variable used to stop the search
//   - mutex: a pointer to the mutex for synchronization
void search_files(const char* root_path, const char* file_name, int* stop_search, pthread_mutex_t* mutex);

#endif