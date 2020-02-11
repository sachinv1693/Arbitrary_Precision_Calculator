#include "apc.h"

Status check_validity(char* argv[])
{
		data_t i = 0;//Iterator 'i'
		while (*(*argv + i) != '\0')//Iterate till the end of string
		{
				//If non-digit character is found, return FAILURE
				if (!isdigit(*(*argv + i++)))
						return FAILURE;
		}
		return SUCCESS;
}

