#include <stdio.h>
#include <stdlib.h>

int main () {

    int vetor[] = {5,4,3,2,1,6,45,3,2,5,78,4,2,1,3,6,89,9,56};
    int sizeOfVetor = sizeof(vetor) / sizeof(vetor[0]);
    int buffer;

    for(int i = 0; i < sizeOfVetor; i++) {
        for (int j = 0; j < sizeOfVetor - 1 - i; j++) {
            if (vetor[j] > vetor[j + 1]) {
                buffer = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = buffer;
            }
        }
    }


    for(int i = 0; i < sizeOfVetor; i ++) {
        printf("%i - ", vetor[i]);
    }

    return 0;
}