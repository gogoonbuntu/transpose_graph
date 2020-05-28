#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct node{
	char a;
	struct node* link;
} Node;

void addNode(Node* head, char a);
void freeNode(Node** head, int size);
int main() {
	FILE* fp;
	bool adjarr[20][20];
	bool Tarr[20][20];
	bool temp[400];
	char ch[20];
	int elemNum = 0;
	int chaNum = 0;
	int i = 0;
	int j = 0;
	int k = 0;
	char c;
	Node** head; //head for adj list
	Node** Thead; //head for transposed adj list

	fp = fopen("hw6_data.txt", "r");
	if (fp == NULL){
		printf("%s\n", "ERROR");
		exit(1);
	}
	

	//put all 1, 0 into temp array, all alphabet into ch array
	while((c = fgetc(fp)) != EOF){
		if(c=='1' || c=='0'){
			temp[elemNum]=c-'0';
			elemNum++;
			if (elemNum > 400){
				printf("\nGraph cannot be bigger than 20x20\nTerminate program.");
				exit(0);
			}
		}
		if((c>='a' && c<='z')||(c>='A' && c<='Z')){
			ch[chaNum]=c;
			chaNum++;
		}
	}
	chaNum=(chaNum+1)/2;
	printf("File reading successful.\n\n");
	printf("Your Graph size is %dx%d.\n",chaNum,chaNum);

	head = (Node**)malloc(sizeof(Node*)*chaNum);
	Thead = (Node**)malloc(sizeof(Node*)*chaNum);

	//from temp array, put into adj array and list
	for(j = 0; j<chaNum; j++){
		head[j] = (Node*)malloc(sizeof(Node)); //맞아
		head[j]->link = NULL;
		for(k = 0; k<chaNum; k++){
			adjarr[j][k] = temp[i];
			//forming adj list
			if(adjarr[j][k]){
				addNode(head[j], ch[k]);
				//printf("%c", head[j]->link->a);
			}
			i++;
		}
	}

	for(j = 0; j<chaNum; j++){
		for(k=0; k<chaNum; k++){
			Tarr[k][j]=adjarr[j][k];
		}
	}

	for(j = 0; j<chaNum; j++){
		Thead[j] = (Node*)malloc(sizeof(Node)); //맞아
		Thead[j]->link = NULL;
		for(k = 0; k<chaNum; k++){
			if(Tarr[j][k]){
				addNode(Thead[j], ch[k]);
			}
		}
	}

	//print out adj list
	printf("\n### Print out adj list\n\n");
	for(j=0; j<chaNum; j++){
		Node* curNode = head[j]->link;
		printf("  [%c Header]->", ch[j]);
		curNode==NULL? printf("") : 0;
		while(curNode != NULL){
			printf("[%c]->",curNode->a);
			curNode = curNode->link;
		}
		printf(" NULL \n");
	}

	//print out adj list
	printf("\n### Print out Transposed adj list\n\n");
	for(j=0; j<chaNum; j++){
		Node* curNode = Thead[j]->link;
		printf("  [%c Header]->", ch[j]);
		curNode==NULL? printf("") : 0;
		while(curNode != NULL){
			printf("[%c]->",curNode->a);
			curNode = curNode->link;
		}
		printf(" NULL \n");
	}

	printf("\n Printout done. Start free Node.\n");
	freeNode(head, chaNum);
	printf("\n Whole adj list is free.\n");
	freeNode(Thead, chaNum);
	printf("\n Whole Transpose adj list is free.\n");
	printf("\n\n\n^o^ Program ended successfully!\n");
}

void addNode(Node* head, char a){
	Node* curNode = head;
	Node* newNode = malloc(sizeof(Node));
	newNode->link = NULL;
	newNode->a = a;
	while(curNode->link != NULL){
		curNode = curNode->link;
	}
	curNode->link = newNode;
}

void freeNode(Node** head, int size){
	int q = 0;
	for(q = 0; q<size; q++){
		Node* curNode = head[q];
		while(curNode->link != NULL){
			Node* tmp = curNode;
			curNode = curNode->link;
			free(tmp);
		}
	}
}