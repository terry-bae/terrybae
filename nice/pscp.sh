#사용자 생성 기능 파일
#!/bin/sh
password=
echo -n " 동기화할 파일을 입력하세요 : "
	read file

echo ""

pscp.pssh -r -h list.txt $file $file;
#2>&1 |tee work.log
exit
