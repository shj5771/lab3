#!/bin/bash

# rm 명령 구현
#작성자:신홍재
if [ -z "$1" ]; then
    echo "사용법: $0 [파일명]"
    exit 1
fi

if [ -f "$1" ]; then
    rm "$1"
    echo "파일 $1 이(가) 삭제되었습니다."
elif [ -d "$1" ]; then
    echo "$1 은(는) 디렉터리입니다. 삭제하려면 -r 옵션을 사용하세요."
else
    echo "파일 $1 이(가) 존재하지 않습니다."
fi
