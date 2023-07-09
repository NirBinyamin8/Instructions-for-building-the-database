#pragma once
#include "InstTreeQ1.h"
#define MAX_SIZE 150
typedef struct
{
	unsigned short insId;//instrument id
	float price;//price for the instrument
} MusicianPriceInstrument;
typedef struct listnode
{
	
	MusicianPriceInstrument cur;
	struct listnode *next;
	
}ListNode;
typedef struct List 
{
	ListNode* head;
	ListNode* tail;


} MPIList ;
typedef struct
{
	char** name;//full name of musician
	int SizeOfName;
	MPIList ListOfInst;//all the musician instruments in list

} Musician;

//name fun
bool ItsSep(char tav);
void promotToSep(char* arr, int* i);
void putBackslash(char* arr);
char** BuildArrOfMusicians(int* size, FILE* Pt);
bool checkifName(char* name, TreeNode* root);
char* findFirstName(char* arr, int* i);
char** NameOfMusician(char* arr, InstrumentTree tr, int* indexofInst, int* SizeOfName);
Musician** BuildMusiciansPArr(FILE* PtToTextMusi, InstrumentTree tr);

//inst fun
MPIList MakeListOfInst(char* arr, InstrumentTree tr, int indexOfInst);
int MakeItInt(char* str);
char* findprice(char* str, int* i);

//lst fun
void makeEmptyList(MPIList* lst);
bool isEmptyList(MPIList lst);
void insertDataToEndList(MPIList* lst, int id, int price);
ListNode* createNewListNode(int id, int price, ListNode* next);
void insertNodeToEndList(MPIList* lst, ListNode* newTail);

//free 
void FreeTheMusiciansGroup(Musician** arr, int size);
void FreeName(char** strOfName, int size);
void FreeTheListOfInst(MPIList lst);
