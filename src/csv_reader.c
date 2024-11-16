// inclui bibliotecas
#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROW 1024 // tamanho maximo das linhas
#define DELIMITER_DEFAULT ";" // delimitador padrao

static PyObject *read_csv(PyObject *self, PyObject *args) {
     // declarar os argumentos da funcao python
     const char *filename;
     const char *delimiter = DELIMITER_DEFAULT;

     // analisar os argumentos passado para a funcao python
     if(!PyArg_ParseTuple(args, "s|s", &filename, &delimiter)) {
        return NULL;
     }
     
     // declara as variaveis para ler o arquivo
     FILE *arquivo;
     char rows[MAX_ROW];
     char *campo;
     PyObject *result = PyList_New(0); // cria uma lista python vazia
     
     // abrir arquivo, em caso de falha
     // levantar uma excesao em python
     arquivo = fopen(filename, "r");
     if(arquivo == NULL) {
        PyErr_SetString(PyExc_FileNotFoundError, "Erro ao abrir arquivo !");
        return NULL;
     }

     while (fgets(rows, sizeof(rows), arquivo) != NULL) {
        rows[strcspn(rows, "\n")] = '\0';
        PyObject *row = PyList_New(0);

        campo = strtok(rows, delimiter);
        while (campo != NULL) {
            PyObject *campo_str = PyUnicode_FromString(campo);
            PyList_Append(row, campo_str);
            Py_DECREF(campo_str);
            campo = strtok(NULL, delimiter);
        }

        PyList_Append(result, row);
        Py_DECREF(row);
     }

     fclose(arquivo);
     return result;
}

static PyMethodDef CsvMethods[] = {
    {"read_csv", read_csv, METH_VARARGS, "Leitura de um arquivo CSV"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef csvmodule = {
    PyModuleDef_HEAD_INIT,
    "csv_reader",
    NULL,
    -1,
    CsvMethods
};

PyMODINIT_FUNC PyInit_csv_reader(void) {
    return PyModule_Create(&csvmodule);
}