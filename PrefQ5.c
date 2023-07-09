#include "PrefQ5.h"
#include <stdlib.h>

//main fun
//returns the concert arr information per concert by reading from the text
Concert* BuildConcerts(FILE* f, MusiciansCollections* MusiciansCollection, InstrumentTree InstTree,int* amountOfConc)
{
	Concert* ArrOfConc;
	int phy = 0;
	int log = 1;
	char* name;
	float hour;
	float min;
	bool finish = false;
	

	

	ArrOfConc = (Concert*)malloc(sizeof(Concert) * log);
	checkallo(ArrOfConc);
	while (!finish)
	{
		if (phy == log)
		{
			log = log * 2;
				ArrOfConc= (Concert*)realloc(ArrOfConc,sizeof(Concert) * log);
		}
		name = FindConcName(f,&finish);
		if (!finish)
		{
			ArrOfConc[phy].name = name;
			ArrOfConc[phy].date_of_concert.day = FindDay(f);
			ArrOfConc[phy].date_of_concert.month = FindMonth(f);
			ArrOfConc[phy].date_of_concert.year = FindYear(f);
			hour = FindHour(f);
			min = FindMin(f);
			ArrOfConc[phy].date_of_concert.hour = hour;
			ArrOfConc[phy].date_of_concert.min = min;
			ArrOfConc[phy].InstLst = BuildListOfInstToConc(f, InstTree);
			phy++;
		}



	}

	*amountOfConc = phy;



	


	return(ArrOfConc);
}
//reading from text the name of the concert and returns it
char* FindConcName(FILE* f,bool* flag)
{
	char c;
	char* name;
	int phy = 0;
	int log = 1;

	name = (char*)malloc(log * sizeof(char));
	checkallo(name);
	c = fgetc(f);
	if (c == EOF)
	{
		*flag = true;
		free(name);
		return(NULL);
	}
	else
	{
		while (c != ' ')//until the name is ended
		{
			if (phy == log)
			{
				log = log * 2;
				name = (char*)realloc(name, log * sizeof(char));
				checkallo(name);
			}
			name[phy] = c;
			phy++;
			c = fgetc(f);
		}

	}
	name[phy] = '\0';
	phy++;
	if(log>phy)
		name = (char*)realloc(name, phy * sizeof(char));

	

	return(name);
}
//returns the day of the concert
int FindDay(FILE* f)
{
	int day;
	fscanf(f, "%d ",&day);
	return(day);
}
//returns the number of the month of the concert
int FindMonth(FILE* f)
{
	int mon;

	fscanf(f, "%d", &mon);
	return(mon);
}
//returns the year of the concert
int FindYear(FILE* f)
{
	int year;
	fscanf(f, "%d ", &year);
	return(year);
}
//returns the hour of the concert
float FindHour(f)
{
	float hour=0;
	char c;

	c = getc(f);
	while (c != ':')
	{
		hour = (c - '0') + hour * 10;
		c = getc(f);
	}

	return(hour);


}
//returns the minute of the concert
float FindMin(f)
{
	float min;
	fscanf(f, "%f ",& min);
	
	return(min);

}

//gets from the text all the information about instruments for the concert and returns it
CIList BuildListOfInstToConc(FILE* f, InstrumentTree InstTree)
{
	CIList lst;
	MakeEmpthyCList(&lst);
	char* nameOfInst;
	int id;
	int amount;
	char impo;
	char c;
	bool finish = false;

	while (!finish)
	{
		id = FunOfInstName(f, InstTree);
		fscanf(f, "%d ", &amount);
		fscanf(f, "%c", &impo);
		insertDataToEndListC(&lst, amount, id, impo);//inserts the amount of instrument,id of instrumant and the importance for the concert
		fscanf(f, "%c", &c);
		if (c == '\n')
			finish = true;
	}
	return(lst);
		 
	 








}
//reading from text the instrument name and returns the id
int FunOfInstName(FILE* f, InstrumentTree InstTree)
{
	char c;
	int phy = 0;
	int log = 1;
	char* nameS = (char*)malloc(log * sizeof(char));
	int id;

	
	checkallo(nameS);
	c = fgetc(f);

	while (c != ' ')
	{
		if ((log-1) == phy)
		{
			log = log * 2;
			nameS = (char*)realloc(nameS, log * sizeof(char));
			checkallo(nameS);

		}
		nameS[phy] = c;
		phy++;
		c = fgetc(f);
	}
	nameS[phy] = '\0';
	phy++;
	
	if (log > phy)
	{
		nameS = (char*)realloc(nameS, phy * sizeof(char));
		checkallo(nameS);
	}

	id= findInsId(InstTree, nameS);//running on the instruments tree by the name and retruns the id of the instrument

	

	return(id);

}

