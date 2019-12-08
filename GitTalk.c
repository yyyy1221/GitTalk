#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <termio.h>
#define CLEAR_BUFFER() {int ch; while((ch = getchar()) != EOF && ch != '\n'){}}

void main_menu_print(void);
void main_menu(void);
void chatting_menu_print(void);
void chatting_menu(void);
void sign_up(void);
int log_in(void);
void refresh(void);
void make_chatting_room(void);
void chatting(char *);
void *refresh_routine(void *);
char* show_list(void);
int getch(void);
void password_look_star(char[]);
int overlap_title_check(char[]);
void scanf_int(int*, int, int);
void scanf_str(char*);
void scanf_char(char*, char, char);
int getTotalLine(char *name);	// 파일의 라인 수 리턴하는 함수

int main(){
	system("clear");
	main_menu();
	return 0;
}

int getch(void){
    int ch;
    struct termios buf, save;
    tcgetattr(0,&save);
    buf = save;
    buf.c_lflag &= ~(ICANON|ECHO);
    buf.c_cc[VMIN] = 1;
    buf.c_cc[VTIME] = 0;
    tcsetattr(0, TCSAFLUSH, &buf);
    ch = getchar();
    tcsetattr(0, TCSAFLUSH, &save);
    return ch;
}
void main_menu_print(void){
	printf("�뵆����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������뵍\n");
	printf("�봻                                                                             �봻\n");
	printf("�봻                                   GitTalk                                   �봻\n");
	printf("�봻                                                                             �봻\n");
	printf("�뵜����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������뵥\n");
	printf("�봻                                                                             �봻\n");
	printf("�봻                                1. �쉶�썝媛��엯                                  �봻\n");
	printf("�봻                                2. 濡쒓렇�씤                                    �봻\n");
	printf("�봻                                3. �봽濡쒓렇�옩 醫낅즺                             �봻\n");
	printf("�봻                                                                             �봻\n");
	printf("�뵒����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������뵖\n");
	printf(" 踰덊샇瑜� �꽑�깮�븯�꽭�슂 : ");
}
void main_menu(void){
	int num, exit_code;
	while(1){
		main_menu_print();
		scanf_int(&num, 1, 3);
		switch(num){
			case 1:
				sign_up();
				break;
			case 2:
				exit_code = log_in();
				if (exit_code){
					chatting_menu();
					system("clear");
				}
				break;
			case 3:
				exit(0);
				break;
			// default :
			// 	printf("�옒紐삳맂 踰덊샇�엯�땲�떎. �떎�떆 �엯�젰�븯�꽭�슂.");
			// 	sleep(2);
			// 	system("clear");
		}
	}
}
void chatting_menu_print(void){
	printf("�뵆����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������뵍\n");
	printf("�봻                                                                             �봻\n");
	printf("�봻                                   GitTalk                                   �봻\n");
	printf("�봻                                                                             �봻\n");
	printf("�뵜����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������뵥\n");
	printf("�봻                                                                             �봻\n");
	printf("�봻                                1. 梨꾪똿諛� �벑濡�                               �봻\n");
	printf("�봻                                2. 梨꾪똿諛� 紐⑸줉                               �봻\n");
	printf("�봻                                3. 濡쒓렇�븘�썐                                  �봻\n");
	printf("�봻                                                                             �봻\n");
	printf("�뵒����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������뵖\n");
	printf(" 踰덊샇瑜� �꽑�깮�븯�꽭�슂 : ");
}
void chatting_menu(void){
	FILE *name_fp;
	char name[30];
	char push_string[100] = "";		
	if((name_fp = fopen("./name.txt", "rt")) == NULL){
		printf("ID �뙆�씪�씠 議댁옱�븯吏� �븡�뒿�땲�떎. �쉶�썝媛��엯�쓣 �떎�떆 吏꾪뻾�빐二쇱꽭�슂.\n");
		return;
	}
	fscanf(name_fp,"%s",name);
	fclose(name_fp);
	int num;

	while(1){
		chatting_menu_print();
		scanf_int(&num, 1, 3);
		switch(num){
			// 梨꾪똿諛� �벑濡� 
			case 1:
				make_chatting_room();
				break;
			// 蹂몄씤�씠 �룷�븿�맂 梨꾪똿諛� 寃��깋
			case 2:
				chatting(show_list());
				break;
			// 濡쒓렇�븘�썐
			case 3:
				return;
				break;
			default:
				printf("�옒紐삳맂 踰덊샇�엯�땲�떎. �떎�떆 �엯�젰�븯�꽭�슂.");
				sleep(2);
				system("clear");
		}
	}
}
void sign_up(void){
	char echo_string_ID[50] = "echo ";
	char echo_string_PW[50] = "echo ";
	char ID[30];
	char PW[30];
	char string_push[100] = "git push https://";
	char check_string[100] = "";
	char check_compare[100] = "remote: Invalid username or password.\n";
	FILE *pFile;
	
	system("clear");
	printf("�뵆����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������뵍\n");
	printf("�봻                                                                             �봻\n");
	printf("�봻                               GitTalk �쉶�썝媛��엯                              �봻\n");
	printf("�봻                                                                             �봻\n");
	printf("�뵒����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������뵖\n");	
	printf(" Github �븘�씠�뵒瑜� �엯�젰�븯�꽭�슂 : ");
	scanf_str(ID);

	printf(" Github 鍮꾨��踰덊샇瑜� �엯�젰�븯�꽭�슂 : ");
	scanf_str(PW);

	strcat(string_push, ID); //git push https://ID
	strcat(string_push, ":"); //git push https://ID:
	strcat(string_push, PW); //git push https://name:PW
	strcat(string_push, "@github.com/noino0819/GitTalk_Test master 2> check.txt");
	system(string_push);

	pFile = fopen("check.txt", "r");
	fgets(check_string, 100, pFile);
	if(strcmp(check_string, check_compare) == 0){ //�쑀�슚�븳 ID媛� �븘�땺 寃쎌슦	
		printf("�쑀�슚�븳 ID��� 鍮꾨��踰덊샇媛� �븘�떃�땲�떎.\n");
		printf("�씠�쟾硫붾돱濡� �룎�븘媛묐땲�떎.\n");
		sleep(2);
		system("clear");
	}
	else{
	strcat(echo_string_ID, ID); //echo ID 
	strcat(echo_string_ID, ">"); //echo ID>
	strcat(echo_string_ID, "name.txt"); //echo ID>name.txt
	system(echo_string_ID);
	strcat(echo_string_PW, PW); //echo PW
	strcat(echo_string_PW, ">"); //echo PW>
	strcat(echo_string_PW, "password.txt"); //echo PW>password.txt
	system(echo_string_PW);

	printf("�쉶�썝媛��엯 �꽦怨�!\n");
	printf("�씠�쟾 硫붾돱濡� �룎�븘媛묐땲�떎.\n");
	sleep(2);
	system("clear");
	}
}
		
