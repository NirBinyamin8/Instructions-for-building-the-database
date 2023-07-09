#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MaxSize 150
#define NOTFOUND -1
#define FOUND 0
typedef struct treeNode {
	char* instrument;
	unsigned short insId;
	struct treeNode* left;
	struct treeNode* right;

}TreeNode;
typedef struct tree {
	TreeNode* root;
} InstrumentTree;

//q1
InstrumentTree BuildTree(FILE* PtToText, char*** Arrofins, int* Size);
char** BuildArrOfInst(int* size, FILE* Pt);
void checkallo(void* pt);
void putZero(char* arr);
void BuildTreeRec(TreeNode* root, TreeNode* NewInst);
TreeNode* createNewTreeNode(char* data, TreeNode* left, TreeNode* right, int* id);
void FreeArray(char** arr, int size); //לסוף התוכנית 
void FreeTheTree(InstrumentTree root);
void FreeTheTreeRec(TreeNode* root);


//q2
int findInsId(InstrumentTree tree, char* instrument);
int findInsIdRec(TreeNode* root, char* instrument);


