#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NO_OF_FILES 10 // max number of file in the SD - get this from the no of files from SD card
#define FILENAME_LENGTH 20 // file name length including '.mp3' extension


char* music_list[MAX_NO_OF_FILES];


/**
 * @brief allocate memory for count number of items 
 * @param count number of items to allocate memory for 
*/
char* allocateMemory(){
        char* memAdress = (char*) malloc(FILENAME_LENGTH);

        return memAdress;    
}

int main () {

    // add items to array 
    music_list[0] = allocateMemory();


    strcpy(music_list[0], "Name1");

    printf("%s \n", music_list[0]);

    return 0;

}