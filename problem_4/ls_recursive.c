#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// 디렉토리 탐색 함수
void list_directory(const char *dir_name, int depth) {
    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;
    
    // 디렉토리 열기
    dir = opendir(dir_name);
    if (dir == NULL) {
        perror("디렉토리 열기 실패");
        return;
    }

    // 들여쓰기 (재귀적으로 호출되면 깊이를 나타내기 위해 사용)
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }

    // 디렉토리 이름 출력
    printf("%s:\n", dir_name);

    // 디렉토리 내의 파일과 디렉토리 나열
    while ((entry = readdir(dir)) != NULL) {
        // 현재 디렉토리(.)와 상위 디렉토리(..)를 건너뛰기
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // 파일이나 디렉토리의 절대 경로 생성
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir_name, entry->d_name);

        // 파일 정보 얻기
        if (stat(full_path, &statbuf) == -1) {
            perror("파일 정보 얻기 실패");
            continue;
        }

        // 파일이면 출력
        if (S_ISREG(statbuf.st_mode)) {
            printf("  %s\n", entry->d_name);
        }
        // 디렉토리이면 재귀적으로 탐색
        else if (S_ISDIR(statbuf.st_mode)) {
            printf("  %s/\n", entry->d_name);
            list_directory(full_path, depth + 1);  // 재귀 호출
        }
    }

    // 디렉토리 닫기
    closedir(dir);
}

int main(int argc, char *argv[]) {
    // 인자가 없으면 현재 디렉토리 탐색
    if (argc < 2) {
        list_directory(".", 0);
    }
    // 인자가 있으면 해당 디렉토리 탐색
    else {
        for (int i = 1; i < argc; i++) {
            list_directory(argv[i], 0);
        }
    }

    return 0;
}
