/**
 * crack.c
 *
 * CS50 hacker2
 *
 * To do: -comment
 *        -add bruteforce routine to run after dictionary attack
 */

#define _XOPEN_SOURCE
#include <unistd.h>
#define _GNU_SOURCE
#include <crypt.h>
#include <cs50.h>
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
        memcpy(salt, argv[1], 2);
        salt[2] = '\0';
        char word[100];
        char * hashed;
        FILE * wordList;

        wordList = fopen("/usr/share/dict/words", "r");
        //wordList = fopen("/home/jharvard/Downloads/rockyou.txt", "r");
        if (!wordList)
        {
            printf("word list not found\n");
            return 2;
        }
        while (fgets(word, 100, wordList) != NULL)
        {
            unsigned int length = strlen(word) - 1;
            if (word[length] == '\n')
            {
                word[length] = '\0';
            }
            hashed = crypt(word, salt);
            if (strcmp(hashed, argv[1]) == 0)
            {
                printf("%s\n", word);
                fclose(wordList);
                return 0;
            }
        }
        fclose(wordList);
        return 0;
    }
}
