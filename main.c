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

void upisiGraf(int **matrix, int n){
    printf("Upisi matricu susednosti red po red, -1 za granu koja ne postoji.\n");
    for(int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            scanf("%d", &matrix[i][j]);
            if (matrix[i][j] == -1){
                matrix[i][j] = INT_MAX;
            }
        }
    }

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
                printf("/ ");
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
    printf("Dodata grana tezine %d izmedju cvorova %d i %d.\n", weight, node1, node2);
}

void ukloniGranu(int **graph, int node1, int node2, int n){
    if (node1 < 0 || node2 < 0 || node1 >= n ||  node2 >= n){
        printf("Nekorektna grana.\n");
        return;
    }
    graph[node1][node2] = INT_MAX;
    graph[node2][node1] = INT_MAX;
}

void ukloniCvor(int **graph, int *n, int node) {
    if (node < 0 || node >= *n) {
        printf("Nekorektan cvor.\n");
        return;
    }

    for (int i = node; i < *n - 1; i++)
        graph[i] = graph[i + 1];

    for (int i = 0; i < *n; i++) {
        for (int j = node; j < *n - 1; j++) {
            graph[i][j] = graph[i][j + 1];
        }
    }

    (*n)--;
    printf("Cvor %d je uklonjen iz grafa.\n", node);
}

void path (int **matrix, int i, int j){
    if (i == j){
        printf("%d", i);
    }
    else{
        if (matrix[i][j] == -1){
            printf("Nema puta izmedju %d i %d\n", i, j);
        }
        else{
            path(matrix, i, matrix[i][j]);
            printf("%d ", j);
        }
    }
    putchar('\n');
}


void warshall(int **graph, int n, int start) {
    int **p = kreirajGraf(&n);
    int **t = kreirajGraf(&n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j] == INT_MAX) {
                p[i][j] = 0;
                t[i][j] = -1;
            } else if (i == j) {
                p[i][j] = 0;
                t[i][j] = -1;
            } else {
                p[i][j] = 1;
                t[i][j] = i;
            }
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (p[i][k] == 1){
                for (int j = 0; j < n; j++){
                    if (p[k][j] == 1 && p[i][j] != 1){
                        t[i][j] = t[k][j];
                    }
                    p[i][j] = p[i][j] || p[k][j];
                }
            }
        }
    }

    printf("Matrica dostiznosti:\n");
    ispisiGraf(p, n);
    putchar('\n');
    printf("Matrica traga:\n");
    ispisiGraf(t, n);
    putchar('\n');

    printf("Za cvor %d dostizni su sledeci cvorovi:\n", start);
    for (int i = 0; i < n; i++){
        if (p[start][i] == 1){
            printf("%d\n", i);
        }
    }
    putchar('\n');
    for (int i = 0; i < n; i++){
        if (p[start][i] == 1){
            printf("Putanja do cvora %d je\n", i);
            path(t, start, i);
        }
    }
    putchar('\n');

    izbrisiGraf(t, n);
    izbrisiGraf(p, n);
}

void centralnost(int** graph, int n){
    int curr;
    int arr[n];
    for (int i = 0; i < n; i++){
        curr = 0;
        for (int j = 0; j < n; j++){
            if(graph[i][j] != INT_MAX && i != j){
                curr++;
            }
        }
        arr[i] = curr;
    }

    for (int i = 0; i < n; i++){
        printf("Centralnost cvora %d po stepenu je  %d\n", i, arr[i]);
    }
}

float fragmentacijaCvorova(int **graph, int n) {
    int **p = kreirajGraf(&n);
    int ukupParova = 0;
    int currParova = 0;
    float res;

    ukupParova = (n * (n - 1)) / 2;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j] == INT_MAX) {
                p[i][j] = 0;
            } else if (i == j) {
                p[i][j] = 0;
            } else {
                p[i][j] = 1;
            }
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (p[i][k] == 1) {
                for (int j = 0; j < n; j++) {
                    if (p[k][j] == 1) {
                        p[i][j] = 1;
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i][j] == 1) {
                currParova += 1;
            }
        }
    }

    izbrisiGraf(p, n);
    res = (float)currParova / ukupParova;
    return res;
}

int main(){
    int **graph = NULL;
    int n = 0, node1, node2, weight, start;
    char opcija;

    do {
        printf("Meni: \n");
        printf("a - Kreiraj graf (matricu susednosti)\n");
        printf("b - Dodaj cvor\n");
        printf("c - Dodaj granu\n");
        printf("d - Ukloni granu\n");
        printf("f - Izbrisi cvor\n");
        printf("g - Ispisi graf\n");
        printf("h - Izbrisi graf\n");
        printf("i - Upisi graf sa standardnog ulaza\n");
        printf("j - Ispitaj centralnost u grafu\n");
        printf("k - Ispitaj dostiznost cvorova\n");
        printf("l - Ispitaj fragmentaciju grafa\n");
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
                break;
            case 'd':
                printf("Unesite cvorove na grani:\n");
                scanf("%d %d", &node1, &node2);
                ukloniGranu(graph, node1, node2, n);
                printf("Uklonjena grana izmedju cvorova %d i %d.\n", node1, node2);
                break;
            case 'f':
                printf("Unesi cvor za brisanje:\n");
                scanf("%d", &node1);
                ukloniCvor(graph, &n, node1);
                break;
            case 'g':
                ispisiGraf(graph, n);
                break;
            case 'h':
                izbrisiGraf(graph, n);
                break;
            case 'i':
                upisiGraf(graph, n);
                break;
            case 'j':
                centralnost(graph, n);
                break;
            case 'k':
                printf("Unesite cvor za koji ispitujete dostiznost.\n");
                scanf("%d", &start);
                warshall(graph, n, start);
                break;
            case 'e':
                printf("Izlaz\n");
                break;
            case 'l':
                printf("Koeficijent fragmentacije grafa iznosi %.2f\n", fragmentacijaCvorova(graph, n));
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