int log_in(void){
	FILE *id_fp, *pw_fp;
	char string[30];
	char string_from_file[30];

	/* �쉶�썝媛��엯�쓣 �떎�떆 吏꾪뻾�빐�빞�븷 寃쎌슦 �삤瑜� 肄붾뱶 -1�쓣 return�븯怨� �븿�닔 醫낅즺 */
	if ((id_fp = fopen("./name.txt", "rt")) == NULL){
		printf("ID �뙆�씪�씠 議댁옱�븯吏� �븡�뒿�땲�떎. �쉶�썝媛��엯�쓣 �떎�떆 吏꾪뻾�빐二쇱꽭�슂.\n");
		return -1;
	}

	if ((pw_fp = fopen("./password.txt", "rt")) == NULL){
		printf("鍮꾨��踰덊샇 �뙆�씪�씠 議댁옱�븯吏� �븡�뒿�땲�떎. �쉶�썝媛��엯�쓣 �떎�떆 吏꾪뻾�빐二쇱꽭�슂.\n");
		return -1;
	}

	/* 濡쒓렇�씤�쓣 �떎�떆 吏꾪뻾�빐�빞�븷 寃쎌슦 �삤瑜� 肄붾뱶 0�쓣 return�븯怨� �븿�닔 醫낅즺 */
	system("clear");
	printf("�뵆����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������뵍\n");
	printf("�봻                                                                             �봻\n");
	printf("�봻                               GitTalk 濡쒓렇�씤                                �봻\n");
	printf("�봻                                                                             �봻\n");
	printf("�뵒����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������뵖\n");
	printf(" Github �븘�씠�뵒瑜� �엯�젰�븯�꽭�슂 : ");
	scanf_str(string);
	fscanf(id_fp, "%s", string_from_file);
	if (strcmp(string, string_from_file)){
		printf("\nID媛� �씪移섑븯吏� �븡�뒿�땲�떎. 濡쒓렇�씤�쓣 �떎�떆 吏꾪뻾�빐二쇱꽭�슂.\n");
		sleep(1);
		system("clear");
		return 0;
	}
	printf(" Github 鍮꾨��踰덊샇瑜� �엯�젰�븯�꽭�슂 : ");
	password_look_star(string);
	fscanf(pw_fp, "%s", string_from_file);
	if (strcmp(string, string_from_file)){
		printf("\n鍮꾨��踰덊샇媛� �씪移섑븯吏� �븡�뒿�땲�떎. 濡쒓렇�씤�쓣 �떎�떆 吏꾪뻾�빐二쇱꽭�슂.\n");
		sleep(1);
		system("clear");
		return 0;
	}

	printf("\n\n濡쒓렇�씤�씠 �셿猷뚮릺�뿀�뒿�땲�떎.\n");
	printf("GitTalk�쓣 �떆�옉�빀�땲�떎.\n");
	sleep(1);
	system("clear");

	/* �꽦怨듭쟻�쑝濡� 濡쒓렇�씤�븯����쓣 寃쎌슦 1�쓣 return�븯怨� �븿�닔 醫낅즺 */
	return 1;
}
void refresh(void){
	FILE *name_fp, *pw_fp;
	char name[30];
	char pw[30];
	char push_string[100] = "git push https://";

	name_fp = fopen("./name.txt", "rt");
	pw_fp = fopen("./password.txt", "rt");

	//name.txt �뙆�씪�씠�굹 password.txt �뙆�씪�씠 �뾾�쓣 �븣
	if (name_fp == NULL || pw_fp == NULL){
		printf("�쉶�썝媛��엯�씠 �젣���濡� 吏꾪뻾�릺吏� �븡�븯�뒿�땲�떎.\n");
		return;
	}
	fscanf(name_fp, "%s", name);
	fscanf(pw_fp, "%s", pw);
	
	fclose(name_fp);
	fclose(pw_fp);

	strcat(push_string, name);
	strcat(push_string, ":");
	strcat(push_string, pw);
	strcat(push_string, "@github.com/noino0819/GitTalk master >> bin.txt 2>> bin.txt");

	//https://github.com/noino0810/GitTalk_Test瑜� 由щえ�듃 ����옣�냼 GitTalk�뿉 異붽���뻽�떎怨� 媛��젙
	system("git pull origin master >> bin.txt 2>> bin.txt");
	// system(push_string);
}

