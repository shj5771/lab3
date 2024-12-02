#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_SENTENCES 5

// 타이핑 연습용 문장
const char* sentences[MAX_SENTENCES] = {
    "The quick brown fox jumps over the lazy dog.",
    "Pack my box with five dozen liquor jugs.",
    "How razorback-jumping frogs can level six piqued gymnasts!",
    "The five boxing wizards jump quickly.",
    "Jinxed wizards pluck thick new shrunken vulture necks."
};

// 타이핑 속도 계산 함수 (WPM)
float calculate_wpm(int correct_chars, time_t start_time, time_t end_time) {
    double elapsed_time = difftime(end_time, start_time);  // 초 단위 시간 차이
    return (correct_chars / 5.0) / (elapsed_time / 60.0);  // 분당 단어수 계산
}

int main() {
    char typed_sentence[200];
    int total_errors = 0;
    int total_correct = 0;
    time_t start_time, end_time;
    
    printf("타자 연습 프로그램에 오신 것을 환영합니다!\n");

    for (int i = 0; i < MAX_SENTENCES; i++) {
        printf("\n문장 #%d: %s\n", i+1, sentences[i]);
        printf("타이핑을 시작하세요: ");
        
        // 타이핑 시작 시간 기록
        time(&start_time);

        // 사용자가 입력한 문장 받기
        fgets(typed_sentence, sizeof(typed_sentence), stdin);

        // 타이핑 종료 시간 기록
        time(&end_time);

        // 문장에서 끝의 개행 문자 제거
        typed_sentence[strcspn(typed_sentence, "\n")] = '\0';

        // 오타와 정확한 문자의 개수 계산
        for (int j = 0; j < strlen(sentences[i]); j++) {
            if (sentences[i][j] == typed_sentence[j]) {
                total_correct++;
            } else {
                total_errors++;
            }
        }

        printf("정확한 타이핑: %d개, 오타: %d개\n", total_correct, total_errors);
    }

    // WPM 계산
    float wpm = calculate_wpm(total_correct, start_time, end_time);
    printf("\n전체 정확한 문자 수: %d, 오타 수: %d\n", total_correct, total_errors);
    printf("평균 분당 타자수(WPM): %.2f\n", wpm);

    return 0;
}
