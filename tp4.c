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
void controlTareas(Nodo **tareasPendientes, Nodo **tareasRealizadas, Nodo **tareasEnProceso);
void moverTarea(Nodo **origen, Nodo **destino, int id);
Nodo *buscarTareaPorID(Nodo **tareasPendientes, Nodo **tareasRealizadas, Nodo **tareasEnProceso, int id);
Nodo *buscarTareaPorPalabra(Nodo **tareasPendientes, Nodo **tareasRealizadas, Nodo **tareasEnProceso, char *palabra);
void liberarMemoria(Nodo *tareas);
void eliminarTarea(Nodo **tareasPendientes, Nodo **tareasEnProceso, Nodo **tareasRealizadas, int id);
Nodo *eliminarNodo(Nodo **inicio, Nodo *nodoAEliminar);
void mostrarDatos(Nodo *inicio);

int main(int argc, char const *argv[]) {
    int menu, idBuscar;
    int cantidadTareas = 0;
    char op;
    // char *palabra[50];
    char *palabra = (char *)malloc(sizeof(char) * 100);

    Nodo *tareasPendientes, *tareasRealizadas, *tareasEnProceso;

    tareasPendientes = CrearListaVacia();
    tareasRealizadas = CrearListaVacia();
    tareasEnProceso = CrearListaVacia();

    do {
        puts("*********** MENU ***********");
        printf("\t1 - Cargar tareas\n");
        printf("\t2 - Control de las tareas pendientes\n");
        printf("\t3 - Mostrar tareas realizadas, pendientes y en progreso \n");
        printf("\t4 - Buscar tareas por ID\n");
        printf("\t5 - Buscar tareas por palabra clave\n");
        printf("\t6 - Mostrar los tiempo\n");
        printf("\t7 - Modificar el lugar de la tarea por id\n");
        printf("\t8 - Eliminar Tarea por id\n");

        printf("\t9 - Salir\n");
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
                    printf("Precione la siguiente tecla para: ");
                    printf("'S' o 's' si desea agregar mas tareas\n ");
                    printf("cualquier otra tecla si no va agregar mas\n ");
                    fflush(stdin);
                    scanf("%s", &op);
                } while (op == 's' || op == 'S');
                break;
            case 2:
                if (cantidadTareas == 0) {
                    printf("--- No hay tareas cargadas ---\n");
                } else {
                    controlTareas(&tareasPendientes, &tareasRealizadas, &tareasEnProceso);
                }

                break;
            case 3:
                if (cantidadTareas == 0) {
                    printf("--- No hay tareas cargadas ---\n");
                } else {
                    printf("--- Tareas realizadas ---\n");
                    mostrarTarea(tareasRealizadas);
                    printf("\n");
                    printf("--- Tareas pendiente ---\n");
                    mostrarTarea(tareasPendientes);
                    printf("\n");
                    printf("--- Tareas en progreso ---\n");
                    mostrarTarea(tareasEnProceso);
                    printf("\n");
                }
                break;
            case 4:
                printf("Ingrese el ID: ");
                fflush(stdin);
                scanf(" %d", &idBuscar);
                Nodo *tareaBuscadaId = buscarTareaPorID(&tareasPendientes, &tareasRealizadas, &tareasEnProceso, idBuscar);
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
                Nodo *tareaEncontrada = buscarTareaPorPalabra(&tareasPendientes, &tareasRealizadas, &tareasEnProceso, palabra);

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
            case 6:
                printf("tarea en progreso\n");
                mostrarDatos(tareasEnProceso);
                printf("tarea en pendiente\n");
                mostrarDatos(tareasPendientes);
                printf("tarea en realizadas\n");
                mostrarDatos(tareasRealizadas);
                break;
            case 7:

                printf("Ingrese el ID de la tarea a modificar: ");
                fflush(stdin);
                scanf(" %d", &idBuscar);
                Nodo *tareaModiId = buscarTareaPorID(&tareasPendientes, &tareasRealizadas, &tareasEnProceso, idBuscar);
                if (tareaModiId == NULL) {
                    printf("La tarea a modificar no se encuentra en ninguna lista\n");
                } else {
                    printf("Presione la siguiente tecla si la tarea esta en:\n");
                    printf("S, Tarea Realizada\n");
                    printf("N, Tarea Pendiente\n");
                    printf("P, Tarea en Progreso\n");
                    fflush(stdin);
                    scanf(" %c", &op);
                    if (op == 's' || op == 'S') {
                        moverTarea(&tareaModiId, &tareasRealizadas, idBuscar);

                    } else if (op == 'P' || op == 'p') {
                        moverTarea(&tareaModiId, &tareasEnProceso, idBuscar);

                    } else if (op == 'N' || op == 'n') {
                        moverTarea(&tareaModiId, &tareasPendientes, idBuscar);
                    }
                }

                break;
            case 8:
                printf("Ingrese el ID de la tarea a eliminar: ");
                fflush(stdin);
                scanf(" %d", &idBuscar);
                Nodo *tareaAEliminar = buscarTareaPorID(&tareasPendientes, &tareasRealizadas, &tareasEnProceso, idBuscar);
                if (tareaAEliminar != NULL) {
                    eliminarNodo(&tareasPendientes, tareaAEliminar);
                } else {
                    printf("La tarea a eliminar no se encuentra en ninguna lista\n");
                }

                break;
            default:
                break;
        }
        printf("\n");
    } while (menu != 9);

    liberarMemoria(tareasPendientes);
    liberarMemoria(tareasRealizadas);
    liberarMemoria(tareasEnProceso);
    fflush(stdin);
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
    printf("******* Tarea N%c %d *******\n", 248, tareas->T.TareaID);
    printf(" Id: %d n", tareas->T.TareaID);
    printf(" Descripcion:\n");
    printf("%s", tareas->T.Descripcion);
    printf("\n Duracion: %d \n", tareas->T.Duracion);
}

