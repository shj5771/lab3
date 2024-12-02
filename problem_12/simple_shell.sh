#!/bin/bash

# 쉘 인터프리터 함수
function simple_shell {
    while true; do
        # 프롬프트 출력
        echo -n "simple-shell> "
        read -r input
        
        # exit 명령으로 종료
        if [[ "$input" == "exit" ]]; then
            echo "프로그램을 종료합니다."
            break
        fi

        # 입력 명령어 실행
        eval "$input"
    done
}

# 인터럽트 신호 처리
trap "echo 'SIGINT (Ctrl-C) 신호를 받았습니다.'" SIGINT
trap "echo 'SIGQUIT (Ctrl-\\) 신호를 받았습니다.'" SIGQUIT

# 쉘 시작
simple_shell
