# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include "symnmf.h"

int goalCases(double **points, double **matrix, int *shape, char *goal);
void matrixShapeFromFile(FILE *file, int *shape);
void matrixFromFile(double **matrix, FILE *file);
void printMatrix(double **matrix, int rows, int cols);
double euc_dist(double *point_1, double *point_2, int cols);
int Frobenius(double **M1, double **M2, int rows, int cols, double eps);
void multiply(double **M1, double **M2, double **res, int rows, int common, int cols);
void transpose(double **M1, double **res, int rows, int cols);
void next_H(double **H, double **numerator, double **denominator, double **res, int rows, int cols);
void swap(double **M1, double **M2, int rows, int cols);

int main(int argc, char **argv)
{
    int shape[2];
    double **points, **matrix;
    FILE *file;

    if (argc != 3) {printf("An Error Has Occurred"); return 1;}

    /*Counting columns, rows*/
    file = fopen(argv[2], "r");
    if (file == NULL) {printf("An Error Has Occurred"); return 1;}

    matrixShapeFromFile(file, shape);
    if (shape == NULL) {printf("An Error Has Occurred"); return 1;}

    /*Matrix first initialization*/
    points = matrixBuilder(shape[0], shape[1]);
    matrix = matrixBuilder(shape[0], shape[0]);
    if (points == NULL || matrix == NULL) {
        printf("An Error Has Occurred");
        return 1;
    }

    /*Storing the contents of the text file into points*/
    matrixFromFile(points, file);

    if(goalCases(points, matrix, shape, argv[1])){
        printf("An Error Has Occurred"); 
        return 1;
    }
    
    /*Print the final matrix*/
    printMatrix(matrix, shape[0], shape[0]);

    /*Freeing memory*/
    freeMatrix(points, shape[0]);
    freeMatrix(matrix, shape[0]);

    return 0;
}


/*choose function based on goal*/
int goalCases(double **points, double **matrix, int *shape, char *goal){

    if (strcmp(goal, "sym") == 0) {
        c_sym(points, matrix, shape[0], shape[1]);
        return 0;
    }

    if (strcmp(goal, "ddg") == 0) {
        c_ddg(points, matrix, shape[0], shape[1]);
        return 0;
    }

    if (strcmp(goal, "norm") == 0) {
        if(c_norm(points, matrix, shape[0], shape[1])) {
            freeMatrix(points, shape[0]);
            freeMatrix(matrix, shape[0]);
            return 1;
        }
        else {return 0;}
    }

    freeMatrix(points, shape[0]);
    freeMatrix(matrix, shape[0]);
    return 1;
}

/*Counting columns, rows*/
void matrixShapeFromFile(FILE *file, int *shape){
    int ch;
    double value;

    shape[0] = 0;
    shape[1] = 0;

    while (fscanf(file, "%lf,", &value) == 1){
        ch = fgetc(file);
        if (ch == '\n' || ch == EOF) {shape[0]++; shape[1]++;} 
        else {ungetc(ch, file);shape[1]++;}
    }
    shape[1] /= shape[0];
}

/*Storing the contents of the text file into a 2D array*/
void matrixFromFile(double **matrix, FILE *file){
    int i=0, j=0, ch;
    double value;
    rewind(file);

    while (fscanf(file, "%lf,", &value) == 1) {
    ch = fgetc(file);
    if (ch == '\n' || ch == EOF) {
        matrix[i++][j] = value;
        j = 0;
        } 
    else {
        ungetc(ch, file);
        matrix[i][j++] = value;
        }
    }
    fclose(file);
}


/*Print a matrix*/
void printMatrix(double **matrix, int rows, int cols){
    int i, j;
    
    for (i=0; i<rows; i++){
        for (j=0; j<cols-1; j++){
            printf("%.4f,",matrix[i][j]);
        }
        printf("%.4f\n",matrix[i][cols-1]);
    }
}


/*Create a matrix*/
double** matrixBuilder(int rows, int cols){
    int i, j;
    double** matrix;
    
    matrix = calloc(rows, sizeof(double *));
    if (matrix == NULL) {return NULL;}

    for (i = 0; i < rows; i++) {
        matrix[i] = calloc(cols, sizeof(double));
        if (matrix[i] == NULL) {
            for (j = 0; j < i; j++){
                free(matrix[i]);
            }
            free(matrix);
            return NULL;
        }
    }
    return matrix;
}


/*Remove matrix*/
void freeMatrix(double **matrix, int rows){
    int i;

    for (i = 0; i < rows; i++){
        free(matrix[i]);
    }
    free(matrix);
}


/*Calculate distance between a two points*/
double euc_dist(double *point_1, double *point_2, int cols){
    double sum = 0;
    int i;
    for (i = 0; i<cols; i++){
        sum += pow((point_1[i] - point_2[i]),2);
    }
    return sum;
}


