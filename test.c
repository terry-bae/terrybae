#include <stdio.h>


#include <string.h>


#include <stdlib.h>


#include <time.h>





/*매크로함수*/


#define LEN 30 //LEN이라는길이는30으로정의


#define MAX_P 100


#define MAX_BOARD 100





/*구조체함수*/


typedef struct person


{


	char id[LEN];


	char password[LEN];


}Person;//회원구조체








typedef struct board


{


	char ID[LEN];


	char Title[LEN];


	char T_num[LEN];


	char Content[300];


}Board;//게시물구조체





int Search_Data_p(Person *p,char *str ,int pnum);


int Search_Data_login(Person *p,char *ID,char *Password ,int pnum);


void Print_Data(Person *p, int pnum);


void Print_Data_board(Board *b, int bnum);


void Load_data_person(Person *p, int *pnum);


void Load_data_board(Board *b, int *bnum);


void Save_Data_p(Person *p ,int pnum);


void Save_Data_board(Board *b ,int bnum);


void member_register(Person *p, int *pnum);


void Delete_Data(Person *p ,int *pnum);


void Login_page(Person *p, int *pnum);


void show_board_list(void);


void board_page(char *str);


void write_board(Board *b, int *bnum, char *ID_str);


void Print_Data_board_var_select(Board *b, int bnum);





void board_page(char *str)


{


	int select=0;


	char ID_temp[LEN];


	int board_number=0;


	Board b_chart[MAX_BOARD];


	Load_data_board(b_chart,&board_number);


	strcpy(ID_temp,str);


	printf("%s\n",ID_temp);





	while(1)


	{


		show_board_list();


		printf("SELECT :");scanf("%d",&select);





		switch(select)


		{


			case 1:


				printf("---------------------->작성\n");


				write_board(b_chart,&board_number, str);


				break;


			case 2:

				printf("---------------------->수정\n");


				break;


			case 3:


				printf("---------------------->삭제\n");


				break; 


			case 4:


				printf("---------------------->목록\n");


				printf("----------->print all board\n");


				Print_Data_board_var_select(b_chart,board_number);


				break;


			case 5:


				printf("-------->내가작성한게시물\n");


				break;


			case 6:


				printf("-------------------->LOGOUT\n");


				Save_Data_board(b_chart,board_number);


				main();


				break;


			case 7:


				printf("----------->print all board\n");


				Print_Data_board(b_chart,board_number);


				break;


			default:


				printf("다시입력하세요\n");//재입력


		}


	}


}





/*로그인페이지*/


void Login_page(Person *p, int *pnum)


{


	char str_id[LEN];


	char str_password[LEN];


	while(1)


	{


		printf("ID :");scanf("%s",str_id);


		printf("Password :");scanf("%s",str_password);


		if(Search_Data_login(p, str_id, str_password ,*pnum)==1)


		{


			break;


		}


		else


		{


			printf("Login 실패\n");


		}


	}


	printf("Login 성공\n");


	board_page(str_id);


}





int main(void)


{


	Person member[MAX_P];


	int P_number=0;


	int select;//선택변수


	Load_data_person(member,&P_number);


	while(1)


	{


		printf("********MENU********\n");


		printf("1.회원가입\n");


		printf("2.로그인\n");


		printf("3.회원탈퇴\n");


		printf("SELECT :");scanf("%d",&select);





		switch(select)


		{


			case 1:


				printf("------------->회원가입\n");


				member_register(member, &P_number);//1번을선택시회원가입함수로


				Save_Data_p(member, P_number);//텍스트파일에회원가입내용저장


				break;


			case 2:


				printf("---------------->LOGIN\n");


				Login_page(member, &P_number);//2번을선택시로그인함수로


				break;


			case 3:


				printf("------------->회원탈퇴\n");


				Delete_Data(member, &P_number);


				Save_Data_p(member, P_number);


				break; 


			case 4:


				Print_Data(member, P_number);


				break;


			default:


				printf("다시입력하세요\n");//재입력


		}


	}

	return 0;

}





/*로드회원데이터*/


void Load_data_person(Person *p, int *pnum)


{


	int ret;


	FILE *fp=fopen("Login_info.txt","rt");


	if(fp==NULL)


	{


		printf("File open error");


	}      


	while(1)


	{


		ret=fscanf(fp,"%s %s",p[*pnum].id,p[*pnum].password);


		if(ret==EOF)


		{


			break;   


		}


		(*pnum)++;


	}


	fclose(fp);


}





/*프린트회원데이터*/


void Print_Data(Person *p, int pnum)


{


	int i;


	printf("*******Printf All ID Data*******\n");


	for(i=0; i<pnum; i++)


	{


		printf("//ID:%s//Password:%s\n",p[i].id,p[i].password);


	}


}


/*아이디찾기*/


int Search_Data_p(Person *p,char *str ,int pnum)


{


	char name[LEN];


	int i;


	strcpy(name,str);


	for(i=0; i<pnum; i++)


	{

		if(strcmp(p[i].id,name)==0)


		{


			return 1;     


		}


	}

}


/*로그인아이디패스워드검색*/


