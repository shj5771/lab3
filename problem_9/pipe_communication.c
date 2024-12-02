#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 100

int main() {
    int pipefd[2];  // 파이프 디스크립터
    pid_t pid;
    char write_msg[] = "안녕하세요, 자식 프로세스입니다!";
    char read_msg[BUFFER_SIZE];

    // 파이프 생성
    if (pipe(pipefd) == -1) {
        perror("파이프 생성 실패");
        exit(1);
    }

    // 자식 프로세스 생성
    pid = fork();
    
    if (pid == -1) {
        // fork 실패 시
        perror("fork 실패");
        exit(1);
    }

    if (pid > 0) {
        // 부모 프로세스: 데이터를 파이프에 작성
        close(pipefd[0]);  // 읽기 끝은 닫음
        write(pipefd[1], write_msg, strlen(write_msg) + 1);  // 파이프에 데이터 쓰기
        close(pipefd[1]);  // 쓰기 끝도 닫음
        wait(NULL);  // 자식 프로세스 종료 대기
    } else {
        // 자식 프로세스: 파이프에서 데이터를 읽기
        close(pipefd[1]);  // 쓰기 끝은 닫음
        read(pipefd[0], read_msg, sizeof(read_msg));  // 파이프에서 데이터 읽기
        close(pipefd[0]);  // 읽기 끝도 닫음
        printf("자식 프로세스가 받은 메시지: %s\n", read_msg);  // 받은 메시지 출력
        exit(0);
    }

    return 0;
}
