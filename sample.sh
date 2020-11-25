#!/bin/bash

echo "

               [1] 사용자 계정 추가 합니다.
               
               [2] 네임서버 추가합니다. 
               
               [3] VirtualHost 추가하기.                 

               [4] Mysql 계정추가하기.
              
               [5] sendmail 계정 추가하기.  
"

echo -n "select Number:"
read Num

case "$Num" in


#사용자 추가 하기 
1)
echo =======================================================
echo
echo  "< Hosting Server 사용자 추가 스크립트>"
echo
echo  계정ID, 계정Password 를 입력       
echo
echo =======================================================
echo 
echo -n "사용자 계정 입력:"
         read id


echo -n "사용자 패스워드 입력:"
         read pass

echo -n "
        사용자 계정: $id
        
        사용자패스워드: $pass
-------------------------------------------------------------
        맞으면 <Enter>를 누르고 틀리면 No를 입력하세요: "
        read chk

if [ "$chk" != "" ]

then
         exit
fi

echo""
echo "호스팅 사용자를 추가합니다."

#계정 ID 추가 
adduser $id
#패스 워드 추가 

echo "$pass" | passwd --stdin "$id"
echo "

 

"
echo "사용자 아이디와 패스워드 입니다"
echo ""
echo ""
echo "사용자 ID: $id" 

echo "패스워드 : $pass"

echo "사용자 추가를 완료했습니다"

exit;;

 

 

#네임 서버 추가 스크립트
2)
echo =======================================================
echo
echo  "< 네임서버 추가 등록추가 >"
echo
echo =======================================================
echo 
echo -n "url 주소를 입력하세요 :"
         read url

echo -n "서버 IP 입력하세요:"
         read ip
echo -n "
       
        사용자 도메인 : $url
          서버 IP     : $ip
-------------------------------------------------------------
        맞으면 <Enter>를 누르고 틀리면 No를 입력하세요: "
        read chk

if [ "$chk" != "" ]

then
         exit
fi

echo "zone \"$url\" IN {
        type master;
        file \"$url.zone\";
        allow-update { none; };
};" >> /etc/named.conf

#포워드존 파일 생성합니다 
touch /var/named/$url.zone

echo "\$TTL    86400
@       IN      SOA     ns.$url. root.ns.$url.  (
                                      1997022700 ; Serial
                                      28800      ; Refresh
                                      14400      ; Retry
                                      3600000    ; Expire
                                      86400 )    ; Minimum
                IN      NS      ns.$url.
                IN      MX 10   mail.$url.
;
@               IN      A       $ip
www             IN      A       $ip
*               IN      A       $ip
" > /var/named/$url.zone

#named restart
/etc/init.d/named restart

echo "설정이  완료했습니다"

exit;;

# 가상호스트 추가하기

3)

echo =======================================================
echo
echo  "< 가상 호스트 추가하기 >"
echo
echo  계정 도메인, 계정ID, IP는 *:80 을 입력   
echo
echo =======================================================
echo 
echo -n "url 주소를 입력하세요 :"
         read url
echo -n "계정 ID를 입력 하세요:"
         read id
echo -n "서버 IP 입력하세요:"
         read ip
echo -n "
       
        사용자 도메인 : $url
            게정 ID   : $id
            서버 IP   : $ip

-------------------------------------------------------------
        맞으면 <Enter>를 누르고 틀리면 No를 입력하세요: "
        read chk

if [ "$chk" != "" ]

then
         exit
fi

echo "<VirtualHost $ip>
DocumentRoot /home/$id/public_html
ServerName $url
ServerAlias www.$url
#    ErrorLog logs/dummy-host.example.com-error_log
#    CustomLog logs/dummy-host.example.com-access_log common
</VirtualHost>" >> /etc/httpd/conf/httpd.conf

echo "설정이  완료했습니다"

#아파치 restart
service httpd restart

exit;;

# Myslq 계정 추가하기 
4)
echo =======================================================
echo
echo  "< Myslq 계정 추가하기  >"
echo
echo  계정ID, MySql Password를 입력
echo
echo =======================================================
echo 
echo -n "Mysql 계정 추가하기:" 
         read id

echo -n "Mysql 패스워드 :"
         read pass
echo -n "
       
        사용자 도메인 : $id
            서버 IP   : $pass

-------------------------------------------------------------
        맞으면 <Enter>를 누르고 틀리면 No를 입력하세요: "
        read chk

if [ "$chk" != "" ]

then
           exit
fi

echo "create database $id;
GRANT ALL PRIVILEGES ON $id.* TO $id@localhost IDENTIFIED by '$pass';" > ./tmp

echo "
       Mysql 루트 패스워드를 입력하세요    
"

mysql -u root -p mysql < ./tmp

rm -f ./tmp


echo "설정이  완료했습니다"
exit;;


5)

echo =======================================================
echo
echo       메일 추가하기        
echo
echo       계정 도메인, 메일ID, 메일Password 를 입력
echo
echo ======================================================= 

echo -n "url 주소를 입력하세요 :"
         read url

echo -n "계정 ID:"
         read id

echo -n "계정 패스워드:" 
         read pass
echo -n "
       
        사용자 도메인 : $url
            계정 ID   : $id
            서버 PASS : $pass
        
-------------------------------------------------------------
        맞으면 <Enter>를 누르고 틀리면 No를 입력하세요: "
        read chk

if [ "$chk" != "" ]

then
           exit
fi

echo "$url" >> /etc/mail/local-host-names


adduser -M $id -s /bin/false

 

echo "$id@$url  $id"  >> /etc/mail/virtusertable
echo "$pass" | passwd --stdin "$id"

#sendmail 설정 적용을 위한 메일 DB작업 
makemap hash /etc/mail/virtusertable < /etc/mail/virtusertable
makemap hash /etc/mail/local-host-names < /etc/mail/local-host-names

#sendmail restart
/etc/init.d/sendmail restart


echo "설정이  완료했습니다"
exit;;*)
  huk.....
esac
