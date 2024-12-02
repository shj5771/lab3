#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSG_SIZE 100

// 메시지 구조체
struct msg_buffer {
    long msg_type;
    char msg_text[MSG_SIZE];
};

int main() {
    key_t key;
    int msgid;
    struct msg_buffer message;

    // 메시지 큐의 키 생성
   key = ftok(".", 65);  // 현재 디렉토리의 파일을 사용

    if (key == -1) {
        perror("ftok 실패");
        exit(1);
    }

    // 메시지 큐 열기
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget 실패");
        exit(1);
    }

    printf("메시지를 입력하세요:\n");

    while (1) {
        // 메시지 입력받기
        fgets(message.msg_text, MSG_SIZE, stdin);

        // 메시지 타입 설정 (1로 설정)
        message.msg_type = 1;

        // 메시지 보내기
        if (msgsnd(msgid, &message, sizeof(message), 0) == -1) {
            perror("메시지 보내기 실패");
            exit(1);
        }

        // "exit"이면 종료
        if (strncmp(message.msg_text, "exit", 4) == 0) {
            break;
        }
    }

    return 0;
}
