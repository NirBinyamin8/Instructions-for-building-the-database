#include "InstTreeQ1.h"
#include "MusicianQ3.h"
#include "MusiciansCoQ4l.h"
#include "PrefQ5.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


void main(int argc, char* argv[])
{
	InstrumentTree InstTree;
	int id;
	Musician** MusiciansGroup;
	MusiciansCollections* MusiciansCollection;
	int AmountOfMusicians;
	Concert* ArrOfConcert;
	int amountOfConc;
	char** ArrOfInstById;
	char** ArrOfInst;
	int SizeOfInst;

	FILE* PtToTextInst = fopen("instruments.txt", "r");
	FILE* PtToTextMusi = fopen("musicians.txt", "r");
	FILE* PtToTextConc = fopen("performances_input.txt", "r");
	if (PtToTextInst == NULL)
	{
		printf("Failed opening the file. Exiting!\n");
		return;
	}

	InstTree = BuildTree(PtToTextInst, &ArrOfInst,&SizeOfInst);//returns the instruments tree
	
	

	if (PtToTextMusi == NULL)
	{
		printf("Failed opening the file. Exiting!\n");
		return;
	}

	MusiciansGroup = BuildMusiciansPArr(PtToTextMusi, InstTree,&AmountOfMusicians);//return the pointers arr of the musicians

	MusiciansCollection = BuildMusiciansCollection(MusiciansGroup, InstTree, AmountOfMusicians);//returns pointers arr of arr by instrument id to musician that plays thet instrument

	ArrOfInstById = BuildArrOfInstById(InstTree);//returns arr of instruments orderd by id

	if (PtToTextConc == NULL)
	{
		printf("Failed opening the file. Exiting!\n");
		return;
	}

	//ArrOfConcert = BuildConcerts(PtToTextConc, MusiciansCollection, InstTree,&amountOfConc);//gets from text the information about concerts 

	//ConcertArrange(ArrOfConcert, amountOfConc, MusiciansCollection, InstTree,ArrOfInstById);//arranges all the concerts by the information we got and prints 
	Makecons(MusiciansCollection, InstTree, ArrOfInstById);

	FreeArray(ArrOfInst, SizeOfInst);
	FreeTheTree(InstTree);
	FreeTheMusiciansGroup(MusiciansGroup, AmountOfMusicians);
	FreeTheMusiciansCollection(MusiciansCollection, SizeOfInst);
	//FreeArrOfConcert(ArrOfConcert, amountOfConc, ArrOfInstById);
	
	





	

}
	
