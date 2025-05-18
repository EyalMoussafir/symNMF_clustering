# ifndef SYMNMF_H_
# define SYMNMF_H_

double** matrixBuilder(int rows, int cols);
void freeMatrix(double** matrix, int rows);
int c_symnmf(double** W, double** H, int dim, int k);
int c_sym(double** points, double** matrix, int rows, int cols);
int c_ddg(double** points, double** matrix, int rows, int cols);
int c_norm(double** points, double** matrix, int rows, int cols);

# endif