//list
void MakeEmpthyCList(CIList* lst)
{
	lst->head = NULL;
	lst->tail = NULL;
}
bool isEmptyListC(CIList lst)
{
	if (lst.head == NULL)
		return(true);
	return(false);
}
void insertDataToEndListC(CIList* lst, int num, int inst,char impo)
{
	CIListNode* newTail;
	newTail = createNewListNodeC(num, inst, impo,NULL);
	insertNodeToEndListC(lst, newTail);
}
CIListNode* createNewListNodeC(int num, int inst, char impo, ListNode* next)
{
	CIListNode* node = (CIListNode*)malloc(sizeof(CIListNode));
	checkallo(node);
	node->cur.num = num;
	node->cur.importance = impo;
	node->cur.inst = inst;
	node->next = next;
	return(node);

}
void insertNodeToEndListC(CIList* lst, CIListNode* newTail)
{
	if (isEmptyListC(*lst))
	{
		lst->head = lst->tail = newTail;
	}
	else
	{
		newTail->next = NULL;
		lst->tail->next = newTail;
		lst->tail = newTail;
	}

}



//concert arrange

/*קלט: מערך של קונצרטים (מכיל שם תאירך ורשימה מקושרת של כלי הנגינה וכמותם
הפונקציה רצה על מערך הקונצרטים, שולחת לפונקציה אחרת את רשימת כלי הנגינה 
*/
void ConcertArrange(Concert* ArrOfConcert, int amountofconc, MusiciansCollections* MusiciansCollection, InstrumentTree InstTree,char** ArrOfInstById)
{
	int i;


	for (i = 0; i < amountofconc; i++)
	{
		PrintConcert(ArrOfConcert[i], MusiciansCollection, InstTree, ArrOfInstById);
	}
}
/*רצה על רשימת הכלי נגינה, וממיינת את מערך המוזיקאים של כל כלי
*/
void PrintConcert(Concert Cons, MusiciansCollections* MusiciansCollection, InstrumentTree InstTree, char** ArrOfInstById)
{
	char* NameOfConcert = Cons.name;
	CIList InsLst = Cons.InstLst;
	ConcertMusicians* ArrOfMusiciansConcert=NULL;
	CIListNode* cur = InsLst.head;
	int id;
	int size=0;
	bool flag;


	while (cur != NULL)
	{
		id = cur->cur.inst;

		flag =Sorted(cur->cur, MusiciansCollection[id], &ArrOfMusiciansConcert,&size, NameOfConcert);
		if (flag==false)//concert isnt available
		{
			return;
		}
		cur = cur->next;
	}


	PrintDetOfCons(Cons, ArrOfMusiciansConcert,size, InstTree, ArrOfInstById);//pritns all the information of the concert
	free(ArrOfMusiciansConcert);

	
}



//קלט : מקבלת כלי נגינה ואת מערך המוזיקאים שמנגנים בכלי זה הפונקציה אמור למיין את מערך המוזיקאים
bool Sorted(ConcertInstrument cur, MusiciansCollections arrofmusicians, ConcertMusicians** arr, int* sizeofuotput, char* name)
{
	ConcertMusicians* OutPutArr = *arr;
	char impo = cur.importance;
	int i;
	Musician* artist;
	int j = 0;


	if (arrofmusicians.size< cur.num)
	{
		
		printf("\nCould not find musicians for the concert %s\n", name);
		if(*sizeofuotput != 0)
			free(OutPutArr);
		return(false);
	}//if ther is not enough musician plays instrument concert isnt available

	sortById(arrofmusicians.ArrOfMusicians, arrofmusicians.size, cur.inst);//sorts the instruments list of musicians by the instrument we looking for right now
	if (impo == '1')//if importance looking for the higher price musician
	{
		SortUp(arrofmusicians.ArrOfMusicians, arrofmusicians.size);
	}
	else
	{
		sortdown(arrofmusicians.ArrOfMusicians, arrofmusicians.size);
	}

	// אחרי מיון המערך 
	if (*sizeofuotput == 0)//the first instrument
	{
		OutPutArr = (ConcertMusicians*)malloc(sizeof(ConcertMusicians) * (cur.num));
		for (i = 0; i < cur.num; i++)
		{
			OutPutArr[i].musician = arrofmusicians.ArrOfMusicians[i];
			OutPutArr[i].id = cur.inst;
			OutPutArr[i].price = arrofmusicians.ArrOfMusicians[i]->ListOfInst.head->cur.price;

		}
		*sizeofuotput = cur.num;
	}

	else
	{
		*(sizeofuotput) = cur.num+ *(sizeofuotput);
		OutPutArr = (ConcertMusicians*)realloc(OutPutArr,sizeof(ConcertMusicians) * (*(sizeofuotput)));
		i = (*(sizeofuotput)) - (cur.num);
		for (; i < (*(sizeofuotput));i++)
		{
			artist = findthenextArt(OutPutArr, i, arrofmusicians);//returns the corrent artist and if he is already taken return NULL

			if (artist != NULL)
			{
				OutPutArr[i].musician = artist;
				OutPutArr[i].id = cur.inst;
				OutPutArr[i].price = artist->ListOfInst.head->cur.price;
				
			}
			else
			{
				free(OutPutArr);
				printf("Could not find musicians for the concert %s\n", name);
				return(false);
			}

		}




	}
	*arr = OutPutArr;
	return(true);
}


