#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int* Filllne(int begin,int size,int *massive){
    for(int i =0; i<size;i++){
        massive[i]=begin + i;
    }
    return massive;

}

int* FillDie(int begin,int size,int *massive){
    for(int i =0; i<size;i++){
        massive[i]=begin -i;
    }
    return massive;

}

int* FillRand(int size,int *massive){
    for(int i =0; i<size;i++){
        massive[i]=rand();
    }
    return massive;

}

int Runnumber(int size,int *massive){
    int MaxS=1;
    for(int i =0; i<size-1;i++){
        if((massive[i+1]) < (massive[i])){
            MaxS+=1;
        }


    }
    return MaxS;
}

int CheckSum(int size, int *massive){
    int summ=0;
    for(int i =0; i<size;i++){
        summ+=massive[i];
    }
    return summ;
}

void Printer(int *massive){
    for(int i =0;i<10;i++){
            printf("%d ",massive[i]);
            printf("\n");
        }
}
