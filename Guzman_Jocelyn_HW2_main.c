/**************************************************************
* Class:  CSC-415-0# Summer 2021
* Name: Jocelyn Guzmam
* Student ID:915040482
* GitHub UserID:jguzman95
* Project: Assignment 2 – Stucture in Memory and Buffering
*
* File: Guzman_Jocelyn_HW2_main.c
*
* Description:
*
**************************************************************/

#include "assignment2.h"


#include <stdlib.h>
#include "string.h"
#include <stdio.h>


void addToBuffer(char *buffer, const char *string, int *index){

    //strlen for null terminated c strings
    int length = strlen(string);

    //getting the size of current buffer to compare to
    int toCopy;

    //loop to keep buffering through the string
    //until null
    while(length > 0){

        //where are we on buffer
        if(length <= (BLOCK_SIZE - *index)){
            toCopy = length;
        }else{
            toCopy = BLOCK_SIZE - *index;
        }
        //update how much left from string to copy
        length = length - toCopy;

        //copy to buffer
        memcpy(buffer + *index, string, toCopy);

        //keeping count of how much in buffer
        *index = *index + toCopy;

        //buffer full
        if(*index == BLOCK_SIZE){

            //committing to buffer
            commitBlock(buffer);

            //buffer empty again reset
            *index = 0;
        }

        //printf("\n in addtobuffer: %s \n", buffer);
        //printf("in addto:  %lu\n", strlen(buffer) );
    }
    //printf("\n in addtocommit: %d \n", *index);
}

int main(int argc, char  **argv){

    //initializing struct to then allocate it
    struct  personalInfo *info;

    //allocating a buffer to block size
    char *buffer = malloc(BLOCK_SIZE);

    //string to be buffered
    const char *string;

    //index of buffer
    int index = 0;


    //allocating for personalInfo
    info = (struct personalInfo*) malloc(sizeof(struct personalInfo));

        //storing info for struct
        info->firstName = argv[1];
        info->lastName = argv[2];
        info->studentID = 915040482;
        info->level = JUNIOR;
        info->languages = KNOWLEDGE_OF_C + KNOWLEDGE_OF_JAVA/2 + KNOWLEDGE_OF_PYTHON/8+
                KNOWLEDGE_OF_CPLUSPLUS/16 + KNOWLEDGE_OF_HTML/2048 + KNOWLEDGE_OF_MIPS_ASSEMBLER/262144;
    //printf("\n in languages: %d \n", info->languages);

    //printf("%d",info->languages);

    //copying the contents of command line argument 3 to struct
    strncpy(info->message, argv[3], 100);

    //writing  the info for struct
    int check = writePersonalInfo(info);
    int value;

    //return value of succession
    if(check != 0) {
        perror("error");
    }

    //printf("\nThe Check Succeeded (%d)\n", check);
    while((string = getNext()) != NULL){
        //copying contents of returned strig into buffer
        addToBuffer(buffer, string, &index);
    }

    // if null still need to commit
    // check if buffer is empty of not empty then comit
    if(index > 0){
        char *temp = malloc(index+1);
        strncpy(temp, buffer, index);
        commitBlock(temp);

        //printf("in index: %lu\n", strlen(temp));
        free(temp);
        temp = NULL;
    }

    // freeing the struct
    free(info);
    //setting info struct to null
    info = NULL;
    // freeing the buffer
    free(buffer);
    //setting buffer to null
    buffer = NULL;

    //exiting with the return value from checkit()
    value = checkIt();

    return value;
}