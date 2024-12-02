#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FILENAME "example.txt"
#define DIRNAME "example_dir"

int main() {
    // 1. 파일 생성 및 쓰기
    int fd = open(FILENAME, O_CREAT | O_WRONLY, 0644);
    if (fd == -1) {
        perror("파일 생성 실패");
        exit(1);
    }

    char *content = "Hello, this is an example file.\n";
    if (write(fd, content, strlen(content)) == -1) {
        perror("파일 쓰기 실패");
        close(fd);
        exit(1);
    }
    close(fd);
    printf("파일 생성 및 내용 쓰기 완료: %s\n", FILENAME);

    // 2. 디렉토리 생성
    if (mkdir(DIRNAME, 0755) == -1) {
        perror("디렉토리 생성 실패");
        exit(1);
    }
    printf("디렉토리 생성 완료: %s\n", DIRNAME);

    // 3. 디렉토리 내 파일 목록 읽기
    DIR *dir = opendir(DIRNAME);
    if (dir == NULL) {
        perror("디렉토리 열기 실패");
        exit(1);
    }

    struct dirent *entry;
    printf("디렉토리 내 파일 목록:\n");
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    closedir(dir);

    // 4. 파일 삭제
    if (unlink(FILENAME) == -1) {
        perror("파일 삭제 실패");
        exit(1);
    }
    printf("파일 삭제 완료: %s\n", FILENAME);

    // 5. 디렉토리 삭제
    if (rmdir(DIRNAME) == -1) {
        perror("디렉토리 삭제 실패");
        exit(1);
    }
    printf("디렉토리 삭제 완료: %s\n", DIRNAME);

    return 0;
}
