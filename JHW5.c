#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_WORD_SIZE 20
#define MAX_MEANING_SIZE 50
// element 타입 정의
typedef struct {
 	char word[MAX_WORD_SIZE]; // key
 	char meaning[MAX_MEANING_SIZE];
} element;
// 트리의 노드 타입 구조체 정의
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
	return NULL; // 탐색에 실패했을 경우 NULL 반환
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
// 재귀를 이용한 원소삽입
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
// word인 단어를 가지는 노드 treePtr을 탐색
// parent는 treePtr의 부모노드
 parent = NULL;
 treePtr = *root;
 while( treePtr != NULL && strcmp(word, treePtr->data.word)) {
	 parent = treePtr;
 	treePtr = (strcmp(word, treePtr->data.word) < 0) ?
 	treePtr->left : treePtr->right;
 }
// 탐색이 종료된 시점에 treePtr이 NULL이면 트리안에
// word가 없음
 if( treePtr == NULL ) { // 탐색트리에 없는 단어
 //printf("key is not in the tree");
 return;
 }
// 첫번째 경우: 단말노드인 경우
 if( (treePtr->left==NULL) && (treePtr->right==NULL) ){
 if( parent != NULL ){
// 부모노드의 자식필드를 NULL로 만든다.
 	if( parent->left == treePtr )
 		parent->left = NULL;
 	else parent->right = NULL;
 }
 else// 만약 부모노드가 NULL이면 삭제되는 노드가 루트
 	*root = NULL;
 }
 	else if((treePtr->left==NULL)||
 	(treePtr->right==NULL)) {
 	child = (treePtr->left != NULL) ?
 	treePtr->left : treePtr->right;
 if( parent != NULL ){
 if( parent->left == treePtr )// 부모를 자식과 연결
 parent->left = child;
 else parent->right = child;
 }
 else // 만약 부모노드가 NULL이면 삭제되는 노드가 루트
 *root = child;
 }
// 세번째 경우: 두개의 자식을 가지는 경우
 else {
// 오른쪽 서브트리에서 successor(후계자: 최소 키의 노드)를 찾는다.
 succ_parent = treePtr;
 succ = treePtr->right;
// successor를 찾아서 계속 왼쪽으로 이동한다.
 while(succ->left != NULL){
 succ_parent = succ;
 succ = succ->left;
 }
// successor의 부모와 자식을 연결
 if( succ_parent->left == succ )
 succ_parent->left = succ->right;
 else
 succ_parent->right = succ->right;
// successor의 데이터를 현재 노드에 복사
 treePtr->data = succ->data;
// successor 삭제
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
// 이진탐색트리에서 알파벳 순서대로 단어와 뜻을 출력
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
 		if(strcmp(command,"단어삽입") == 0) {
 			scanf("%s", item.word);
 			scanf("%s", item.meaning);
 			if (searchItem(&T, item.word, &item) == 1)
 				printf("error1\n");
 			else
 				insertItem(&T, item);
 		}
 		else if(strcmp(command,"단어삭제") == 0) {
 			scanf("%s", item.word);
 			if (searchItem(&T, item.word, &item) == 0)
 				printf("error2\n");
 			else
 				deleteItem(&T, item.word);
 		}
 	else if(strcmp(command,"단어검색") == 0) {
 			scanf("%s", item.word);
 			if (searchItem(&T, item.word, &item) == 1)
 				printf("%s\n", item.meaning);
 			else
 				printf("error2\n");
 		}
	else if(strcmp(command, "단어뜻수정") == 0){
		scanf("%s", item.word);
		if (searchItem(&T, item.word, &item) == 1){
			scanf("%s", item.meaning);
			fixMeaning(&T, item);
		}
 		else
 			printf("error2\n");
	}
 	else if(strcmp(command,"전체단어출력") == 0) {
 		printAll(&T);
 		}
 	else if(strcmp(command,"종료") == 0) {
 		break;
 		}
 	} // while (strcmp(command,"종료") == 0)
 	returnDynamicMemory(&T);
	return 0;
}
