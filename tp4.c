#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tarea {
    int TareaID;
    char *Descripcion;
    int Duracion;
} Tarea;

typedef struct Nodo {
    Tarea T;
    struct Nodo *Siguiente;
} Nodo;

Nodo *CrearListaVacia();
Nodo *CrearNodo(Tarea tarea);
void InsertarNodo(Nodo **Start, Tarea tarea);
Tarea cargar(int cantidadTareas);
void mostrarTarea(Nodo *tareas);
void controlTareas(Nodo **tareasPendientes, Nodo **tareasRealizadas);
void moverTarea(Nodo **pendientes, Nodo **realizadas, int id);
Nodo *buscarTareaPorID(Nodo **tareasPendientes, Nodo **tareasRealizadas, int id);
Nodo *buscarTareaPorPalabra(Nodo **tareasPendientes, Nodo **tareasRealizadas, char *palabra);
void liberarMemoria(Nodo *tareas);

int main(int argc, char const *argv[]) {
    int menu, idBuscar;
    int cantidadTareas = 0;
    char op;
    // char *palabra[50];
    char *palabra = (char *)malloc(sizeof(char) * 100);

    Nodo *tareasPendientes, *tareasRealizadas;

    tareasPendientes = CrearListaVacia();
    tareasRealizadas = CrearListaVacia();

    do {
        puts("*********** MENU ***********");
        printf("\t1 - Cargar tareas\n");
        printf("\t2 - Controlar tareas\n");
        printf("\t3 - Mostrar tareas pendientes y realizadas\n");
        printf("\t4 - Buscar tareas por ID\n");
        printf("\t5 - Buscar tareas por palabra clave\n");
        printf("\t6 - Salir\n");
        puts("\n");
        printf("Ingrese una opcion: ");
        fflush(stdin);
        scanf("%d", &menu);

        switch (menu) {
            case 1:
                do {
                    cantidadTareas++;
                    Tarea tarea = cargar(cantidadTareas);
                    InsertarNodo(&tareasPendientes, tarea);
                    printf("Si desea seguir agregando mas tareas presione s o S para continuar sino cualquier otra tecla: ");
                    fflush(stdin);
                    scanf("%s", &op);
                } while (op == 's' || op == 'S');
                break;
            case 2:
                if (cantidadTareas == 0) {
                    printf("--- No hay tareas cargadas ---\n");
                } else {
                    controlTareas(&tareasPendientes, &tareasRealizadas);
                }

                break;
            case 3:
                if (cantidadTareas == 0) {
                    printf("--- No hay tareas cargadas ---\n");
                } else {
                    printf("--- Tareas realizadas ---\n");
                    mostrarTarea(tareasRealizadas);
                    printf("--- Tareas pendiente ---\n");
                    mostrarTarea(tareasPendientes);
                }
                break;
            case 4:
                printf("Ingrese el ID: ");
                fflush(stdin);
                scanf(" %d", &idBuscar);
                Nodo *tareaBuscadaId = buscarTareaPorID(&tareasPendientes, &tareasRealizadas, idBuscar);
                if (tareaBuscadaId != NULL) {
                    mostrarTarea(tareaBuscadaId);
                    // printf("La tarea con ID %d es:\n", idBuscar);
                    // printf("Descripcion: %s\n", tareaBuscadaId->T.Descripcion);
                    // printf("Duracion: %d\n", tareaBuscadaId->T.Duracion);
                } else {
                    printf("No se encontro la tarea con ID %d\n", idBuscar);
                }

                break;
            case 5:

                // Llamar a buscarTareaPorPalabra para buscar una tarea por palabra clave

                printf("Ingrese la palabra clave a buscar: ");
                fflush(stdin);
                gets(palabra);
                Nodo *tareaEncontrada = buscarTareaPorPalabra(&tareasPendientes, &tareasRealizadas, palabra);

                // Verificar si se encontró una tarea que coincida con la palabra clave
                if (tareaEncontrada != NULL) {
                    mostrarTarea(tareaEncontrada);
                    // printf("Tarea encontrada:\n");
                    // printf("La tarea con la palabra ' %s ' es:\n", palabra);
                    // printf("Descripcion: %s\n", tareaBuscadaId->T.Descripcion);
                    // printf("Duracion: %d\n", tareaBuscadaId->T.Duracion);
                } else {
                    printf("No se encontraron tareas que coincidan con la palabra clave '%s'\n", palabra);
                }

                break;
            default:
                break;
        }
        printf("\n");
    } while (menu != 6);

    liberarMemoria(tareasPendientes);
    liberarMemoria(tareasRealizadas);
    fflush(stdin);
    getchar();
    return 0;
}

Nodo *CrearListaVacia() {
    return NULL;
}

Nodo *CrearNodo(Tarea tarea) {
    Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));
    nuevoNodo->T = tarea;
    nuevoNodo->Siguiente = NULL;
    return nuevoNodo;
}

