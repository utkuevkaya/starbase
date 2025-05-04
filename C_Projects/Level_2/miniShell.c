#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CMD_LEN 1024
#define MAX_ARGS 64

int main() {
    char input[MAX_CMD_LEN];
    char *args[MAX_ARGS];
    
    while (1) {
        printf("myshell> ");
        fflush(stdout);

        // Kullanıcı girdisini oku
        if (!fgets(input, sizeof(input), stdin)) {
            perror("fgets failed");
            break;
        }

        // Satır sonunu temizle
        input[strcspn(input, "\n")] = 0;

        // Çıkmak isterse
        if (strcmp(input, "exit") == 0) {
            break;
        }

        // Komutu ayır (strtok ile boşluklara göre)
        int arg_index = 0;
        char *token = strtok(input, " ");
        while (token != NULL && arg_index < MAX_ARGS - 1) {
            args[arg_index++] = token;
            token = strtok(NULL, " ");
        }
        args[arg_index] = NULL; // execvp için NULL ile sonlandır

        pid_t pid = fork();
        if (pid < 0) {
            perror("fork failed");
            continue;
        } else if (pid == 0) {
            // Çocuk process: komutu çalıştır
            execvp(args[0], args);
            // exec başarısız olursa:
            perror("exec failed");
            exit(1);
        } else {
            // Ana process: çocuğu bekle
            wait(NULL);
        }
    }

    return 0;
}
