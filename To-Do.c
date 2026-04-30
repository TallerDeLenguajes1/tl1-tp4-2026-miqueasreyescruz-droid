#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

Nodo * crearListaVacia(); 
Nodo * crearTarea (int *ID);
void insertarTarea (Nodo **Start,Nodo *Nodo);

int main () {
  int ID = ID_INICIAL, aux;
  Nodo *tPendientes, *tRealizadas;

  tPendientes = crearListaVacia();
  tRealizadas = crearListaVacia();

  printf("___INGRESANDO TAREAS___\n");
  do {
    insertarTarea(&tPendientes,crearTarea(&ID));

    printf("->Desea ingresar otra tarea?\n1. Si\n2. No\n");
    scanf("%d",&aux);
  } while (aux == 1);

  return 0;
}

Nodo * crearListaVacia() {
  return NULL;
}

Nodo * crearTarea (int *ID) {
  int aux;
  char buffer[100];
  Nodo *nNodo = (Nodo*) malloc (sizeof(Nodo));

  printf("->Creando Tarea\n");
  nNodo -> T.TareaID = *ID;
  (*ID)++;

  printf("-Ingrese una descripcion de la tarea: \n");
  while(getchar() != '\n');
  fgets(buffer, 100, stdin);
  buffer[strcspn(buffer, "\n")] = 0;
  nNodo -> T.Descripcion = (char*) malloc ((strlen(buffer) + 1) * sizeof(char));
  strcpy(nNodo -> T.Descripcion,buffer);

  printf("-Ingrese la duracion de la tarea: \n");
  scanf("%d",&aux);
  nNodo -> T.Duracion = aux;

  nNodo -> Siguiente = NULL;

  return nNodo;
}

void insertarTarea (Nodo **Start,Nodo *Tarea) {
  Tarea -> Siguiente = *Start;
  *Start = Tarea;
}
