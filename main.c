#include "apc.h"

/*Function prototypes*/
//Function to print values
void print_list(Dlist* head);
void non_zero_head(Dlist** head, data_t* opnd_len);
//Function to know if operand2 value is greater than operand1 value
data_t negative_result(Dlist* head1, Dlist* head2, data_t opnd1_len, data_t opnd2_len);

/*Main driver function to invoke all the functions*/

int main(int argc, char* argv[])
{
		if (argc != 4)//Validate no. of command line arguments
		{
				printf("\nERROR: Please pass exactly 3 arguments. ({Operand1} {operator} {Operand2}).\nFor multiplication, make sure you provide '\\*' and not just '*'.\n\n");
				exit(SUCCESS);
		}
		//Validate operands
		if (!check_validity(argv + 1) || !check_validity(argv + 3))
		{
				printf("\nERROR: Invalid operand provided!! Operands should contain only digits (0-9).\n\n");
				exit(SUCCESS);
		}
		//Validate operators
		if (strlen(argv[2]) != 1)
		{
				printf("\nERROR: Invalid operator!\n\n");
				exit(SUCCESS);
		}
		/*Pointer Declarations*/
		Dlist* head1, *tail1, *head2, *tail2, *headR, *tailR;
		//Initialize all of them to NULL
		head1 = tail1 = head2 = tail2 = headR = tailR = NULL;
		/*we shall extract operand-1 string's head node string size */
		data_t opr_head1_size = strlen(argv[1]) % MAX_NODE_SIZE;
		//Here we need to add extra node based on truthness of head size
		data_t opnd1_len = (strlen(argv[1]) / MAX_NODE_SIZE) + !!opr_head1_size;
		/*we shall extract operand-2 string's head node string size */
		data_t opr_head2_size = strlen(argv[3]) % MAX_NODE_SIZE;
		//Here we need to add extra node based on truthness of head size
		data_t opnd2_len = (strlen(argv[3]) / MAX_NODE_SIZE) + !!opr_head2_size;
		//A string to extract head-1 node data
		char ext_arr1[opr_head1_size + NUL_CHAR_SIZE];
		//Fill up head1 node data
		strncpy(ext_arr1, argv[1], opr_head1_size);
		ext_arr1[opr_head1_size] = '\0';//Append NUL character in the end
		if (opr_head1_size)//If head-1 size is non-zero then make 1st node
				insert_at_first(&head1, &tail1, ext_arr1);
		argv[1] += opr_head1_size;//Move argv[1] address by head size
		//Fill up remaining nodes from tail end
		//Here we need to subtract 1 count based on truthness of head size
		for (data_t i = 0; i < opnd1_len - !!opr_head1_size; i++)
		{
				insert_at_last(&head1, &tail1, argv[1]);
				argv[1] += MAX_NODE_SIZE;
		}	
		//A string to extract head-2 node data
		char ext_arr2[opr_head2_size + NUL_CHAR_SIZE];
		//Fill up head2 node data
		strncpy(ext_arr2, argv[3], opr_head2_size);
		ext_arr2[opr_head2_size] = '\0';//Append NUL character in the end
		if (opr_head2_size)//If head-2 size is non-zero then make 1st node
				insert_at_first(&head2, &tail2, ext_arr2);
		argv[3] += opr_head2_size;//Move argv[3] address by head size
		//Fill up remaining nodes from tail end
		//Here we need to subtract 1 count based on truthness of head size
		for (data_t i = 0; i < opnd2_len - !!opr_head2_size; i++)
		{
				insert_at_last(&head2, &tail2, argv[3]);
				argv[3] += MAX_NODE_SIZE;
		}	
		/*Store the Math operator*/
		char operator = argv[2][0];
		non_zero_head(&head1, &opnd1_len);
		non_zero_head(&head2, &opnd2_len);
#if DEBUG_ON
		//Print all stages for debugging
		printf("head1 size = %d\n", opr_head1_size);
		printf("head2 size = %d\n", opr_head2_size);
		printf("No. of opnd1 nodes = %d\n", opnd1_len);
		printf("No. of opnd2 nodes = %d\n", opnd2_len);
		printf("head1 data = %s\n", head1 -> data);
		printf("Operator = %c\n", operator);
		printf("head2 data = %s\n", head2 -> data);
		Dlist* temp = head1;
		printf("Link list 1: ");
		print_list(head1);
		temp = head2;
		printf("Link list 2: ");
		print_list(head2);
#endif
		//A flag to indicate negative result
		data_t negative = negative_result(head1, head2, opnd1_len, opnd2_len);
		//Check which operation is demanded
		switch (operator)
		{
				case '+'://Addition
						addition(head1, tail1, head2, tail2, &headR, &tailR);
						break;
				case '-'://Subtraction
						subtraction(head1, tail1, head2, tail2, &headR, &tailR, negative);
						break;
				case '*'://Multiplication
						multiplication(head1, tail1, head2, tail2, &headR, &tailR);
						break;
				case '/'://Division
						break;
				case '%'://Modulo
						break;
				default://Invalid operator
						printf("\nERROR: Invalid operator provided!\n\n");
		}
		//Consider no. of result nodes as product of opnd1 and opnd2 nodes
		data_t headR_len = opnd1_len * opnd2_len;
		//If result list head is non-NULL then, remove its zero data nodes
		if (headR)
				non_zero_head(&headR, &headR_len);
		//Printing the result
		printf("\nResult: ");
		print_list(headR);
		return 0;
}

void print_list(Dlist* head)
{
		//Check if head is NULL
		if (head == NULL)
		{
				printf("Result not obtained\n");
				return;
		}
		//In case negative answer, print string else print integer form
		if (head -> data[0] == '-')
		{
				printf("%s", head -> data);
		}
		else
				printf("%d", atoi(head -> data));
		head = head -> next;
#if DEBUG_ON
		//Printing arrow notation while debugging
		if (head)
				printf("->");
#endif
		while (head)
		{
				printf("%s", head -> data);
				head = head -> next;
#if DEBUG_ON
		//Printing arrow notation while debugging
		if (head)
				printf("->");
#endif
		}
		//Move to next line
		printf("\n\n");

}

/*Function to determine if opnd2 is greater than opnd1. This is useful in peerforming subtraction*/
data_t negative_result(Dlist* head1, Dlist* head2, data_t opnd1_len, data_t opnd2_len)
{
		//If both operands have same node length, then keep tracing till end
		if (opnd1_len == opnd2_len)
		{
				while (head1 || head2)//Iterate till getting NULL address
				{
						//Compare integer value of operands at every node
						if (atoi(head1 -> data) > atoi(head2 -> data))
								return 0;
						else if (atoi(head1 -> data) < atoi(head2 -> data))
								return 1;
						else
						{//Move both heads
								head1 = head1 -> next;
								head2 = head2 -> next;
						}
				}
				return 0;
		}
		//Operand with higher length is greater
		else 
				return (opnd2_len > opnd1_len);
}

//Function to move the head to a non-zero value
void non_zero_head(Dlist** head, data_t* opnd_len)
{
		while ((*head) -> next)//Iterate till last node
		{
				//Check if head node data is zero
				if (atoi((*head) -> data) == 0)
				{
						//Reduce the opnd length
						--(*opnd_len);
						//Move head to next node
						*head = (*head) -> next;
				}
				else
						break;
		}
}

