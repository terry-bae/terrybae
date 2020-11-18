#!/bin/sh

echo " 사용자 계정 정보를 동기화하겠습니다"
ret=$?

cat /etc/passwd |awk -F: '{print $1, $3}' > 1.txt
ssh root@192.168.12.228 cat /etc/passwd |awk -F: '{print $1, $3}' > 2.txt
ssh root@192.168.12.225 cat /etc/passwd |awk -F: '{print $1, $3}' > 3.txt

A=`cat 1.txt`
B=`cat 2.txt`
C=`cat 3.txt`

if [ "$A" == "$B" ] && [ "$A" == "$C" ];
then
	for xx in `cat list.txt`
	do
		rsync -avP /etc/passwd $xx:/etc/passwd
		rsync -avP /etc/group $xx:/etc/group
		rsync -avP /etc/shadow $xx:/etc/shadow
		echo "$xx와 동기화 완료"
	done

else
	echo "각 노드 사용자 정보가 동일하지 않습니다."
fi

cat /dev/null > 1.txt
cat /dev/null > 2.txt
cat /dev/null > 3.txt

echo $?
