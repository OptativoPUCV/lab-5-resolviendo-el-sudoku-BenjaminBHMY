#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
    int i,j,k,l;

    //Revisar filas y columnas
    for (i = 0; i < 9; i++) {
        int fila[10] = {0};
        int col[10] = {0};
        for (j = 0; j < 9; j++) {
            int num_fila = n->sudo[i][j];
            int num_col = n->sudo[j][i];
            if (num_fila > 0) {
                if (fila[num_fila] == 1) return 0; // Repetido en fila
                fila[num_fila] = 1;
            }
            if (num_col > 0) {
                if (col[num_col] == 1) return 0; // Repetido en columna
                col[num_col] = 1;
            }
        }
    }

    //Revisar submatrices 3x3
    for (k = 0; k < 3; k++) {
        for (l = 0; l < 3; l++) {
            int subMat[10] = {0};
            for (i = 0; i < 3; i++) {
                for (j = 0; j < 3; j++) {
                    int num = n->sudo[k * 3 + i][l * 3 + j];
                    if (num > 0) {
                        if (subMat[num] == 1) return 0; // Repetido en subcuadrante
                        subMat[num] = 1;
                    }
                }
            }
        }
    }
    return 1;
}


List* get_adj_nodes(Node* n) {
    List* list = createList();
    Node* new;
    int i, j, k;

    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            if (n->sudo[i][j] == 0) {
                for (k = 1; k <= 9; k++) {
                    new = copy(n);
                    new->sudo[i][j] = k;
                    if (is_valid(new)) {
                        pushBack(list, new);
                    } else {
                        free(new);
                    }
                }
                return list; 
            }
        }
    }

    return list;
}


int is_final(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(n->sudo[i][j]==0)
            return 0;
       }
    }
    return 1;
}

Node* DFS(Node* initial, int* cont){
    Stack* stack = createStack();
    push(stack, initial);
    
    while (!is_empty(stack)) {
        Node* current = (Node*) top(stack);
        pop(stack);
        (*cont)++;
        
        if (is_final(current)) {
            while (!is_empty(stack)) {
                Node* temp = (Node*) top(stack);
                pop(stack);
                free(temp);
            }
            return current;
        }
    return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/