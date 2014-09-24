/**
 * Validate credit card numbers with the Luhn algorithm.
 *
 * CS50 hacker1
 *    
 */

#include <stdio.h>
#include <cs50.h>
#include <string.h>

// Prototype for luhnCheck function
int luhnCheck(char * number, int numberLength);

int main(void)
{
    char charArray[16];
    printf("Number: ");
    // get long long from user, int will not set aside enough memory
    long long int usersNumber = GetLongLong();
    // convert user supplied number to a string (array of char's)
    sprintf(charArray, "%lld", usersNumber);
    // get length of string
    int numberOfDigits = strlen(charArray);
    
    if ((numberOfDigits == 13 || numberOfDigits == 16) && charArray[0] == '4')
    {
        // if luhnCheck is true (returns 1)
        if (luhnCheck(charArray, numberOfDigits))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (numberOfDigits == 16 && charArray[0] == '5' && (charArray[1] > '0' && charArray[1] < '6'))
    {
        if (luhnCheck(charArray, numberOfDigits))
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (numberOfDigits == 15 && (charArray[0] == '3' && (charArray[1] == '4' || charArray[1] == '7')))
    {
        if (luhnCheck(charArray, numberOfDigits))
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        // fail early if possible to avoid running luhnCheck unless necessary
        printf("INVALID\n");
    }

    return 0;
}

/**
 *  function for the luhncheck algorithm.
 *  returns 1 if number passes validation
 *  or 0 if it fails.
 */
int luhnCheck(char * number, int numberLength)
{
    int sumOdds = 0;
    int sumEvens = 0;
    int offsetOdds;
    int offsetEvens;
    // choose correct offset for array iteration if CC# is even
    if ((numberLength % 2) == 0)
    {
        offsetOdds = 1;
        offsetEvens = 0;   
    }
    else
    {
        offsetOdds = 0;
        offsetEvens = 1;
    }
    for (int i = offsetOdds; i < numberLength; i += 2)
    {
        // sum of all digits not doubled convert ascii code for number to int value (-48)
        sumOdds = sumOdds + (number[i] - 48);
    }
    int firstDigit;
    int secondDigit;
    // loop through every other digit starting from second to last digit
    for (int i = offsetEvens; i < numberLength; i += 2)
    {
        // if product of doubling is a double digit
        if (((number[i] - 48) * 2) > 9)
        {
            // find first digit from the right
            secondDigit = ((number[i] - 48) * 2) % 10;
            // and consecutive digit(s)
            firstDigit = (((number[i] - 48) * 2) / 10) % 10;
            // sum the results
            sumEvens = sumEvens + firstDigit + secondDigit;
        }
        else
        {
            // sum of all doubled digits
            sumEvens = sumEvens + ((number[i] - 48) * 2);
        }
    }
    // check that last digit of summed digits is 0
    if (((sumOdds + sumEvens) % 10) == 0)
    {
        // number passes validation
        return 1;
    }
    else
    {
        // fail
        return 0;
    }
}
