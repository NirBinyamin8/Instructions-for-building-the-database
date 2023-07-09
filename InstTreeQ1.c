#include "InstTreeQ1.h"

//q1
InstrumentTree BuildTree(FILE* PtToText,char***Arrofins,int* Size)
{
	InstrumentTree tr;
	int size;
	int id = 0;
	TreeNode* cur;

	char** ArrOfIns;
	
	ArrOfIns =BuildArrOfInst(&size,PtToText);//reading from instruments text
	tr.root = createNewTreeNode(ArrOfIns[0], NULL, NULL, &id);//building the root by the first instrument
	for (int i = 1;i < size; i++)
	{
		cur = createNewTreeNode(ArrOfIns[i],NULL, NULL, &id);
		BuildTreeRec(tr.root, cur);//puts the instrument by placing order

	}
	
	
	*Arrofins = ArrOfIns;
	*Size = size;
	fclose(PtToText);
	return(tr);







	

}
//creates new node for new instrument
TreeNode* createNewTreeNode(char* data, TreeNode* left, TreeNode* right,int* id)
{
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	checkallo(node);

	node->instrument = data;
	node->insId = *id;
	(*id)++;
	node->left = left;
	node->right = right;

	return node;
}
//checking by lexicograph order where to put the next instrument
void BuildTreeRec(TreeNode* root, TreeNode* NewInst )
{
	
	if (root == NULL)
		return;
	if (strcmp(root->instrument, NewInst->instrument) == 0)//checks if the instrument is already on the tree
		return;
	if (strcmp(root->instrument, NewInst->instrument) > 0)//checking the order of the instruments
	{
		if (root->left == NULL)//checks if the node is available for the left side
		{
			root->left = NewInst;
			return;
		}
		else
		{
			BuildTreeRec(root->left, NewInst);
			return;
		}
		
	}
	else
	{
		if (root->right == NULL)//checks if the node is available for the right side
		{
			root->right = NewInst;
			return;
		}
		else
		{
			BuildTreeRec(root->right, NewInst);
			return;

		}

	}
	
}
//reading from the text into arr of strings and returns it and the number of instruments there are in the file .
char** BuildArrOfInst(int* size, FILE* Pt)
{
int log = 1;
char** arr= (char**)malloc(sizeof(char*) * log);
int phy = 0;

arr[phy] = malloc(MaxSize * sizeof(char));//allocation by maximum chars for string

while (fgets(arr[phy], MaxSize, Pt))
{
	putZero(arr[phy]);
	phy = phy + 1;
	if (phy == log)
	{
		log = log * 2;
		arr = (char**)realloc(arr, log * sizeof(char*));
		checkallo(arr);
		

	}
	arr[phy] = malloc(MaxSize * sizeof(char));

}
if (log > phy)
{
	arr = (char**)realloc(arr,(phy)*sizeof(char*));
	checkallo(arr);

}
*size = phy;
return(arr);



}
//checks allocation status
void checkallo(void* pt)
{
	if (pt == NULL)
	{
		printf("Memory allocation failure!!!\n");
		exit(1);
	}
}
//puts \0 at the end of the string
void putZero(char* arr)
{
	int i = 0;
	bool flag = false;
	while (!flag)
	{
		if (arr[i] >= 'A' && arr[i] <= 'z')
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
void FreeArray(char** arr, int size)
{
	int i = 0;
	for (i = 0; i < size; i++)
	{
		free(arr[i]);

	}
	free(arr);

} //לסוף התוכנית 
void FreeTheTree(InstrumentTree root)
{
	FreeTheTreeRec(root.root);

}
void FreeTheTreeRec(TreeNode* root)
{
	if (root == NULL)
		return;
	else
	{
		FreeTheTreeRec(root->left);
		FreeTheTreeRec(root->right);
		free(root);
	}
}

//q2
//helper function for findIdRec
int findInsId(InstrumentTree tree, char* instrument)
{
	return(findInsIdRec(tree.root, instrument));
}
//by the name of the instrument, checks if the instrument is on the tree and returns his id else returns -1
int findInsIdRec(TreeNode* root, char* instrument)
{
	int idLft;
	int idRgt;
	if (root == NULL)
		return(NOTFOUND);
	if (strcmp(root->instrument, instrument) == FOUND)//checks for similar name on the tree
	{
		return(root->insId);
	}
	idLft = findInsIdRec(root->left, instrument);
	idRgt= findInsIdRec(root->right, instrument);
	if (idLft != NOTFOUND)
		return(idLft);
	if (idRgt != NOTFOUND)
		return(idRgt);
	else
		return(NOTFOUND);
}




