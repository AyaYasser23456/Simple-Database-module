#include<stdio.h>
#include"StdTypes.h"

#define max 10
sint8 entries = -1;

struct SimpleDb {
	uint8 Student_ID;
	uint8 Student_Year;
	uint8 Curse1_ID;
	uint8 Curse1_Grade;
	uint8 Curse2_ID;
	uint8 Curse2_Grade;
	uint8 Curse3_ID;
	uint8 Curse3_Grade;	
}Student[max];
typedef struct SimpleDb* SDB;

SDB S_ptr=Student;
/*typedef struct{
	Student_Data arr[max];
	sint8 entries;
}SimpleDb;
*/

void init(void);
bool SDB_IsFull(void);
uint8 SDB_GetUsedSize(void);
bool SDB_AddEntry(uint8, uint8, uint8* ,uint8*);
void SDB_DeleteEntry(uint8);
bool SDB_ReadEntry(uint8, uint8*, uint8* ,uint8*);
void SDB_GetIdList(uint8*,uint8*);
bool SDB_IsIdExist(uint8);

int main(){
	init();
	uint8 S_year,S_sub[3],S_grades[3];
	uint8 list_count,list[max];	
	uint8 i;
	printf("Read entries:%d\n",SDB_ReadEntry(110,&S_year, S_sub,S_grades));
	printf("SDB_IsFull: %d\n",SDB_IsFull());
	uint8 s1_Sub[]={232,143,155};
	uint8 s1_Grd[]={10,7,9};

	uint8 s2_Sub[]={100,140,105};
	uint8 s2_Grd[]={4,3,6};
	
	printf("Add new entry:%d\n",SDB_AddEntry(110,98,s1_Sub,s1_Grd));
	printf("Add new entry:%d\n",SDB_AddEntry(111,97,s2_Sub,s2_Grd));
	printf("Add new entry:%d\n",SDB_AddEntry(120,21,s1_Sub,s2_Grd));	
	printf("Student database size=%d\n",SDB_GetUsedSize());

	SDB_GetIdList(&list_count,list);
	printf("Is Id '120' Exist:%d\n",SDB_IsIdExist(120));
	printf("Read entries:%d\n",SDB_ReadEntry(110,&S_year, S_sub,S_grades));
	printf("Read entries:%d\n",SDB_ReadEntry(111,&S_year, S_sub,S_grades));
	printf("Read entries:%d\n",SDB_ReadEntry(120,&S_year, S_sub,S_grades));	
	
	SDB_DeleteEntry(111);
	printf("Is Id '111' Exist:%d\n",SDB_IsIdExist(111));
	
	SDB_DeleteEntry(110);
	SDB_DeleteEntry(120);	
	
	SDB_GetIdList(&list_count,list);
		
	printf("Is Id '110' Exist:%d\n",SDB_IsIdExist(110));
		
	printf("Read entries:%d\n",SDB_ReadEntry(111,&S_year, S_sub,S_grades));	
	return 0;
	
}

void init(){
	entries=-1;
}

bool SDB_IsFull(void){	
	if (entries==max-1)
		return true;
	else
		return false;
}

uint8 SDB_GetUsedSize(void){
	return entries+1;
}

bool SDB_AddEntry(uint8 id, uint8 year, uint8* subjects,uint8* grades){
	if(SDB_IsFull==true){
		printf("SDB is full\n");
		return false;
	}
	else{
		entries++;
		(S_ptr+entries)->Student_ID =id;
		(S_ptr+entries)->Student_Year=year;
		(S_ptr+entries)->Curse1_ID=*subjects;
		(S_ptr+entries)->Curse1_Grade=*grades;
		(S_ptr+entries)->Curse2_ID=*(subjects+1);
		(S_ptr+entries)->Curse2_Grade=*(grades+1);
		(S_ptr+entries)->Curse3_ID=*(subjects+2);
		(S_ptr+entries)->Curse3_Grade=*(grades+2);
		
		//printf("\n year=%d",(S_ptr+entries)->Student_Year);
		return true;
	}
}

void SDB_DeleteEntry(uint8 id){
	if(entries==-1){
		printf("Database is empty\n");
	}
	else{
		uint8 i;		
		for(i=0;i<=entries;i++)
			if((S_ptr+i)->Student_ID==id){
				(S_ptr+i)->Student_ID =(S_ptr+i+1)->Student_ID ;
				(S_ptr+i)->Student_Year =(S_ptr+i+1)->Student_Year;
				(S_ptr+i)->Curse1_ID =(S_ptr+i+1)->Curse1_ID;
				(S_ptr+i)->Curse1_Grade =(S_ptr+i+1)->Curse1_Grade;
				(S_ptr+i)->Curse2_ID =(S_ptr+i+1)->Curse2_ID;
				(S_ptr+i)->Curse2_Grade =(S_ptr+i+1)->Curse2_Grade;
				(S_ptr+i)->Curse3_ID =(S_ptr+i+1)->Curse3_ID;
				(S_ptr+i)->Curse3_Grade =(S_ptr+i+1)->Curse3_Grade;	
				entries--;
				break;			
			}			
	}
}

bool SDB_ReadEntry(uint8 id, uint8* year, uint8* subjects,uint8* grades){
	if(entries==-1){
		printf("Database is empty\n");
		return false;
	}
	else{
		uint8 i;		
		for(i=0;i<=entries;i++)
			if((S_ptr+i)->Student_ID==id){
				*year=(S_ptr+i)->Student_Year;
				*subjects =(S_ptr+i)->Curse1_ID;
				*grades =(S_ptr+i)->Curse1_Grade;	
				*(subjects+1) =(S_ptr+i)->Curse2_ID;
				*(grades+1)=(S_ptr+i)->Curse2_Grade;
				*(subjects+2) =(S_ptr+i)->Curse3_ID;
				*(grades+2)=(S_ptr+i)->Curse3_Grade;								
				printf("\n\nStudent_ID \t Student_Year\t   Curse1_ID \t Curse1_Grade  \t   Curse2_ID \t Curse2_Grade \tCurse3_ID \t Curse3_Grade \n");
				printf("\n%d\t\t\t%d\t\t%d\t\t%d \t\t%d \t \t%d\t\t%d\t\t   %d\n\n\n",id,* year,*subjects,* grades,*(subjects+1),*(grades+1),*(subjects+2),*(grades+2));
				return true;			
		}
	}
	return false;
}

void SDB_GetIdList(uint8* count,uint8* list){
	if(entries==-1){
		printf("Database is empty\n");
	}
	else{
		*count=entries+1;
		uint8 i;
		for(i=0;i<*count;i++){
			*(list+i)=(S_ptr+i)->Student_ID;
		}
		printf("\nlist_count=%d\n List :\n",*count);
		for(i=0;i<*count;i++){
			printf("\t%d\n",*(list+i));
		}
	}	
}

bool SDB_IsIdExist(uint8 id){
	if(entries==-1){
		printf("Database is empty\n");
		return false;
	}
	else {
		uint8 i;
		for(i=0;i<=entries;i++){
			if((S_ptr+i)->Student_ID==id)
				return true;
		}
		
	}
	return false;
}
