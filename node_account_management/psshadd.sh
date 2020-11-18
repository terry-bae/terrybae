#사용자 생성 기능 파일
#!/bin/sh
password=
echo -n " 사용자 계정을 입력하세요 : "
	read id

echo -n " 사용자 비밀번호를 입력하세요 : "
stty -echo
	read password
stty echo
echo ""

pssh -h list.txt useradd -p `openssl passwd $password` $id
#2>&1 |tee work.log
exit
