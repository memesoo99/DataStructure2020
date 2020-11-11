#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode {
	element data;
	struct ListNode* link;
}; ListNode;

void init(ListNode* phead) {
	phead->link = phead;
	phead->data = NULL;
}
void add(ListNode** phead, int data) {
	ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->data = data;
	newNode->link = *phead;
	*phead = newNode;
}
ListNode* clone(ListNode* list) {
	if (list == NULL) return NULL;

	ListNode* now = list;
	ListNode* newList = NULL;
	ListNode** lastPointer;
	lastPointer = &newList;
	while (now != NULL) {
		add(lastPointer, now->data);
		lastPointer = &((*lastPointer)->link);
		now = now->link;
	}
	return newList;
}

void display(ListNode* phead) {
	ListNode* p = phead;
	while (p) {
		printf("| %d | --->\n", p->data);
		p = p->link;
	}
	printf("\n");
}

ListNode* concat(ListNode* first, ListNode* second) {
	ListNode* p;
	if (first == NULL) return first;
	else if (second == NULL) return second;
	else {
		p = first;
		while (p->link != NULL) p = p->link;
		p->link = second;
		return first;
	}
}
void swap(ListNode* a, ListNode* b)
{
	int temp = a->data;
	a->data = b->data;
	b->data = temp;
}
void Sort(ListNode* phead)
{
	int swapped, i;
	ListNode* ptr1;
	ListNode* lptr = NULL;

	if (phead == NULL)
		return;
	do
	{
		swapped = 0;
		ptr1 = phead;
		while (ptr1->link != lptr)
		{
			if (ptr1->data > ptr1->link->data)
			{
				swap(ptr1, ptr1->link);
				swapped = 1;
			}
			ptr1 = ptr1->link;
		}
		lptr = ptr1;
	} while (swapped);
}


int main(void) {
	ListNode* a_head_node = NULL;
	/*init(a_head_node);*/
	int a_array[7] = { 25,20,15,10,5,2,1 };
	for (int i = 0; i < 7; i++) {
		add(&a_head_node, a_array[i]);
	}
	printf("List A\n");
	display(a_head_node);

	ListNode* b_head_node = NULL;
	int b_array[6] = { 30,18,15,8,7,3 };
	for (int i = 0; i < 6; i++) {
		add(&b_head_node, b_array[i]);
	}
	printf("List B\n");
	display(b_head_node);
	ListNode* first = clone(a_head_node);
	ListNode* second = clone(b_head_node);
	ListNode* c_head_node = NULL;
	c_head_node = concat(first, second);

	printf("List C (Merge and Sorted)\n");
	Sort(c_head_node);
	display(c_head_node);

}