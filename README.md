# Módulo `csv_reader`: Leitura de Arquivos CSV em Python Usando C

Este repositório contém um módulo Python implementado em C, chamado `csv_reader`. Ele oferece uma função eficiente para leitura de arquivos CSV, retornando os dados no formato de lista de listas em Python.

---

## Funcionalidade

O módulo possui a função principal `read_csv`, que:
1. Lê arquivos CSV linha por linha.
2. Divide cada linha em campos, baseando-se em um delimitador (padrão: `;`).
3. Retorna uma lista de listas:
   - Cada linha do CSV é uma lista.
   - Cada campo é um elemento da lista correspondente.

---

## Explicação Detalhada do Código

### 1. Inclusão de Bibliotecas

```c
#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
```

* Python.h: Inclui a API do Python.
* stdio.h, stdlib.h, string.h: Para funções de entrada/saída padrão e manipulação de strings.

### 2. Definição de Constantes

```c
#define MAX_ROW 1024 // tamanho máximo das linhas
#define DELIMITER_DEFAULT ";" // delimitador padrão
```