/**
 * crack.c
 *
 * CS50 hacker2
 *
 * To do:
 *        -add bruteforce routine to run after dictionary attack
 */

#define _XOPEN_SOURCE
#include <unistd.h>
#define _GNU_SOURCE
#include <crypt.h>
#include <string.h>
#include <stdio.h>


int main(int argc, char* argv[])
{   
    //input argument validation
    if (argc < 2)
    {
        printf("Too few arguments. Usage: crack [ciphertext]\n");
        return 1;
    }
    else if (argc > 2)
    {
        printf("Too many arguments. Usage: crack [ciphertext]\n");
        return 1;
    }
    else
    {
        char salt[3];
        // copy first 2 chars of the argument to salt array, avoid pointer folly
        memcpy(salt, argv[1], 2);
        // terminate with null char, makes a real string, avoid trailing garbage
        salt[2] = '\0';
        char word[100];
        char * hashed;
        // declare a file pointer
        FILE * wordList;

        // assign it to to a dictionary file on HDD using fopen()
        wordList = fopen("/usr/share/dict/words", "r");
        
        // rockyou wordlist finds works a lot better than dict/words
        // wordList = fopen("/home/jharvard/Downloads/rockyou.txt", "r");
        
        // Handle situation where the file is not found
        if (!wordList)
        {
            printf("word list not found\n");
            return 2;
        }
        
        // use fgets get string from file 1 line at a time while if no error (null)
        while (fgets(word, 100, wordList) != NULL)
        {
            // replace the newline char that fgets returns with null char
            unsigned int length = strlen(word) - 1;
            if (word[length] == '\n')
            {
                word[length] = '\0';
            }
            // assign the result of des algo on dict word and salt to variable
            hashed = crypt(word, salt);
            // compare that hashed result with the user supplied hash
            if (strcmp(hashed, argv[1]) == 0)
            {
                // if hashes match (strcmp returns 0), print the word from dict
                printf("%s\n", word);
                // close the file and exit the program
                fclose(wordList);
                return 0;
            }
        }
        // if nothing is found close the file and exit the program
        fclose(wordList);
        return 0;
    }
}
