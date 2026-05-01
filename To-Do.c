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
Nodo * extraerPorID (Nodo **Start, int idBuscado);
Nodo * extraerPorClave (Nodo **Start, char *clave);
Nodo * buscarElementoPorID (Nodo *Start, int idBuscado);
Nodo * buscarElementoPorClave (Nodo *Start,char *clave);
void insertarTarea (Nodo **Start,Nodo *Nodo);
void liberarLista (Nodo *Nodo);
void mostrarLista (Nodo *Start);
void mostrarNodo (Nodo *Nodo);

int main () {
  int ID = ID_INICIAL, aux, aux2, idBuscado;
  Nodo *tPendientes, *tRealizadas, *nodoAux;
  char claveBuscada[100];

  tPendientes = crearListaVacia();
  tRealizadas = crearListaVacia();

  printf("___INGRESANDO TAREAS___\n");
  do {
    printf("->Desea ingresar una tarea?\n1. Si\n2. No\n");
    scanf("%d",&aux);

    if (aux == 1) {
      insertarTarea(&tPendientes,crearTarea(&ID));
    }
  } while (aux == 1);

  printf("___TAREAS REALIZADAS___\n");
  do {
    printf("->Desea marcar una tarea como realizada?\n1. Si\n2. No\n");
    scanf("%d",&aux);

    if (aux == 1) {
      do {
        printf("->De que manera desea buscar la tarea?\n1.Por ID\n2.Por una palabra clave\n");
        scanf("%d",&aux2);
      } while (aux2 != 1 && aux2 != 2);

      if (aux2 == 1) {
        printf("Ingrese el ID a buscar: \n");
        scanf("%d",&idBuscado);
        nodoAux = extraerPorID(&tPendientes,idBuscado);
      }
      else {
        printf("Ingrese la palabra clave a buscar: \n");
        while(getchar() != '\n');
        fgets(claveBuscada, 100, stdin);
        claveBuscada[strcspn(claveBuscada, "\n")] = 0;
        nodoAux = extraerPorClave(&tPendientes,claveBuscada);
      }

      if (nodoAux != NULL) {
        printf("Tarea marcada como realizada con exito!\n");
        insertarTarea(&tRealizadas,nodoAux);
      }
      else {
        printf("Error: No se encontro la tarea\n");
      }
    }

    if (tPendientes == NULL) {
      printf("->La lista de Tareas Pendientes se encuentra vacia!\n");
    }
  } while (tPendientes != NULL && aux == 1);

  printf("___MOSTRANDO LISTAS ___\n");
  if (tPendientes != NULL) {
    printf("->Lista de Tareas Pendientes:\n");
    mostrarLista(tPendientes);
  }
  else {
    printf("Lista de Tareas Pendientes vacia!\n");
  }

  if (tRealizadas != NULL) {
    printf("->Lista de Tareas Realizadas\n");
    mostrarLista(tRealizadas);
  }
  else {
    printf("->Lista de Tareas Realizadas vacia!\n");
  }
  
  printf("___BUSQUEDA DE TAREAS___\n");
  do {
    printf("->Desea buscar un elemento en las listas?\n1.Si\n2.No\n");
    scanf("%d",&aux);

    if (aux == 1) {
      do {
        printf("->De que manera desea buscar la tarea?\n1.Por ID\n2.Por una palabra clave\n");
        scanf("%d",&aux2);
      } while (aux2 != 1 && aux2 != 2);

      if (aux2 == 1) {
        //Busqueda por ID
        printf("Ingrese el ID a buscar: \n");
        scanf("%d",&idBuscado);
        if ((nodoAux = buscarElementoPorID(tPendientes,idBuscado)) != NULL) {
          printf("Tarea encontrada en la lista de Tareas Pendientes!\n");
          mostrarNodo(nodoAux);
        }
        else if ((nodoAux = buscarElementoPorID(tRealizadas,idBuscado)) != NULL){
          printf("Tarea encontrada en la lista de Tareas Realizadas!\n");
          mostrarNodo(nodoAux);
        }
        else {
          printf("Error: ID no encontrado\n");
        }
      }
      else {
        //Busqueda por Clave
        printf("Ingrese la palabra clave a buscar: \n");
        while(getchar() != '\n');
        fgets(claveBuscada, 100, stdin);
        claveBuscada[strcspn(claveBuscada, "\n")] = 0;
        if ((nodoAux = buscarElementoPorClave(tPendientes,claveBuscada)) != NULL) {
          printf("Tarea encontrada en la lista de Tareas Pendientes!\n");
          mostrarNodo(nodoAux);
        }
        else if ((nodoAux = buscarElementoPorClave(tRealizadas,claveBuscada)) != NULL){
          printf("Tarea encontrada en la lista de Tareas Realizadas!\n");
          mostrarNodo(nodoAux);
        }
        else {
          printf("Error: ID no encontrado\n");
        }
      }
    }
  } while (aux == 1);

  liberarLista(tPendientes);
  liberarLista(tRealizadas);

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

  do {
    printf("-Ingrese la duracion de la tarea (min 10 - 100 max): \n");
    scanf("%d",&aux);
  } while (aux < 10 || aux > 100);
  nNodo -> T.Duracion = aux;

  nNodo -> Siguiente = NULL;

  return nNodo;
}

