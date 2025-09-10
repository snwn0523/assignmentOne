#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 26

int parent[MAX];
int child[MAX][MAX];
int childCount[MAX];
int used[MAX];
int visited[MAX];

int cycle(int node){
    if (visited[node] == 1){
        return 1;
    }
    if (visited[node] == 2){
        return 0;
    }

    visited[node] = 1;
    for (int i = 0; i < childCount[node]; i++){
        int c = child[node][i];
        if (cycle(c)){
            return 1;
        }
    }
    visited[node] = 2;
    
    return 0;
}

void sorting(int arr[], int n){
    for (int i = 0; i < (n - 1); i++){
        for (int j = (i + 1); j < n; j++){
            if (arr[i] > arr[j]){
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void printing(int node[], int n){
    if (n == 0){
        return;
    }
    for (int i = 0; i < n; i++){
        int p = node[i];
        if (childCount[p] == 0){
            printf("#");
        }
        else{
            for (int j = 0; j < childCount[p]; j++){
                printf("%c", 'A' + child[p][j]);
            }
        }
        if (i != (n - 1)){
            printf(" ");
        }
    }
    printf("\n");

    int next[MAX];
    int count = 0;

    for(int i = 0; i < n; i++){
        int p = node[i];
        for (int j = 0; j < childCount[p]; j++){
            next[count++] = child[p][j];
        }
    }
    if (count > 0){
        printing(next, count);
    }
}

int main(int argc, char **argv){
    if (argc != 2){
        return EXIT_FAILURE;
    }

    FILE * fptr = fopen(argv[1], "r");
    if (fptr == NULL){
        return EXIT_FAILURE;
    }

    for (int i = 0; i < MAX; i++){
        parent[i] = -1;
        childCount[i] = 0;
        used[i] = 0;
    }

    char line[100];
    while (fgets(line, sizeof(line), fptr)){
        int len = strlen(line);
        if (len > 0 && line[len - 1] == '\n'){
            line[len - 1] = '\0';
        }
        
        int p = line[0] - 'A';
        int c = line[1] - 'A';
        used[p] = used[c] = 1;

        if (parent[c] != -1 && parent[c] != p){
            printf("INVALID\n");
            fclose(fptr);
            return 0;
        }
        parent[c] = p;

        int duplicate = 0;
        for (int i = 0; i < childCount[p]; i++){
            if (child[p][i] == c){
                duplicate = 1;
                break;
            }
        }
        if (!duplicate){
            child[p][childCount[p]++] = c;
        }
    }
    fclose(fptr);

    for (int i = 0; i < MAX; i++){
        if (childCount[i] > 1){
            sorting(child[i], childCount[i]);
        }
    }

    for (int i = 0; i < MAX; i++){
        if (used[i] && visited[i] == 0){
            if (cycle(i)){
                printf("INVALID\n");
                return 0;
            }
        }
    }

    int root[MAX];
    int rootCount = 0;
    for (int i = 0; i < MAX; i++){
        if (used[i] && parent[i] == -1){
            root[rootCount++] = i;
        }
    }
    if (rootCount == 0){
        printf("INVALID\n");
        return 0;
    }

    sorting(root, rootCount);

    for (int i = 0; i < rootCount; i++){
        printf("%c\n", 'A' + root[i]);
        int arr[1] = { root[i] };
        printing(arr, 1);
        if (i != (rootCount - 1)){
            printf("\n");
        }
    }
    printf("\n");

    return 0;
}