#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int minfo; //회원정보수
int binfo; //보드정보수
typedef struct member   ////회원가입 양식 구조체
{
	char id[20];
	char passwd[20];
	char name[20];
	char age[20];
} Member;

typedef struct board     ////게시판 양식 구조체
{
	char ID[30];
	char title[60];
	char tnum[30];
	char content[1000];
} Board;

int search_mdata(Member *info, char *str, int minfo); //회원정보 찾기
int search_login(Member *info, char *ID, char *Passwd, int minfo);
void signup(Member *info, int *minfo);  //회원가입 함수 선언 
void login(Member *info, int *minfo); // 로그인 함수 선언
void list(Member *info, int minfo);  //회원목록 함수 선언
void modify(Member *info, int *minfo); // 회원정보 수정 함수 선언
void withdraw(Member *info, int *minfo); //회원탈퇴 함수 선언
void load_mdata(Member *info, int *minfo); //회원정보 파일 로드 함수 선언
void save_mdata(Member *info, int minfo); //회원정보 파일 세이브 함수 선언
void board_main(char *str); //게시판 메인 함수
void board_write(Board *txt, int *binfo, char *write_id); //게시판 글쓰기 함수
void board_delete(Board *txt, int *binfo, char *write_id); //게시판 글삭제 함수
void board_modify(Board *txt, int *binfo, char *write_id); //게시판 글수정 함수
void board_list(Board *txt, int binfo); //게시판 글목록 함수
void board_mylist(Board *txt, int *binfo, char *write_id); //내가 쓴글 확인 함수
void include_id(Board *txt, int *binfo); //특정 사용자가 쓴 글 확인 함수
void include_word(Board *txt, int *binfo); //특정 단어가 포함된 글 확인 함수
void load_bdata(Board *txt, int *binfo); //게시판 파일 로드 데이터 함수
void save_bdata(Board *txt, int binfo); //게시판 파일 세이브 데이터 함수




/*프로그램 메인 함수*/
int main()
{	
	Member info[100]; // 100명 가입 선언
	int m_number=0;
	load_mdata(info, &m_number);
	int n;
	n=0;
	while(1)  ///프로그램 실행중에 안꺼지게 설정
	{
		//	struct member info[100];  //100명 가입 선언
		printf("==== 게시판 프로그램 1.0ver ==== \n");
		printf("1. 회원가입 \n");
		printf("2. 로그인 \n");
		printf("3. 회원정보 수정 \n");
		printf("4. 회원목록 확인 \n");
		printf("5. 회원탈퇴 \n");
		printf("6. 게시판 프로그램 종료 \n");
		printf(" \n");
		printf(" 이용하실 기능에 대한  번호를 입력하세요: ");
		scanf("%d", &n);
		printf("\n");

		if(n==1)
		{
			signup(info, &m_number);
			save_mdata(info, m_number);	
		}
		if(n==2)
		{	
			login(info, &m_number);
		}
		if(n==3)
		{
			modify(info, &m_number);	
			//	save_mdata(info, m_number);
		}
		if(n==4)
		{
			list(info, m_number);
		}
		if(n==5)
		{
			withdraw(info, &m_number);
			save_mdata(info, m_number);
		}
		if(n==6)
		{
			printf(" 게시판 프로그램을 종료합니다 \n");
			break ;
		}
	}
	return 0;
}


