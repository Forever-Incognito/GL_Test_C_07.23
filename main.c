#include <stdio.h>
#include <pthread.h>
#include "file_search_lib.h"

#define MAX_THREADS 8

// Структура для передачі аргументів у потік
struct ThreadArgs {
    const char* root_path;
    const char* file_name;
    int* stop_search;
    pthread_mutex_t* mutex;
    pthread_cond_t* cond;
};

// Функція виконання потоку
void* thread_function(void* arg) {
    struct ThreadArgs* args = (struct ThreadArgs*)arg;
    search_files(args->root_path, args->file_name, args->stop_search, args->mutex);
    pthread_cond_broadcast(args->cond); // Повідомлення всіх потоків про завершення пошуку
    return NULL;
}

int main() {
    const char* root_path = "/"; // Задайте кореневу директорію для пошуку файлів
    const char* file_name = "example.txt"; // Задайте назву файлу, який потрібно знайти

    // Створення потоків та ініціалізація mutex та cond
    pthread_t threads[MAX_THREADS];
    struct ThreadArgs args[MAX_THREADS];
    int stop_search = 0;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

    for (int i = 0; i < MAX_THREADS; ++i) {
        args[i].root_path = root_path;
        args[i].file_name = file_name;
        args[i].stop_search = &stop_search;
        args[i].mutex = &mutex;
        args[i].cond = &cond;
        pthread_create(&threads[i], NULL, thread_function, &args[i]);
    }

    // Очікуємо завершення потоків
    for (int i = 0; i < MAX_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}