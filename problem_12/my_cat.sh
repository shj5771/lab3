#!/bin/bash

# cat 명령 구현
#작성자:신홍재
if [ -z "$1" ]; then
    echo "사용법: $0 [파일명]"
    exit 1
fi

if [ -f "$1" ]; then
    cat "$1"
else
    echo "파일 $1 이(가) 존재하지 않거나 파일이 아닙니다."
fi
