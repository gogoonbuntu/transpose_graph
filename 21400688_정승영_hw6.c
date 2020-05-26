#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct node{
	char a;
	struct node* link;
} Node;

int addNode(Node* head, char a);

int main() {
	FILE* fp;
	bool adjarr[20][20];
	bool temp[400];
	char ch[20];
	int elemNum = 0;
	int chaNum = 0;
	int i = 0;
	int j = 0;
	int k = 0;
	char c;
	Node** head;

	fp = fopen("hw6_data.txt", "r");
	if (fp == NULL){
		printf("%s\n", "ERROR");
		exit(1);
	}

	while((c = fgetc(fp)) != EOF){
		if(c=='1' || c=='0'){
			temp[elemNum]=c-'0';
			elemNum++;
		}
		if((c>='a' && c<='z')||(c>='A' && c<='Z')){
			ch[chaNum]=c;
			printf("%d : %c\n", chaNum, ch[chaNum]);
			chaNum++;
		}
	}
	chaNum=(chaNum+1)/2;

	head = (Node**)malloc(sizeof(Node*)*chaNum);

	// for(i=0; i<elemNum; i++){
	// 	if((i)%(chaNum/2)==0){
	// 		printf("\n");
	// 	}
	// 	printf("[ %d ] ", temp[i]);
	// } i=0;
	for(j = 0; j<chaNum; j++){
		head[j] = (Node*)malloc(sizeof(Node)); //맞아
		head[j]->link = NULL;
		for(k = 0; k<chaNum; k++){
			adjarr[j][k] = temp[i];
			if(adjarr[j][k]){
				addNode(head[j], ch[k]);
				//printf("%c", head[j]->link->a);
			}
			printf("%d  ", adjarr[j][k]);
			i++;
		}
		printf("\n");
	}
	for(j=0; j<chaNum; j++){
		Node* curNode = head[j]->link;
		printf("[%c Header]->", ch[j]);
		curNode==NULL? printf("NULL") : 0;
		while(curNode != NULL){
			printf("[%c]->",curNode->a);
			curNode = curNode->link;
		}
		printf("\n");
	}
}

int addNode(Node* head, char a){
	Node* curNode = head;
	Node* newNode = malloc(sizeof(Node));
	newNode->link = NULL;
	newNode->a = a;
	while(curNode->link != NULL){
		curNode = curNode->link;
	}
	curNode->link = newNode;
}