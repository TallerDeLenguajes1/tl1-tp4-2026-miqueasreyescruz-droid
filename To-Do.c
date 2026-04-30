#include <stdio.h>
#define ID_INICIAL 1000

typedef struct Tarea {
  int TareaID; //comienza desde 1000
  char *Descripcion; 
  int Duracion; // entre 10 - 100
} Tarea;

typedef struct Nodo {
  Tarea T;
  struct Nodo *Siguiente;
} Nodo;

int main () {
  int ID = ID_INICIAL;
  
  return 0;
}
