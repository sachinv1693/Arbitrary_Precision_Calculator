#include "apc.h"

/*This function performs addition of 2 large numbers and stores the result in the resultant list*/

Status addition(Dlist* head1, Dlist* tail1, Dlist* head2, Dlist* tail2, Dlist** headR, Dlist** tailR)
{
		if (tail1 == NULL && tail2 == NULL)//Check if both tails are NULL
				return FAILURE;//Cannot proceed
		//Variables to store Operand 1, Operand 2 & Carry
		data_t opnd1, opnd2, carry = 0;//Initialize carry with 0
		//Result string
		char result[MAX_NODE_SIZE + NUL_CHAR_SIZE + CARRY_SIZE];
		//Loop till both the operand nodes become NULL
		while (tail1 || tail2)
		{
				//If tail value is NULL, store oprand value as 0
				//Else convert node data string into integer and store
				opnd1 = (tail1) ? atoi(tail1 -> data) : 0;
				opnd2 = (tail2) ? atoi(tail2 -> data) : 0;
				//Store the addition with carry into result string
				itoa(opnd1 + opnd2 + carry, result);
				//Store result string's length for further use
				data_t result_len = strlen(result);
				//Check if carry is generated
				if (result_len == MAX_NODE_SIZE + CARRY_SIZE)
				{
						//Check if both are not last nodes. Since carry is generated only when both operands have non-zero digits, both tails must be having a valid address, so (tail -> prev) won't result into a segmentation fault.
						if (tail1 -> prev || tail2 -> prev)
						{
								//Store 1st byte of result string
								char to_int = result[0];
								//Convert it to integer and store as carry
								carry = atoi((const char*)&to_int);
								//Advance string address by 1 byte
								strcpy(result, result + 1);
						}
						//If both are last nodes then, no need to propogate carry, rather we include it in our result.
				}
				//Now result length must be lesser
				else
				{
						append_zeros(result);
						carry = 0;//No carry is generated
				}
				//Append from start of result link list
				insert_at_first(headR, tailR, result);
				//Check if pointers are not holding NULL address and move them
				if (tail1)
						tail1 = tail1 -> prev;
				if (tail2)
						tail2 = tail2 -> prev;
		}
		return SUCCESS;
}