void controlTareas(Nodo **tareasPendientes, Nodo **tareasRealizadas, Nodo **tareasEnProceso) {
    int id;
    char op;
    printf("\n");
    printf("Control de Tareas\n");
    mostrarTarea(*tareasPendientes);
    printf("Indique el ID de la tarea a controlar: ");
    fflush(stdin);
    scanf(" %d", &id);

    printf("Presiones los siguientes teclas si la tarea esta en:\n");
    printf("S, Tarea Realizada\n");
    printf("N, Tarea Pendiente\n");
    printf("P, Tarea en Progreso\n");
    fflush(stdin);
    scanf(" %c", &op);
    if (op == 's' || op == 'S') {
        moverTarea(tareasPendientes, tareasRealizadas, id);
    } else if (op == 'P' || op == 'p') {
        moverTarea(tareasPendientes, tareasEnProceso, id);
    }
}

void moverTarea(Nodo **origen, Nodo **destino, int id) {
    Nodo *actual = *origen;
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
        *origen = actual->Siguiente;
    } else {
        anterior->Siguiente = actual->Siguiente;
    }

    // Agregar la tarea a la lista de tareas realizadas
    actual->Siguiente = *destino;
    *destino = actual;

    printf("La tarea con ID %d ha sido movida.\n", id);
}

Nodo *buscarTareaPorID(Nodo **tareasPendientes, Nodo **tareasRealizadas, Nodo **tareasEnProceso, int id) {
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
    // Buscar en tareas en progresp
    aux = *tareasEnProceso;
    while (aux != NULL) {
        if (aux->T.TareaID == id) {
            return aux;
        }
        aux = aux->Siguiente;
    }

    // No se encontró la tarea
    return NULL;
}

Nodo *buscarTareaPorPalabra(Nodo **tareasPendientes, Nodo **tareasRealizadas, Nodo **tareasEnProceso, char *palabra) {
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
    aux = *tareasEnProceso;
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

void eliminarTarea(Nodo **tareasPendientes, Nodo **tareasEnProceso, Nodo **tareasRealizadas, int id) {
    Nodo *temp;
    Tarea *tareaAEliminar = NULL;

    // Buscar la tarea a eliminar en las tareas pendientes
    temp = *tareasPendientes;
    while (temp != NULL) {
        if (temp->T.TareaID == id) {
            tareaAEliminar = &temp->T;
            *tareasPendientes = eliminarNodo(tareasPendientes, temp);
            break;
        }
        temp = temp->Siguiente;
    }

    // Si la tarea no se encuentra en las tareas pendientes, buscar en las tareas en proceso
    if (tareaAEliminar == NULL) {
        temp = *tareasEnProceso;
        while (temp != NULL) {
            if (temp->T.TareaID == id) {
                tareaAEliminar = &temp->T;
                *tareasEnProceso = eliminarNodo(tareasEnProceso, temp);
                break;
            }
            temp = temp->Siguiente;
        }
    }

    // Si la tarea no se encuentra en las tareas en proceso, buscar en las tareas realizadas
    if (tareaAEliminar == NULL) {
        temp = *tareasRealizadas;
        while (temp != NULL) {
            if (temp->T.TareaID == id) {
                tareaAEliminar = &temp->T;
                *tareasRealizadas = eliminarNodo(tareasRealizadas, temp);
                break;
            }
            temp = temp->Siguiente;
        }
    }

    // Si se encontró la tarea, liberar la memoria asignada a la tarea
    if (tareaAEliminar != NULL) {
        free(tareaAEliminar->Descripcion);
        free(tareaAEliminar);
    }
}

Nodo *eliminarNodo(Nodo **inicio, Nodo *nodoAEliminar) {
    Nodo *temp = *inicio;

    // Si el nodo a eliminar es el primero
    if (temp == nodoAEliminar) {
        *inicio = temp->Siguiente;
        free(temp);
    }

    // Si el nodo a eliminar no es el primero
    while (temp->Siguiente != NULL && temp->Siguiente != nodoAEliminar) {
        temp = temp->Siguiente;
    }
    if (temp->Siguiente == NULL) {
        printf("El nodo a eliminar no se encuentra en la lista\n");
    }
    temp->Siguiente = temp->Siguiente->Siguiente;
    free(nodoAEliminar);
}

void mostrarDatos(Nodo *inicio) {
    int cantidadTareas = 0;
    int tiempoTotal = 0;
    Nodo *nodoActual = inicio;
    while (nodoActual != NULL) {
        cantidadTareas++;
        tiempoTotal += nodoActual->T.Duracion;
        nodoActual = nodoActual->Siguiente;
    }
    printf("Cantidad de tareas: %d\n", cantidadTareas);
    printf("Tiempo total: %d\n", tiempoTotal);
}
