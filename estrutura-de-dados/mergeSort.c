#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Merge Sort garante que os arrays que sobem na call stack estejam ordenados.
// Com isso, temos um tempo melhor de ordenação do que n^2
// O segredo esta na funcao que une os 2 vetores.

// Why Is Merge Sort O(n * log(n))? The Really Really Long Answer.
// https://www.youtube.com/watch?v=alJswNJ4P3U&ab_channel=BackToBackSWE


int vetor[] = {5,4,3,2,1,6,45,3,2,5,78,4,2,1,3,6,89,9,56};
int sizeOfVetor = sizeof(vetor) / sizeof(vetor[0]) -1;
int meio;

void merge() {

}

void mergeSort(int arr[], int inicio, int fim) {

    printf("%i\n", arr[fim]);
    printf("%i\n", fim);

    if (inicio < fim){
        meio = floor(fim - inicio / 2);
        mergeSort(arr, inicio, meio);
        mergeSort(arr, meio + 1, fim);
    } 
    
}



int main () {

    mergeSort(vetor, 0, sizeOfVetor);


    return 0;
}

