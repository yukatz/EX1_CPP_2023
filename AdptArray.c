#include <string.h>
#include <stdlib.h>
#include "stdio.h"
#include "AdptArray.h"
typedef struct AdptArray_{
        PElement* arr;//Array of PElements
        int size;//Size of the addapted array
        COPY_FUNC cf;//Copy function of specific PElements
        DEL_FUNC df;//Delete function of specific PElements
        PRINT_FUNC pf;//Print function of specific PElements
        //Everey type of PElements (books or persons) have unic functions.
        //Non of this functions doesn't deal with NULL, so we have to deal with NULL.
}AdptArray;

PAdptArray CreateAdptArray(COPY_FUNC cf, DEL_FUNC df,PRINT_FUNC pf){
    PAdptArray adaptedArr = (PAdptArray)malloc(sizeof(AdptArray));//Memory allocation for new addapted array.
    adaptedArr->size = 0;
    adaptedArr->cf = cf;
    adaptedArr->df = df;
    adaptedArr->arr = NULL;
    adaptedArr->pf = pf;
    return adaptedArr;

};
void DeleteAdptArray(PAdptArray adaptedArr){
    if(adaptedArr==NULL) return;//if the structure doesn't exists, do nothing.
    for (int i = 0; i < adaptedArr->size; i++) {//delete (using the specific delete function) all the elements.
        if(adaptedArr->arr[i]!=NULL){        
            adaptedArr->df((adaptedArr->arr)[i]);
        }
        //If the cell is NULL, do nothing.
    }
    free(adaptedArr->arr);//free the array
    free(adaptedArr);//free all structure

};
Result SetAdptArrayAt(PAdptArray adaptedArr, int index, PElement pe){
    PElement* resArr;//new and resized array.
    //1. If given addapted array is empty, do nothing and return FAIL.
    if(adaptedArr==NULL) return FAIL;
    //2. If index grater then size of array
    if(index >= adaptedArr->size){
      if((resArr=(PElement*)calloc((index+1), sizeof(PElement)))==NULL) return FAIL;//aloocate (and check) memory for new resized array.
      for (int i = 0; i < adaptedArr->size; i++){//Create pointers to the elements from new resized array.
        resArr[i] = adaptedArr->arr[i];
      }
      free(adaptedArr->arr);//Free old array memory
      adaptedArr->arr = resArr;//Replace the old array with new resized one
      adaptedArr->size = index + 1;//Resize the the addapted array
    };
    //3. If in this index already exists another element - delete and replace or if NULL insert.
    if((adaptedArr->arr)[index]!= NULL){
     adaptedArr->df((adaptedArr->arr)[index]); //delete preveous object in index
    }
    (adaptedArr->arr)[index]=adaptedArr->cf(pe);//place an a copy of new object in given index
    return SUCCESS;
};

PElement GetAdptArrayAt(PAdptArray adaptedArr, int index){
    if(adaptedArr==NULL) return FAIL;//If the addapted array is NULL there is nothing to get.
    if(index>=adaptedArr->size)return FAIL;//If the index doesn't exists in the array.
    if(adaptedArr->arr[index]==NULL) return NULL; //If there is no element, return NULL
    return adaptedArr->cf(adaptedArr->arr[index]);//Return the copy of the element
};
int GetAdptArraySize(PAdptArray adaptedArr){
    if(adaptedArr==NULL){
        return -1;
    }
    return adaptedArr->size;
}
void PrintDB(PAdptArray adaptedArr){
    if(adaptedArr==NULL) return;//If addapted array is empty
    for (int i = 0; i < adaptedArr->size; i++) {
        if(adaptedArr->arr[i]!=NULL){//Do not use print function on NULL's
           adaptedArr->pf((adaptedArr->arr)[i]);
           }
        }
    };


