#pragma once
#include "MusicianQ3.h"
typedef struct MusiciansCollectio
{
	int size;
	Musician** ArrOfMusicians;

}MusiciansCollections;
MusiciansCollections* BuildMusiciansCollection(Musician** MusiciansGroup, InstrumentTree tr, int AmountOfMusicians);
int CheckSizeOfTrRec(TreeNode* root);
Musician** BuildArrOfCol(Musician** MusiciansGroup, int idOfInst, int* size, int AmountOfMusicians);
bool checkIfHePlay(MPIList lst, int id);
bool checkIfHePlayRec(ListNode* cur, int id);
char** BuildArrOfInstById(InstrumentTree tree);
void BuildArrById(char** Arr, TreeNode* root);

//free
void FreeTheMusiciansCollection(MusiciansCollections* arr, int size);