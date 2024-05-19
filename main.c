#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

int** kreirajGraf(int *n){
    int** matrix;
    matrix = calloc(*n, sizeof(int*));
    for (int i = 0; i < *n; i++){
        matrix[i] = calloc(*n, sizeof(int));
    }

    for (int i = 0; i < *n; i++){
        for (int j = 0; j < *n; j++){
            matrix[i][j] = INT_MAX;
        }
    }

    return matrix;
}

int** dodajCvor(int** graph, int *n){
    (*n)++;
    int lastpos = (*n) - 1;

    graph = (int**)realloc(graph, (*n) * sizeof(int*));
    graph[lastpos] = (int*)calloc(*n, sizeof(int));

    for (int i = 0; i < lastpos; i++){
        graph[i] = (int*)realloc(graph[i], (*n) * sizeof(int));
        graph[i][lastpos] = INT_MAX;
    }

    printf("Dodat je novi cvor sa ID-jem %d\n", lastpos);
    return graph;
}

void ispisiGraf(int **graph, int n){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (graph[i][j] == INT_MAX){
                printf("inf ");
            }
            else{
                printf("%d ", graph[i][j]);
            }
        }
        putchar('\n');
    }
}

void izbrisiGraf(int **graph, int n) {
    for (int i = 0; i < n; i++) {
        free(graph[i]);
    }
    free(graph);
}

void dodajGranu(int **graph, int weight, int node1, int node2, int n){
    if (node1 < 0 || node2 < 0 || node1 >= n ||  node2 >= n){
        printf("Nekorektna grana.\n");
        return;
    }
    graph[node1][node2] = weight;
    graph[node2][node1] = weight;
}

void ukloniGranu(int **graph,int node1, int node2, int n){
    if (node1 < 0 || node2 < 0 || node1 >= n ||  node2 >= n){
        printf("Nekorektna grana.\n");
        return;
    }
    graph[node1][node2] = INT_MAX;
    graph[node2][node1] = INT_MAX;
}

int main(){
    int **graph = NULL;
    int n = 0, node1, node2, weight;
    char opcija;

    do {
        printf("Meni: \n");
        printf("a - Kreiraj graf (matricu susednosti)\n");
        printf("b - Dodaj cvor\n");
        printf("c - Dodaj granu\n");
        printf("d - Ukloni granu\n");
        printf("f - Ispisi graf\n");
        printf("g - Izbrisi graf\n");
        printf("e - Izlaz\n");
        scanf(" %c", &opcija);

        switch (opcija) {
            case 'a':
                printf("Unesite broj cvorova: \n");
                scanf(" %d", &n);
                graph = kreirajGraf(&n);
                break;
            case 'b':
                graph = dodajCvor(graph, &n);
                break;
            case 'c':
                printf("Unesite cvorove:\n");
                scanf("%d %d", &node1, &node2);
                printf("Unesite tezinu:\n");
                scanf("%d", &weight);
                dodajGranu(graph, weight, node1, node2, n);
                printf("Dodata grana tezine %d izmedju cvorova %d i %d.\n", weight, node1, node2);
                break;
            case 'd':
                printf("Unesite cvorove na grani:\n");
                scanf("%d %d", &node1, &node2);
                ukloniGranu(graph, node1, node2, n);
                printf("Uklonjena grana izmedju cvorova %d i %d.\n", node1, node2);
                break;
            case 'f':
                ispisiGraf(graph, n);
                break;
            case 'g':
                izbrisiGraf(graph, n);
                break;
            case 'e':
                printf("Izlaz\n");
                break;

            default:
                printf("Nepoznata opcija\n");
        }
    } while (opcija != 'e');

    if (graph) {
        izbrisiGraf(graph, n);
    }

    return 0;
}