/*저장된 회원정보 로드 함수*/
void load_mdata(Member *info, int *minfo)
{
	int ret;
	FILE *fps;
	fps=fopen("member_info.txt", "rt");
	if(fps==NULL)
	{
		printf("파일 로드를  실패했습니다");	
	}
	while(1)
	{
		ret=fscanf(fps, "%s %s %s %s", info[*minfo].id, info[*minfo].passwd, info[*minfo].name, info[*minfo].age);

		if(ret==EOF)
		{
			break;
		}
		(*minfo)++;
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

/*회원가입 함수*/
void signup(Member *info, int *minfo)
{
	int n;
	char sign_id[20];
	char sign_passwd[20];
	char sign_name[20];
	char sign_age[20];

	printf("회원가입을 계속 하시겠습니다? 1. 예 2. 아니요 ");
	scanf("%d", &n);

	if(n==1)
	{	
		printf("아이디 : ");
		scanf("%s", sign_id);
		if(search_mdata(info, sign_id, *minfo)==1)
			//if(strcmp(sign_id, info[*minfo].id)==0)
		{
			printf("동일한 ID가 있습니다 \n");
		}
		else
		{
			printf("가입가능한 ID입니다. 나머지 정보를 입력해주세요 \n");
			printf("패스워드 : ");
			scanf("%s", sign_passwd);
			printf("이름 : ");
			scanf("%s", sign_name);
			printf("나이 :");
			scanf("%s", sign_age);
			strcpy(info[*minfo].id, sign_id);
			strcpy(info[*minfo].passwd, sign_passwd);
			strcpy(info[*minfo].name, sign_name);
			strcpy(info[*minfo].age, sign_age);
			(*minfo)++; //가입된 회원 수 추가
			printf("회원가입이 완료되었습니다. \n");
		}
	}
	else if(n==2)
	{
		printf("====메인화면으로 돌아가겠습니다.==== \n");
		main();
	}
	else
	{
		printf("====메인화면으로 돌아가겠습니다. ==== \n");
		main();
	}

}

/*회원정보 파일 저장 함수*/
void save_mdata(Member *info, int minfo)
{
	int i;
	FILE *fp;
	fp=fopen("member_info.txt", "wt");
	if(fp==NULL)
	{
		printf("파일을 여는데 실패했습니다");
	}

	//fprintf(fp, "전체 회원수 : %d \n", minfo);
	for(i=0; i<minfo; i++)
	{
		fprintf(fp, "%s %s %s %s" ,info[i].id, info[i].passwd, info[i].name, info[i].age);
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


/*로그인 함수*/
void login(Member *info, int *minfo)                     
{	
	char login_id[30]; //아이디
	char login_passwd[30]; //비밀번호
	int i;
	printf("====로그인 화면입니다.====\n");
	while(1)
	{
		printf(" 아이디를 입력하세요: ");
		scanf("%s", login_id);
		printf(" 비밀번호를 입력하세요: ");
		scanf("%s", login_passwd);
		if(search_login(info, login_id, login_passwd, *minfo)==1)
		{
			break;
		}
		else
		{
			printf(" 로그인을 실패했습니다.\n");
			printf(" 계정정보를 다시 입력하십시오.\n");
		}
	}
	printf("==== 로그인이 성공했습니다. ====\n");
	board_main(login_id);
}
/*for(i=0; i<*minfo; i++) 
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


  printf("===로그인이 성공했습니다.===\n");/
  board_main(str_id);
  G }
  */

/*사용자 목록 조회 함수*/
void list(Member *info, int minfo)
{
	int i;
	printf("사용자 목록을 조회하겠습니다. \n");
	for(i=0; i<minfo; i++) 
	{
		printf("계정 : %s 패스워드 : %s 이름 : %s 나이 : %s \n", info[i].id, info[i].passwd, info[i].name, info[i].age);
	}
}

/*회원정보 수정 함수*/
void modify(Member *info, int *minfo)
{
	char m_id[30]; //수정할 아이디 변수
	int i;
	printf(" 수정하실 회원 아이디를 입력하시오:");
	scanf("%s", m_id);
	printf("***해당 하는 계정 유무가 확인하겠습니다.");
	printf("\n");
	printf("\n");
	for(i=0; i<*minfo; i++)  
	{
		if(strcmp(m_id,info[i].id)==0)
		{
			//	while(1)
			//	{
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
			//	}


		}
		else
		{
			printf(" ====일치하는 계정이 없습니다 메인화면으로 돌아가겠습니다.==== \n");
		}
	}
}

/*회원탈퇴 함수*/
void withdraw(Member *info, int *minfo)
{
	char del_id[20];
	char del_passwd[20];
	int i,j,n;

	printf(" 회원탈퇴를 시작하겠습니다.\n");
	printf(" 탈퇴 계정을 입력하세요 : ");
	scanf("%s", del_id);
	printf(" 비밀번호를 입력하세요 : ");
	scanf("%s", del_passwd);
	for(i=0; i<*minfo; i++)
	{
		if(strcmp(info[i].id, del_id)==0 && strcmp(info[i].passwd, del_passwd)==0)
		{
			printf("탈퇴하고자 하는 계정이 존재합니다. 탈퇴진행하겠습니다. \n");
			for(j=i+1; j<*minfo; j++)
			{
				strcpy(info[j-1].id, info[j].id);
				strcpy(info[j-1].passwd, info[j].passwd);
				strcpy(info[j-1].name, info[j].name);
				strcpy(info[j-1].age, info[j].age);
			}
			(*minfo)--;
			printf(" 데이터가 삭제되었습니다. 메인으로 돌아갑니다. \n");
		}
	}
}

/*회원가입시 id 유무 서치함수*/
int search_mdata(Member *info, char *str, int minfo) 
{
	char find_id[20];
	int i;
	strcpy(find_id, str);
	for(i=0; i<minfo; i++)
	{
		if(strcmp(info[i].id, find_id)==0)
		{
			return 1;
		}
	}
}

/*로그인 계정일치 서치함수*/
int search_login(Member *info, char *ID, char *Passwd, int minfo)
{
	char login_id[20];
	char login_passwd[20];
	int i;
	strcpy(login_id,ID);
	strcpy(login_passwd,Passwd);
	for(i=0; i<minfo; i++)
	{
		if(strcmp(info[i].id,login_id)==0 && strcmp(info[i].passwd,login_passwd)==0)
		{
			return 1;
		}
	}
}

/*게시판 메인함수*/
void board_main(char *str)
{
	Board txt[100]; //100개 게시물  작성 가능 선언
	char user_id[30]; //사용중인 유저
	char user_passwd[30];
	int b_number=0;
	int n;
	load_bdata(txt, &b_number);
	strcpy(user_id, str);
	//	strcpy(user_passwd, str);


	while(1)
	{
		printf("==== 게시판 페이지입니다. ====\n");
		printf("1. 게시물 작성 \n");
		printf("2. 게시물 삭제 \n");
		printf("3. 게시물 수정 \n");
		printf("4. 게시물 목록 \n");
		printf("5. 로그아웃 \n");
		printf("6. 내가 쓴 글 확인  \n");
		printf("7. 특정 사용자가 쓴 글 확인 \n");
		printf("8. 특정 단어가 포함된 글 확인 \n");
		printf(" 이용하실 기능에 대한 번호를 입력하세요 : ");
		scanf("%d", &n);
		printf("\n");
		if(n==1)
		{
			board_write(txt, &b_number, str);
			save_bdata(txt, b_number);
		}
		else if(n==2)
		{
			board_delete(txt, &b_number, str);
			save_bdata(txt, b_number);
		}
		else if(n==3)
		{
			board_modify(txt, &b_number, str);
			save_bdata(txt, b_number);
		}
		else if(n==4)
		{
			board_list(txt, b_number);
		}
		else if(n==5)
		{
			break;	
		}
		else if(n==6)
		{	
			board_mylist(txt, &b_number, str);
		}
		else if(n==7)
		{
			include_id(txt, &b_number);
		}
		else if(n==8)
		{
			include_word(txt, &b_number);
		}
		else
		{
			printf("==== 다시 입력해주세요====\n");
			printf(" \n\n\n");
		}
	}
}

/*게시판 글쓰기 함수*/
void board_write(Board *txt, int *binfo, char *write_id)	
{
	int n;
	char write_title[60];
	char write_content[1000];
	getchar();
	printf("제목을 입력해 주십시오 \n");
	printf("제목 : ");
	fgets(write_title, 60, stdin);
	write_title[strlen(write_title)-1]=0;
	printf("내용을 입력해 주십시오 \n");
	printf("내용 : ");
	fgets(write_content, 1000, stdin);
	write_content[strlen(write_content)-1]=0;
	strcpy(txt[*binfo].title, write_title);
	strcpy(txt[*binfo].content, write_content);
	strcpy(txt[*binfo].ID, write_id);
	(*binfo)++;
}

void board_delete(Board *txt, int *binfo, char *write_id)
{
	char del_title[60];
	int i,j;

	printf(" 게시판 글 삭제를 하겠습니다. \n");
	getchar();
	printf(" 삭제할 글 제목을 입력하세요. : ");
	fgets(del_title, 60, stdin);
	del_title[strlen(del_title)-1]=0;
	printf("작성자가 게시한 글의 제목과 일치하는 글 유무를 확인하겠습니다. \n");

	for(i=0; i<*binfo; i++)
	{
		if(strcmp(del_title, txt[i].title)==0 && strcmp(txt[i].ID, write_id)==0)
		{
			printf("해당 글을 삭제하겠습니다 \n");
			for(j=i+1; j<*binfo; j++)
			{
				strcpy(txt[j-1].ID, txt[j].ID);
				strcpy(txt[j-1].title, txt[j].title);
				strcpy(txt[j-1].content, txt[j].content);
			}
			(*binfo)--;
			printf("게시글이 삭제되었습니다. 메인으로 돌아갑니다. \n");
		}
		else if(strcmp(txt[i].title, del_title)==0 && strcmp(txt[i].ID, write_id)!=0)
		{
			printf("작성자와 현재 사용자 정보가 다릅니다.\n");
		}
		else if(strcmp(txt[i].title, del_title)!=0 && strcmp(txt[i].ID, write_id)==0)
		{
			printf("입력하신 제목의 게시글이 존재하지 않습니다. \n");
		}
		else
		{
			printf(" 입력하신 게시글과 계정을 모두 찾을 수 없습니다. \n");
		}
	}
}


/*게시판 글수정 함수*/
void board_modify(Board *txt, int *binfo, char *write_id)
{
	char modify_title[60];
	int i;
	getchar();
	printf(" 수정하실 글 제목을 입력하시오: ");
	fgets(modify_title, 60, stdin);
	modify_title[strlen(modify_title)-1]=0;
	printf("해당 하는 글 유무를 확인하겠습니다.");
	printf("\n");

	for(i=0; i<*binfo; i++)
	{	//if(strcmp(modify_title, txt[i].title)==0)
		if(strcmp(modify_title, txt[i].title)==0 && strcmp(write_id, txt[i].ID)==0)
		{
			printf("==== 제목과 일치하는 글을 찾았습니다. ====\n");
			printf("제목을 수정하십시오. : ");
			fgets(txt[i].title, 60, stdin);
			txt[i].title[strlen(txt[i].title)-1]=0;
			printf("내용을 수정하십시오. : ");
			fgets(txt[i].content, 1000, stdin);
			txt[i].content[strlen(txt[i].content)-1]=0;
		}
		else if(strcmp(modify_title, txt[i].title)==0 && strcmp(write_id, txt[i].ID)!=0)
		{
			printf("작성자와 현재 사용자가 다릅니다.\n");
		}
		else if(strcmp(modify_title, txt[i].title)!=0 && strcmp(write_id, txt[i].ID)==0)
		{	
			printf("입력하신 제목의 게시글이 존재하지 않습니다. \n");
		}
		else
		{
			printf("입력하신값이 모두 잘못되었습니다. \n");
		}
	}
}


/*게시판 글목록 함수*/
void board_list(Board *txt, int binfo)
{
	int i;
	printf(" ====게시판 목록을 조회합니다.==== \n");
	for(i=0; i<binfo; i++)
	{
		printf("글번호 : %d, 사용자 : %s, 제목 : %s, 내용 : %s \n",i+1, txt[i].ID, txt[i].title, txt[i].content);
	}
}

/*내가 쓴 글 확인 함수 */
void board_mylist(Board *txt, int *binfo, char *write_id)
{
	char check_id[20];
	int i,j;
	printf(" ==== 내가 쓴 글 목록입니다. === \n");
	for(i=0; i<(*binfo); i++)
	{
		if(strcmp(txt[i].ID, write_id)==0)
		{
				printf("글번호 : %d, 사용자 :%s, 제목 : %s, 내용 : %s \n" \
						, i, txt[i].ID,txt[i].title, txt[i].content);
		}
	}
}

/*특정 사용자가 쓴 글 확인 함수*/
void include_id(Board *txt,  int *binfo)
{
	char search_id[20];
	int i;
	printf(" 특정 사용자가 쓴 글을 확인하겠습니다. \n");
	getchar();
	printf("사용자 계정을 입력해주십시오. : ");
	fgets(search_id, 20, stdin);
	search_id[strlen(search_id)-1]=0;
	fputs(" ==== ", stdout);
	fputs(search_id, stdout);
	fputs("님이 쓴 게시글 목록입니다. ====\n", stdout);
	/*
	printf("사용자 계정을 입력해주십시오. ");
	scanf("%s", search_id);
	printf(" ==== %s님이 쓴 게시글 목록입니다. ==== \n", search_id);
	*/
	for(i=0; i<(*binfo); i++)
	{
		if(strcmp(txt[i].ID, search_id)==0)
		{
			printf("글번호 : %d, 사용자 : %s, 제목 : %s, 내용 : %s \n" , i, txt[i].ID, txt[i].title, txt[i].content);
		}
	}
}	

/*특정 단어가 포함된 글 확인 함수*/
void include_word(Board *txt, int *binfo)
{
	char search_word[100];
	int i;
	/*
	printf("특정 단어가 포함된 글을 찾겠습니다. \n");
	gethchar();
	printf("단어를 입력해주십시오. \n");
	fgets(search_word, 100, stdin);
	search_word[strlen(search_word)-1]=0;
	printf("특정 단어가 포함된 글을 찾겠습니다.");
	printf("\n");
	*/
	printf(" 특정단어가 포함된 글을 찾겠습니다. \n");
	printf(" 단어를 입력해 주십시오. :");
	scanf("%s", search_word);
	
	for(i=0; i<(*binfo); i++)
	{
		if(strstr(txt[i].content, search_word)==0)
		{
			printf("글 번호 : %d, 사용자 %s, 제목 : %s, 내용 : %s \n", \
					i, txt[i].ID,txt[i].title, txt[i].content);
		}
	}


}

/*게시판 글 저장 함수*/
void save_bdata(Board *txt, int binfo)
{
	int i;
	FILE *fp;
	fp=fopen("board_info.txt", "wt");
	if(fp==NULL)
	{
		printf("파일을 여는데 실패했습니다");
	}

	for(i=0; i<binfo; i++)
	{
		fprintf(fp, "%s %s %s \n" ,txt[i].ID, txt[i].title, txt[i].content);
	}
	fflush(fp);
	fclose(fp);
}

/*게시판 글 로드 함수*/
void load_bdata(Board *txt, int *binfo)
{
	int ret;  //fscanf에 필요한 변수
	FILE *fps;
	fps=fopen("board_info.txt", "rt");
	if(fps==NULL)
	{
		printf(" 파일 로드를 실패했습니다.");
	}
	while(1)
	{
		ret=fscanf(fps,"%s %s %s \n", txt[*binfo].ID, txt[*binfo].title, txt[*binfo].content);

		if(ret==EOF)
		{
			break;
		}
		(*binfo)++;
	}
	fclose(fps);
}
/* 아직 접근안했음 나중에 할 것 우선 글 삭제와 수정부터 해결후 진행할 
   void board_check()
   {
   int n;
   n=0;
   while(1)
   {
   printf("==== 게시판 탐색 화면  ====\n");
   printf("1. 전체 글 확인. \n");
   printf("2. 게시글 수정. \n");
   printf("3. 내가 쓴 글 확인. \n");
   printf("4. 특정 사용자가 쓴 글 확인. \n");
   printf("5. 특정 단어가 포함된 글 확인. \n");
   printf("\n");
   printf("이용하실 기능에 대한 번호를 입력하세요: ");
   scanf("%d", &n);
   printf("\n");

   if(n==1)
   {
   board_lists(Board *txt, int binfo);
   }
   if(n==2)
   {
   board_modify(Board *txt, int *binfo);
   }
   if(n==3)
   {
   board_mydoc(Board *txt, int binfo);
   }
   if(n==4)
   {
   board_finduser(Board *txt, int *binfo);
   }
   if(n==5)
   {
   board_findword(Board *txt, int *binfo);
   }
   if(n==6)
   {
   printf("게시판 메인으로 돌아갑니다. \n");
   break;
   }

   }
   }
   */
