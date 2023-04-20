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
void mostrar(struct Tarea **tareas, int cantTareas);
void controlTareasRealizadas(struct Tarea **tareasPendientes, struct Tarea **tareasRealizadas, int cantTareas);
int main(int argc, char const *argv[]) {
    int cantTareas;
    struct Tarea **tareasPendientes;
    struct Tarea **tareasRealizadas;

    printf("Ingrese la cantidad de tareas a realizar: ");
    scanf("%d", &cantTareas);

    tareasPendientes = (struct Tarea **)malloc(sizeof(struct Tarea *) * cantTareas);
    tareasRealizadas = (struct Tarea **)malloc(sizeof(struct Tarea *) * cantTareas);

    inicializarTareas(tareasPendientes, cantTareas);
    inicializarTareas(tareasRealizadas, cantTareas);

    ingresarTareas(tareasPendientes, cantTareas);
    mostrar(tareasPendientes, cantTareas);
    controlTareasRealizadas(tareasPendientes, tareasRealizadas, cantTareas);
    printf("tareas realizadas\n");
    mostrar(tareasRealizadas, cantTareas);
    printf("tareas pendiente\n");
    mostrar(tareasPendientes, cantTareas);

    /*
        // Mostrar tareas y moverlas a tareas realizadas si se completan
        printf("\nTareas cargadas:\n");
        char respuesta[10];
        for (int i = 0; i < cantTareas; i++) {
            printf("%d. %s\n", i + 1, tareas[i]->Descripcion);

            // Preguntar si la tarea se ha completado
            printf("Ha completado esta tarea (s/n): ");
            scanf("%s", respuesta);

            if (respuesta[0] == 's' || respuesta[0] == 'S') {
                // Mover tarea a tareas realizadas
                tareas[i]->completada = 1;
                // Imprimir mensaje de confirmación
                printf("La tarea '%s' ha sido completada.\n", tareas[i]->Descripcion);
            }
            if (respuesta[0] == 'n' || respuesta[0] == 'N') {
                // Mover tarea a tareas realizadas
                tareas[i]->pendiente = 1;
                // Imprimir mensaje de confirmación
                printf("La tarea '%s' ha sido completada.\n", tareas[i]->Descripcion);
            }
        }

        // Mostrar tareas realizadas
        printf("\nTareas realizadas:\n");
        for (int i = 0; i < cantTareas; i++) {
            if (tareas[i]->completada) {
                printf("%d. %s\n", i + 1, tareas[i]->Descripcion);
            } else {
                printf("%d. %s\n", i + 1, tareas[i]->Descripcion);
            }
        }

        // for (int i = 0; i < cantTareas; i++) {
        //     printf("\nLa descripcion de la tarea %d es: %s", i + 1, tareas[i]->Descripcion);
        //     printf("\nLa duracion de la tarea %d es: %d", i, tareas[i]->Duracion);
        // }

        for (int i = 0; i < cantTareas; i++) {
            free(tareas[i]->Descripcion);
            free(tareas[i]);
        }
        free(tareas); */

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
        // scanf("%s", &descripcion);
        fflush(stdin);
        gets(descripcion);

        do {
            printf("ingrese la duracion entre 10 a 100 de la tarea %d: ", i + 1);
            fflush(stdin);
            scanf("%d", &duracion);
            // gets(duracion);
        } while (duracion < 10 || duracion > 100);

        tareas[i] = (struct Tarea *)malloc(sizeof(struct Tarea));
        tareas[i]->Descripcion = (char *)malloc(sizeof(char) * (strlen(descripcion) + 1));

        strcpy(tareas[i]->Descripcion, descripcion);

        tareas[i]->Duracion = duracion;
        tareas[i]->TareaID = +1;
    }
}

void mostrar(struct Tarea **tareas, int cantTareas) {
    for (int i = 0; i < cantTareas; i++) {
        if (tareas[i] != NULL) {
            printf("%d. %s\n", i + 1, tareas[i]->Descripcion);
        }
    }
}

void controlTareasRealizadas(struct Tarea **tareasPendientes, struct Tarea **tareasRealizadas, int cantTareas) {
    printf("\nTareas cargadas:\n");
    char respuesta[2];
    for (int i = 0; i < cantTareas; i++) {
        printf("la tareas %d fue realizada\n", i + 1);
        printf("Ha completado esta tarea (s/n): ");
        scanf("%s", respuesta);

        if (respuesta[0] == 's' || respuesta[0] == 'S') {
            // Mover tarea a tareas realizadas
            tareasRealizadas[i] = tareasPendientes[i];
            // Imprimir mensaje de confirmación
            printf("La tarea '%d' ha sido completada.\n", tareasPendientes[i]->TareaID);
            tareasPendientes[i] = NULL;
        } else if (respuesta[0] == 'n' || respuesta[0] == 'N') {
            // Mover tarea a tareas realizadas
            tareasPendientes[i] = tareasPendientes[i];
            // Imprimir mensaje de confirmación
            printf("La tarea '%d' no ha sido completada.\n", tareasPendientes[i]->TareaID);
        }
    }
}
