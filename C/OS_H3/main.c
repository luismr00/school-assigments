#include <stdio.h>
#include <stdlib.h>
/* Declare dynamic arrays and global variables*/
int *resource = NULL;
int *available = NULL;
int *max_claim = NULL;
int *allocated = NULL;
int *need = NULL;

int num_resources;
int num_processes;


/***********************************************************/
void printResourceVector() {
    /* declare local variables */

    // OPTIONAL: header of units total & available
    printf("\tUnits\tAvailable\n");

    /* for loop: print each resource index */
    for (int i = 0; i < num_resources; i++) {
        //print number of total units and available units of each resource __has_include_next
        printf("r%d\t%d\t%d\n", i, resource[i],available[i]);
    }
    /* for loop: print number of total units and available units of each resource index */
    printf("\n");

    return;
}
/***************************************************************/
void printMatrix() {
    /* declare local variables */

    /* OPTIONAL for loop: print each resource index */
    printf("\tMaximum\t\t\tCurrent\t\t\tPotential\n");
    printf("\t");
    for(int i = 0; i < num_resources; i++)
        for (int j = 0; j < num_resources; j++)
            printf("r%d\t", j);
    printf("\n");


    /* for each process: i from 0 up to and not including total number of processes */
    for (int i = 0; i < num_processes; i++) {
        printf("p%d\t", i);
        /* for each resource: j from 0 to and not including total number of recources */
        for (int j = 0; j < num_resources; j++) {
            /* print maximum number of units each process may request, is allocated, and needs from each resource */
            printf("%d\t", max_claim[i * num_resources + j]);
        }

        for (int j = 0; j < num_resources; j++) {
            /* print maximum number of units each process may request, is allocated, and needs from each resource */
            printf("%d\t", allocated[i * num_resources + j]);
        }

        for (int j = 0; j < num_resources; j++) {
            /* print maximum number of units each process may request, is allocated, and needs from each resource */
            printf("%d\t", need[i * num_resources + j]);
        }

        printf("\n");
    }

    printf("\n");

    return;
}
/****************************************************************/
void getParameters() {
    /* declare local variables */

    /* prompt for number of processes and number of resources */
    printf("Enter number of processes: ");
    scanf("%d", &num_processes);
    printf("Enter number of resources: ");
    scanf("%d", &num_resources);


    /* allocate memory for vectors and arrays: resource, available, max_claim, allocated, need */
    resource = (int *)malloc(num_resources * sizeof(int));
    available = (int *)malloc(num_resources * sizeof(int));
    max_claim = (int *)malloc(num_processes * num_resources * sizeof(int));
    allocated = (int *)malloc(num_processes * num_resources * sizeof(int));
    need = (int *)malloc(num_processes * num_resources * sizeof(int));
    

    /* for each resource, prompt for number of units, set resource and available vectors indices*/
    for (int i = 0; i < num_resources; i++) {
        printf("Enter number of units for resource r%d: ", i);
        scanf("%d", &resource[i]); 
        available[i] = resource[i];
    }

    // for each process i, 
    for (int i = 0; i < num_processes; i++)
        // for each resource, prompt for maximum number of units requested by process, N[initialize need array] O[update max_claim and need array] 
        for (int j = 0; j < num_resources; j++) {
            printf("Enter max units process p%d will request from resource r%d: ", i,j);
            scanf("%d", &max_claim[i * num_resources + j]);
            need[i * num_resources + j] = max_claim[i * num_resources + j];
        }
    
    // for each process i, 
    for (int i = 0; i < num_processes; i++)
        // for each resource j, prompt for number of resource units allocated to process 
        for (int j = 0; j < num_resources; j++) {
            printf("Enter number of units for resource r%d allocated to process p%d: ", j,i);
            scanf("%d", &allocated[i * num_resources + j]);
            /* update need array */
            need[i * num_resources + j] -= allocated[i * num_resources + j];
            available[j] -= allocated[i * num_resources + j];
        }
    
    printf("\n");

    /* print resource vector, available vector, max_claim array, allocated array, need array */
    printResourceVector();
    printMatrix();
    
    return;
}
/********************************************************************/
void runAlgorithm() {
    /* declare local variables, including vector to indicate if process is safely sequenced and "num_sequenced" count*/
    int i, j; 

    int finished = 0; //counter for the number of processes that have been successfully sequenced
    int less_than_or_equal = 1;
    int *sequenced = (int *)calloc(num_processes, sizeof(int)); //set sequenced [i] to 0 is not sequenced, 1 if already sequenced
    int at_least_one = 1;

    /* while not all processed are sequenced */
    while ((finished < num_processes) && (at_least_one == 1)) {
        at_least_one = 0;
    
        /* for each process: i */
        for (int i = 0; i < num_processes; i++) {

            less_than_or_equal = 1;

            /* if process has not been safely sequenced yet */
            if(sequenced[i] == 0) {

                printf("Checking: < ");
                for (j = 0; j < num_resources; j++) {
                    printf("%d", need[i * num_resources + j]);
                    printf(" ");
                }
                printf("> ");

                printf("<= < ");
                for (j = 0; j < num_resources; j++) {
                    printf("%d", available[j]);
                    printf(" ");
                }
                printf("> :");

                /* check for safe sequencing by comparing process' need vector to available vector */
                for (j = 0; j < num_resources; j++)
                    less_than_or_equal &= (need[i * num_resources + j] <= available[j]);

                if (less_than_or_equal == 1) {

                    /* print message that process had been safely sequenced */
                    printf("p%d safely sequenced \n", i);

                    sequenced[i] = 1; // mark as sequenced
                    at_least_one = 1;
                    
                    /* update number of available units of resource because processes freed all its allocated resources */
                    /* for each resource: j */
                    for (j = 0; j < num_resources; j++) {
                        /* free all resources allocated to process */
                        available[j] += allocated[i * num_resources + j];
                        allocated[i * num_resources + j] = 0;
                    }
                    
                    /* increment number of sequenced processes */
                    finished++;

                } else {
                    /* print message that process could not be sequenced */
                    printf("p%d could not be sequenced\n", i);
                } 
            }
        } 
    }

    printf("\n");

    // OPTIONAL: print message if at_least_one == 0 that deadlock reached
    if (at_least_one == 0)
        printf("\nReached a deadlock!");

    return;
}
/********************************************************************/
void freeMemory() {
    /* check if vectors/array are not NULL--if so, free each vector/array */ 
    printf("Quitting program...");
    
    if (resource != NULL) {
        free(resource);
        free(available);
        free(max_claim);
        free(allocated);
        free(need);
    }
    return;
}
/***************************************************************/
int main() {
    /* Declare local variables */
    int input = 0;

    /* Until the user quits, print the menu, prompt for the menu choice, call the appropriate procedure */
    while(input != 3) {
        printf("Banker's Algorithm \n");
        printf("------------------ \n");
        printf("1) Enter parameters \n2) Determine safe sequence \n3) Quit program \n\n");
        
        printf("Enter selection: ");
        scanf("%d", &input);
        printf("\n");

        switch (input) {
        case 1: 
            getParameters();
            break;
        case 2: 
            runAlgorithm();
            break;
        case 3: 
            freeMemory();
            break;
        }
    }

    return 1;
}