int Search_Data_login(Person *p,char *ID,char *Password ,int pnum)

{


	char ID_temp[LEN];


	char Password_temp[LEN];


	int i;


	strcpy(ID_temp,ID);


	strcpy(Password_temp,Password);


	for(i=0; i<pnum; i++)


	{


		if(strcmp(p[i].id,ID_temp)==0&&strcmp(p[i].password,Password_temp)==0)


		{


			return 1;     


		}


	}


}


/*회원등록*/


void member_register(Person *p, int *pnum)

{


	char str_id[LEN];


	char str_password[LEN];


	printf("id :");


	scanf("%s",str_id);


	getchar();


	if(Search_Data_p(p, str_id ,*pnum)==1)


	{


		printf("동일한ID존재\n");


	}


	else


	{


		printf("가입가능\n");


		printf("Password:");scanf("%s",str_password);


		strcpy(p[*pnum].id,str_id);


		strcpy(p[*pnum].password,str_password);


		(*pnum)++;


	}


}


/*회원정보텍스트저장*/


void Save_Data_p(Person *p ,int pnum)


{


	int i;


	FILE *fp=fopen("Login_info.txt","wt");


	if(fp==NULL)


	{


		printf("File open error");


	}


	for(i=0; i<pnum; i++)


	{


		fprintf(fp,"%s %s",p[i].id,p[i].password);


		fputc('\n',fp);


	}


	fflush(fp);


	fclose(fp);


}


/*회원탈퇴함수*/


void Delete_Data(Person *p ,int *pnum)


{


	char ID[LEN];


	char Password[LEN];


	int i,j;


	printf("ID:");scanf("%s",ID);


	printf("Password:");scanf("%s",Password);


	for(i=0; i<*pnum; i++)


	{


		if(strcmp(p[i].id, ID)==0&&strcmp(p[i].password, Password)==0)


		{


			for(j=i+1; j<*pnum; j++)


			{      


				strcpy(p[j-1].id, p[j].id);


				strcpy(p[j-1].password, p[j].password);


			}


			(*pnum)--;


			printf("-------->회원탈퇴성공\n");


			return;


		}


	}


	printf("Data not found\n");


}


/*게시판리스트*/


void show_board_list(void)
{


	printf("*******BOARD MENU*******\n");

	printf("1.게시물작성\n");
	printf("2.게시물수정\n");

	printf("3.게시물삭제\n");


	printf("4.게시물목록\n");


	printf("5.작성한게시물보기\n");


	printf("6.LOGOUT\n");


}


/*프린트게시판번호아이디제목내용*/


void Print_Data_board(Board *b, int bnum)


{


	int i;


	printf("*******Printf All*******\n");


	for(i=0; i<bnum; i++)


	{


		printf("//NUMBER:%d//ID:%s//TITLE:%s//CONTENT:%s",i+1,b[i].ID,b[i].Title,b[i].Content);


	}


}


/*프린트게시판번호제목and 선택사항의내용보기*/


void Print_Data_board_var_select(Board *b, int bnum)


{


	int i;


	int select;


	printf("*******Printf All*******\n");


	for(i=0; i<bnum; i++)


	{

		printf("NUM:%d//TITLE:%s\n",i+1,b[i].Title);


	}


	while(1)


	{


		printf("뒤로가려면-1을입력!\n제목의num을입력하세요:");scanf("%d",&select);


		if(select==-1)


		{


			break;


		}


		printf("Title:%s\nContent:%s\n",b[select-1].Title,b[select-1].Content);


	}





}


/*게시판작성*/


void write_board(Board *b, int *bnum, char *ID_str)


{


	char title_temp[LEN];


	char content_temp[LEN];


	getchar();


	printf("******insert Board******\n");


	printf("TITLE:");fgets(title_temp,LEN,stdin);


	title_temp[strlen(title_temp)-1]=0;


	printf("CONTENT:");fgets(content_temp,LEN*10,stdin);


	content_temp[strlen(content_temp)-1]=0;


	strcpy(b[*bnum].Title,title_temp);


	strcpy(b[*bnum].Content,content_temp);


	strcpy(b[*bnum].ID,ID_str);


	(*bnum)++;


}





/*로드게시물데이터*/


void Load_data_board(Board *b, int *bnum)


{


	int ret;


	FILE *fp=fopen("Board.txt","r");


	if(fp==NULL)


	{                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           printf("File open error");

	}      


	while(1)


	{


		ret=fscanf(fp,"#%[^#]#%[^#]#%[^#]", b[*bnum].ID, b[*bnum].Title, b[*bnum].Content);


		if(ret==EOF)


		{


			break;   


		}


		(*bnum)++;


	}


	fclose(fp);


}





/*게시물텍스트저장함수*/


void Save_Data_board(Board *b ,int bnum)


{


	int i;


	FILE *fp=fopen("Board.txt","wt");


	if(fp==NULL)


	{


		printf("File open error");


	}


	for(i=0; i<bnum; i++)


	{


		fprintf(fp,"#%s#%s#%s", b[i].ID, b[i].Title, b[i].Content);


		fputc('\n',fp);


	}


	fflush(fp);


	fclose(fp);


}

