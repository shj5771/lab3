#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

// 명령 헤더 파일
#include "rm.h"
#include "mv.h"
#include "cat.h"

#define MAX_INPUT 1024

// SIGINT 핸들러
void handle_sigint(int sig) {
    printf("\nSIGINT (Ctrl+C) 감지. 종료하려면 'exit'을 입력하세요.\n$ ");
    fflush(stdout);
}

// SIGQUIT 핸들러
void handle_sigquit(int sig) {
    printf("\nSIGQUIT (Ctrl+Z) 감지. 종료하려면 'exit'을 입력하세요.\n$ ");
    fflush(stdout);
}

int main() {
    char input[MAX_INPUT];
    char *args[100];

    // SIGINT와 SIGQUIT 처리
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, handle_sigquit);

    // 디렉토리 변경
    if (chdir("problem_12") == -1) {
        perror("Failed to change directory");
        return 1;
    }

    while (1) {
        printf("$ ");
        if (!fgets(input, MAX_INPUT, stdin)) {
            break;
        }

        input[strcspn(input, "\n")] = 0; // 개행 문자 제거

        // 종료 명령
        if (strcmp(input, "exit") == 0) {
            break;
        }

        // 입력 파싱
        int i = 0;
        args[i] = strtok(input, " ");
        while (args[i] != NULL) {
            i++;
            args[i] = strtok(NULL, " ");
        }

        // 명령 실행
        if (args[0] == NULL) {
            continue;
        } else if (strcmp(args[0], "rm") == 0) {
            execute_rm(args[1]); // rm 명령 실행
        } else if (strcmp(args[0], "mv") == 0) {
            execute_mv(args[1], args[2]); // mv 명령 실행
        } else if (strcmp(args[0], "cat") == 0) {
            execute_cat(args[1]); // cat 명령 실행
        } else {
            printf("Unknown command: %s\n", args[0]);
        }
    }

    return 0;
}
