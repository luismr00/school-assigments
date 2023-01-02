#include <stdio.h>
#include <stdlib.h>

/* Define structures and global variables*/

/* number of processess */
int n;

/* linked list of pcb's or node for child processes */
struct node1 {
	int process;
	struct node1 *link;
}; 

typedef struct node1 linked_list_type;

/* pcb structure */
struct node2 {
	int parent;
	linked_list_type *children;
} *pcb = NULL;

typedef struct node2 pcb_type;

/***************************************************************/
void printList() {
	/* declare local vars */
	linked_list_type *next;

	/* for each PCB index i from 0 up to (but not including) maximum number*/	
  	for (int i = 0; i < n; i++) {
		/* check if PCB[i] has a parent and children */
		if ((pcb[i].parent != -1) && (pcb[i].children != NULL)) {
			/* print message about children of the current PCB[i] */
			printf("PCB[%d] is the parent of: ", i);
			/* intilize variable to head of list of children */
			next = pcb[i].children;		

			/* while the end of the linked list of children is not reached */ 						
			while(next != NULL) {
				/* print message about current child process index */
				printf("PCB[%d] ", next->process);
				/* move to next node in linked list */
				next = next->link;	
			}

			/* print newline */
			printf("\n");
		}/* if */
	} /* for */
} /* end of procedure */

/***************************************************************/
void createList() {
	/* declare local vars */

	/* prompt for maximum number of processes */
	printf("Enter the maximum number of processes: ");
	scanf("%d", &n);
	
	/* allocate memory for dynamic array of PCBs */
	pcb = (pcb_type*)malloc(n * sizeof(pcb_type));

	/* Define PCB[0] */
	pcb[0].parent = 0;
	pcb[0].children = NULL; 
	
	/* for-loop i=1 up to n-1 to initialize all other indices' parent to -1 */
  	for (int i = 1; i < n; i++)
		pcb[i].parent = -1;	

	return;

} /* end of procedure */

	
/***************************************************************/
void createChildProcess() {
	
	/* define local vars */
	int p; 
	int q = 1; 
	linked_list_type *new_child;
  	linked_list_type *next;
	
	/* prompt for parent process index p */
	printf("Enter the parent process: ");
	scanf("%d", &p);	

	/* search for first available index q without a parent in a while loop */
	while (pcb[q].parent != -1) {
		q++;
	}

	/* allocate memory for new child process, initilize fields */
	new_child = (linked_list_type *)malloc(sizeof(linked_list_type));
	new_child->process = q;
	new_child->link = NULL;

	/* record the parent's index p in PCB[q] */
	pcb[q].parent = p;

	/* initialize the list of children of PCB[q] as empty */
	pcb[q].children = NULL;

	/* create a new link containing the child's index q and append the link to the end of the linked list of PCB[p] */
	if (pcb[p].children == NULL) {
		pcb[p].children = new_child;
	}
	else {
		next = pcb[p].children;
		while(next->link != NULL) {
			next = next->link;	
		}
		next->link = new_child;
	}

	/* call procedure to print current hierachy of processes */
  	printList();

	return;
} /* end of procedure */


/***************************************************************/
void deleteNodes(linked_list_type *node) {
	/* declare local vars */
	int q;
	
	/* check if end of linked list--if so return */
	if (node == NULL) {
		return;
	}

	/* else call self on next node in linked list */
	else {
		deleteNodes(node->link);
		/* set variable q to current node's process index field */
		q = node->process;		

		/* call self on children of PCB[q] */ 	
		deleteNodes(pcb[q].children);
		
		/* free memory of paramter */
		free(node);
		
		/* reset parent of PCB[q] to -1 */
		pcb[q].parent = -1;

		/* set paramter to NULL */
		node = NULL;

	} /* end of else */
	return;
} /* end of procedure */


/***************************************************************/
void destroyDescendants() {
	/* declare local vars */
  	int p;
	
	/* prompt for process index p */
	printf("Enter the parent process: ");
	scanf("%d", &p);	

	/* call recursive procedure to destroy children/descendants of PCB[p] */
  	deleteNodes(pcb[p].children);

	/* reset children of PCB[p] to NULL */
	pcb[p].children = NULL;

	/* call procedure to print current hierarchy of processes */
  	printList();

	return;
} /* end of procedure */


/***************************************************************/
void freeMemory() {
	/* check if PCB is non null) */
	if (pcb != NULL) {
		/* check if children of PCB[0] is not null */
		if (pcb[0].children != NULL) {
			/* call recursive procedure to destroy children of PCB[0] */
      		deleteNodes(pcb[0].children);
		} /* if */
	/* free memory of PCB */
	free(pcb);
	} /* if */
	return;
} /* end of procedure */


/***************************************************************/
int main() {
	/* declare local vars */
	int choice;

	/* while user has not chosen to quit */
	while (choice != 4) {
		/* print menu of options */
		printf("Process creation and destruction\n");
    	printf("---------------------------------\n");		

		/* prompt for menu selection */
		printf("1) Enter parameters\n");
    	printf("2) Create a new child process\n");
    	printf("3) Destroy all descendants of a process\n");
    	printf("4) Quit program and free memory\n");
		scanf("%d", &choice);


		/* call appropriate procedure based on choice--use switch statement or series of if, else if, else statements */
		if (choice == 1) 
			createList();
		else if (choice == 2) 
			createChildProcess();
		else if (choice == 3) 
			destroyDescendants();
		else if (choice == 4) {
			freeMemory();
      break;
    }
		else
      printf("Invalid input. Try again.");
	
	} /* while loop */

	 return 1; /* indicates success */
} /* end of procedure */