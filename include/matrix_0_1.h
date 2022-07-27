#ifndef MATRIX_0_1_H
#define MATRIX_0_1_H 1
/*the matrix is stored in the heap
a matrix_0_1 has all of these values in the matrix 
*/
struct matrix_0_1
{
    int size;
    double ** matrix;
};
void matrix_0_1_dealloc(struct matrix_0_1 *matrix);
struct matrix_0_1 *matrix_0_1_init(int size);
int matrix_Change_Val(struct matrix_0_1* b,int i,int j,double k);
double matrix_Val_i_j(struct matrix_0_1* b,int i,int j);
double matrix_Trace(struct matrix_0_1* b);
int matrix_Size(struct matrix_0_1*);
int matrix_Set_Size(struct matrix_0_1*,int);
#endif