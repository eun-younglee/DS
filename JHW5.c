#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_WORD_SIZE 20
#define MAX_MEANING_SIZE 50
// element Ÿ�� ����
typedef struct {
 	char word[MAX_WORD_SIZE]; // key
 	char meaning[MAX_MEANING_SIZE];
} element;
// Ʈ���� ��� Ÿ�� ����ü ����
typedef struct TreeNode {
 	element data;
 	struct TreeNode *left, *right;
} TreeNode;
typedef struct BST {
 TreeNode *root;
} BST;
void init(BST *T)
{
 	T->root = NULL;
}

TreeNode *search(TreeNode *treePtr, char *word)
{
 	while(treePtr != NULL){
 	if( strcmp(word, treePtr->data.word ) == 0)
 		return treePtr;
 	else if( strcmp(word, treePtr->data.word ) < 0)
 		treePtr = treePtr->left;
 	else
 		treePtr = treePtr->right;
 	}
	return NULL; // Ž���� �������� ��� NULL ��ȯ
} 
int searchItem(BST *T, char *word, element *item)
{
 	TreeNode *treePtr = search(T->root, word);
 	if (treePtr == NULL)
 		return 0;
 	else {
 	*item = treePtr->data;
 		return 1;
 	}
}
// ��͸� �̿��� ���һ���
void fixMeaning(BST *T, element item){
	TreeNode *location = search(T -> root, item.word);
	strcpy(location -> data.meaning, item.meaning);
}
void insert_node(TreeNode **treePtr, element item)
{
 if (*treePtr == NULL) {
 * treePtr = (TreeNode *) malloc(sizeof(TreeNode));
 (* treePtr)->data = item;
 (* treePtr)->left = (* treePtr)->right = NULL;
 }
 else if (strcmp(item.word, (* treePtr)->data.word) < 0 )
 insert_node(&((* treePtr)->left), item);
 else if (strcmp(item.word, (* treePtr)->data.word) > 0 )
 insert_node(&((* treePtr)->right),item);
}
void insertItem(BST *T, element item)
{
 	insert_node(&(T->root), item);
}
void delete_node(TreeNode **root, char *word)
{
 TreeNode *parent, *child, *succ, *succ_parent, *treePtr;
// word�� �ܾ ������ ��� treePtr�� Ž��
// parent�� treePtr�� �θ���
 parent = NULL;
 treePtr = *root;
 while( treePtr != NULL && strcmp(word, treePtr->data.word)) {
	 parent = treePtr;
 	treePtr = (strcmp(word, treePtr->data.word) < 0) ?
 	treePtr->left : treePtr->right;
 }
// Ž���� ����� ������ treePtr�� NULL�̸� Ʈ���ȿ�
// word�� ����
 if( treePtr == NULL ) { // Ž��Ʈ���� ���� �ܾ�
 //printf("key is not in the tree");
 return;
 }
// ù��° ���: �ܸ������ ���
 if( (treePtr->left==NULL) && (treePtr->right==NULL) ){
 if( parent != NULL ){
// �θ����� �ڽ��ʵ带 NULL�� �����.
 	if( parent->left == treePtr )
 		parent->left = NULL;
 	else parent->right = NULL;
 }
 else// ���� �θ��尡 NULL�̸� �����Ǵ� ��尡 ��Ʈ
 	*root = NULL;
 }
 	else if((treePtr->left==NULL)||
 	(treePtr->right==NULL)) {
 	child = (treePtr->left != NULL) ?
 	treePtr->left : treePtr->right;
 if( parent != NULL ){
 if( parent->left == treePtr )// �θ� �ڽİ� ����
 parent->left = child;
 else parent->right = child;
 }
 else // ���� �θ��尡 NULL�̸� �����Ǵ� ��尡 ��Ʈ
 *root = child;
 }
// ����° ���: �ΰ��� �ڽ��� ������ ���
 else {
// ������ ����Ʈ������ successor(�İ���: �ּ� Ű�� ���)�� ã�´�.
 succ_parent = treePtr;
 succ = treePtr->right;
// successor�� ã�Ƽ� ��� �������� �̵��Ѵ�.
 while(succ->left != NULL){
 succ_parent = succ;
 succ = succ->left;
 }
// successor�� �θ�� �ڽ��� ����
 if( succ_parent->left == succ )
 succ_parent->left = succ->right;
 else
 succ_parent->right = succ->right;
// successor�� �����͸� ���� ��忡 ����
 treePtr->data = succ->data;
// successor ����
 treePtr = succ;
 }
 free(treePtr);
}
void deleteItem(BST *T, char *word)
{
 delete_node(&(T->root), word);
}
void print(TreeNode *treePtr)
{
 if(treePtr != NULL) {
 print(treePtr ->left);
 printf("%s %s\n", treePtr ->data.word, treePtr ->data.meaning);
 print(treePtr ->right);
 }
}
// ����Ž��Ʈ������ ���ĺ� ������� �ܾ�� ���� ���
void printAll(BST *T)
{
 print(T->root);
}
void freeMemory(TreeNode *treePtr)
{
 if (treePtr){
 freeMemory(treePtr->left);
 freeMemory(treePtr->right);
 free(treePtr);
 }
}
void returnDynamicMemory(BST *T)
{
 freeMemory(T->root);
}
int main()
{
 	BST T;
 	element item;
 	char command[20];
 	init(&T);
 	while (1) { // do
 		scanf("%s", command);
 		if(strcmp(command,"�ܾ����") == 0) {
 			scanf("%s", item.word);
 			scanf("%s", item.meaning);
 			if (searchItem(&T, item.word, &item) == 1)
 				printf("error1\n");
 			else
 				insertItem(&T, item);
 		}
 		else if(strcmp(command,"�ܾ����") == 0) {
 			scanf("%s", item.word);
 			if (searchItem(&T, item.word, &item) == 0)
 				printf("error2\n");
 			else
 				deleteItem(&T, item.word);
 		}
 	else if(strcmp(command,"�ܾ�˻�") == 0) {
 			scanf("%s", item.word);
 			if (searchItem(&T, item.word, &item) == 1)
 				printf("%s\n", item.meaning);
 			else
 				printf("error2\n");
 		}
	else if(strcmp(command, "�ܾ�����") == 0){
		scanf("%s", item.word);
		if (searchItem(&T, item.word, &item) == 1){
			scanf("%s", item.meaning);
			fixMeaning(&T, item);
		}
 		else
 			printf("error2\n");
	}
 	else if(strcmp(command,"��ü�ܾ����") == 0) {
 		printAll(&T);
 		}
 	else if(strcmp(command,"����") == 0) {
 		break;
 		}
 	} // while (strcmp(command,"����") == 0)
 	returnDynamicMemory(&T);
	return 0;
}
