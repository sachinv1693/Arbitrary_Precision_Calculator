#include "apc.h"

Status insert_at_last(Dlist** head, Dlist** tail, const char a[])
{
		//Create a new node
		Dlist* new = malloc(sizeof(Dlist));
		//Check if node is created or not
		if (new == NULL)
		{
				printf("Error: Unable to allocate dynamic memory!\n\n");
				return FAILURE;
		}
		//Update the link
		new -> next = NULL;
		strncpy(new -> data, a, 9);
		new -> data[9] = '\0';
		//Check whether the list is empty
		if (*tail == NULL)
		{
				//Update head and tail
				*tail = new;
				*head = new;
				//Update backward link of new node
				new -> prev = NULL;
				return SUCCESS;
		}
		//Establish a link between tail node + new node and update the tail
		(*tail) -> next = new;
		new -> prev = *tail;
		*tail = new;
		return SUCCESS;
}