//sorting musicians instrument list by the id
void sortById(Musician** MusArr, int size, int id)
{
	int i;

	for (i = 0; i < size; i++)
	{
		FindTheInst(&MusArr[i]->ListOfInst, id);
	}

	

}
//sorting the list from the highest price to the lowest
void SortUp(Musician** MusArr, int size)
{
	qsort(MusArr, size, sizeof(Musician*), SortUpTheArr);
}
//sorting the list from the lowest price to the highest
void sortdown(Musician** MusArr, int size)
{
	qsort(MusArr, size, sizeof(Musician*), SortDownTheArr);
}
//compare function for sourtUp
int SortUpTheArr(const void* ai, const void* bi)
{
	Musician* a = *(Musician**)ai;
	Musician* b = *(Musician**)bi;
	int priceA, priceB;
	priceA =(int) a->ListOfInst.head->cur.price;
	priceB =(int) b->ListOfInst.head->cur.price;
	return(priceB - priceA);
	
}
//compare function for sortDown
int SortDownTheArr(const void* ai, const void* bi)
{
	Musician* a = *(Musician**)ai;
	Musician* b = *(Musician**)bi;
	int priceA, priceB;
	priceA = (int)a->ListOfInst.head->cur.price;
	priceB = (int)b->ListOfInst.head->cur.price;
	return(priceA - priceB);
}



//running on the list while looking for the instrument by id then replace him to the head of the list
void FindTheInst(MPIList* lst, int id)
{
	ListNode* temp;
	ListNode* cur = lst->head;
	temp = cur;
	while (cur != NULL)
	{
		
		if (cur->cur.insId == id)//if found the instrumnet
		{
			if (cur == lst->tail)//if the instrument is the tail of the list
			{
				if (lst->head->next->next==cur)//if the list includes only 3 instruments
				{
					cur->next = lst->head->next;
				
					cur->next->next = lst->head;
					lst->head->next = NULL;
					lst->tail = lst->head;
					lst->head = cur;
					return;

				}
				
				else
				{
					temp->next = lst->head;
					cur->next = lst->head->next;
					lst->head->next = NULL;
					lst->tail = lst->head;
					lst->head = cur;

					return;
				}
			}
			if (cur != lst->head)//if the instrument is not the head of the list and not the tail
			{
				if (cur != lst->head->next)//if the list includes only 3 instruments
				{
					temp->next = lst->head;
					temp = lst->head->next;
					lst->head->next = cur->next;
					cur->next = temp;
					lst->head = cur;
					return;
				}
				else
				{
					lst->head->next = cur->next;
					cur->next = lst->head;
					lst->head = cur;
					return;

				}
			}
			else
				return;
		}
		temp = cur;
		cur = cur->next;

	}
	
}
float PriceOfinstCon(ListNode* cur, int id)
{
	return(cur->cur.price);
}
//checks for the musician thats going to play on the instrument by availability and importance
Musician* findthenextArt(ConcertMusicians* arr, int index,MusiciansCollections arrOfMusi)
{
	int i;
	int j;
	Musician* Mus;
	bool found = false;

	for (j = 0; j < arrOfMusi.size; j++)
	{
		found = false;
		Mus = arrOfMusi.ArrOfMusicians[j];
		for (i = 0; (i < index)&&(!found); i++)
		{
			if (arr[i].musician == Mus)//checks if the musician is already taken
			{
				found = true;

			}

		}
		if (!found)//musician is available
		{
			return(Mus);
		}
	}

	return(NULL);

}
//prints the concert information
void PrintDetOfCons(Concert cons, ConcertMusicians* Arr, int size, InstrumentTree InstTree, char** ArrOfInstById)
{
	int i;
	int TotalPrice = 0;
	char* InstName;
	int HourTime = (int)cons.date_of_concert.hour;
	int MinTime =(int) cons.date_of_concert.min;
	printf("\n%s %d %02d %d %d:%02d: ", cons.name, cons.date_of_concert.day, cons.date_of_concert.month, cons.date_of_concert.year, HourTime, MinTime);
	for (i = 0; i < size; i++)
	{
		printMusName(Arr[i].musician->name, Arr[i].musician->SizeOfName);
		InstName = FindInstNameById(Arr[i].id, ArrOfInstById);//gets the instrument name by id
		printf(" - %s (%0.2d),", InstName, (int)Arr[i].price);
		TotalPrice += Arr[i].price;//sums the concert price

	}
	printf("Total price : %d\n", TotalPrice);
	
}
//returns the instrument name
char* FindInstNameById(int id, char** ArrOfInstById)
{
	return(ArrOfInstById[id]);


}
//prints full name of musician
void printMusName(char** FullName, int size)
{
	int i;

	for (i = 0; i < size; i++)
	{
		printf(" %s", FullName[i]);
	}
}

