#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int minfo; //회원정보
int binfo; //보드정보
struct member   ////회원가입 양식 구조체
{
	char id[20];
	char passwd[20];
	char name[20];
	char age[20];
};

struct board     ////게시판 글쓰기 양식 아직 미구현 상태
{
	char id[30];
	char title[30];
	char num[30];
	char content[500];
};

void signup(struct member *info);  //회원가입 함수 선언
void login(struct member *info); // 로그인 함수 선언
void list(struct member *info);  //회원목록 함수 선언
void modify(struct member *info); // 회원정보 수정 함수 선언
void withdraw(struct member *info); //회원탈퇴 함수 선언
void load_mdata(struct member *info); //회원정보 파일 로드 함수 선언
void save_mdata(struct member *info); //회원정보 파일 세이브 함수 선언

void board_main(char *id);


int main()
{	
	struct member info[100]; // 100명 가입 선언
	load_mdata(info);
	while(1)  ///프로그램 실행중에 안꺼지게 설정
	{
		//	struct member info[100];  //100명 가입 선언
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

		if(i==1)
		{
			signup(info);
			i=0;
		}
		if(i==2)
		{
			login(info);

		}
		if(i==3)
		{
			modify(info);
		}
		if(i==4)
		{
			list(info);
		}
		/*		if(i==5)
				{
				withdraw(info);
				}	*/
		if(i==6)
		{
			printf(" 게시판 프로그램을 종료합니다 \n");
			save_mdata(info);
			break ;
		}
	}
	return 0;
}


void load_mdata(struct member *info)  // 저장된 회원정보 로드
{
	int i;
	FILE *fps;
	fps=fopen("member_info.txt", "rt");
	if(fps==NULL)
	{
		printf("파일 여는데 실패했습니다");	
	}
	for(i=0; i<minfo; i++)
	{
		fscanf(fps, "%s %s %s %s", \
				info[i].id, info[i].passwd, info[i].name, info[i].age);
	}
	fclose(fps);
}
		/*
		   }
		   fscanf(fp, "%*[^:]:%d", &minfo);

		   for(i=0; i<minfo; i++)
		   {
		   fscanf(fp, "%*[^:]:%s %*[^:]:%s %*[^:]:%s %*[^:]:%s" \
		   ,info[i].id, info[i].passwd, info[i].name, info[i].age);
		   }
		   fclose(fp);
		   }
		   */
//	while(1)
//	{	
	//j=fscanf(fp," 계정 : %s, 비밀번호 : %s, 이름 : %s, 나이 : %s" ,info[i].id, info[i].passwd, info[i].name, info[i].age);
//		j=fscanf(fp, "계정: %s, 비밀번호: %s, 이름: %s, 나이: %s" ,info[i].id, \
//				info[i].passwd, info[i].name, info[i].age);
//		if(j==EOF)
//		{		
//			break;
//		}
//		minfo++;
//	}
//	fclose(fp);
			
//}


void signup(struct member *info) //회원가입
{
	int i,j;
	for(i=minfo; i<100; i++) //main함수에 따른 100명 연속 가입가능 반복문 선언
		//i=pinfo 선언해줘야 i=0이 안되면서 회원등록 한 사람이 쌓임
	{
		printf("회원가입을 계속 하시겠습니다? 1. 예 2. 아니요 ");
		scanf("%d", &j);

		if(j==1)
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
			minfo ++; //가입된 사람 정보 추가
		}
		if(j==2)
			printf("====메인화면으로 돌아가겠습니다.==== \n");
		break ;
	}
}


void save_mdata(struct member *info )  ////회원정보 파일 세이브
{
	int i;
	FILE *fp;
	fp=fopen("member_info.txt", "at");
	if(fp==NULL)
	{
		printf("파일을 여는데 실패했습니다");
	}
	
	fprintf(fp, "전체 회원수 : %d \n", minfo);
	for(i=0; i<minfo; i++)
	{
		fprintf(fp, "%s %s %s %s" \
				,info[i].id, info[i].passwd, info[i].name, info[i].age);
		fputc('\n', fp);
	}
	fflush(fp);
	fclose(fp);
}
	/*
	FILE *fp=fopen("member_info.txt", at);
	   int tmp = 0; //파일에 저장된 회원수를 받아올 변수 선언
	   FILE *fp2=fopen("member_info.txt", "rt");

	   if(fp2 ==NULL)
	   {
	   printf("파일 여는데 실패했습니다");
	   }

	   fscanf(fp2, "%*[^:]:%d", &tmp); //현재 파일에 저장된 총 회원수 받아옴

	   fclose(fp2);
	   */

