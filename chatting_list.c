#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
struct chatting_list{
	char chatting_room[100];
	int unread;
	bool is_it_multi_room;
}list[100];
int main(){
	FILE *chatting_fp;
	char chatting_room[100];
	int unread;
	bool is_it_multi_room;
	
	fopen("./chatting_list.txt","rt");
	int i = 0;
	while(fscanf(chatting_fp, "%s%d%d",
	chatting_room, &unread, &is_it_multi_room) != EOF){
		strcpy(list[i].chatting_room, chatting_room);
		list[i].unread = unread;
		list[i].is_it_multi_room = is_it_multi_room;
		i++; 
	}
	for(i=0;i<2;i++)
	printf("%s %d %d\n",list[i].chatting_room , list[i].unread, list[i].is_it_multi_room);
}