//free
void FreeArrOfConcert(Concert* arr, int size)
{
	int i;

	for (i = 0; i < size; i++)
	{
		free(arr[i].name);
		FreeListOfInstConcert(arr[i].InstLst);
	}
	free(arr);

}
void FreeListOfInstConcert(CIList lst)
{
	CIListNode* root = lst.head;
	CIListNode* temp = root->next;

	while (root != NULL)
	{
		free(root);
		root = temp;
		if (temp != NULL)
			temp = temp->next;
	}
	
}

void Makecons(MusiciansCollections* MusiciansCollection, InstrumentTree InstTree, char** ArrOfInstById)
{
	Concert* con;
	int size;
	int i;
	int hour, min;

	printf("Enter number of Concerts\n");
	scanf("%d", &size);
	con = (Concert*)malloc(sizeof(Concert) * size);
	checkallo(con);


	for (i = 0; i < size; i++)
	{
		con[i].name=MakeConNamd();
		
		con[i].date_of_concert.day = FindDay1();
		con[i].date_of_concert.month = FindMonth1();
		con[i].date_of_concert.year = FindYear1();
		hour = FindHour1();
		min = FindMin1();
		con[i].date_of_concert.hour = hour;
		con[i].date_of_concert.min = min;
		con[i].InstLst = BuildListOfInstToConc1( InstTree);

		PrintConcert(con[i], MusiciansCollection,InstTree,ArrOfInstById);

	}
}
char* MakeConNamd()
{
	char* name;
	int phy = 0;
	int log = 1;
	char c;

	name = (char*)malloc(log * sizeof(char));
	checkallo(name);

	scanf(" %c", &c);
	while (c != ' ')
	{

		if (phy == log)
		{
			log = log * 2;
			name = (char*)realloc(name, log * sizeof(char));
			checkallo(name);
		}
		name[phy] = c;
		phy++;
		scanf("%c", &c);



	}
	name[phy] = '\0';
	phy++;
	if (log > phy)
		name = (char*)realloc(name, phy * sizeof(char));

	return(name);
}
int FindDay1()
{
	int day;
	scanf( "%d ", &day);
	return(day);
}
int FindMonth1()
{
	int mon;

	scanf( "%d", &mon);
	return(mon);
}
//returns the year of the concert
int FindYear1()
{
	int year;
	scanf("%d ", &year);
	return(year);
}

float FindHour1()
{
	float hour = 0;
	char c;

	scanf("%c", &c);
	while (c != ':')
	{
		hour = (c - '0') + hour * 10;
		scanf("%c", &c);
	}

	return(hour);


}
//returns the minute of the concert
float FindMin1()
{
	float min;
	scanf( "%f ", &min);

	return(min);

}
//gets from the text all the information about instruments for the concert and returns it
CIList BuildListOfInstToConc1( InstrumentTree InstTree)
{
	CIList lst;
	MakeEmpthyCList(&lst);
	char* nameOfInst;
	int id;
	int amount;
	char impo;
	char c;
	bool finish = false;
	scanf("%c", &c);
	while (c!='\n')
	{

		id = FunOfInstName1(&nameOfInst,InstTree);
		scanf("%d ", &amount);
		scanf("%c", &impo);
		insertDataToEndListC(&lst, amount, id, impo);//inserts the amount of instrument,id of instrumant and the importance for the concert
		scanf("%c", &c);
		
	}
	return(lst);










}
int FunOfInstName1(char** name, InstrumentTree InstTree, char** ArrOfInstById)
{
	char c;
	int phy = 0;
	int log = 1;
	char* nameS = (char*)malloc(log * sizeof(char));
	int id;


	checkallo(nameS);
	scanf("%c", &c);

	while (c != ' ')
	{
		if ((log - 1) == phy)
		{
			log = log * 2;
			nameS = (char*)realloc(nameS, log * sizeof(char));
			checkallo(nameS);

		}
		nameS[phy] = c;
		phy++;
		scanf("%c", &c);
	}
	nameS[phy] = '\0';
	phy++;

	if (log > phy)
	{
		nameS = (char*)realloc(nameS, phy * sizeof(char));
		checkallo(nameS);
	}

	id = findInsId(InstTree, nameS);//running on the instruments tree by the name and retruns the id of the instrument

	*name = nameS;

	return(id);

}