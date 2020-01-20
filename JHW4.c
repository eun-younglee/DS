#include <string.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct Node{
	int number;
	char title[20];
	int price;
	int stock;
	struct Node *link;
}NodeType;
typedef struct{
	NodeType * head;
	int length;
}UnsortedLinkedList;
void init(UnsortedLinkedList *L){
	L -> head = NULL;
	L -> length = 0; 
}
int is_empty(UnsortedLinkedList *L){
	return L -> head == NULL; 
}
void insertItemFirst(UnsortedLinkedList *L){
	int num, price, stock;
	char title[20];
	NodeType *tmp = (NodeType *)malloc(sizeof(NodeType));
	scanf("%d %s %d %d", &num, title, &price, &stock);
	if(getItem(L, num) == 1)
		printf("error1\n");
	else{
		tmp -> number = num;
		strcpy(tmp -> title, title);
		tmp -> price = price;
		tmp -> stock = stock;
		tmp -> link = L -> head;
		L -> head = tmp;
	}
}
void insertItemAgain(UnsortedLinkedList *L){
	NodeType *location = L -> head;
	int stock, num, original = 0;
	scanf("%d %d", &num, &stock);
	if(getItem(L, num) != 1)
		printf("error2\n");
	else
		while(location != NULL) {
			if (location -> number == num) {
				location -> stock = location -> stock + stock;
				break;
				}
			location = location -> link;
		}
	}
void insertSoldItem(UnsortedLinkedList *S, int num, int sell, int price, char *title){
	NodeType *tmp = (NodeType *)malloc(sizeof(NodeType));
	tmp -> number = num; 
	tmp -> stock = sell; 
	strcpy(tmp -> title, title);
	tmp -> price = price;
	tmp -> link = S -> head;
	S -> head = tmp;
	}
void insertSoldItemAgain(UnsortedLinkedList *S, int num, int sell, int price, char *title){
	NodeType *tmp = (NodeType *)malloc(sizeof(NodeType));
	NodeType *location = S -> head;
	int original;
	while(location != NULL) {
		if (location -> number == num) {
			original = location -> stock;
				break;
			}
			location = location -> link;
		}
		sell = original + sell;
		location -> stock = sell;
}
void deleteItem(UnsortedLinkedList *L, int num){
	int i;
	NodeType *location = L -> head;
	NodeType *tmp;
	int found = 0;
	if (L -> head -> number == num) {
		tmp = L -> head;
		L -> head = L -> head->link;
		L -> length--;
		free(tmp);
	}
	else {
		while (location != NULL) {
			if (location -> link -> number == num) {
				found = 1;
				break;
			}
			else
			location = location -> link;
			}
		}
	if (found == 1) {
		tmp = location->link;
		location->link = tmp->link;
		L->length--;
		free(tmp);
	}
}
int getSize(UnsortedLinkedList *L){
	NodeType *location = L -> head;
	int count = 0;
	while(location != NULL){
		count++;
		location = location -> link;
	}
	return count;
}
int getItem(UnsortedLinkedList *L, int num){
	NodeType *location = L -> head;
	while(location != NULL) {
		if (location -> number == num) {
			return 1;
		}
		else
			location = location->link;
	}	
	return 0;
}
void changeStock(UnsortedLinkedList *L, int num, int sell){
	NodeType *location = L -> head;
	int original;
	while(location != NULL) {
		if (location -> number == num) {
			original = location -> stock;
			break;
		}
		location = location->link;
	}	
	sell = original - sell;
	location -> stock = sell;
}
int getStock(UnsortedLinkedList *L, int num){
	NodeType *location = L -> head;
	while(location != NULL) {
		if (location -> number == num) {
			return location -> stock;
			break;
		}	
		else 
			location = location -> link;
		}
}
int getPrice(UnsortedLinkedList *L, int num){
	NodeType *location = L -> head;
	while(location != NULL) {
		if (location -> number == num) {
			return location -> price;
			break;
		}	
		else 
			location = location -> link;
		}
}
char *getTitle(UnsortedLinkedList *L, int num){
	NodeType *location = L -> head;
	while(location != NULL) {
		if (location -> number == num) {
			return location -> title;
			break;
		}	
		else 
			location = location -> link;
		}
}
void printBooks(UnsortedLinkedList *L){
	int i = 1, j, tmp, size;
	NodeType *location = L -> head;
	int book[100] =  { 100000, };
	size = getSize(L);
	for(i = 0; i < size; i++){
		book[i] = location -> number;
		location = location -> link;
	}
	for(i = 0; i < size - 1; i++){
		for(j = 0; j < size - 1; j++){
			if(book[j] > book[j + 1]){
				tmp = book[j];	
				book[j] = book[j + 1];
				book[j + 1] = tmp;
			}
		}
	}
	i = 0;
	location = L -> head;
	while(location != NULL) {
		if(location -> number == book[i]){
			printf("%d %s %d %d\n", location -> number, location -> title, location -> price, location -> stock);
			i++;
			location = L -> head;
		}
		else
			location = location -> link;
	}	
}
int main(){
	UnsortedLinkedList L;
	UnsortedLinkedList S; 
	init(&L);
	init(&S);
	char command;
	char title[50];
	int num, price, stock, key, sell;
	while(1){
		scanf("%c", &command);
		 if(command == 'N'){ //새 책 입고 
			insertItemFirst(&L);
		}
		else if(command == 'R') { //이미 있는 도서 입고 
			insertItemAgain(&L);
		}
		else if(command == 'S') { //판매 
			scanf("%d %d", &num, &sell);
			if(getItem(&L, num) != 1)
				printf("error2\n");
			else if(sell > getStock(&L, num))
				printf("error3\n");
			else if(getItem(&S, num) == 1){
				int price = getPrice(&L, num);
				char title[20];
				strcpy(title, getTitle(&L, num));
				insertSoldItemAgain(&S, num, sell, price, title);
				changeStock(&L, num, sell);
			}
			else{
					int price = getPrice(&L, num);
					char title[20];
					strcpy(title, getTitle(&L, num));
					insertSoldItem(&S, num, sell, price, title);
					changeStock(&L, num, sell);
			} 
		}
		else if(command == 'D'){ 
			scanf("%d", &num);
			if(getItem(&L, num) != 1)
				printf("error2\n");
			else
					deleteItem(&L, num);
		} 
		else if(command == 'I') {  
			scanf("%d", &num);
			if(getItem(&L, num) == 0)
				printf("error2\n");
			else{
				int stock = getStock(&L, num);
				int price = getPrice(&L, num);
				char title[20];
				strcpy(title, getTitle(&L, num));
				printf("%d %s %d %d\n", num, title, price, stock);
			}
		}
		else if(command == 'P') {
			printBooks(&L);
		}
		else if(command == 'L'){
			printBooks(&S);
		}
		else if (command == 'Q')  {
			break;
		}
	}
	return 0;
}
