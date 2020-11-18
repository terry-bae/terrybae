# 사용자 수정 기능 파일
#!/bin/sh

echo -n " 사용자 계정을 입력하세요 : "
	read id
echo -n " 사용하고자 하는 옵션을 이용하세요 : "
	read option
echo -n " 변경하고자 하는 내용을 입력하세요 : "
	read modify 

pssh -h list.txt usermod -$option $modify $id
usermod -$option $modify $id
