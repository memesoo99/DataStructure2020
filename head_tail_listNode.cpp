#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode {
	element data;
	struct ListNode* link;
} ListNode;

typedef struct {
	ListNode* head;
	ListNode* tail;
	int length;
}ListType;
void error(const char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}
void init(ListType* list) {
	list->length = 0;
	list->head = list->tail = NULL;
}
int is_empty(ListType* list) {
	if (list->head == NULL) return 1;
	else return 0;
}
int get_length(ListType* list) {
	return list->length;
}
ListNode* get_node_at(ListType* list, int pos) {
	int i;
	ListNode* temp = list->head;
	if (pos < 0) return NULL;
	for (i = 0; i < pos; i++) {
		temp = temp->link;
	}
	return temp;
}

void add_last(ListType* list, element data) {
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	if (node == NULL) error("Memory allocation eror");

	node->data = data;
	node->link = NULL;
	list->tail->link = node;
	list->tail = node;
	list->length++;
}
void add_first(ListType* list, element data) {
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	if (node == NULL) error("Memory allocation eror");
	if (list->length == 0) {
		list->tail = node;
	}
	node->data = data;
	node->link = list->head;
	list->head = node;
	list->length++;
}
void insert_node(ListNode** list, ListNode* before, ListNode* add) {//구현!!!!!!!!!!!!!!!
	add->link = before->link;
	before->link = add;
}
void add_node(ListType* list, int pos, element data) {
	ListNode* a;
	if ((pos >= 0) && (pos <= list->length)) { //pos가 옳바른 범위안에 있는지 확인하는 기능
		if (pos == 0) {
			add_first(list, data);
			return;
		}
		if (pos == list->length) {
			add_last(list, data);
			return;
		}
		ListNode* node = (ListNode*)malloc(sizeof(ListNode));
		if (node == NULL) error("Memory allocation eror"); //추가할 노드
		/*if (list->length == pos) list->tail = node;*/
		node->data = data;
		a = get_node_at(list, pos - 1); // a는 before 노드
		/*printf("before 노드 | %d | %x | --->\n", a->data, a->link);*/
		insert_node(&(list->head), a, node);
		list->length++;
	}
}
void remove_node(ListNode** list, ListNode* before, ListNode* remove) {//구현!!!!!!!!!!!!!!!
	if (*list == NULL) return;
	ListNode* temp = *list;
	before->link = remove->link;
	free(remove);

}

void delete_first(ListType* list) {

	if (!is_empty(list)) {
		ListNode* removed = get_node_at(list, 0);
		list->head = list->head->link;
		free(removed);
		list->length--;
	}

}
void delete_last(ListType* list) {
	if (!is_empty(list)) {
		ListNode* removed = get_node_at(list, (list->length)-1);
		ListNode* before = get_node_at(list, (list->length) - 2);
		list->tail = before;
		before->link = NULL;
		free(removed);
		list->length--;
	}
}
void delete_node(ListType* list, int pos) {
	if (!is_empty(list) && (pos >= 0) && (pos < list->length)) {
		if (pos == 0) {
			delete_first(list);
			return;
		}
		if (pos == list->length - 1) {
			delete_last(list);
			return;
		}
		ListNode* p = get_node_at(list, pos - 1); // 하나전 노드
		ListNode* removed = get_node_at(list, pos); // 삭제할 노드
		remove_node(&(list->head), p, removed);
		list->length--;
	}
}
element get_entry(ListType* list, int pos) {
	ListNode* a;
	if (pos >= list->length) error("Position Error");
	a = get_node_at(list, pos);
	return a->data;
}
void display(ListType* list) {
	int i;
	ListNode* node = list->head;
	for (i = 0; i < list->length; i++) {
		printf("| %d | %x | --->\n", node->data, node->link);
		node = node->link;
	}
	printf("\n");
}
int is_in_list(ListType* list, element item) {
	ListNode* p;
	p = list->head;
	while ((p != NULL)) {
		if (p->data == item)
			break;
		p = p->link;
	}
	if (p == NULL) return 0;
	else return 1;
}
int main(void) {
	ListType list1;
	init(&list1);
	add_first(&list1, 20); 
	add_last(&list1, 30);
	add_first(&list1, 10);
	add_last(&list1, 40);
	add_node(&list1, 2, 70);
	display(&list1);
	delete_node(&list1, 2);
	delete_first(&list1);
	delete_last(&list1);
	display(&list1);
	printf("%s\n", is_in_list(&list1, 20) == 1 ? "TRUE" : "FALSE");
	printf("%d\n", get_entry(&list1, 0));
}