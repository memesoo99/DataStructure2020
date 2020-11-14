// huffman.cpp : Defines the entry point for the console application.
//

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#define MAX_ELEMENT 1000
#define MAX_BIT		10
#define MAX_CHAR	20

typedef struct ListNode {
	int value;
	ListNode* link;
};
typedef struct ListHeader {
	ListNode* head;
};
// Input data for huffman code
typedef struct input_huff {
	char* data;		// Character array (a ~ f)
	int* freq;		// Frequency array
	int size;		// Number of characters
} input_huff;

// Structure for huffman binary tree
typedef struct TreeNode {
	char data;			// Character (a ~ f)
	int key;			// Frequency
	int bits[MAX_BIT];	// Huffman codeword
	int bit_size;		// Huffman codeword's size
	struct TreeNode* l;	// Left child of huffman binary tree
	struct TreeNode* r;	// Right child of huffman binary tree
} TreeNode;

// Structure for bits stream
typedef struct bits_stream {
	int* stream;
	int length;
} bits_stream;

// Elements used in the heap
typedef struct element {
	TreeNode* ptree;  //�θ�Ʈ�����????
	int key;	// frequency of each character
} element;

// Heap
typedef struct HeapType {
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

int** m_LUT, * m_bit_size;
int	m_char_size = 6;

// Initialization
void init(HeapType* h)
{
	h->heap_size = 0;
}
//
int is_empty(HeapType* h)
{
	if (h->heap_size == 0)
		return true;
	else
		return false;
}

void insert_min_heap(HeapType* h, element item)
{
	int i;
	i = ++(h->heap_size);

	// compare it with the parent node in an order from the leaf to the root
	while ((i != 1) && (item.key < h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item; // Insert new node
}

element delete_min_heap(HeapType* h)
{
	int parent, child;
	element item, temp;
	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		if ((child < h->heap_size) && (h->heap[child].key) > h->heap[child + 1].key)
			child++;
		if (temp.key <= h->heap[child].key) break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

// Node generation in binary tree
TreeNode* make_tree(TreeNode* left, TreeNode* right)
{
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	if (node == NULL) {
		fprintf(stderr, "Memory allocation error\n");
		exit(1);
	}
	node->l = left;
	node->r = right;
	return node;
}

// Binary tree removal
void destroy_tree(TreeNode* root)
{
	if (root == NULL) return;
	destroy_tree(root->l);
	destroy_tree(root->r);
	free(root);
}

// Huffman code generation
element huffman_tree(input_huff* huff)
{
	int i;
	TreeNode* node, * x;
	HeapType heap;
	element e, e1, e2;
	init(&heap);

	int n = huff->size; //6

	for (i = 0; i < n; i++) {
		node = make_tree(NULL, NULL);
		e.ptree = node;
		node->data = huff->data[i];
		e.key = node->key = huff->freq[i];
		memset(node->bits, 0, sizeof(int) * MAX_BIT); //node ���� codeword 0000�ʱ�ȭ
		node->bit_size = 0;

		insert_min_heap(&heap, e);
	}

	for (i = 1; i < n; i++) {
		// Delete two nodes with minimum values
		e1 = delete_min_heap(&heap);
		e2 = delete_min_heap(&heap);

		// Merge two nodes
		x = make_tree(e1.ptree, e2.ptree);
		e.ptree = x;
		x->data = NULL;
		e.key = x->key = e1.key + e2.key;
		memset(x->bits, 0, sizeof(int) * MAX_BIT);
		x->bit_size = 0;

		insert_min_heap(&heap, e);
	}
	e = delete_min_heap(&heap); // Final Huffman binary tree

	return e;
	//	destroy_tree(e.ptree);
}
bool is_leaf(TreeNode* a) {
	if ((a->l == NULL) && (a->r == NULL)) return true;
	else return false;
}
// Generate the huffman codeword from the huffman binary tree
// Hint: use the recursion for tree traversal
// input: root node
// output: m_LUT, m_bit_size

void saveArr(int arr[], int n, int index)
{
	int i;
	for (i = 0; i < n; ++i) {
		m_LUT[index][i] = arr[i];
	}
	m_bit_size[index] = n;
}

void huffman_traversal(TreeNode* node, int arr[], int top)
{
	if (node->l) {
		arr[top] = 0;
		huffman_traversal(node->l, arr, top + 1);
	}
	if (node->r) {
		arr[top] = 1;
		huffman_traversal(node->r, arr, top + 1);
	}
	if (is_leaf(node))
	{
		char data = node->data;

		switch (data) {
		case 'a':
			saveArr(arr, top, 0);
			break;
		case 'b':
			saveArr(arr, top, 1);
			break;
		case 'c':
			saveArr(arr, top, 2);
			break;
		case 'd':
			saveArr(arr, top, 3);
			break;
		case 'e':
			saveArr(arr, top, 4);
			break;
		case 'f':
			saveArr(arr, top, 5);
			break;
		}


	}
}

int** mem_2D_int(int row, int col)
{
	int** m2 = (int**)malloc(sizeof(int*) * row);
	for (int i = 0; i < row; i++)
		m2[i] = (int*)malloc(sizeof(int) * col);
	return m2;
}

void print_codeword()
{
	printf("* Huffman codeword\n");
	for (int i = 0; i < m_char_size; i++)
	{
		switch (i) {
		case 0:
			printf("%c: ", 'a');
			break;
		case 1:
			printf("%c: ", 'b');
			break;
		case 2:
			printf("%c: ", 'c');
			break;
		case 3:
			printf("%c: ", 'd');
			break;
		case 4:
			printf("%c: ", 'e');
			break;
		case 5:
			printf("%c: ", 'f');
			break;
		}

		for (int j = 0; j < m_bit_size[i]; j++)
			printf("%d", m_LUT[i][j]);

		printf("\n");
	}

}
void bits_add(bits_stream* bits_str, int i) {
	int len = bits_str->length;
	int row = i;
	int n;
	for (n = 0; n < m_bit_size[row]; n++) {
		bits_str->stream[len + n] = m_LUT[i][n];
		bits_str->length++;
	}
}
// Input: 'str'
// Output: 'bits_stream' (consisting of 0 or 1)
// 'bits_stream' is generated using 'm_LUT' generated by the huffman binary tree
// Return the total length of bits_stream
void huffman_encoding(char* str, bits_stream* bits_str)
{
	int interval = 0;
	int len = strlen(str);
	/*printf("%d", len);*/ //9
	for (int i = 0; i < len; i++) {
		char ch = str[i];
		switch (ch) {
		case 'a':
			interval += m_bit_size[0];
			bits_add(bits_str, 0);
			break;
		case 'b':
			interval += m_bit_size[1];
			bits_add(bits_str, 1);
			break;
		case 'c':
			interval += m_bit_size[2];
			bits_add(bits_str, 2);
			break;
		case 'd':
			interval += m_bit_size[3];
			bits_add(bits_str, 3);
			break;
		case 'e':
			interval += m_bit_size[4];
			bits_add(bits_str, 4);
			break;
		case 'f':
			interval += m_bit_size[5];
			bits_add(bits_str, 5);
			break;
		}
	}

	printf("\n* Huffman encoding\n");
	printf("total length of bits stream: %d\n", interval);
	printf("bits stream: ");
	for (int i = 0; i < interval; i++)
		printf("%d", bits_str->stream[i]);
	printf("\n");
}

// input: 'bits_stream' and 'total_length'
// output: 'decoded_str'
int huffman_decoding(bits_stream* bits_str, TreeNode* node, char* decoded_str)
{
	int* arr;
	int index_char = 0;
	TreeNode* curr = node;
	for (int i = 0; i < bits_str->length; i++) {
		if (bits_str->stream[i] == 0) {
			curr = curr->l;
		}
		else {
			curr = curr->r;
		}
		if ((curr->l == NULL) && (curr->r == NULL)) {
			decoded_str[index_char] = curr->data;
			index_char++;
			curr = node;
		}
	}

	printf("\n* Huffman decoding\n");
	printf("total number of decoded chars: %d\n", index_char);
	printf("decoded chars: ");
	for (int i = 0; i < index_char; i++)
		printf("%c", decoded_str[i]);
	printf("\n");

	return index_char;
}

void main()
{
	char data[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
	int freq[] = { 45, 13, 12, 16, 9, 5 };

	input_huff* huff1 = (input_huff*)malloc(sizeof(input_huff));
	huff1->data = data;
	huff1->freq = freq;
	huff1->size = m_char_size;

	// m_LUT: each row corresponds to the codeword for each character
	// m_bit_size: 1D array of codeword size for each character
	// For instance, a = 0, b = 101, ...
	// 1st row of 'm_LUT': 0 0 ... 0
	// 2nd row of 'm_LUT': 1 0 1 ...0
	// m_bit_size = {1, 3, ...}
	m_LUT = mem_2D_int(m_char_size, MAX_BIT);
	m_bit_size = (int*)malloc(sizeof(int) * m_char_size);

	// Generate the huffman binary tree on heap
	// 'element_root': element containing the root node
	element element_root = huffman_tree(huff1);
	int arr[MAX_BIT];
	int top = 0;
	// Generate the huffman codeword from the huffman binary tree
	huffman_traversal(element_root.ptree, arr, top);
	//printf out the huffman codeword
	print_codeword();

	//example of input data
	char str[MAX_CHAR] = { "abacdebaf" };
	//char str[MAX_CHAR] = { "ab" };
	char decoded_str[MAX_CHAR];

	printf("\n* input chars: ");
	for (int i = 0; i < strlen(str); i++)
		printf("%c", str[i]);
	printf("\n");

	//start encoding
	bits_stream* bits_str1 = (bits_stream*)malloc(sizeof(bits_stream));
	bits_str1->stream = (int*)malloc(sizeof(int) * MAX_BIT * MAX_CHAR);
	memset(bits_str1->stream, -1, sizeof(int) * MAX_BIT * MAX_CHAR);
	bits_str1->length = 0;

	huffman_encoding(str, bits_str1);

	//start decoding	
	int decoded_char_length = huffman_decoding(bits_str1, element_root.ptree, decoded_str);
}