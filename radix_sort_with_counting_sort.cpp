#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "time.h"

#define RANGE 64 //6bit : 0-63
#define SIZE 1000

int** counting_sort(int** inp, int t) { // t는 지금 몇차례째 counting sort 하는지 나타냄
	int i = 0, j = 0;
	int* c = (int*)malloc(sizeof(int) * 64); // 배열 c : counting 할 array

	int** out = (int**)malloc(sizeof(int*) * 1000); // 결과 저장할 함수 초기화
	for (int i = 0; i < 1000; i++) {
		out[i] = (int*)malloc(sizeof(int) * 4);
	}
	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 4; j++) {
			*(*(out + i) + j) = 0;
		}
	}

	for (i = 0; i < RANGE; i++) {
		c[i] = 0;
	}
	for (j = 0; j < SIZE; j++) {
		c[inp[j][t]] += 1;
	}
	for (i = 1; i < RANGE; i++) {//누적 array
		c[i] = c[i] + c[i - 1];
	}
	//t는 현재 counting sort하고 있는 segment
	//해당 segment를 기준으로 sort 할때 나머지 segment도 같이 이동시킨다
	for (j = SIZE - 1; j > -1; j--) {
		int num = c[inp[j][t]] - 1; //누적 빈도수 = 넣을 인덱스
		out[num][t] = inp[j][t];
		out[num][(t + 1) % 4] = inp[j][(t + 1) % 4];
		out[num][(t + 2) % 4] = inp[j][(t + 2) % 4];
		out[num][(t + 3) % 4] = inp[j][(t + 3) % 4];
		c[inp[j][t]] -= 1;
	}
	for (i = 0; i < 1000; i++) {
		free(inp[i]);
	}
	free(inp);
	free(c);

	return out;
}
int** radix_sort(int** a) {

	for (int j = 0; j < 4; j++) {
		a = counting_sort(a, j);
	}
	return a;
}
int main(void) {
	// 초기 난수 생성 24bit 4개segment로나누어서 6bit씩 a 에저장
	 srand((unsigned int)time(0));

	//input_data는 int**[1000][4]로 생성. [1000][0]이 LSD, [1000][3]이 MSD
	int** input_data = (int**)malloc(sizeof(int*) * 1000);
	for (int i = 0; i < 1000; i++) {
		input_data[i] = (int*)malloc(sizeof(int) * 4);
	}//input_data 동적할당
	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 4; j++) {
			*(*(input_data + i) + j) = rand() % 64;
		}
	}//input_data 배열에 64미만의 랜덤값 삽입

	input_data = radix_sort(input_data);
	/*for (int j = 0; j < SIZE; j++) {
				for (int i = 3; i >-1; i--) {
					printf("%d\t", input_data[j][i]);
				}
				printf("\n");
			}*/

	int* result = (int*)malloc(sizeof(int) * 1000);//4개의 segment로 나눠져있던배열 하나의 수로 합치기
	for (int i = 0; i < SIZE; i++) {
		int total = 0;
		for (int j = 0; j < 4; j++) {
			total += input_data[i][j] << 6 * j;
		}
		result[i] = total;
	}
	
	for (int j = 0; j < SIZE; j++) {
		printf("%d\n", result[j]);
	}

}