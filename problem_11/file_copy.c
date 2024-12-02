#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define SHM_SIZE 1024  // 공유 메모리 크기

// 세마포어 구조체
struct sembuf semOp;

// 공유 메모리 구조체
struct shared_memory {
    char data[SHM_SIZE];
    int read_flag;  // 부모가 읽었는지 여부
};

void P(int sem_id, int sem_num) {
    semOp.sem_num = sem_num;
    semOp.sem_op = -1;
    semOp.sem_flg = 0;
    if (semop(sem_id, &semOp, 1) == -1) {
        perror("semop P failed");
        exit(1);
    }
}

void V(int sem_id, int sem_num) {
    semOp.sem_num = sem_num;
    semOp.sem_op = 1;
    semOp.sem_flg = 0;
    if (semop(sem_id, &semOp, 1) == -1) {
        perror("semop V failed");
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <source_file> <destination_file>\n", argv[0]);
        return 1;
    }

    // 파일 열기
    int source_fd = open(argv[1], O_RDONLY);
    if (source_fd == -1) {
        perror("Error opening source file");
        return 1;
    }

    int dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1) {
        perror("Error opening destination file");
        return 1;
    }

    // 공유 메모리 생성
    key_t key = ftok("shmfile", 65);
    int shm_id = shmget(key, sizeof(struct shared_memory), 0666 | IPC_CREAT);
    if (shm_id == -1) {
        perror("Error creating shared memory");
        return 1;
    }

    // 세마포어 생성
    int sem_id = semget(key, 2, 0666 | IPC_CREAT);
    if (sem_id == -1) {
        perror("Error creating semaphore");
        return 1;
    }

    // 세마포어 초기화
    semctl(sem_id, 0, SETVAL, 1);  // 읽기 세마포어
    semctl(sem_id, 1, SETVAL, 0);  // 쓰기 세마포어

    // 공유 메모리 연결
    struct shared_memory *shm_ptr = (struct shared_memory *)shmat(shm_id, NULL, 0);
    if (shm_ptr == (void *)-1) {
        perror("Error attaching shared memory");
        return 1;
    }

    // 부모 프로세스가 데이터를 읽고 공유 메모리에 저장
    P(sem_id, 0);  // 읽기 세마포어 잠금
    int bytes_read = read(source_fd, shm_ptr->data, SHM_SIZE);
    if (bytes_read == -1) {
        perror("Error reading file");
        return 1;
    }
    shm_ptr->read_flag = 1;  // 읽음 표시
    V(sem_id, 1);  // 쓰기 세마포어 신호

    // 자식 프로세스가 데이터를 읽고 다른 파일에 씀
    if (fork() == 0) {
        P(sem_id, 1);  // 쓰기 세마포어 잠금
        write(dest_fd, shm_ptr->data, bytes_read);
        V(sem_id, 0);  // 읽기 세마포어 신호

        // 자식 프로세스 종료
        exit(0);
    }

    // 부모 프로세스 종료
    wait(NULL);
    close(source_fd);
    close(dest_fd);
    shmctl(shm_id, IPC_RMID, NULL);  // 공유 메모리 제거
    semctl(sem_id, 0, IPC_RMID);  // 세마포어 제거

    return 0;
}
