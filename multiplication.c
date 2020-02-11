#include "apc.h"

/*This function performs multiplication of 2 large numbers and stores the result in the resultant list*/

Status multiplication(Dlist* head1, Dlist* tail1, Dlist* head2, Dlist* tail2, Dlist** headR, Dlist** tailR)
{
		//Return FAILURE if any of the operands is not present
		if (tail1 == NULL && tail2 == NULL)
				return FAILURE;
		//Variables to store Operand 1, Operand 2 and Carry (Initialize to 0)
		data_t opnd1, opnd2, carry = 0;
		//Each product gets stored in a long int type variable
		long_data_t current_product = 0;
		//String to store result in each iteration
		char result[MAX_NODE_SIZE + NUL_CHAR_SIZE];
		//Product_add is a pointer for storing address of intermediate products
		//Product_extra helps bringing the product_add back to shifted position
		//temp_result is a pointer initialized to NULL to create initial nodes
		Dlist* product_add = NULL, *temp_result = NULL, *product_extra = NULL;
		//Loop till both operand nodes become NULL
		while (tail2)
		{
				//Convert opnd2 node data string into integer and store
				opnd2 = atoi(tail2 -> data);
				//Pointer to tail1 since we want to iterate over it again and again
				Dlist* tail1_ptr = tail1;
				//Debug messages in #if format
				while (tail1_ptr)
				{
						//Convert opnd1 node data string into integer and store
						opnd1 = atoi(tail1_ptr -> data);
						//Store the multiplication in a long_data_t variable
						current_product = (long_data_t) opnd1 * opnd2 + carry;
#if DEBUG_ON                   
						printf("opnd1 = %d\nopnd2 = %d\n", opnd1, opnd2);
						printf("current product = %ld\n", current_product);
#endif
						//Last 9 digits are stored as current result
						itoa((data_t)(current_product % 1000000000), result);
						//Append zeros if resultant node is less than MAX_NODE_SIZE
						append_zeros(result);
						if (temp_result == NULL)
						{
								//Inflate a new node
								insert_at_first(headR, tailR, result);
#if DEBUG_ON
								printf("current node result = %s\n",(*headR) -> data);
#endif
								//Product_extra keeps pointing to last node
								product_extra = *tailR;
						}
						else if (product_add)
						{
#if DEBUG_ON
								printf("Product add = %d\n", atoi(product_add -> data));
#endif
								//Add new result with intermediate product
								current_product += atoi(product_add -> data);
#if DEBUG_ON
								printf("current product after adding = %ld\n", current_product);
#endif
								itoa((data_t)(current_product % 1000000000), result);
								//Append zeros if resultant node is less than MAX_NODE_SIZE
								append_zeros(result);
								//Update intermediate result
								strcpy(product_add -> data, result);
#if DEBUG_ON
								printf("current node result = %s\n", product_add -> data);
#endif
								//Shift intermediate pointer to previous node
								product_add = product_add -> prev;
						}
						else
						{
								//Inflate a new node and store the current result. Code may reach here in the last multiplication term
								insert_at_first(headR, tailR, result);
						}
						//Chop off more than 9 digits and store as carry
						carry = (data_t) (current_product / 1000000000);
#if DEBUG_ON
						printf("carry = %d\n", carry);
#endif
						//Move the tail1 pointer
						tail1_ptr = tail1_ptr -> prev;
				}
				//Legal address to temp_result prevents inflating more nodes
				temp_result = *tailR;
				//Move intermediate product to second last current result node
				product_add = product_extra -> prev;
				//Move the product_extra pointer also to the same node
				product_extra = product_add;
				//If carry is non-zero, create extra node
				if (carry)
				{
						//Store carry into result string
						itoa(carry, result);
						//Append zeros if resultant node is less than MAX_NODE_SIZE and inflate new node
						append_zeros(result);
						insert_at_first(headR, tailR, result);
#if DEBUG_ON
						printf("Carry added = %s\n", (*headR) -> data);
#endif
						//Now the next carry term should be zero
						carry = 0;
				}
				//Move the tail2 pointer
				tail2 = tail2 -> prev;
		}
		return SUCCESS;
}

