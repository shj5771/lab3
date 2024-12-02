#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// SIGINT 시그널을 처리하는 핸들러 함수
void handle_sigint(int sig) {
    printf("\nSIGINT 시그널을 받았습니다! 프로그램을 종료합니다.\n");
    exit(0);  // 프로그램 종료
}

int main() {
    // SIGINT 시그널에 대해 handle_sigint 함수 등록
    if (signal(SIGINT, handle_sigint) == SIG_ERR) {
        printf("시그널 핸들러 설정 실패\n");
        return 1;
    }

    // 시그널을 기다리며 계속 실행
    printf("Ctrl+C를 눌러 SIGINT 시그널을 보내면 프로그램이 종료됩니다.\n");

    // 무한 루프를 돌며 시그널을 기다린다
    while (1) {
        sleep(1);  // 1초씩 기다리며 시그널을 받기 대기
    }

    return 0;
}