void make_chatting_room(void){
	char Git_address[100];
	char echo_remote[100] = "git remote add "; //remote ����옣�냼 �씠由꾩�� 梨꾪똿諛� �씠由꾧낵 �룞�씪.
	FILE* name_fp;
	char echo_string2[50] = "echo  ";
	char name[30];
	char chatting_partner[30];
	char chatting_room_name[50] = "";
	char echo_chattinglist[100] = "echo ";
	int option;
	
	//chatting_list 援ъ“泥� �꽑�뼵 諛� list_num 泥댄겕
	struct chatting_list{
		int num;
		char chatting_room[100];	// 梨꾪똿諛� �씠由�
		int unread;			// �븞�씫��� 硫붿떆吏�
		int individual_or_group;	// 媛쒖씤�넚/�떒�넚
		char key[20];			// �븫�샇�솕 �궎
	}list[100];				// 梨꾪똿諛� 由ъ뒪�듃 100媛� 源뚯�� 
	FILE *list_fp;
	
	if((list_fp = fopen("./chatting_list.txt","rt")) == NULL){
		system("touch chatting_list.txt");
		list_fp = fopen("./chatting_list.txt","rt");
	}
	int list_num = 1;
	char slash;
	while(fscanf(list_fp, "%c",&slash) != EOF)
		if(slash == '\\') list_num++;
	fclose(list_fp);
	//chatting_list

	system("clear");
	printf("�뵆����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������뵍\n");
	printf("�봻                                                                             �봻\n");
	printf("�봻                                 梨꾪똿諛� �깮�꽦                                 �봻\n");
	printf("�봻                                                                             �봻\n");
	printf("�뵒����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������뵖\n");
	printf(" 梨꾪똿諛� �샃�뀡�쓣 �꽑�깮�븯�꽭�슂. (1. 媛쒖씤梨꾪똿諛� 2. �떒泥댁콈�똿諛�) : ");
	scanf_int(&option, 1, 2);
	
	printf("\n梨꾪똿諛⑹쓣 �뾽濡쒕뱶 �븷 github 二쇱냼瑜� �엯�젰�븯�꽭�슂 : ");
	scanf_str(Git_address);
	
	if(option == 1){
		printf("����솕瑜� �썝�븯�뒗 �긽���諛⑹쓽 Git�븘�씠�뵒瑜� �엯�젰�븯�꽭�슂 : ");
		scanf_str(chatting_partner);

		name_fp = fopen("./name.txt", "rt");
		fscanf(name_fp, "%s", name);
		
		if(strcmp(chatting_partner, name) < 0){//partner_name
			strcat(echo_string2, ">"); //echo  >
			strcat(echo_string2, "./Chatting/"); //echo  >./Chatting/
			strcat(echo_string2, chatting_partner); //echo  >./Chatting/chatting_partner
			strcat(echo_string2, "_"); //echo >./Chatting/chatting_partner_
			strcat(echo_string2, name); //echo >./Chatting/chatting_partner_name
			
			strcat(chatting_room_name, chatting_partner);
			strcat(chatting_room_name, "_");
			strcat(chatting_room_name, name); //chatting_room_name = chatting_partner_name
		}
		else if(strcmp(chatting_partner, name) > 0){//name_partner
			strcat(echo_string2, ">"); //echo  >
			strcat(echo_string2, "./Chatting/"); //echo  >./Chatting/
			strcat(echo_string2, name); //echo  >./Chatting/name
			strcat(echo_string2, "_"); //echo  >./Chatting/name_
			strcat(echo_string2, chatting_partner); //echo  >./Chatting/name_chatting_partner

			strcat(chatting_room_name, name);
			strcat(chatting_room_name, "_");
			strcat(chatting_room_name, chatting_partner);//chatting_room_name = name_chatting_partner
		}
		else{
			printf("�옄�떊怨쇱쓽 ����솕");
		}
	}
	else if(option == 2){
		printf("�깮�꽦�븷 梨꾪똿諛⑹쓽 �씠由꾩쓣 �엯�젰�븯�꽭�슂 : ");
		scanf_str(chatting_room_name);
		strcat(echo_string2, ">"); //echo  >
		strcat(echo_string2, "./Chatting/"); //echo  >./Chatting/
		strcat(echo_string2, chatting_room_name); //echo  >./Chatting/chatting_room_name
	}
	
	// chatting_list �뙆�씪�뿉 吏��젙�맂 �삎�떇���濡� �엯�젰
	list_fp = fopen("./chatting_list.txt","at");
	
	list[list_num].num = list_num;
	strcpy(list[list_num].chatting_room, chatting_room_name);
	list[list_num].unread = 0;
	list[list_num].individual_or_group = option;
	strcpy(list[list_num].key,"random");			
	// �븫�샇�솕�궎 �깮�꽦 異붽�� �삁�젙 (�옖�뜡 �궃�닔 �샊��� �뒪�듃留�)
		
	fprintf(list_fp, "%d %s %d %d %s;\n",
			list[list_num].num,
			list[list_num].chatting_room,
			list[list_num].unread,
			list[list_num].individual_or_group,
			list[list_num].key);
	fclose(list_fp);
	// chatting_list
	
	if(overlap_title_check(chatting_room_name) == 0){
		printf("�씠�쟾 硫붾돱濡� �룎�븘媛묐땲�떎.\n");
		sleep(2);
		system("clear");
	}
	else{
		system(echo_string2);
		strcat(echo_remote, chatting_room_name); //git remote add 梨꾪똿諛⑹씠由�
		strcat(echo_remote, " "); 
		strcat(echo_remote, Git_address); //git remote add 梨꾪똿諛⑹씠由� 二쇱냼
		system(echo_remote);
		printf("%s  梨꾪똿諛⑹씠 �깮�꽦�릺�뿀�뒿�땲�떎.\n", chatting_room_name);
		printf("梨꾪똿�쓣 �썝�븯�떆硫� 梨꾪똿諛� 紐⑸줉�뿉�꽌 梨꾪똿諛⑹쓣 �꽑�깮�빐二쇱꽭�슂.\n");
		sleep(2);
		system("clear");
	}
}
char* show_list(void){
	char ls_string[100] = "ls -1 --format=single-column ./Chatting"; //�븳以꾩뿉 �븳媛쒖뵫 �꽭濡쒕줈 異쒕젰
	char* select;
	char* select2;
	char select_arr[100] = "";
	char rm_string[50] = "rm ";
	char remote_rm_string[50] = "git remote rm ";
	int option;
	char yn;

	select = (char*)malloc(sizeof(char)*100);
	select2 = (char*)malloc(sizeof(char)*100);
	system("clear");
	printf("�뵆����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������뵍\n");
	printf("�봻                                                                             �봻\n");
	printf("�봻                                 梨꾪똿諛� 紐⑸줉                                 �봻\n");
	printf("�봻                                                                             �봻\n");
	printf("�뵒����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������뵖\n");
	putchar('\n');
	system(ls_string);
	printf("\n�샃�뀡�쓣 �꽑�깮�빐二쇱꽭�슂. (1. 梨꾪똿 �떆�옉 2. 梨꾪똿諛� �궘�젣 3. �씠�쟾�쑝濡� �룎�븘媛�湲�) : ");
	scanf_int(&option, 1, 3);
	if(option == 1){ //梨꾪똿�떆�옉
		printf("\n�썝�븯�뒗 梨꾪똿諛⑹쓽 �씠由꾩쓣 �엯�젰�븯�꽭�슂 : ");
		scanf_str(select);
		//梨꾪똿諛� �씠由꾩씠 �뾾�쓣 寃쎌슦瑜� 寃��궗�빐�꽌 �삁�쇅泥섎━ �빐�빞�맖.
		printf("%s 梨꾪똿諛⑹씠 �꽑�깮�릺�뿀�뒿�땲�떎.\n", select);
		sleep(2);
		system("clear");
		return select;
	}

	if(option == 2){ //梨꾪똿諛� �궘�젣
		printf("\n�궘�젣�븷 梨꾪똿諛⑹쓽 �씠由꾩쓣 �엯�젰�븯�꽭�슂 : ");
		scanf_str(select2);
		strcpy(select_arr, select2);
		strcat(rm_string, "./Chatting/");
		strcat(rm_string, select_arr);
		strcat(remote_rm_string, select_arr);
		printf("%s 梨꾪똿諛⑹쓣 �궘�젣�븯�떆寃좎뒿�땲源�?(y/n) : ", select2);
		scanf_char(&yn, 'y', 'n');
		if(yn == 'y'){
			("%s 梨꾪똿諛⑹쓣 �궘�젣�빀�땲�떎. \n", select_arr);
			system(rm_string);
			system(remote_rm_string);
			printf("�씠�쟾硫붾돱濡� �룎�븘媛묐땲�떎.\n");
			sleep(2);
			system("clear");
			return NULL;
		}
		else if(yn == 'n'){
			printf("梨꾪똿諛� �궘�젣媛� 痍⑥냼�릺�뿀�뒿�땲�떎. �씠�쟾硫붾돱濡� �룎�븘媛묐땲�떎.\n");
			sleep(2);
			system("clear");
			return NULL;
		}
	}
	if(option == 3){ //�씠�쟾�쑝濡� �룎�븘媛�湲�
		printf("�씠�쟾 硫붾돱濡� �룎�븘媛묐땲�떎.\n");
		sleep(2);
		system("clear");
		return NULL;
	}	
}
void chatting(char *chatting_file){
	FILE *ifp, *ofp;
	pthread_t refresh_thread;
	struct tm* tm_ptr;
	time_t timer;

	char ch;
	char* AM_PM[2] = {"�삤�쟾", "�삤�썑"};
	char name[30], pw[30];
	char push_string[100] = "git push https://";
	char chatting_file_string[100] = "./Chatting/";
	char msg[200];
	char total_msg[300];
	char add_string[100] = "git add ";

	if (chatting_file == NULL){
		return;
	}
	
	strcat(chatting_file_string, chatting_file);
	strcat(add_string, chatting_file_string);
	strcat(add_string, ">> bin.txt 2>> bin.txt");

	if ((ifp = fopen(chatting_file_string, "rt")) == NULL){
			printf("梨꾪똿諛⑹씠 議댁옱�븯吏� �븡�뒿�땲�떎.");
			system("clear");
			return;
	}
	
	ifp = fopen("./name.txt", "rt");
	fscanf(ifp, "%s", name);
	fclose(ifp);
	ifp = fopen("./password.txt", "rt");
	fscanf(ifp, "%s", pw);
	fclose(ifp);

	strcat(push_string, name);
	strcat(push_string, ":");
	strcat(push_string, pw);
	strcat(push_string, "@github.com/noino0819/GitTalk master >> bin.txt 2>> bin.txt");

	pthread_create(&refresh_thread, NULL, refresh_routine, chatting_file_string);
	sleep(1);
	while(1){
		ch = getch();
		if (ch == 10){ //'\n' == 10
			pthread_cancel(refresh_thread);
			printf("蹂대궪 硫붿떆吏�瑜� �엯�젰�븯�꽭�슂. (200諛붿씠�듃 �씠�궡)\n");
			scanf("%[^\n]", msg);
			CLEAR_BUFFER();
			timer = time(NULL);
			tm_ptr = localtime(&timer);
			if (tm_ptr -> tm_hour > 12){ //�삤�썑
				if (tm_ptr -> tm_min < 10){
					sprintf(total_msg, "[%s] [%d/%d %s %d:0%d] ", name, tm_ptr -> tm_mon, tm_ptr -> tm_mday, AM_PM[1], tm_ptr -> tm_hour - 12, tm_ptr -> tm_min);
				} else {	
					sprintf(total_msg, "[%s] [%d/%d %s %d:%d] ", name, tm_ptr -> tm_mon, tm_ptr -> tm_mday, AM_PM[1], tm_ptr -> tm_hour - 12, tm_ptr -> tm_min);
				}
			} else if (tm_ptr -> tm_hour == 12){ //�삤�썑 12�떆
				if (tm_ptr -> tm_min < 10){
					sprintf(total_msg, "[%s] [%d/%d %s %d:0%d] ", name, tm_ptr -> tm_mon, tm_ptr -> tm_mday, AM_PM[1], tm_ptr -> tm_hour, tm_ptr -> tm_min);
				} else {
					sprintf(total_msg, "[%s] [%d/%d %s %d:%d] ", name, tm_ptr -> tm_mon, tm_ptr -> tm_mday, AM_PM[1], tm_ptr -> tm_hour, tm_ptr -> tm_min);
				}
			} else { //�삤�쟾
				if (tm_ptr -> tm_min < 10){
					sprintf(total_msg, "[%s] [%d/%d %s %d:0%d] ", name, tm_ptr -> tm_mon, tm_ptr -> tm_mday, AM_PM[0], tm_ptr -> tm_hour, tm_ptr -> tm_min);
				} else {
					sprintf(total_msg, "[%s] [%d/%d %s %d:%d] ", name, tm_ptr -> tm_mon, tm_ptr -> tm_mday, AM_PM[0], tm_ptr -> tm_hour, tm_ptr -> tm_min);
				}
			}
			strcat(total_msg, msg);			
			ofp = fopen(chatting_file_string, "at");
			fprintf(ofp, "\n%s", total_msg);
			fclose(ofp);
			system(add_string);
			system("git commit -m 'chatting_test_commit' >> bin.txt 2>> bin.txt"); //�굹以묒뿉 而ㅻ컠 硫붿떆吏� �닔�젙 �삁�젙
			printf("git commit �떎�뻾 以�...\n");
			system("git pull origin master >> bin.txt 2>> bin.txt");
			printf("git pull �떎�뻾 以�...\n");
			system(push_string);
			printf("git push �떎�뻾 以�...\n");
			printf("硫붿떆吏� �쟾�넚�씠 �셿猷뚮릺�뿀�뒿�땲�떎. 梨꾪똿�쓣 �옱媛쒗빀�땲�떎.\n");
			sleep(1);
			pthread_create(&refresh_thread, NULL, refresh_routine, chatting_file_string);
		} else if (ch == 27){ //ESC == 27
			pthread_cancel(refresh_thread);
			printf("�씠�쟾 硫붾돱濡� �룎�븘媛묐땲�떎.\n");
			sleep(1);
			system("clear");
			return;
		}
	}
}
void *refresh_routine(void *chatting_file_string){
	FILE *ifp;
	char ch;
	while(1){
		refresh();
		system("clear");
		ifp = fopen(chatting_file_string, "rt");
		while ((ch = getc(ifp)) != EOF){
			putchar(ch);
		}
		fclose(ifp);
		printf("\n������������������������������������������������������������������������������������������������������������梨꾪똿 �궡�슜������������������������������������������������������������������������������������������������������������\n");
		printf("** �궡�슜�쓣 �엯�젰�븯�젮硫� [Enter] �궎瑜�, �씠�쟾�쑝濡� �룎�븘媛��젮硫� [Esc] �궎瑜� �닃�윭二쇱꽭�슂.\n");
		sleep(5);
	}
}

