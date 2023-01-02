#include <stdio.h>
#include <stdlib.h>

// declare structure to store block information (id, starting address, ending address, link to next block)
struct node {
    int id;
    int start;
    int end; 
    struct node *link;
} *block_list = NULL; 

// declare linked list to connect allocation blocks
typedef struct node block_type;

// declare global variables
int pm_size;
int algorithm;
int remaining;


/********************************************************************/
void setParameters() {
	
	// declare local variables (if any)
     
	// prompt for size of physical memory and choice of hole-fitting algorithm (0=first-fit, 1=best-fit), initialize remaining memory
    printf("Enter size of Physical Memory: "); 
    scanf("%d", &pm_size);
    printf("Enter hole-fitting algorithm (0 = first-fit, 1 = best-fit):  ");
    scanf("%d", &algorithm);
    printf("\n");
    
    remaining = pm_size; 

    // allocate memory for block_list
	block_list = (block_type*)malloc(sizeof(block_type));  
	
    // initilize linked list with "dummy" block of size 0
	block_list->id = -1; 
	block_list->start = 0;
	block_list->end = 0;
	block_list->link = NULL;
    
	return;
}


/********************************************************************/
void printTable() {
	
	// declare local variables 
    block_type* current =  block_list; 
    
	// print table containing block id, starting address, ending address
    printf("ID\tStart\tEnd\n"); 
    printf("---------------------\n");
    while(current != NULL){
        printf("%d\t", current->id);
        printf("%d\t", current->start);
        printf("%d\n", current->end);
        current = current->link;     
    }

    printf("\n");

	return;
}


/********************************************************************/
void allocateMemory() {
	
	// declare local variables
    block_type* new_block; 
    block_type* current_block = block_list; 
    block_type* best_block; 
    int best_hole;
    int block_id; 
    int block_size;
    int hole_start; 
    int hole_end; 
    int hole_size; 
    int best_start;
    int one_Hole = 0; 
    
    

	// initialize best hole so far to size of physical memory
    best_hole = pm_size; 

	// prompt for block id & block size
	printf("Enter block ID: ");
	scanf("%d",&block_id);
	printf("Enter block size: ");
	scanf("%d",&block_size); 
    printf("\n");

	// check if size of block is larger than remaining unallocated space, if so, print message and return	
    if(block_size > remaining){
        printf("Not enough allocated space!\n\n");
        return;
    }
    
    // allocate space for new block and set id
	new_block = (block_type*)malloc(sizeof(block_type));  
	
    // setting aside space for the new block 
	new_block->id = block_id; 
	
    // if only "dummy" block exists, insert block at end of linked list, set fields, return
	if(block_list->link == NULL){

	    new_block->start = 0;
	    new_block->end = block_size;
	    new_block->link = NULL;
	    block_list->link = new_block;
	    remaining = remaining - block_size; 
	    
	    printTable(); 
	    return; 
	}
	
	current_block = block_list; 

	// else traverse list until either appropriate hole is found or the end of the list is reached
	while(current_block != NULL){
        
        // if id already exists, reject request and return   
	    if(current_block->id == block_id){  
	        printf("Cannot duplicate ID!\n\n");
	        return; 
	    }
	        
	    // set values for start and end of currently found hole
	    hole_start = current_block->end;
	        
	    if(current_block->link == NULL){
	        hole_end = pm_size;
	    } else {
	        hole_end = current_block->link->start;    
	    }
	         
	    hole_size =  hole_end - hole_start; 
	        
	    // if hole is large enough for block
	    if(block_size <= hole_size){
	        one_Hole = 1; 

	        // if first-fit algorithm
		    if(algorithm == 0) {

                // set start & end fields of new block & add block into linked list
                new_block->start = hole_start;
                new_block->end = hole_start + block_size; 
                    
                // put new block inside of a pre-existing linked list. 
                new_block->link = current_block->link;
                current_block->link = new_block; 
                    
                // reduce remaining available memory and return
                remaining = remaining - block_size; 
		        return; 
		    } else {

                // if hole is smaller than best so far
                if(hole_size < best_hole) {
                    // set values of best start & best end & best hole size so far       
                    printf("%d\n", hole_start);          
                    best_hole = hole_size; 
                    best_start = hole_start; 
                    best_block = current_block;      
                }

            }
		      
		}

        // update best block & advance next block  
	    current_block = current_block->link;

	} //End While-Loop 
	        
	if(one_Hole == 0){
	    printf("No hole big enough for block request!\n\n");
        free(new_block);
	    return; 
	}
	            
	// set start & end fields of new block & add block into linked list 
	new_block->start = best_start; 
	new_block->end = best_start + block_size;              
	new_block->link = best_block->link;
    best_block->link = new_block; 
                
	// reduce remaining available memory and return   
	remaining = remaining - block_size; 

	printTable();    
	return;	
}
	

/********************************************************************/
void deallocateMemory() {
	// declare local variables
	int block_id; 
	block_type* current_block = block_list; 
	block_type* prev_block; 
	
	// prompt for block id
	printf("Enter block ID: ");
    scanf("%d", &block_id); 
    printf("\n");

	// until end of linked list is reached or block id is found 
	while((current_block != NULL ) && (block_id != current_block->id)){
		// traverse list
		
		prev_block = current_block; 
		current_block = current_block->link; 
		
	}
	
    // if end of linked list reached, print block id not found
    if(current_block == NULL){
	    printf("Unable to find block ID!\n\n"); 
	    return; 
	        
	} else {
	    // else remove block and deallocate memory
	    prev_block->link = current_block->link;
	    remaining = remaining + (current_block->end - current_block->start);
	    free(current_block); 
	}

    printTable();

	return;
}


/********************************************************************/
void defragmentMemory() {
	// declare local variables 	
	int block_size; 
    block_type* current_block = block_list;  
    int prev_end = 0; 
     
    // until end of list is reached
    while(current_block !=  NULL) {
         
        // calculate current hole size
        block_size = current_block->end - current_block->start; 

		// adjust start & end fields of current block to eliminate hole
        current_block->start = prev_end; 
        current_block->end = prev_end + block_size; 
        prev_end = current_block->end;
        current_block = current_block->link; 
    }
         
    printf("\n");
    printTable();

	return;
}


/********************************************************************/
void freeMemory(block_type *node) {
	
	// if node is NULL, return
	if(node == NULL){
	    return; 
	} else {

		// recursively call procedure on node->link 
        freeMemory(node->link); 
        
        // deallocate memory from node  
        free(node); 
	    
	}
	    
	return;
}


/***************************************************************/
int main() {
	/* declare local vars */
    int answer = 0;
	
    /* while user has not chosen to quit */
	while(answer != 5){
	    /* print menu of options */
		/* prompt for menu selection */
        printf("Memory allocation \n");
        printf("-----------------\n");
        printf("1. Enter parameters \n");
        printf("2. Allocate memory for block \n");
        printf("3. Deallocate memory for block \n");
        printf("4. Defragment memory \n");
        printf("5. Quit program \n\n");
        
        printf("Enter selection: ");
        scanf("%d", &answer);
        
        switch(answer){
            case 1: setParameters();
            break;
            case 2: allocateMemory();
            break;
            case 3: deallocateMemory();
            break;
            case 4: defragmentMemory();
            break;
            case 5: freeMemory(block_list);
            break;
        }		    
        
    }
	
    printf("Quitting program...");

	return 1; /* indicates success */
} /* end of procedure */