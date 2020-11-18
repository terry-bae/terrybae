# 사용자 비밀번호 변경 기능 파일
#!/bin/sh

echo -n " 사용자 계정을 입력하세요: "
	read id

passwd $id

cp /etc/shadow /etc/shadow.old
for xx in `cat list.txt`
do
	echo $xx
	scp /etc/passwd $xx:/etc/passwd
	scp /etc/group $xx:/etc/group
	scp /etc/shadow.old $xx:/etc/shadow
done
