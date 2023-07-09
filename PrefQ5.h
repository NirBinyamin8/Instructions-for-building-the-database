#pragma once

#include"MusiciansCoQ4l.h"
#define HOUR 60
typedef struct
{
	int day, month, year;
	float hour;
	float min;
} Date;
typedef struct concertInstrument
{
	int num;
	int inst;
	char importance;
} ConcertInstrument;
typedef struct cIListNode
{
	ConcertInstrument cur;
	struct cIListNode* next;

}CIListNode;
typedef struct cIList
{
	CIListNode* head;
	CIListNode* tail;


}CIList;
typedef struct concert
{
	Date date_of_concert;
	char* name;
	CIList InstLst;

}Concert;
typedef struct concertMusicians
{
	Musician* musician;
	int id;
	float price;
}ConcertMusicians;



Concert* BuildConcerts(FILE* f, MusiciansCollections* MusiciansCollection, InstrumentTree InstTree, int* amountOfConc);

//concert fun
char* FindConcName(FILE* f, bool* flag);
int FindDay(FILE* f);
int FindMonth(FILE* f);
int FindYear(FILE* f);
float FindHour(f);
float FindMin(f);
int FunOfInstName(FILE* f, InstrumentTree InstTree);

//main list fun
CIList BuildListOfInstToConc(FILE* f, InstrumentTree InstTree);

//buildUpListFun
void MakeEmpthyCList(CIList* lst);
bool isEmptyListC(CIList lst);
void insertDataToEndListC(CIList* lst, int num, int inst, char impo);
CIListNode* createNewListNodeC(int num, int inst, char impo, ListNode* next);
void insertNodeToEndListC(CIList* lst, CIListNode* newTail);

//concert arrange
void ConcertArrange(Concert* ArrOfConcert, int amountofconc, MusiciansCollections* MusiciansCollection, InstrumentTree InstTree, char** ArrOfInstById);
void sortById(Musician** MusArr, int size, int id);
void SortUp(Musician** MusArr, int size);
void sortdown(Musician** MusArr, int size);
int SortUpTheArr(const void* ai, const void* bi);
int SortDownTheArr(const void* ai, const void* bi);
void printMusName(char** FullName, int size);
bool Sorted(ConcertInstrument cur, MusiciansCollections arrofmusicians, ConcertMusicians* OutPutArr, int* sizeofuotput, char* name);
void PrintDetOfCons(Concert cons, ConcertMusicians* Arr, int size, InstrumentTree InstTree, char** ArrOfInstById);
Musician* findthenextArt(ConcertMusicians* arr, int index, MusiciansCollections arrOfMusi);
void FindTheInst(MPIList* lst, int id);
char* FindInstNameById(int id, char** ArrOfInstById);
void PrintConcert(Concert Cons, MusiciansCollections* MusiciansCollection, InstrumentTree InstTree, char** ArrOfInstById);

//free 
void FreeArrOfConcert(Concert* arr, int size);
void FreeListOfInstConcert(CIList lst);
 
void Makecons(MusiciansCollections* MusiciansCollection, InstrumentTree InstTree, char** ArrOfInstById);
char* MakeConNamd();
int FindDay1();
int FindMonth1();
int FindYear1();
float FindHour1(); 
float FindMin1();
CIList BuildListOfInstToConc1(InstrumentTree InstTree);
int FunOfInstName1(char** name, InstrumentTree InstTree);
