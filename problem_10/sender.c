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

    // 메시지 큐 생성
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget 실패");
        exit(1);
    }

    printf("채팅 메시지 보내기. (종료하려면 'exit' 입력)\n");

    while (1) {
        // 사용자로부터 메시지 입력받기
        printf("보낼 메시지: ");
        fgets(message.msg_text, MSG_SIZE, stdin);

        // 'exit' 입력 시 종료
        if (strncmp(message.msg_text, "exit", 4) == 0) {
            break;
        }

        message.msg_type = 1;  // 메시지 타입 설정 (1번 타입으로 설정)
        
        // 메시지 큐에 메시지 보내기
        if (msgsnd(msgid, &message, sizeof(message), 0) == -1) {
            perror("메시지 보내기 실패");
            exit(1);
        }

        printf("메시지가 전송되었습니다: %s\n", message.msg_text);
    }

    // 메시지 큐 닫기
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}
