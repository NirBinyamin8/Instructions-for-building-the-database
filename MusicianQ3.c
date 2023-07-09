#include "MusicianQ3.h"

//exract name fun
//promoting the index to the begining of name(instrument or musician name) and returns the index
void promotToSep(char* arr, int* i)
{
	int j = *i;
	while (ItsSep(arr[j]))
		j++;
	*i = j;
}
//checks by all the signs and returns true if it does else false
bool ItsSep(char tav)
{
	if (tav == ' ' || tav == '"' || tav == ',' || tav == '.' || tav == ';' || tav == ':' || tav == '?' || tav == '!' || tav == '-' || tav == '\t' || tav == '\'' || tav == '(' || tav == ')' || tav == '[' || tav == ']' || tav == '{' || tav == '}' || tav == '<' || tav == '>' || tav == '~' || tav == '_')
		return (true);
	return(false);
}
void putBackslash(char* arr)
{
	int i = 0;
	bool flag = false;
	while (!flag)
	{
		if ((arr[i] >= 'A' && arr[i] <= 'z')||(ItsSep(arr[i]))|| (arr[i] >='0' && arr[i] <='9'))
		{
			i++;
		}
		else
		{
			arr[i] = '\0';
			flag = true;

		}

	}

}
// reads from text all rows and returns them as arr of strings
char** BuildArrOfMusicians(int* size, FILE* Pt)
{
	int log = 1;
	char** arr = (char**)malloc(sizeof(char*) * log);
	int phy = 0;

	arr[phy] = malloc(MAX_SIZE * sizeof(char));//allocation by maximum szie of row

	while (fgets(arr[phy], MAX_SIZE, Pt))
	{
		
		phy = phy + 1;
		if (phy == log)
		{
			log = log * 2;
			arr = (char**)realloc(arr, log * sizeof(char*));
			checkallo(arr);


		}
		arr[phy] = malloc(MAX_SIZE * sizeof(char));

	}
	if (log > phy)
	{
		arr = (char**)realloc(arr, (phy+1) * sizeof(char*));
		checkallo(arr);

	}
	*size = phy;
	return(arr);



}
//checks with the instrument tree if the name is instrument or part of the musician name 
bool checkifName(char* name,TreeNode* root)
{
	if (root == NULL)
		return(true);
	if (strcmp(name, root->instrument) == 0)
		return(false);
	else
		return(checkifName(name, root->left) && checkifName(name, root->right));

}
//gets the first name of musician and return it and returns name of instrument
char* findFirstName(char* arr, int* i)
{
	int size = 0;
	int j = *(i);
	bool flag = false;
	char* name=(char*)malloc(MAX_SIZE*(sizeof(char)));
	checkallo(name);
	while (ItsSep(arr[j]))//promots index until its not 1 of the separators defined by question
	{
		j++;
	}
	while (!(ItsSep(arr[j]))&&!flag)//until its names char keeps writing to the name arr
	{
		if (arr[j] == '\n' || arr[j] == '\0')
			flag = true;
		else
		{
			name[size] = arr[j];
			size++;
			j++;
		}
		

	}
	name[size] = '\0';
	size++;
	name = (char*)realloc(name, size * sizeof(char));
	*i = j;

	return(name);
}
//extracting the full name of the musician
char** NameOfMusician(char* arr, InstrumentTree tr,int* indexofInst,int* SizeOfName)
{
	char** FullName;
	int phy = 0;
	int log = 1;
	bool flag =false;
	int i = 0;
	char* name;
	int size = 0;
	int temp;

	FullName = (char**)malloc(sizeof(char*) * log);
	checkallo(FullName);

	while (!flag)
	{
		temp = i;
		name = findFirstName(arr, &i);//gets the musician first name
		promotToSep(arr, &i);
		if (checkifName(name,tr.root))
		{
			if (log == phy)
			{
				log = log * 2;
				FullName = (char**)realloc(FullName, log * sizeof(char*));
			}
			FullName[phy] = name;
			phy++;


		}
		else//if its a instrument name
		{
			free(name);
			flag = true;
			*indexofInst = temp;

		}
	}
	if(log>phy)
		FullName = (char**)realloc(FullName, phy * sizeof(char*));
	*SizeOfName = phy;
	return(FullName);

}

//list fun