/*Frobenius norm*/
int Frobenius(double **M1, double **M2, int rows, int cols, double eps){
    int i, j;
    double sum = 0;

    for (i=0 ; i<rows ; i++){
        for (j=0; j<cols; j++){
            sum += pow(M1[i][j] - M2[i][j], 2);
        }
    }

    return (sum < eps) ? 1 : 0;
}


/*Multiply matrices*/
void multiply(double **M1, double **M2, double **res, int rows, int common, int cols){
    int i, j, k;

    for (i = 0; i < rows; i++) {
        for (j=0; j < cols; j++){
            res[i][j] = 0;
            for (k=0; k < common; k++){
                res[i][j] = res[i][j] + M1[i][k] * M2[k][j];
            }
        }
    }
}


/*Transpose*/
void transpose(double **M1, double **res, int rows, int cols){
    int i, j;

    for (i=0 ; i<rows ; i++){
        for (j=0; j<cols; j++){
            res[j][i] = M1[i][j];
        }
    }
}


/*Next H*/
void next_H(double **H, double **numerator, double **denominator, double **res, int rows, int cols){
    int i, j;
    double b = 0.5;

    for (i=0 ; i<rows ; i++){
        for (j=0; j<cols; j++){
            res[i][j] = H[i][j]*(1-b + b*(numerator[i][j]/denominator[i][j]));
        }
    }
}


/*Swap matrices values*/
void swap(double **M1, double **M2, int rows, int cols){
    int i, j;
    double tmp;

    for(i = 0; i < rows; i++){
        for(j=0; j < cols; j++){
            tmp = M1[i][j];
            M1[i][j] = M2[i][j];
            M2[i][j] = tmp;
        }
    }
}


/*Update H matrix*/
int c_symnmf(double** W, double** H, int n, int k){
    int i, iter = 300;
    double eps = 1e-4, **numerator, **denominator, **H_new, **H_tranpose, **helper_NxN;

    numerator = matrixBuilder(n, k);
    denominator = matrixBuilder(n, k);
    H_new = matrixBuilder(n, k);
    H_tranpose = matrixBuilder(k, n);
    helper_NxN = matrixBuilder(n, n);
    if (numerator == NULL || denominator == NULL || H_new == NULL || H_tranpose == NULL || helper_NxN == NULL) {return 1;}

    for(i = 0; i < iter; i++){
        /*Calculating numerator*/
        multiply(W, H, numerator, n, n, k);

        /*Calculating denominator*/
        transpose(H, H_tranpose, n, k);
        multiply(H, H_tranpose, helper_NxN, n, k, n);
        multiply(helper_NxN, H, denominator, n, n, k);

        /*Calculating next H*/
        next_H(H, numerator, denominator, H_new, n, k);

        /*Swap H, next H*/
        swap(H, H_new, n, k);

        if(Frobenius(H, H_new, n, k, eps)) {break;}
    }

    /*Freeing memory*/
    freeMatrix(numerator, n);
    freeMatrix(denominator, n);
    freeMatrix(H_new, n);
    freeMatrix(H_tranpose, k);
    freeMatrix(helper_NxN, n);

    return 0;
}


/*Similarity matrix*/
int c_sym(double** points, double** matrix, int rows, int cols){
    int i, j;
    for (i=0 ; i<rows ; i++){
        for (j=i; j<rows; j++){
            if (i == j){matrix[i][i] = 0;}
            else{
                matrix[i][j] = matrix[j][i] = exp(-euc_dist(points[i],points[j], cols)/2);}
        }
    }
    return 0;
}


/*Diagonal degree matrix*/
int c_ddg(double** points, double** matrix, int rows, int cols){
    int i, j;
    c_sym(points, matrix, rows, cols);
    for (i=0 ; i<rows ; i++){
        for (j=0; j<rows; j++){
            if(i != j){matrix[i][i] += matrix[i][j]; matrix[i][j] = 0;}
        }
    }
    return 0;
}


/*Normalized similarity matrix*/
int c_norm(double** points, double** matrix, int rows, int cols){
    int i, j;
    double *ddg;
    c_sym(points, matrix, rows, cols);

    ddg = calloc(rows, sizeof(double));
    if (ddg == NULL) {return 1;}

    for (i=0 ; i<rows ; i++){
        for (j=0; j<rows; j++){ddg[i] += matrix[i][j];}
        ddg[i] = pow(ddg[i], -0.5);
    }
    for (i=0; i<rows; i++){
        for (j=0; j<rows; j++){
            matrix[i][j] = matrix[i][j] * ddg[i] * ddg[j];
        }
    }
    free(ddg);
    return 0;
}