void password_look_star(char password[30]){
	int i = 0;
	
	while(1){
		password[i] = getch();
		if(password[i] == '\n'){
			password[i] = '\0';
			break;
		} else if(password[i] == 127 || password[i] == 8){
			password[i] = '\0';
			if (i != 0){
				i--;
				printf("\b \b");
			}
			continue;
		}
		if(i == 29){
			printf("鍮꾨��踰덊샇 �젣�븳�쓣 珥덇낵�븯�뀲�뒿�땲�떎.");
			break;
		}
		i++;
		printf("*");
	}
}


int overlap_title_check(char chatting_room_name[50]){
	FILE *pFile;
	char ls_string[100] = "ls -1 --format=single-column ./Chatting >title_check.txt";
	char title[30] = "";
	char chatting_room[50] = "";
	strcpy(chatting_room, chatting_room_name);
	system(ls_string);
	pFile = fopen("title_check.txt", "r");
	while(!feof(pFile)){
		fgets(title, 30, pFile);
		strcat(chatting_room, "\n");
		if(strcmp(title, chatting_room) == 0){
			printf("�씠誘� 議댁옱�븯�뒗 �씠由꾩쓽 梨꾪똿諛⑹엯�땲�떎.\n");
			return 0;
		}
		
	}
	return 1;
}
/* start_range <= int媛� <= end_range�씪 �븣源뚯�� �엯�젰�븯寃� �빐二쇰뒗 �엯�젰 �븿�닔 */
void scanf_int(int* ap, int start_range, int end_range){
	scanf("%d", ap);
	CLEAR_BUFFER();
	while (*ap < start_range || *ap > end_range){
		printf("\n�옒紐삳맂 媛믪쓣 �엯�젰�뻽�뒿�땲�떎. %d遺��꽣 %d源뚯���쓽 媛믪쓣 �엯�젰�빐二쇱꽭�슂.\n", start_range, end_range);
		printf("踰덊샇瑜� �꽑�깮�븯�꽭�슂 : ");
		scanf("%d", ap);
		CLEAR_BUFFER();
	}
}
void scanf_str(char* ap){
	scanf("%s", ap);
	CLEAR_BUFFER();
}
void scanf_char(char* ap, char choice1, char choice2){
	scanf("%c", ap);
	CLEAR_BUFFER();
	while (*ap != choice1 || *ap != choice2){
		printf("\n�옒紐삳맂 媛믪쓣 �엯�젰�뻽�뒿�땲�떎. %c�샊��� %c瑜� �엯�젰�빐二쇱꽭�슂.\n", choice1, choice2);
		printf("踰덊샇瑜� �꽑�깮�븯�꽭�슂 : ");
		scanf("%c", ap);
		CLEAR_BUFFER();
	}
}
int getTotalLine(char *name){
  FILE *fp;
  int line=0;
  char c;
  fp=fopen(name,"r");
  while((c=fgetc(fp))!=EOF)
    if(c=='\n') line++;
  fclose(fp);
  return(line);
}

