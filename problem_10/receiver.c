#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSG_SIZE 100

// 메시지 구조체
struct msg_buffer {
    long msg_type;  // 메시지 타입
    char msg_text[MSG_SIZE];  // 메시지 내용
};

int main() {
    key_t key;
    int msgid;
    struct msg_buffer message;

    // 메시지 큐의 키 생성
    key = ftok("chat_program.c", 65);
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

    printf("채팅 메시지 받기 시작...\n");

    while (1) {
        // 메시지 큐에서 메시지 받기
        if (msgrcv(msgid, &message, sizeof(message), 1, 0) == -1) {
            perror("메시지 받기 실패");
            exit(1);
        }

        printf("받은 메시지: %s\n", message.msg_text);

        // 'exit' 메시지가 오면 종료
        if (strncmp(message.msg_text, "exit", 4) == 0) {
            break;
        }
    }

    // 메시지 큐 닫기
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}
