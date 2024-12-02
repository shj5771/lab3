#!/bin/bash

# mv 명령 구현
# 작성자:신홍재
if [ -z "$1" ] || [ -z "$2" ]; then
    echo "사용법: $0 [원본파일] [대상파일]"
    exit 1
fi

if [ -e "$1" ]; then
    mv "$1" "$2"
    echo "파일 $1 이(가) $2 로 이동되었습니다."
else
    echo "파일 $1 이(가) 존재하지 않습니다."
fi
