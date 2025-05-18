# define PY_SSIZE_T_CLEAN
# include <Python.h>
# include <math.h>
# include "symnmf.h"

int matrixShape(PyObject* matrix, int shape[]);
void PythontoC_list(double** res, PyObject* matrix, int rows, int cols);
PyObject* CtoPython_list(double** matrix, int rows, int cols);


/*symnmf*/
static PyObject *symnmf(PyObject *self, PyObject *args)
{
    double **c_W, **c_H;
    int k, shape[2];
    PyObject *W, *H, *list;
    
    /*Reading args from Python and initilasing variebles*/
    if (!PyArg_ParseTuple(args, "iOO", &k, &W, &H) || PyObject_Length(W) < 0 || PyObject_Length(H) < 0) {
        PyErr_SetString(PyExc_ValueError, "An Error Has Occurred");
        return NULL;
    }
    if(matrixShape(W, shape)){
        PyErr_SetString(PyExc_ValueError, "An Error Has Occurred");
        return NULL;
    }

    /*W, H first initialization*/
    c_W = matrixBuilder(shape[0], shape[0]), c_H = matrixBuilder(shape[0], k);
    if (c_W == NULL || c_H == NULL) {
        PyErr_SetString(PyExc_MemoryError, "An Error Has Occurred");
        return NULL;
    }
    PythontoC_list(c_W, W, shape[0], shape[0]);
    PythontoC_list(c_H, H, shape[0], k);
    
    /*Calling c_symnmf on W, H*/
    if (c_symnmf(c_W, c_H, shape[0], k)){
        PyErr_SetString(PyExc_MemoryError, "An Error Has Occurred");
        return NULL;
    }

    /*injecting the result into a PyList*/
    list = CtoPython_list(c_H, shape[0], k);
    
    /*Freeing memory*/
    freeMatrix(c_W, shape[0]);
    freeMatrix(c_H, shape[0]);
    
    return list;
}


/*sym*/
static PyObject *sym(PyObject *self, PyObject *args){
    double **c_points, **c_matrix;
    int shape[2];
    PyObject *points, *list;
    
    /*Reading args from Python and initilasing variebles*/
    if (!PyArg_ParseTuple(args, "O", &points) || PyObject_Length(points) < 0) {
        PyErr_SetString(PyExc_ValueError, "An Error Has Occurred");
        return NULL;
    }
    if(matrixShape(points, shape)){
        PyErr_SetString(PyExc_ValueError, "An Error Has Occurred");
        return NULL;
    }

    /*Points, Matrix first initialization*/
    c_points = matrixBuilder(shape[0], shape[1]);
    c_matrix = matrixBuilder(shape[0], shape[0]);
    if (c_points == NULL || c_matrix == NULL) {
        PyErr_SetString(PyExc_MemoryError, "An Error Has Occurred");
        return NULL;
    }
    PythontoC_list(c_points, points, shape[0], shape[1]);

    /*Calling c_sym on points*/
    if (c_sym(c_points, c_matrix, shape[0], shape[1])){
        PyErr_SetString(PyExc_MemoryError, "An Error Has Occurred");
        return NULL;
    }

    list = CtoPython_list(c_matrix, shape[0], shape[0]);
    
    /*Freeing memory*/
    freeMatrix(c_points, shape[0]);
    freeMatrix(c_matrix, shape[0]);
    
    return list;
}


/*ddg*/
static PyObject *ddg(PyObject *self, PyObject *args){
    double **c_points, **c_matrix;
    int shape[2];
    PyObject *points, *list;
    
    /*Reading args from Python and initilasing variebles*/
    if (!PyArg_ParseTuple(args, "O", &points) || PyObject_Length(points) < 0) {
        PyErr_SetString(PyExc_ValueError, "An Error Has Occurred");
        return NULL;
    }
    if(matrixShape(points, shape)){
        PyErr_SetString(PyExc_ValueError, "An Error Has Occurred");
        return NULL;
    }

    /*points, Matrix first initialization*/
    c_points = matrixBuilder(shape[0], shape[1]);
    c_matrix = matrixBuilder(shape[0], shape[0]);
    if (c_points == NULL || c_matrix == NULL) {
        PyErr_SetString(PyExc_MemoryError, "An Error Has Occurred");
        return NULL;
    }
    PythontoC_list(c_points, points, shape[0], shape[1]);

    /*Calling c_ddg on points*/
    if (c_ddg(c_points, c_matrix, shape[0], shape[1])){
        PyErr_SetString(PyExc_MemoryError, "An Error Has Occurred");
        return NULL;
    }

    list = CtoPython_list(c_matrix, shape[0], shape[0]);
    
    /*Freeing memory*/
    freeMatrix(c_points, shape[0]);
    freeMatrix(c_matrix, shape[0]);
    
    return list;
}




