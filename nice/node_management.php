#!/bin/php
<?php

main();
#monitor_main();
#command_main();


/*메인화면 함수*/
function main(){

	echo "********** 노드 관리 프로그램 ********** \n";
	echo "1. 모니터링 기능 \n";
	echo "2. 명령어 기능 \n";
	echo "3. 동기화 기능 \n";
	echo "이용하실 기능 숫자를 입력하세요 : ";
	$select = trim(fgets(STDIN));

	switch ($select){
		case 1:
			echo "1. 모니터링 기능 \n";
			monitor_main(); 
			break;

		case 2:
			echo "2. 명령어 기능 \n";
			command_main();
			break;

		case 3:
			echo "3. 동기화 기능 \n";
			sync();
			break;

		default;
			echo "입력값이 잘못되었습니다. \n";
			break;
	}
}

/* 모니터링 메인함수*/
function monitor_main(){

	echo "********** 모니터링 기능 ********** \n";
	echo "1. 전체 모니터링 기능 \n";
	echo "2. 일부 모니터링 기능 \n";
	echo "이용하실 기능 숫자를 입력하세요 : ";
	$select = trim(fgets(STDIN));

	switch ($select){

		case 1:
			echo "1. 전체 모니터링 기능 \n ";
			allnode_monitor();
			break;

		case 2:
			echo "2. 일부 모니터링 기능 \n ";
			selectnode_monitor();
			break;

		default;
			echo "입력값이 잘못되었습니다. \n ";
	}
}


/*전체 노드 모니터링 함수*/
function allnode_monitor(){

	require 'list.txt';
	$cmd = 'pssh -i -h list.txt df -h 2>&1 |tee df.txt';
	$cmd1 = 'pssh -i -h list.txt cat /proc/cpuinfo 2>&1 |tee cpu.txt';
	$cmd2 = 'pssh -i -h list.txt free 2>&1 |tee memory.txt';
#$cmd = 'pssh -i -h list.txt useradd';
	exec("$cmd", $output);
	exec("$cmd1", $output1);
	exec("$cmd2", $output2);
	echo "\n";
	echo "\n\n";
	echo "********** df정보 입니다. **********\n";
	echo join($output, "\n");
	echo "\n";
	echo "\n\n";
	echo "********** cpu정보 입니다. **********\n";
	echo join($output1, "\n");
	echo "\n";
	echo "\n\n";
	echo ("********** 메모리 정보 입니다. **********\n");
	echo join($output2, "\n");
#df -h |awk '{print $1,$2,$3,$4}'s
	echo "\n";
#print_r($output);
}


/*선택 노드 모니터링 함수*/
function selectnode_monitor(){		

	require 'list.txt';
	echo "확인할 노드를 입력하세요 : ";
	$ip = trim(fgets(STDIN));
	$cmd = "ssh $ip df -h 2>&1 |tee df.txt";
	$cmd1 = "ssh $ip cat /proc/cpuinfo 2>&1 |tee cpu.txt";
	$cmd2 = "ssh $ip free 2>&1 |tee memory.txt";
	echo "$ip 노드에 대한 모니터링을 실행합니다";
	exec("$cmd", $output);
	exec("$cmd1", $output1);
	exec("$cmd2", $output2);
	echo "\n";
	echo ("********** df정보 입니다. ********** \n");
	echo join($output, "\n");
	echo "\n";
	echo "\n";
	echo ("********** cpu정보 입니다. ********** \n");
	echo join($output1, "\n");
	echo "\n";
	echo "\n";
	echo ("********** 메모리 정보 입니다. ********** \n");
	echo join($output2, "\n");
	echo "\n";
}


/*명령어 수행 메인 함수*/
function command_main(){
	echo "********** 명령어 수행 기능 ********** \n";
	echo "1. 전체 노드 명령어 수행 기능 \n";
	echo "2. 일부 노드 명령어 수행 기능 \n";
	echo "이용하실 기능 숫자를 입력하세요 : ";
	$select = trim(fgets(STDIN));

	switch ($select){
		case 1:
		echo "1. 전체 노드 명령어 수행 기능 \n";
		allnode_cmd();
		break;

		case 2:
		echo "2. 일부 노드 명령어 수행 기능 \n";
		selectnode_cmd();
		break;

		default;
		echo "잘못 된 입력값입니다. \n";
	}
}


/*전체 노드 명령어 수행 함수*/
function allnode_cmd(){

	require 'list.txt';
	echo "실행할 명령어를 입력하세요 : ";
	$exe = trim(fgets(STDIN));
	$cmd = "pssh -i -h list.txt $exe";

	exec("$cmd", $output);
	echo "\n";
	echo "\n";
	echo join($output, "\n");
	echo "\n";
	echo " 전체 노드 명령어 실행이 완료되었습니다. \n";
}


/*선택 노드 명령어 수행 함수*/
function selectnode_cmd(){

	require 'list.txt';
	echo "명령어를 실행시킬 노드를 입력하세요 : ";
	$ip = trim(fgets(STDIN));
	echo "실행할 명령어를 입력하세요 : ";
	$exe = trim(fgets(STDIN));
	$cmd = "ssh $ip $exe";
	echo "*****$ip 노드에서 명령을 실행합니다";
	exec("$cmd", $output);
	echo "\n";
	echo join($output, "\n");
	echo "\n";
}

function sync(){

	echo "********** 동기화 기능 화면입니다. **********\n";
	echo "********** 동기화 옵션을 선택하세요. **********\n";
	echo "1. 디렉토리 \n";
	echo "2. 파일 \n";
	echo "동기화 대상을 입력하세요 : ";
	$kind = trim(fgets(STDIN));

	switch ($kind){
		case 1:
		echo "1. 디렉토리 동기화 옵션을 선택하셨습니다. \n";
		require 'list.txt';
		echo "동기화할 디렉토리를 입력하세요 : ";
		$local_dir = trim(fgets(STDIN));
		echo " 동기화시킬 경로를 입력하세요 :";
		$remote_dir = trim(fgets(STDIN));
#$cmd = "pscp.pssh -r -h list.txt $dir $dir";
		$cmd = "prsync -r -h list.txt $local_dir $remote_dir";
		exec("$cmd", $output);
		echo "\n\n";
		echo "$local_dir 디렉토리 동기화를 실행합니다. \n";
		echo join($output, "\n");
		echo "\n";
		break;

		case 2:
		echo "2. 파일 동기화 옵션을 선택하셨습니다. \n";
		require 'list.txt';
		echo " 동기화할 파일을 입력하세요 : ";
		$local_file = trim(fgets(STDIN));
		echo " 동기화시킬 경로를 입력하세요 : ";
		$remote_file = trim(fgets(STDIN));
#	$conn = ssh2_connect('list.txt', 22);
#	$sftp = ssh2_sftp($conn);
#	ssh2_scp_send($conn, "$file", "$file", 0644);
		$cmd = "prsync -h list.txt $local_file $remote_file";
		exec("$cmd", $output);
		echo "\n\n";
		echo "$local_file 파일 동기화를 실행합니다. \n";
		echo join($output, "\n");
		echo "\n";
		break;
		
		default;
		echo "잘못된 입력값입니다. \n";
	}
}
?>
