#include "MusiciansCoQ4l.h"
//returns pointers arr orderd by instrument id and points on the musicians that plays this instrument
MusiciansCollections* BuildMusiciansCollection(Musician** MusiciansGroup, InstrumentTree tr,int AmountOfMusicians)
{
	MusiciansCollections* ArrOfCol;
	int size;
	int i;

	size = CheckSizeOfTrRec(tr.root);

	ArrOfCol = (MusiciansCollections*)malloc(size * sizeof(MusiciansCollections));
	
	for (i = 0; i < size; i++)
	{
		ArrOfCol[i].ArrOfMusicians = BuildArrOfCol(MusiciansGroup, i, &ArrOfCol[i].size, AmountOfMusicians);//gets the pointers arr of instrument by id
	}

	return(ArrOfCol);
}
//returns the size of the instrument tree for the size of the pointers arr
int CheckSizeOfTrRec(TreeNode* root)
{
	if (root == NULL)
		return(0);
	else
	{
		return(CheckSizeOfTrRec(root->left) + CheckSizeOfTrRec(root->right) + 1);
	}
	
}
//checks by instrument id if the musician plays that instrument and returns the pointer arr by id
Musician** BuildArrOfCol(Musician** MusiciansGroup, int idOfInst, int* size, int AmountOfMusicians)
{
	int i;
	int phy = 0;
	int log = 1;
	Musician** ArrOfMusi = (Musician**)malloc(log * sizeof(Musician*));
	checkallo(ArrOfMusi);


	for (i = 0; i < AmountOfMusicians; i++)
	{
		if (checkIfHePlay(MusiciansGroup[i]->ListOfInst, idOfInst))
		{

			if (log == phy)
			{
				log = log * 2;
					ArrOfMusi = (Musician**)realloc(ArrOfMusi,log * sizeof(Musician*));
					checkallo(ArrOfMusi);

			}
			ArrOfMusi[phy] = MusiciansGroup[i];//puts the musician pointer
				phy++;
		}

	}
		
	
	
	if (log > phy)
	{
		ArrOfMusi = (Musician**)realloc(ArrOfMusi,phy * sizeof(Musician*));
		checkallo(ArrOfMusi);
	}
	*size = phy;
	return(ArrOfMusi);

}
//helper function for checkIfHePlayRec
bool checkIfHePlay(MPIList lst, int id)
{
	if (isEmptyList(lst))
	{
		return(false);
	}
	return(checkIfHePlayRec(lst.head, id));
}
//runing on the musician instruments list and checks if he plays the instrument by id 
bool checkIfHePlayRec(ListNode* cur, int id)
{
	if (cur == NULL)
		return(false);
	else
	{
		if (cur->cur.insId == id)
			return(true);
		else
		{
			return(checkIfHePlayRec(cur->next,id));
		}

	}
}

//Build Arr Of Inst By Id
char** BuildArrOfInstById(InstrumentTree tree)
{
	int size = CheckSizeOfTrRec(tree.root);
	char** Arr = (char**)malloc(size * sizeof(char*));
	checkallo(Arr);

	BuildArrById(Arr, tree.root);
	return(Arr);




}
void BuildArrById(char** Arr, TreeNode* root)
{
	if (root == NULL)
	{
		return;
	}
	else
	{
		int id = root->insId;
		Arr[id] = root->instrument;
		BuildArrById(Arr, root->left);
		BuildArrById(Arr, root->right);
		return;

	}
	
}

//free
void FreeTheMusiciansCollection(MusiciansCollections* arr, int size)
{
	int i;

	for (i = 0; i < size; i++)
	{
		free(arr[i].ArrOfMusicians);

	}
	free(arr);
}
