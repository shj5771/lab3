#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid;  // 프로세스 ID

    printf("부모 프로세스 시작\n");

    // fork() 함수로 자식 프로세스 생성
    pid = fork();

    if (pid < 0) {
        // fork 실패
        perror("fork 실패");
        exit(1);
    }

    if (pid == 0) {
        // 자식 프로세스
        printf("자식 프로세스: ls 명령어 실행\n");
        
        // execvp()로 ls 명령어 실행
        char *args[] = {"ls", "-l", NULL};
        execvp(args[0], args);

        // execvp가 성공하면 아래 코드는 실행되지 않음
        perror("execvp 실패");
        exit(1);
    } else {
        // 부모 프로세스
        int status;
        wait(&status);  // 자식 프로세스가 종료될 때까지 기다림

        printf("부모 프로세스: 자식 프로세스 종료\n");
    }

    return 0;
}
