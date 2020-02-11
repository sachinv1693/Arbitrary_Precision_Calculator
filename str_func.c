#include "apc.h"

char* itoa(data_t n, char* s)
{
        //Set no. of digits as 0 and copy the iteger data_to another number x
        data_t no_of_digits = 0, x = n;
        //calculate no. of digits
        while (x != 0)
        {   
                no_of_digits++;
                //keep dividing the number till it is not 0
                x /= 10; 
        }   
        //After coming out of the loop, x = 0, let's use the same to iterate.
        //Till no. of bits is not 0, calculate 10s place of the number, divide it by its proper 10s value and again find the unit's place value. Finally add 48 to convert numeric digit data_to char value.
        while (no_of_digits != 0)
        {
                no_of_digits--;
                s[x++] = ((n / tens(no_of_digits)) % 10) + 48 ;
        }
        //Append last character as NUL character
        s[x] = '\0';
        return s;
}

data_t tens(data_t power)
{
        return (power) ? (10 * tens(power - 1)) : 1;
}

char* append_zeros(char* result)
{
        data_t result_len = strlen(result);
        if (result_len < MAX_NODE_SIZE)
        {
                data_t i;//Iterator 'i'
                //An answer string to store copy of result string
                char answer[MAX_NODE_SIZE + NUL_CHAR_SIZE];
                //Now store result string into answer string
                strcpy(answer, result);
                //Append MAX_NODE_SIZE - result_len zeros
                for (i = 0; i < MAX_NODE_SIZE - result_len; i++)
                {
                        result[i] = '0';
                }
                result[i] = '\0';
                //Append back the answer string to result string
                strcat(result, answer);
        }
        return result;
}

