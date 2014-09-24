/**
 * initials.c
 * 
 * turn user supplied string to initials using
 * strtok() and toupper()
 *
 * CS50 hacker2
 */
 
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

int main(void)
{
    string name = GetString();
    // get length for size to initialize amalgam array
    int length = strlen(name);
    char delimiter[] = " ";
    char * extracted = NULL;
    string amalgam[length];
    extracted = strtok(name, delimiter);
    
    // iterate tokens into array amalgam
    int index = 0;
    while(extracted != NULL)
    {   
        amalgam[index] = extracted;
        index++;  
        extracted = strtok(NULL, delimiter);
    }
    
    // print first char of each token
    for (int i = 0; i < index; i++)
    {
        // make char uppercase with toupper()
        printf("%c", toupper(amalgam[i][0]));
    }
    printf("\n");
    
    return 0;
}