//making the instruments of the musician list and returns it
MPIList MakeListOfInst(char* arr, InstrumentTree tr,int indexOfInst)
{
	MPIList lst;
	char* insname;
	char* PriceC;
	int price;
	int id;
	bool flag = false;
	

	makeEmptyList(&lst);

	while (!flag)
	{
		insname = findFirstName(arr, &indexOfInst);//extracting the instrument name
		promotToSep(arr, &indexOfInst);
		

		id = findInsId(tr, insname);//gets id by the instrument name
		free(insname);
		PriceC = findprice(arr, &indexOfInst);//gets the instrument price
		price = MakeItInt(PriceC);//makes the price in char in to price in int
		free(PriceC);
		insertDataToEndList(&lst, id, price);//entering the instrumnet to the end of the list
		if (arr[indexOfInst] == '\n' || arr[indexOfInst] == '\0')//checks if finished the musician
			flag = true;
		else
		{
			promotToSep(arr, &indexOfInst);

		}
		

		


	}

	return(lst);


}
//gets str on price and makes it number in int
int MakeItInt(char* str)
{
	int i = 0;
	int price = 0;

	while (str[i] != '\0' && !(ItsSep(str[i])))
	{
		price = (price*10) + str[i] - '0';
		i++;
	}
	return (price);
}
//returns the price in char
char* findprice(char* str, int* i)
{
	int j = *i;
	int size = 0;
	char* Price = (char*)malloc(MAX_SIZE * sizeof(char));

	while ((!ItsSep(str[j]))&&(str[j] !='\0')&&(str[j] !='\n'))
	{
		Price[size] = str[j];
		size++;
		j++;

	}
	Price[size] = '\0';
	size++;
	Price = (char*)realloc(Price,size * sizeof(char));
	*i = j;
	return(Price);

}

//list funactions
void makeEmptyList(MPIList* lst)
{
	lst->head = NULL;
	lst->tail = NULL;
}
bool isEmptyList(MPIList lst)
{
	if (lst.head == NULL)
		return(true);
	return(false);
}
void insertDataToEndList(MPIList* lst, int id, int price)
{
	ListNode* newTail;
	newTail = createNewListNode(id,price,NULL,NULL);
	insertNodeToEndList(lst, newTail);
}
ListNode* createNewListNode(int id, int price, ListNode* next)
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	checkallo(node);
	node->cur.insId = id;
	node->cur.price = price;
	node->next = next;
	
	return(node);

}
void insertNodeToEndList(MPIList* lst, ListNode* newTail)
{
	if (isEmptyList(*lst))
	{
		lst->head = lst->tail = newTail;
	}
	else
	{
		
		newTail->next = NULL;
		lst->tail->next =newTail;
		lst->tail = newTail;
	}

}



//main fun
//builds pointers arr of musicians from the text and returns it.
Musician** BuildMusiciansPArr(FILE* PtToTextMusi, InstrumentTree tr,int* AmountOfMusicians)
{
	Musician** ArrOfMusicians;
	int size;
	char** Rows;
	int i;
	int IndexOfInst;

	Rows = BuildArrOfMusicians(&size, PtToTextMusi);//reads the file in to strings arr
	ArrOfMusicians = (Musician**)malloc(sizeof(Musician*) * size);
	checkallo(ArrOfMusicians);

	for (i = 0; i < size; i++)
	{
		ArrOfMusicians[i] = (Musician*)malloc(sizeof(Musician));
		checkallo(ArrOfMusicians[i]);

	}

	for (i = 0; i < size; i++)
	{
		ArrOfMusicians[i]->name = NameOfMusician(Rows[i],tr,&IndexOfInst, &(ArrOfMusicians[i]->SizeOfName));
		ArrOfMusicians[i]->ListOfInst = MakeListOfInst(Rows[i], tr, IndexOfInst);

	}
	*AmountOfMusicians = size;
	return(ArrOfMusicians);






}

//free
void FreeTheMusiciansGroup(Musician** arr, int size)
{
	int i;

	for (i = 0; i < size; i++)
	{
		FreeName(arr[i]->name, arr[i]->SizeOfName);
		FreeTheListOfInst(arr[i]->ListOfInst);
		free(arr[i]);
	}
	free(arr);

}
void FreeName(char** strOfName, int size)
{
	int i;

	for (i = 0; i < size; i++)
	{
		free(strOfName[i]);
	}
	free(strOfName);
}
void FreeTheListOfInst(MPIList lst)
{
	ListNode* cur = lst.head;
	ListNode* temp=cur->next;

	while (cur != NULL)
	{
		free(cur);
		cur = temp;
		if(temp!=NULL)
		temp = temp->next;


	}


}