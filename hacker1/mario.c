/**
 * Print mario pyramids
 * CS50 hacker1
 */
 
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
    // do-while to prompt at least once
    do
    {
        printf("Height: ");
        height = GetInt();
    }
    // keep re-prompting if user input is out of boounds
    while (height < 0 || height > 23);
    // set a counter to decrement the height for the inner loops
    int count = height;
    // the first for loop will create 'height' amount of lines
    for (int i = 0; i < height; i++)
    {
        // count-1: leave a space for our #'s
        for (int x = count - 1; x > 0; x--)
        {
            printf(" ");
        }
        for (int y = count - 1; y < height; y++)
        {
            printf("#");
        }
        // here is our gap between the two pyramids
        printf("  ");
        // mirror the left (initial) pyramid, no need for spaces after #'s
        for (int y = count - 1; y < height; y++)
        {
            printf("#");
        }
        printf("\n");
        count--;
    }
    return 0;
}