//	FILE *fp=fopen("member_info.txt", "at");

//	if(fp==NULL)
//	{
//		printf("파일 여는데 실패했습니다");

//	}
	/*
	   if(tmp !=0)  // 현재 저장된 회원있으면 읽기 쓰기모드로 열기
	   {
	   FILE *fp3=fopen("member_info.txt", "r+");

	   fprintf(fp3, "전체회원수 : %d \n", minfo); // 새롭게 변경된 회원수 저장

	   fclose(fp3);
	   }
	   else
	   fprintf(fp, "전체회원수 : %d \n", minfo); // 기존 회원수 그대로 저장
	   */
//	for(i=0; i<minfo; i++)
//	{
//		fprintf(fp, "계정 : %s, 비밀번호 : %s, 이름 : %s, 나이 : %s" \
//				,info[i].id, info[i].passwd, info[i].name, info[i].age);
		//	fprintf(fp, " %s, %s, %s, %s" \
		,info[i].id, info[i].passwd, info[i].name, info[i].age);
//		fputc('\n', fp); 
//	}
//	fflush(fp);
//	fclose(fp);
//}


void login(struct member *info)                     
{	
	char id[20]; //아이디
	char passwd[20]; //비밀번호
	int i;
	printf("====로그인 화면입니다.====\n");
	printf(" 아이디를 입력하세요: ");
	scanf("%s", id);
	printf(" 비밀번호를 입력하세요: ");
	scanf("%s", passwd);
	for(i=0; i<minfo; i++) 
	{
		if(strcmp(id,info[i].id)==0 && strcmp(passwd,info[i].passwd)==0)

		{
			break;
		}
		else
		{
			printf("====아이디 또는 비밀번호가 틀립니다.====");
			printf("\n\n");
		}
	}
	printf("===로그인이 성공했습니다.===\n");
	board_main(id);
}

void list(struct member *info)  ////사용자 목록 조회
{
	int i;
	printf("사용자 목록을 조회하겠습니다. \n");

	for(i=0; i<minfo; i++) 
	{
		printf("계정 : %s, 이름 : %s, 나이 : %s \n", info[i].id, info[i].name, info[i].age);
	}
}

void modify(struct member *info)
{
	char a[20]; //수정할 아이디 변수
	int i;
	printf(" 수정하실 회원 아이디를 입력하시오:");
	scanf("%s", a);
	printf("***해당 하는 계정 유무가 확인하겠습니다.");
	printf("\n");
	printf("\n");
	for(i=0; i<minfo; i++)  /////////////////cnt대체
	{
		if(strcmp(a,info[i].id)==0)
		{
			while(1)
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
/*
   void withdraw(struct member *info)
   {
   char id[20]; //탈퇴하고자 하는 아이디
   char passwd[20] //탈퇴하고자 하는 비밀번호
   int i,j;

   printf("탈퇴하고자 하는 계정 입력 : " );
   scanf("%s", id);
   printf("비밀번호도 입력하세요 : ");
   scanf("%s", passwd);
   for(i=0; i<pinfo; i++)
   {
   if(strcmp(info[i].id, id)==0 && strcmp(info[i].passwd, passwd)
   {
   for(j=i+1; j<*pinfo; j++)
   {
   strcpy(info[j-1].id, info[j].id);
   strcpy(info[j-1].passwd, info[j].passwd);
   }
   (*pnum)--;
   return ;
   }
   }
   printf("회원님의 정보가 삭제되었습니다. \n");
   }*/

void board_main(char *id)
{
	struct board binfo[100]; //100개 게시물  작성 가능 선언
	while(1)
	{
		int i;
		printf("==== 게시판 페이지입니다. ====\n");
		printf("1. 게시물 작성 \n");
		printf("2. 게시물 삭제 \n");
		printf("3. 게시물 목록 \n");
		printf("4. 내가 쓴 게시물 확인 \n");
		printf("5. 나가기 \n");
		printf("6. 로그아웃 \n");
		printf(" 이용하실 기능에 대한 번호를 입력하세요 : ");
		scanf("%d", &i);
		printf("\n");

		//		if(i==1)
		//		{
		//			write_board();
		//		}
		//		if(i==2)
		//		{
		//			delete_board();
		//		if(i==3)
		//		{
		//			list_board();
		//		}
		//		if(i==4)
		//		{
		//			check_mydoc();
		//		}
		if(i==5)
		{
			main();
		}
		//		if(i==6)
		//		{
		//			save_bdata();
		//			break;
		//		}
		//		default;
		//			printf("다시 입력해주세요\n");
	}
	}

