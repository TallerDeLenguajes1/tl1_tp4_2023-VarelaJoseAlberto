#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tarea {
    int TareaID;  // Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion;  // entre 10 – 100
};
void inicializarTareas(struct Tarea **tareas, int cantTareas);
void ingresarTareas(struct Tarea **tareas, int cantTareas);
void mostrarTotal(struct Tarea **tareas, int cantTareas);
void mostrarPendientes(struct Tarea **tareas, int cantTareas);
void mostrarRealizadas(struct Tarea **tareas, int cantTareas);
void controlTareasRealizadas(struct Tarea **tareasPendientes, struct Tarea **tareasRealizadas, int cantTareas);
void buscarTareaID(struct Tarea **tareasPedientes, struct Tarea **tareasRelizadas, int cantTareas);

int main(int argc, char const *argv[]) {
    int cantTareas;
    printf("hola");
    struct Tarea **tareasPendientes;
    struct Tarea **tareasRealizadas;

    printf("Ingrese la cantidad de tareas a realizar: ");
    scanf("%d", &cantTareas);

    tareasPendientes = (struct Tarea **)malloc(sizeof(struct Tarea *) * cantTareas);
    tareasRealizadas = (struct Tarea **)malloc(sizeof(struct Tarea *) * cantTareas);

    inicializarTareas(tareasPendientes, cantTareas);
    inicializarTareas(tareasRealizadas, cantTareas);

    ingresarTareas(tareasPendientes, cantTareas);
    mostrarTotal(tareasPendientes, cantTareas);

    controlTareasRealizadas(tareasPendientes, tareasRealizadas, cantTareas);

    mostrarRealizadas(tareasRealizadas, cantTareas);
    mostrarPendientes(tareasPendientes, cantTareas);

    buscarTareaID(tareasPendientes, tareasRealizadas, cantTareas);

    return 0;
}

void inicializarTareas(struct Tarea **tareas, int cantTareas) {
    for (int i = 0; i < cantTareas; i++) {
        tareas[i] = NULL;
    }
}

void ingresarTareas(struct Tarea **tareas, int cantTareas) {
    char descripcion[20];
    int duracion;

    for (int i = 0; i < cantTareas; i++) {
        printf("ingrese la descripcion de la tarea %d: ", i + 1);
        fflush(stdin);
        gets(descripcion);

        do {
            printf("Ingrese la duracion entre 10 a 100 de la tarea %d: ", i + 1);
            fflush(stdin);
            scanf("%d", &duracion);
        } while (duracion < 10 || duracion > 100);

        tareas[i] = (struct Tarea *)malloc(sizeof(struct Tarea));
        tareas[i]->Descripcion = (char *)malloc(sizeof(char) * (strlen(descripcion) + 1));

        strcpy(tareas[i]->Descripcion, descripcion);

        tareas[i]->Duracion = duracion;
        tareas[i]->TareaID = i + 1;
    }
}

void mostrarTotal(struct Tarea **tareas, int cantTareas) {
    printf("---Tareas Total %d ---\n", cantTareas);
    for (int i = 0; i < cantTareas; i++) {
        if (tareas[i] != NULL) {
            printf("ID tarea realizada: %d\n", tareas[i]->TareaID);
            printf("Duracion de tarea realizada: %d\n", tareas[i]->Duracion);
            printf("Descripcion: %s\n", tareas[i]->Descripcion);
            printf("\n");
        }
    }
}

void mostrarRealizadas(struct Tarea **tareas, int cantTareas) {
    printf("---Tareas Realizada %d ---\n", cantTareas);
    for (int i = 0; i < cantTareas; i++) {
        if (tareas[i] != NULL) {
            printf("Id de la tarea: %d\n", tareas[i]->TareaID);
            printf("Duracion de la tarea: %d\n", tareas[i]->Duracion);
            printf("Descripcion de la tarea: %s\n", tareas[i]->Descripcion);
            printf("\n");
        }
    }
}

void mostrarPendientes(struct Tarea **tareas, int cantTareas) {
    printf("---Tareas Pendientes %d ---\n", cantTareas);
    for (int i = 0; i < cantTareas; i++) {
        if (tareas[i] != NULL) {
            printf("Id de la tarea: %d\n", tareas[i]->TareaID);
            printf("Duracion de la tarea: %d\n", tareas[i]->Duracion);
            printf("Descripcion de la tarea: %s\n", tareas[i]->Descripcion);
            printf("\n");
        }
    }
}

void controlTareasRealizadas(struct Tarea **tareasPendientes, struct Tarea **tareasRealizadas, int cantTareas) {
    printf("\nTareas cargadas:\n");
    char respuesta[2];
    for (int i = 0; i < cantTareas; i++) {
        printf("la tareas de id %d fue realizada\n", i + 1);
        printf("Ha completado esta tarea (s/n): ");
        fflush(stdin);
        scanf("%s", respuesta);

        if (respuesta[0] == 's' || respuesta[0] == 'S') {
            // Mover tarea a tareas realizadas
            tareasRealizadas[i] = tareasPendientes[i];
            // Imprimir mensaje de confirmación
            printf("\nLa tarea '%d' ha sido completada.\n", tareasPendientes[i]->TareaID);
            tareasPendientes[i] = NULL;
        }
    }
}

void buscarTareaID(struct Tarea **tareasPendientes, struct Tarea **tareasRealizadas, int cantTareas) {
    int id;
    printf("Ingrese el id de la tareas a buscar: ");
    fflush(stdin);
    scanf("%d", &id);

    for (int i = 0; i < cantTareas; i++) {
        if (tareasPendientes[i] != NULL) {
            if (id == tareasPendientes[i]->TareaID) {
                printf("---Tarea encontrada---\n");
                printf("Descripcion: %s\n", tareasPendientes[i]->Descripcion);
                printf("Duracion: %d\n", tareasPendientes[i]->Duracion);
                printf("Estado de la tarea encontrada: PENDIENTE\n");
            }
        }
        if (tareasRealizadas[i] != NULL) {
            if (id == tareasRealizadas[i]->TareaID) {
                printf("Tarea encontrada---\n");
                printf("Descripcion: %s\n", tareasRealizadas[i]->Descripcion);
                printf("Duracion: %d\n", tareasRealizadas[i]->Duracion);
                printf("Estado de la tarea encontrada: REALIZADA\n");
            }
        }
    }
}