void insertarTarea (Nodo **Start,Nodo *Tarea) {
  Tarea -> Siguiente = *Start;
  *Start = Tarea;
}

void liberarLista (Nodo *Start) {
  Nodo *aux;
  while (Start != NULL) {
    aux = Start;
    Start = Start -> Siguiente;
    free(aux -> T.Descripcion);
    free(aux);
  }
}

Nodo * extraerPorID (Nodo **Start, int idBuscado) {
  Nodo *aux = *Start;
  Nodo *ant = NULL;

  while (aux && aux -> T.TareaID != idBuscado) {
    ant = aux;
    aux = aux -> Siguiente;
  }

  if (aux != NULL) {
    if (aux == (*Start)) {
      (*Start) = aux -> Siguiente;
    }
    else {
      ant -> Siguiente = aux -> Siguiente;
    }
    aux -> Siguiente = NULL;
  }
  
  return aux;
}

Nodo * extraerPorClave (Nodo **Start, char *clave) {
  Nodo *aux = *Start;
  Nodo *ant = NULL;

  while (aux && (strstr(aux -> T.Descripcion,clave) == NULL)) {
    ant = aux;
    aux = aux -> Siguiente;
  }

  if (aux != NULL) {
    if (aux == (*Start)) {
      (*Start) = aux -> Siguiente;
    }
    else {
      ant -> Siguiente = aux -> Siguiente;
    }
    aux -> Siguiente = NULL;
  }
  
  return aux;
}

void mostrarLista (Nodo *Start) {
  Nodo *aux = Start;
  while (aux != NULL) {
    printf("-Tarea:\n");
    printf("ID: %d\n",aux -> T.TareaID);
    printf("Descripcion: %s\n",aux -> T.Descripcion);
    printf("Duracion: %d\n",aux -> T.Duracion);
    aux = aux -> Siguiente;
  }
}

Nodo * buscarElementoPorID (Nodo *Start, int idBuscado) {
  Nodo *aux = Start;
  while (aux && (aux -> T.TareaID != idBuscado)) {
    aux = aux -> Siguiente;
  }
  return aux;
}

Nodo * buscarElementoPorClave (Nodo *Start,char *clave) {
  Nodo *aux = Start; 
  while (aux && (strstr(aux -> T.Descripcion,clave) == NULL)) {
    aux = aux -> Siguiente;
  }
  return aux;
}

void mostrarNodo (Nodo *Nodo) {
    printf("-Tarea:\n");
    printf("ID: %d\n",Nodo -> T.TareaID);
    printf("Descripcion: %s\n",Nodo -> T.Descripcion);
    printf("Duracion: %d\n",Nodo -> T.Duracion);
}