void InsertarNodo(Nodo **Start, Tarea tarea) {
    Nodo *nuevoNodo = CrearNodo(tarea);
    nuevoNodo->Siguiente = *Start;
    *Start = nuevoNodo;
}

Tarea cargar(int cantidadTareas) {
    Tarea tarea;
    tarea.TareaID = cantidadTareas;
    printf("--- Tarea N%c %d\n  ", 248, tarea.TareaID);
    printf("Ingrese la descripcion de la tarea con un maximo de 50 caracteres: ");
    tarea.Descripcion = malloc(sizeof(char) * 100);
    fflush(stdin);
    gets(tarea.Descripcion);
    do {
        printf("Ingrese la duracion entre 10 a 100 de la tarea N%c %d: ", 248, tarea.TareaID);
        fflush(stdin);
        scanf("%d", &tarea.Duracion);
    } while (tarea.Duracion < 10 || tarea.Duracion > 100);

    return tarea;
}

void mostrarTarea(Nodo *tareas) {
    // este funcion muestra en el orden invertido
    if (tareas == NULL) {
        return;
    }
    mostrarTarea(tareas->Siguiente);
    printf("--- Tarea N%c %d ---\n", 248, tareas->T.TareaID);
    printf(" Id: %d n", tareas->T.TareaID);
    printf(" Descripcion:\n");
    printf("%s", tareas->T.Descripcion);
    printf("\n Duracion: %d \n", tareas->T.Duracion);
}

void controlTareas(Nodo **tareasPendientes, Nodo **tareasRealizadas) {
    int id;
    char op;
    printf("\n");
    printf("Control de Tareas\n");
    mostrarTarea(*tareasPendientes);
    printf("Indique el ID de la tarea a controlar: ");
    fflush(stdin);
    scanf(" %d", &id);
    printf("Si fue realizada la tareas presione s o S para confirmar sino cualquier otra tecla: ");
    fflush(stdin);
    scanf(" %c", &op);

    if (op == 's' || op == 'S') {
        moverTarea(tareasPendientes, tareasRealizadas, id);
    }
}

void moverTarea(Nodo **tareasPendientes, Nodo **tareasRealizadas, int id) {
    Nodo *actual = *tareasPendientes;
    Nodo *anterior = NULL;
    // Buscar la tarea en la lista de tareas pendientes
    while (actual != NULL && actual->T.TareaID != id) {
        anterior = actual;
        actual = actual->Siguiente;
    }

    if (actual == NULL) {
        // No se encontró la tarea en la lista de tareas pendientes
        printf("No se encontro la tarea con ID %d en la lista de tareas pendientes.\n", id);
        return;
    }

    // Eliminar la tarea de la lista de tareas pendientes
    if (anterior == NULL) {
        // El nodo a eliminar es el primero de la lista
        *tareasPendientes = actual->Siguiente;
    } else {
        anterior->Siguiente = actual->Siguiente;
    }

    // Agregar la tarea a la lista de tareas realizadas
    actual->Siguiente = *tareasRealizadas;
    *tareasRealizadas = actual;

    printf("La tarea con ID %d ha sido movida a la lista de tareas realizadas.\n", id);
}

Nodo *buscarTareaPorID(Nodo **tareasPendientes, Nodo **tareasRealizadas, int id) {
    Nodo *aux;

    // Buscar en tareas pendientes
    aux = *tareasPendientes;
    while (aux != NULL) {
        if (aux->T.TareaID == id) {
            return aux;
        }
        aux = aux->Siguiente;
    }

    // Buscar en tareas realizadas
    aux = *tareasRealizadas;
    while (aux != NULL) {
        if (aux->T.TareaID == id) {
            return aux;
        }
        aux = aux->Siguiente;
    }

    // No se encontró la tarea
    return NULL;
}

Nodo *buscarTareaPorPalabra(Nodo **tareasPendientes, Nodo **tareasRealizadas, char *palabra) {
    Nodo *aux = *tareasPendientes;
    while (aux != NULL) {
        if (strstr(aux->T.Descripcion, palabra) != NULL) {
            // La tarea contiene la palabra buscada en su descripción
            return aux;
        }
        aux = aux->Siguiente;
    }

    aux = *tareasRealizadas;
    while (aux != NULL) {
        if (strstr(aux->T.Descripcion, palabra) != NULL) {
            // La tarea contiene la palabra buscada en su descripción
            return aux;
        }
        aux = aux->Siguiente;
    }

    // La tarea no se encontró en ninguna de las listas
    return NULL;
}

void liberarMemoria(Nodo *tareas) {
    Nodo *aux = tareas;
    Nodo *auxAnterior = tareas;
    Nodo *auxActual = tareas;

    while (aux) {
        if (aux->T.Descripcion) {
            free(aux->T.Descripcion);
        }
        aux = aux->Siguiente;
    }

    while (auxActual) {
        auxAnterior = auxActual;
        auxActual = auxActual->Siguiente;
        free(auxAnterior);
    }
}