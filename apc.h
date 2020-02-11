#ifndef APC_H
#define APC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef int data_t;
typedef long int long_data_t;

//Macros
#define MAX_NODE_SIZE     9
#define DEBUG_ON          0
#define NUL_CHAR_SIZE     1
#define CARRY_SIZE        1
#define BORROW_SIZE       1

//Double Linked List structure
typedef struct node
{
		char data[MAX_NODE_SIZE + NUL_CHAR_SIZE + CARRY_SIZE];
		struct node* prev;//Pointer to previous node
		struct node* next;//Pointer to next node
}Dlist;

//Enum to identify return status of functions
typedef enum
{
		FAILURE,
		SUCCESS
}Status;

//Function prototypes
Status addition(Dlist* head1, Dlist* tail1, Dlist* head2, Dlist* tail2, Dlist** headR, Dlist** tailR);
Status subtraction(Dlist* head1, Dlist* tail1, Dlist* head2, Dlist* tail2, Dlist** headR, Dlist** tailR, data_t negative);
Status multiplication(Dlist* head1, Dlist* tail1, Dlist* head2, Dlist* tail2, Dlist** headR, Dlist** tailR);
Status division(Dlist* head1, Dlist* tail1, Dlist* head2, Dlist* tail2, Dlist** headR, Dlist** tailR);
Status modulo(Dlist* head1, Dlist* tail1, Dlist* head2, Dlist* tail2, Dlist** headR, Dlist** tailR);
Status insert_at_first(Dlist** head, Dlist** tail, const char a[]);
Status insert_at_last(Dlist** head, Dlist** tail, const char a[]);
Status check_validity(char* argv[]);
char* itoa(data_t n, char* s);
char* append_zeros(char* result);
data_t tens(data_t power);
void adjust_zeros(Dlist** tail, Dlist** headR, Dlist** tailR, data_t* opnd_len);

#endif
