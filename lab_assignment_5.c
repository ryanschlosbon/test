#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char letter;
	struct node* next;
} node;

//Ryan Schlosbon - COP3502C - Lab 4 - Start

// Returns number of nodes in the linkedList.
int length(node* head)
{
	int len = 0;
	node* temp = head;
	//Loops through the linked list until it reaches the null pointer. Increments length by 1 per loop
	while(temp!=NULL){
		len++;
		temp = temp->next;
	}
	return len;
}

// parses the string in the linkedList
//  if the linked list is head -> |a|->|b|->|c|
//  then toCString function wil return "abc"
char* toCString(node* head)
{
	int len = length(head);  //find length of linked list to use when allocating memory for string
	node* temp = head;
	char* str = (char*)malloc(sizeof(char)*(len + 1));  //length + 1 for null 
	if (str == NULL){
		printf("Memory allocation failed: line 28\n");
		exit(1);   //exits if memory allocation fails and alerts where the fault occurs
	}
	int i = 0;
	//Loops through linked list until it reaches the null pointer. Increments i and str. sets str[i] to temp->letter.
	while(temp!=NULL){
		str[i] = temp->letter;
		temp = temp->next;
		i++;
	}
	//Sets the final str char to null
	str[i] = '\0';
	return str;
}

// inserts character to the linkedlist
// f the linked list is head -> |a|->|b|->|c|
// then insertChar(&head, 'x') will update the linked list as foolows:
// head -> |a|->|b|->|c|->|x|
void insertChar(node** pHead, char c)
{
	node* newNode = (node*)malloc(sizeof(node));
	if(newNode == NULL){
		printf("Memory allocation failed: line 50\n");
		exit(1);	//exits if memory allocation fails and alerts where the fault occurs
	}

	//If newNode succeeds in allocating, set the next and letter
	newNode->letter = c;
	newNode->next = NULL;

	//if pHead == NULL, linked list is empty, set pHead to newNode
	if(*pHead == NULL)
		*pHead = newNode;
	//if pHead != NULL, linked list is full, iterate through until temp->next is NULL. then, set temp->next to newNode.
	else{
		node* temp = *pHead;
		while(temp->next != NULL){
			temp = temp->next;
		}
		temp->next = newNode;
	}
	
}

// deletes all nodes in the linkedList.
void deleteList(node** pHead)
{
	//if pHead is NULL, there is nothing to free in the linked list.
	if(pHead==NULL){
		return;
	}

	node* temp = *pHead;
	node* nextNode;

	//Iterate through the linked list until temp is NULL.
	while(temp != NULL){
		nextNode=temp->next;	//nextNode is set to temp->next for saving node position
		free(temp);	//Frees temp
		temp = nextNode;	//temp = nextNode
	}

	*pHead = NULL;
}

//Ryan Schlosbon - COP3502C - Lab 4 - End

int main(void)
{
	int i, strLen, numInputs;
	node* head = NULL;
	char* str;
	char c;
	FILE* inFile = fopen("input.txt","r");

	fscanf(inFile, " %d\n", &numInputs);
	
	while (numInputs-- > 0)
	{
		fscanf(inFile, " %d\n", &strLen);
		for (i = 0; i < strLen; i++)
		{
			fscanf(inFile," %c", &c);
			insertChar(&head, c);
		}

		str = toCString(head);
		printf("String is : %s\n", str);

		free(str);
		deleteList(&head);

		if (head != NULL)
		{
			printf("deleteList is not correct!");
			break;
		}
	}

	fclose(inFile);
}