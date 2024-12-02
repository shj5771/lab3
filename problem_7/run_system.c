#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

// 쉘 명령어를 실행하는 함수
void run_command(char *command, char *args[]) {
    pid_t pid = fork();  // 자식 프로세스 생성

    if (pid < 0) {
        // fork 실패 시
        perror("fork 실패");
        exit(1);
    }

    if (pid == 0) {
        // 자식 프로세스에서 명령어 실행
        execvp(command, args);  // execvp로 명령어 실행

        // execvp가 실패하면 아래 코드가 실행
        perror("execvp 실패");
        exit(1);
    } else {
        // 부모 프로세스는 자식 프로세스가 종료될 때까지 기다림
        int status;
        wait(&status);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        // 명령어 인자가 없으면 에러 메시지 출력
    
