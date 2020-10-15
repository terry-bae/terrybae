#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int cnt;
int pinfo; //사람정보
int binfo; //보드정보
int flag;
typedef struct member   ////회원가입 양식 구조체
{
	char id[20];
	char passwd[20];
	char name[20];
	char age[20];
} Member;

typedef struct board     ////게시판 글쓰기 양식 아직 미구현 상태
{
	char ID[30];
	char Title[30];
	char num[30];
	char Content[500];
} Board;

void signup(Member* info);  //회원가입 함수 선언
void login(Member* info); // 로그인 함수 선언
void list(Member* info);  //회원목록 함수 선언
void modify(Member* info); // 회원정보 수정 함수 선언
void withdraw(Member* info); //회원탈퇴 함수 선언
void load_pdata(Member* info); //회원정보 파일 로드 함수 선언
void save_pdata(Member* info); //회원정보 파일 세이브 함수 선언


int main()
{
	Member info[100];  //100명 가입 선언
	FILE *fp;
	fp=fopen("member_info.txt","rt");
	if (fp == NULL) flag = 0;
	else {
		load_pdata(info);
		flag = 1;
	}

	while (1)  ///프로그램 실행중에 안꺼지게 설정
	{
		int i;
		printf("1. 회원가입 \n");
		printf("2. 로그인 \n");
		printf("3. 회원정보 수정 \n");
		printf("4. 회원목록 확인 \n");
		printf("5. 회원탈퇴 \n");
		printf("6. 게시판 프로그램 종료 \n");
		printf(" \n");
		printf(" 이용하실 기능에 대한  번호를 입력하세요: ");
		scanf("%d", &i);
		printf("\n");

		if (i == 1)
		{
			signup(info);
			i = 0;
		}
		if (i == 2)
		{
			login(info);
		}
		if (i == 3)
		{
			modify(info);
		}
		if (i == 4)
		{
			list(info);
		}
		if (i == 5)
		{
			withdraw(info);
		}   	
		if (i == 6)
		{
			printf(" 게시판 프로그램을 종료합니다 \n");
			save_pdata(info);
			break;
		}
	}
	return 0;
}

void load_pdata(Member* info)       /////회원정보 데이터 파일 로
{
	int i;
	FILE* fp;
	fp= fopen("member_info.txt", "rt");
	if (fp == NULL)
	{
		printf("파일 여는데 실패했습니다");
	}
	fscanf(fp, "%*[^:]:%d", &pinfo);
	for	(i = 0; i < pinfo; i++) {
		fscanf(fp, "%*[^:]:%s %*[^:]:%s %*[^:]:%s %*[^:]:%s", (info + i)->id, (info + i)->passwd, (info + i)->name, (info + i)->age);
	}

	fclose(fp);
}

void signup(Member* info) //회원가입 signup 함수 선언
{
	int i, j, k;
	for (i = pinfo; i < 100; i++) //main함수에 따른 100명 연속 가입가능 반복문 선언
		//i=cnt                  //i=cnt 선언해줘야 i=0이 안되면서 회원등록 한 사람이 쌓임
	{
		printf("회원가입을 계속 하시겠습니다? 1. 예 2. 아니요 ");
		scanf("%d", &j);

		if (j == 1)
		{
			printf("아이디 : ");
			scanf("%s", info[i].id);
			printf("패스워드 : ");
			scanf("%s", info[i].passwd);
			printf("이름 : ");
			scanf("%s", info[i].name);
			printf("나이 :");
			scanf("%s", info[i].age);
			printf("회원가입이 완료되었습니다. \n");
			pinfo++; //cnt 대체////////////////// 
		}
		if (j == 2) {
			printf("====메인화면으로 돌아가겠습니다.==== \n");
		}
		break;
	}
}

