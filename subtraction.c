#include "apc.h"

/*This function performs subtraction of 2 large numbers and stores the result in the resultant list*/

Status subtraction(Dlist* head1, Dlist* tail1, Dlist* head2, Dlist* tail2, Dlist** headR, Dlist** tailR, data_t negative)
{
		//Check if both opearnd addresses are valid
		if (head1 == NULL && tail1 == NULL)
				return FAILURE;
		//Result string
		char result[MAX_NODE_SIZE + NUL_CHAR_SIZE + BORROW_SIZE];
		//Variables to store operands and borrow
		data_t opnd1, opnd2, borrow = 0;
		while (tail1 || tail2)//Iterate till both tails reach at NULL
		{
                //If tail value is NULL, store oprand value as 0
                //Else convert node data string into integer and store
				opnd1 = (tail1) ? atoi(tail1 -> data) : 0;
				opnd2 = (tail2) ? atoi(tail2 -> data) : 0;
				if (negative)//Perform opnd2 - opnd1
				{
						//opnd2 reaches at head node, append '-' sign
						//Use itoa() to store every string
						if (tail2 == head2)
						{
								result[0] = '-';
								itoa(opnd2 - borrow - opnd1, result + 1);
						}
						else if ((opnd2 - borrow) < opnd1)
						{
								opnd2 += 1000000000;//Borrow extra decade
								itoa(opnd2 - borrow - opnd1, result);
								borrow = 1;//Create borrow for next iteration
						}
						else
						{
								itoa(opnd2 - borrow - opnd1, result);
								borrow = 0;//No borrow in next iteration
						}

				}
				else
				{//Perform opnd1 - opnd2
						if ((opnd1 - borrow) < opnd2)
						{
								opnd1 += 1000000000;//Borrow extra decade
								itoa(opnd1 - borrow - opnd2, result);
								borrow = 1;//Borrow for next iteration
						}
						else
						{
								itoa(opnd1 - borrow - opnd2, result);
								borrow = 0;//No borrow for next iteration
						}
				}
				//Store the result string length in a variable
				data_t result_len = strlen(result);
				//Append zeros if resultant node is less than MAX_NODE_SIZE
				if ((result[0] != '-') && (result_len < MAX_NODE_SIZE))
				{
						append_zeros(result);
				}
				//Insert result string into result node
				insert_at_first(headR, tailR, result);
				//Iterate pointers
				if (tail1)
						tail1 = tail1 -> prev;
				if (tail2)
						tail2 = tail2 -> prev;
		}
		return SUCCESS;
}

