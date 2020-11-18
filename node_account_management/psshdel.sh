# 사용자 삭제 기능 파일
#!/bin/sh

echo -n " 사용자 계정을 입력하세요 : "
	read id
{
pssh -h list.txt userdel -r $id
#userdel -r $id
ret=$?
echo $?
} #2>&1 |tee work.log
