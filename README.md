# Módulo `csv_reader`: Leitura de Arquivos CSV em Python Usando C

Este repositório contém um módulo Python implementado em C, chamado `csv_reader`. Ele oferece uma função eficiente para leitura de arquivos CSV, retornando os dados no formato de lista de listas em Python.

---

# Funcionalidade

O módulo possui a função principal `read_csv`, que:
1. Lê arquivos CSV linha por linha.
2. Divide cada linha em campos, baseando-se em um delimitador (padrão: `;`).
3. Retorna uma lista de listas:
   - Cada linha do CSV é uma lista.
   - Cada campo é um elemento da lista correspondente.

---

# Explicação Detalhada do Código

## 1. Inclusão de Bibliotecas

```c
#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
```

* `Python.h`: Inclui a API do Python.
* `stdio.h`, `stdlib.h`, `string.h`: Para funções de entrada/saída padrão e manipulação de strings.

## 2. Definição de Constantes

```c
#define MAX_ROW 1024 // tamanho máximo das linhas
#define DELIMITER_DEFAULT ";" // delimitador padrão
```

* `MAX_ROW`: Define o tamanho máximo de uma linha lida do arquivo CSV.
* `DELIMITER_DEFAULT`: Define o delimitador padrão como ponto e vírgula (;).

## 3. Função `read_csv`

A função `read_csv` é a principal função do módulo, responsável por ler o arquivo CSV e retornar os dados como uma lista de listas.

### Declaração da Função

```c
static PyObject *read_csv(PyObject *self, PyObject *args) {
```    

* A função é declarada como `static` para limitar seu escopo ao arquivo atual.
* Recebe dois parâmetros: `self` (referência ao próprio módulo) e `args` (argumentos passados a partir de Python).

### Declaração dos Argumentos

```c
const char *filename;
const char *delimiter = DELIMITER_DEFAULT;
```

* `filename`: Nome do arquivo CSV a ser lido.
* `delimiter`: Delimitador usado para separar os campos do CSV (padrão é `;`).

### Análise dos Argumentos

```c
if(!PyArg_ParseTuple(args, "s|s", &filename, &delimiter)) {
    return NULL;
}
```

* `PyArg_ParseTuple`: Analisa os argumentos passados da função Python. Espera pelo menos um argumento (`filename`), e opcionalmente um segundo (`delimiter`).

### Declaração das Variáveis

```c
FILE *arquivo;
char rows[MAX_ROW];
char *campo;
PyObject *result = PyList_New(0); // cria uma lista Python vazia
```

* `arquivo`: Ponteiro para o arquivo CSV.
* `rows`: Buffer para armazenar cada linha lida.
* `campo`: Ponteiro para cada campo na linha.
* `result`: Lista Python para armazenar os resultados.

### Abertura do Arquivo

```c
arquivo = fopen(filename, "r");
if(arquivo == NULL) {
    PyErr_SetString(PyExc_FileNotFoundError, "Erro ao abrir arquivo !");
    return NULL;
}
```

* `fopen`: Abre o arquivo CSV em modo de leitura.
* Em caso de erro, levanta uma exceção `FileNotFoundError` em Python.

### Leitura e Processamento das Linhas

```c
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
```

* **Leitura de Linhas**: `fgets` lê cada linha do arquivo.
* **Remoção do Caractere de Nova Linha**: `strcspn` remove o caractere \n.
* **Divisão da Linha em Campos**: `strtok` divide a linha em campos usando o delimitador.
* **Criação da Lista**: Cria uma lista Python para armazenar os campos.
* **Conversão para String Python**: `PyUnicode_FromString` converte cada campo para uma string Python.
* **Adição à Lista**: `PyList_Append` adiciona cada campo à lista.
* **Adição da Linha à Lista de Resultados**: Adiciona a lista de campos (linha) à lista de resultados.

### Fechamento do Arquivo

```c
fclose(arquivo);
return result;
```

* Fecha o arquivo CSV.
* Retorna a lista de resultados.

### Definição dos Métodos do Módulo

```c
static PyMethodDef CsvMethods[] = {
    {"read_csv", read_csv, METH_VARARGS, "Leitura de um arquivo CSV"},
    {NULL, NULL, 0, NULL}
};
```

* Define os métodos do módulo. No caso, apenas o método read_csv.

### Inicialização do Módulo

```c
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
```

* Define a estrutura do módulo.
* `PyInit_csv_reader`: Função de inicialização do módulo, que é chamada quando o módulo é importado em Python.