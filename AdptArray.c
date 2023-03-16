#include <string.h>
#include <stdlib.h>
#include "stdio.h"
#include "AdptArray.h"
typedef struct AdptArray_{
        PElement* arr;
        int size;
        COPY_FUNC cf;
        DEL_FUNC df;
        PRINT_FUNC pf;


}AdptArray;

PAdptArray CreateAdptArray(COPY_FUNC cf, DEL_FUNC df,PRINT_FUNC pf){
    PAdptArray adaptedArr = (PAdptArray)malloc(sizeof(AdptArray));
    adaptedArr->size = 0;
    adaptedArr->cf = cf;
    adaptedArr->df = df;
    adaptedArr->arr = NULL;
    adaptedArr->pf = pf;

    return adaptedArr;

};
void DeleteAdptArray(PAdptArray adaptedArr){
    if(adaptedArr==NULL) return;//if the structure doesn't exists, do nothing.
    for (int i = 0; i < adaptedArr->size; i++) {//delete (using the specific delete function) all the objects.
        adaptedArr->df((adaptedArr->arr)[i]);
    }
    free(adaptedArr->arr);//free the array
    free(adaptedArr);//free all structure

};
Result SetAdptArrayAt(PAdptArray adaptedArr, int index, PElement pe){

    //1. If empty, do nothing.
    //2. If index grater then size of array
    //3. If in this index already exists another object - delete and replace.



};


PElement GetAdptArrayAt(PAdptArray adaptedArr, int index){
    return adaptedArr->arr[index];
};
int GetAdptArraySize(PAdptArray adaptedArr){
    return adaptedArr->size;//if empty, size=0.
};
void PrintDB(PAdptArray adaptedArr){
    if(adaptedArr==NULL) return;
    for (int i = 0; i < adaptedArr->size; i++) {
        adaptedArr->pf((adaptedArr->arr)[i]);
    }
};

