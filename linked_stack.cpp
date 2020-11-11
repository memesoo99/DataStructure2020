// linked_stack.cpp : Defines the entry point for the console application.
//
//#include "stdafx.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"


typedef int element;

typedef struct DlistNode {
	element data;
	struct DlistNode* llink;
	struct DlistNode* rlink;
}DlistNode;

typedef struct LinkedStackType {
	struct DlistNode* top;
}LinkedStackType;

void init(LinkedStackType* s, DlistNode* phead) //phead = headnode
{
	s->top = phead;
	phead->llink = phead;
	phead->rlink = phead;
	

}

int is_empty(LinkedStackType* s, DlistNode* phead)
{
	if (s->top == phead) return 1;
	return 0;
}

void push(LinkedStackType* s, element item)
{
	DlistNode* phead = s->top->llink;
	DlistNode* temp = (DlistNode*)malloc(sizeof(DlistNode));
	if (temp == NULL) {
		fprintf(stderr, "Memory allocation error\n");
		return;
	}

	else { //sth like add_first in SLL
		temp->data = item;
		if (is_empty(s, phead) == 1) {
			phead->rlink = temp;
			phead->llink = temp;
			temp->llink = phead;
			temp->rlink = phead;
			s->top = temp;
		}
		else {
			temp->rlink = s->top;
			temp->llink = phead;
			phead->rlink = temp;
			s->top->llink = temp;
			s->top = temp;

		}

	}
}

element pop(LinkedStackType* s)
{
	DlistNode* phead = s->top->llink;
	if (is_empty(s, phead)==1) {
		fprintf(stderr, "Stack is empty\n");
		exit(1);

	}
	else {

		DlistNode* temp = s->top; // 빠질원소
		if (phead->llink ==temp ) { // 원소 하나일때
			int item = temp->data;
			init(s, phead);
			free(temp);
			return item;
		}
		else {
			int item = temp->data;
			phead->rlink = temp->rlink;
			temp->rlink->llink = phead;
			s->top = temp->rlink;
			free(temp);
			return item;
		}


	}
}

element peek(LinkedStackType* s)
{
	DlistNode* phead = s->top->llink;
	if (is_empty(s,phead)==1) {
		fprintf(stderr, "Stack is empty\n");
		exit(1);
	}
	else {
		return s->top->data;
	}
}

int main(void)
{
	LinkedStackType s;
	DlistNode* phead = (DlistNode*)malloc(sizeof(DlistNode));


	init(&s, phead);

	push(&s, 1);
	push(&s, 2);
	push(&s, 3);
	push(&s, 10);
	printf("%d\n", peek(&s));
	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));
	push(&s, 7);
	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));

}




