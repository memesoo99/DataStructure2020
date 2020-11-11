#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 100

 typedef struct {
    int row;
    int col;
    int value;
} element;

typedef struct {
    element data[MAX_TERMS];
    int row;
    int col;
    int terms;
}SparseMatrix;

SparseMatrix sparse_matrix_transpose(SparseMatrix m) {
    int bindex;
    SparseMatrix b;
    b.row = m.row;
    b.col = m.col;
    b.terms = m.terms;

    if (m.terms > 0) {
        bindex = 0;
        for (int c = 0; c < m.col; c++) {
            for (int i = 0; i < m.terms; i++) {
                if (m.data[i].col == c) {
                    b.data[bindex].row = m.data[i].col;
                    b.data[bindex].col = m.data[i].row;
                    b.data[bindex].value = m.data[i].value;
                    bindex++;
                }
            }
        }

    }

    return b;
}


void matrix_print(SparseMatrix a) {
    printf("\n");
    int flag=0;
    for (int i = 0; i < a.row; i++) {
        for (int t = 0; t < a.col; t++) {
            for (int c = 0; c < a.terms; c++) {
                flag = 0;
                if (a.data[c].row == i && a.data[c].col == t) {
                    printf("%d ", a.data[c].value);
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) printf("0 ");
        }
            printf("\n");
    }

        printf("\n");
}
int main(void) {
        SparseMatrix a = { {{0,3,7},{1,0,9},{1,5,8},{3,0,6},{3,1,5},{4,5,1},{5,2,2}},6,6,7 };
        SparseMatrix b;
        b = sparse_matrix_transpose(a);
        printf("Original Matrix\n");
        matrix_print(a);
        printf("Transposed Matrix\n");
        matrix_print(b);
}