/*norm*/
static PyObject *norm(PyObject *self, PyObject *args){
    double **c_points, **c_matrix;
    int shape[2];
    PyObject *points, *list;
    
    /*Reading args from Python and initilasing variebles*/
    if (!PyArg_ParseTuple(args, "O", &points) || PyObject_Length(points) < 0) {
        PyErr_SetString(PyExc_ValueError, "An Error Has Occurred");
        return NULL;
    }
    if(matrixShape(points, shape)){
        PyErr_SetString(PyExc_ValueError, "An Error Has Occurred");
        return NULL;
    }

    /*Points, Matrix first initialization*/
    c_points = matrixBuilder(shape[0], shape[1]);
    c_matrix = matrixBuilder(shape[0], shape[0]);
    if (c_points == NULL || c_matrix == NULL) {
        PyErr_SetString(PyExc_MemoryError, "An Error Has Occurred");
        return NULL;
    }
    PythontoC_list(c_points, points, shape[0], shape[1]);

    /*Calling c_norm on points*/
    if (c_norm(c_points, c_matrix, shape[0], shape[1])){
        PyErr_SetString(PyExc_MemoryError, "An Error Has Occurred");
        return NULL;
    }

    list = CtoPython_list(c_matrix, shape[0], shape[0]);
    
    /*Freeing memory*/
    freeMatrix(c_points, shape[0]);
    freeMatrix(c_matrix, shape[0]);
    
    return list;
}


/*Necessary methods for C Python link*/
static PyMethodDef symnmfMethods[] = {
    {"symnmf",
      (PyCFunction) symnmf,
      METH_VARARGS,
      PyDoc_STR("expects two 2D array points, int dim, int k")},

    {"sym",
      (PyCFunction) sym,
      METH_VARARGS,
      PyDoc_STR("expects 2D array points, int rows, int cols")},

    {"ddg",
      (PyCFunction) ddg,
      METH_VARARGS,
      PyDoc_STR("expects 2D array points, int rows, int cols")},

    {"norm",
      (PyCFunction) norm,
      METH_VARARGS,
      PyDoc_STR("expects 2D array points, int rows, int cols")},

    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef symnmfmodule = {
    PyModuleDef_HEAD_INIT,
    "symnmfmodule",
    NULL,
    -1,
    symnmfMethods
};

PyMODINIT_FUNC PyInit_symnmfmodule(void)
{
    PyObject *m;
    m = PyModule_Create(&symnmfmodule);
    if (!m) {
        return NULL;
    }
    return m;
}

/*Updating matrix dimensions to rows, cols*/
int matrixShape(PyObject* matrix, int shape[]){
    shape[0] = PyObject_Length(matrix);
    if (shape[0] < 0) {return 1;}

    shape[1] = PyList_Size(PyList_GetItem(matrix, 0));
    if (shape[1] < 0) {return 1;}

    return 0;
}

/*Reading points from Python into a C array*/
void PythontoC_list(double** res, PyObject* matrix, int rows, int cols){
    int i, j;
    double cord;
    PyObject *row;

    for (i = 0; i < rows; i++) {
        row = PyList_GetItem(matrix, i);
        for (j = 0; j < cols; j++) {
            cord = PyFloat_AsDouble(PyList_GetItem(row, j));
            res[i][j] = cord;
        }
    }
}


/*injecting the result into a PyList*/
PyObject* CtoPython_list(double** matrix, int rows, int cols){
    int i, j;
    PyObject *list, *sublist;
    
    list = PyList_New(rows);
    for (i = 0; i < rows; i++)
    {
        sublist = PyList_New(cols);
        for (j = 0; j < cols; j++) {
            PyList_SetItem(sublist, j, PyFloat_FromDouble(matrix[i][j]));
        }
        PyList_SetItem(list, i, sublist);
    }
    return list;
}