void save_pdata(Member* info)  ////회원정보 파일 세이브
{
	int i;
	if (flag == 1) {
		FILE* fp2;
		fp2 = fopen("member_info.txt", "rt");
		if (fp2 == NULL) printf("파일 여는데 실패했습니다");
		int temp = 0; //파일에 저장된 회원수를 받아올 변수

		fscanf(fp2, "%*[^:]:%d", &temp); //현재 파일에 저장된 총 회원수를 받아옴
		fclose(fp2);

		FILE* fp;
		fp= fopen("member_info.txt", "at");

		if (fp == NULL)
		{
			printf("파일 여는데 실패했습니다");
		}

		if (temp != 0) { //현재 저장된 회원이 있다면
			FILE* fp3;
			fp3= fopen("member_info.txt", "r+");  //파일을 읽기/쓰기 모드로 열기
			fprintf(fp3, "전체 회원수 : %d\n", pinfo); // 새롭게 변경된 pinfo 즉 현재 프로그램내 저장된 사람수로 변경
			fclose(fp3);//스트림 해제
		}
		else //저장된 회원이 없다면
			fprintf(fp, "전체 회원수 : %d\n", pinfo); // 그대로 파일에 저장


		for (i = temp; i < pinfo; i++)
		{
			fprintf(fp, "계정 : %s, 비밀번호 : %s, 이름 : %s, 나이 : %s", info[i].id, info[i].passwd, info[i].name, info[i].age);
			fputc('\n', fp); ///이거 왜 쓰는지 모르고 그냥 양식때려넣음 조사할 것
		}
		fclose(fp);
	}
	else {
		FILE* fp;
		fp= fopen("member_info.txt", "wt");
		if (fp == NULL)printf("error to open the file");
		fprintf(fp, "전체 회원수 : %d\n", pinfo);
		for (i = 0; i < pinfo; i++) {
			fprintf(fp, "계정 : %s, 비밀번호 : %s, 이름 : %s, 나이 : %s", info[i].id, info[i].passwd, info[i].name, info[i].age);
			fputc('\n', fp); ///이거 왜 쓰는지 모르고 그냥 양식때려넣음 조사할 것
		}
		fclose(fp);
	}
}

void login(Member* info)
{
	char str1[20]; //아이디
	char str2[20]; //비밀번호
	int i;
	printf("====로그인 화면입니다.====\n");
	printf(" 아이디를 입력하세요: ");
	scanf("%s", str1);
	printf(" 비밀번호를 입력하세요: ");
	scanf("%s", str2);
	for (i = 0; i < pinfo; i++)
	{
		if (strcmp(str1, info[i].id) == 0 && strcmp(str2, info[i].passwd) == 0)

		{
			printf("====로그인이 성공했습니다.====\n");
			printf("\n");
			break;
		}
		else
		{
			printf("====아이디 또는 비밀번호가 틀립니다.====");
			printf("\n\n");
		}
	}
}

void list(Member* info)
{
	int i;
	printf("사용자 목록을 조회하겠습니다. \n");

	for (i = 0; i < pinfo; i++) //////////////cnt 대체 info
	{
		printf("계정 : %s 이름 : %s 나이 : %s \n", info[i].id, info[i].name, info[i].age);
	}
}

void modify(Member* info)
{
	char a[20]; //수정할 아이디 변수
	int i;
	printf(" 수정하실 회원 아이디를 입력하시오:");
	scanf("%s", a);
	printf("***해당 하는 계정 유무가 확인하겠습니다.");
	printf("\n");
	printf("\n");
	for (i = 0; i < pinfo; i++)  /////////////////cnt대체
	{
		if (strcmp(a, info[i].id) == 0)
		{
			while (1)
			{
				printf("====일치하는 계정을 찾았습니다.====\n");
				printf("====회원 정보를 수정하십시오====. \n");
				printf("수정하실 이름을 입력하십시오: ");
				scanf("%s", info[i].name);
				printf("\n");
				printf("수정하실 나이를 입력하십시오: ");
				scanf("%s", info[i].age);
				printf("수정하실 비밀번호를 입력하십시오: ");
				scanf("%s", info[i].passwd);

				break;
			}


		}
		else
		{
			printf("====일치하는 계정이 없습니다 메인화면으로 돌아가겠습니다.==== \n");
		}
	}
}

void withdraw(struct member *info)
{
	char id[20]; //탈퇴하고자 하는 아이디
	char passwd[20]; //탈퇴하고자 하는 비밀번호
	int i,j;

	printf("탈퇴하고자 하는 계정 입력 : " );
	scanf("%s", &id);
	printf("비밀번호도 입력하세요 : ");
	scanf("%s", &passwd);
	for(i=0; i < pinfo; i++)
	{
		if(strcmp(info[i].id, id)==0 && strcmp(info[i].passwd, passwd)==0)
		{
			for(j=i+1; j<pinfo; j++)
			{
				strcpy(info[j-1].id, info[j].id);
				strcpy(info[j-1].passwd, info[j].passwd);
			}
		
		
		}
		else
		{
			printf("탈퇴하고자 하는 계정정보를 다시 입력하세요 \n");
		}
	pinfo--;
	printf("회원 탈퇴가 완료되었습니다 \n");
	main();
			
	}
}




/*void board_list(void)
  {
  printf("1. 게시물 작성 \n");
  printf("2. 게시물 삭제 \n");
  printf("3. 게시물 목록 \n");
  printf("4. 내가 쓴 게시물 확인 \n");
  printf("5. 나가기 \n");
  */
