// #include <stdio.h>
// #include <stdlib.h>
// #include <limits.h>

// /* declare global variables including a table structure to hold scheduling information */
// int processes;

// struct node {
// 	int id;
// 	int arrival;
// 	int total_cpu;
// 	int total_remaining;
// 	int done;
// 	int start_time;
// 	int already_started;
// 	int end_time;
// 	int turnaround_time;
// } *table = NULL;

// typedef struct node table_type;


// /* optional: define a function that finds the maximum of two integers */
// #define max(a,b) (a > b ? a : b)

// /***************************************************************/
// void printTable() {
	
// 	/* declare local variables */

// 	/* print table header */
// 	printf("\nID\tArrival\tTotal\tStart\tEnd\tTurnaround\n");	
// 	printf("--------------------------------------------------\n");

// 	/* for each process */
// 	for (int i = 0; i < processes; i++) {
// 		/* print the contents (id, arrival time, total_cycles) of each field of the table's index */
// 		printf("%d\t%d\t%d", table[i].id, table[i].arrival, table[i].total_cpu);
// 		/* if process has been scheduled ("done" field is 1, print other contents (start time, end time, turnaround time) */
// 		if (table[i].done == 1)
// 			printf("\t%d\t%d\t%d", table[i].start_time, table[i].end_time, table[i].turnaround_time);

// 		printf("\n");
// 	}

// 	return;
// }


// /***************************************************************/
// void declareProcesses() {
	
// 	/* declare local variables */

// 	/* prompt for total number of processes */	
// 	printf("Enter total number of processes: ");
// 	scanf("%d", &processes);
	
// 	/* allocate memory for table to hold process parameters */
// 	table = (table_type *)malloc(processes * sizeof(table_type));

// 	/* for each process */
// 	for (int i = 0; i < processes; i++) {
// 		/* prompt for process id, arrival time, and total cycle time */	
// 		printf("Enter process id: ");
// 		scanf("%d", &table[i].id);
// 		printf("Enter arrival cycle for process P[%d]: ", table[i].id);
// 		scanf("%d", &table[i].arrival);
// 		printf("Enter total cycles for process P[%d]: ", table[i].id);
// 		scanf("%d", &table[i].total_cpu);
// 	}
// 	/* print contents of table */
// 	printTable();

// 	return;		
// }	
		

// /***************************************************************/
// void FIFO() {

// 	/* declare (and initilize when appropriate) local variables */
// 	int i;
// 	int num_done = 0;
// 	int min_value;
// 	int min_index;
// 	int current_cycle = 0;

// 	/* for each process, reset "done" field to 0 */
// 	for (i = 0; i < processes; i++) 
// 		table[i].done = 0;

// 	/* while there are still processes to schedule */
// 	while (num_done < processes) {	
// 		/* initilize the earliest arrival time to INT_MAX (largest integer value) */
// 		min_value = INT_MAX;

// 		/* for each process not yet scheduled */
// 		for (i = 0; i < processes; i++) {
// 			if (table[i].done == 0) {
// 				/* check if process has earlier arrival time than current earliest and update */	
// 				if (table[i].arrival < min_value) {
// 					min_value = table[i].arrival;
// 					min_index = i;
// 				}
// 			}
// 		}

// 		/* set start time, end time, turnaround time, done fields for unscheduled process with earliest arrival time */
// 		table[min_index].start_time = max(current_cycle, table[min_index].arrival);
// 		table[min_index].end_time = table[min_index].start_time + table[min_index].total_cpu;
// 		table[min_index].turnaround_time = table[min_index].end_time - table[min_index].arrival;
// 		table[min_index].done = 1;

// 		/* update current cycle time and increment number of processes scheduled */
// 		current_cycle = table[min_index].end_time;
// 		num_done++;
// 	}

// 	/* print contents of table */
// 	printTable();

// 	return;		
// }	



// /***************************************************************/
// void SJF() {

// 	/* declare (and initilize when appropriate) local variables */
// 	int i;
// 	int num_done = 0;
// 	int min_value;
// 	int min_index;
// 	int current_cycle = 0;

// 	/* for each process, reset "done" field to 0 */
// 	for (i = 0; i < processes; i++) 
// 		table[i].done = 0;

// 	/* while there are still processes to schedule */	
// 	while (num_done < processes) {	
// 		/* initilize the lowest total cycle time to INT_MAX (largest integer value) */
// 		min_value = INT_MAX;

// 		/* for each process not yet scheduled */
// 		for (i = 0; i < processes; i++) {
// 			if (table[i].done == 0) {
// 				/* check if process has lower total cycle time than current lowest and has arrival time less than current cycle time and update */	
// 				if ((table[i].total_cpu < min_value) && (table[i].arrival <= current_cycle)) {
// 					min_value = table[i].total_cpu;
// 					min_index = i;
// 				}
// 			}
// 		}

// 		/* set start time, end time, turnaround time, done fields for unscheduled process with lowest (and available) total cycle time */       	
// 		table[min_index].start_time = max(current_cycle, table[min_index].arrival);
// 		table[min_index].end_time = table[min_index].start_time + table[min_index].total_cpu;
// 		table[min_index].turnaround_time = table[min_index].end_time - table[min_index].arrival;
// 		table[min_index].done = 1;

// 		/* update current cycle time and increment number of processes scheduled */
// 		current_cycle = table[min_index].end_time;
// 		num_done++;
// 	}

// 	/* print contents of table */
// 	printTable();

// 	return;		
// }	
        	

// /***************************************************************/
// void SRT() {

// 	/* declare (and initilize when appropriate) local variables */
// 	int i;
// 	int num_done = 0;
// 	int min_value;
// 	int min_index;
// 	int current_cycle = 0;

// 	/* for each process, reset "done", "total_remaining" and "already_started" fields to 0 */
// 	for (i = 0; i < processes; i++) { 
// 		table[i].done = 0;
// 		table[i].total_remaining = table[i].total_cpu;
// 		table[i].already_started = 0;
// 	}

// 	/* while there are still processes to schedule */	
// 	while (num_done < processes) {	
// 		/* initilize the lowest total remaining time to INT_MAX (largest integer value) */
// 		min_value = INT_MAX;

// 		/* for each process not yet scheduled */
// 		for (i = 0; i < processes; i++) {
// 			if (table[i].done == 0) {
// 				/* check if process has lower total remaining time than current lowest and has arrival time less than current cycle time and update */	
// 				if ((table[i].total_remaining < min_value) && (table[i].arrival <= current_cycle)) {
// 					min_value = table[i].total_remaining;
// 					min_index = i;
// 				}
// 			}
// 		}
		
// 		if (table[min_index].already_started == 0) {
// 			table[min_index].start_time = max(current_cycle, table[min_index].arrival);
// 			table[min_index].end_time = current_cycle + 1;
// 			table[min_index].turnaround_time = table[min_index].end_time - table[min_index].arrival;
// 			table[min_index].already_started = 1;
// 		} else {
// 			table[min_index].end_time = current_cycle + 1;
// 			table[min_index].turnaround_time = table[min_index].end_time - table[min_index].arrival;
// 		}

// 		table[min_index].total_remaining -= 1;

// 		if (table[min_index].total_remaining == 0) {
// 			table[min_index].done = 1;
// 			num_done++;
// 		}

// 		current_cycle++;
// 	}
// 	/* print contents of table */
// 	printTable();

// 	return;		
// }	
        	

// /***************************************************************/
// void freeMemory() {

// 	/* free the schedule table if not NULL */

// 	if (table != NULL) {
// 		printf("Memory is now clear. Good job!\n");
// 		table = NULL;
// 	}
// 	else 
// 		printf("Nothing to delete. Good Bye.\n");

// 	return;
// }


// /***************************************************************/
// int main() {

// 	/* declare local vars */
// 	int choice = 0;

// 	/* while user has not chosen to quit */
// 	while (choice != 5) {
// 		/* print menu of options */
// 		printf("\nBatch scheduling\n");
// 		printf("----------------\n");
// 		printf("1) Enter parameters\n");
// 		printf("2) Schedule processes with FIFO algorithm\n");
// 		printf("3) Schedule processes with SJF algorithm\n");
// 		printf("4) Schedule processes with SRT algorithm\n");
// 		printf("5) Quit and free memory\n");
		
// 		/* prompt for menu selection */
// 		printf("\nEnter selection: ");
// 		scanf("%d", &choice);
// 		printf("\n");

// 		/* call appropriate procedure based on choice--use switch statement or series of if, else if, else statements */
// 		if(choice == 1) 
// 			declareProcesses();
// 		else if (choice == 2) 
// 			FIFO();
// 		else if (choice == 3)
// 			SJF();
// 		else if (choice == 4)
// 			SRT(); 
// 		else if (choice == 5) 
// 			freeMemory();
// 		else 
// 			printf("Invalid input. Try again.\n");

// 	} /* while loop */

// 	 return 1; /* indicates success */
// } /* end of procedure */





#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* declare global variables including a table structure to hold scheduling information */

struct node {
	int id;
	int arrival;
	int total_CPU;
	int total_remaining;
	int done;
	int start_time;
	int already_started;
	int turnaround_time;
	int end_time;
} 
*table = NULL;

typedef struct node table_type;

int totalP;
/* optional: define a function that finds the maximum of two integers */
#define max(a,b) (a > b ? a : b)

/***************************************************************/
void printChart() {
	
	/* declare local variables */
    int P = totalP; 
	/* print table header */
	printf("\nID\tArrival\tTotal\tStart\tEnd\tTurnaround\n");	
	printf("---------------------------------------------\n");

	/* for each process */
	for (int i = 0; i < P; i++) {
		/* print the contents (id, arrival time, total_cycles) of each field of the table's index */
		printf("%d\t%d\t%d", table[i].id, table[i].arrival, table[i].total_CPU);
		if (table[i].done == 1){
			printf("\t%d\t%d\t%d\n", table[i].start_time, table[i].end_time, table[i].turnaround_time);
		}
	}


	return;
}


/***************************************************************/
void option1() {
	/* declare local variables */
	int P = totalP;
	 
	/* prompt for total number of processes */	
	printf("Enter total number of processes: ");
	scanf("%d", &P);
	
	/* allocate memory for table to hold process parameters */
	table = (table_type *)malloc(P * sizeof(table_type));

	/* for each process */
	for (int i = 0; i < P; i++) {
		/* prompt for process id, arrival time, and total cycle time */	
		printf("Enter process id: ");
		scanf("%d", &table[i].id);
		printf("Enter arrival cycle for process P[%d]: ", table[i].id);
		scanf("%d", &table[i].arrival);
		printf("Enter total cycles for process P[%d]: ", table[i].id);
		scanf("%d", &table[i].total_CPU);
	}
	/* print contents of table */
	printChart();

	return;		
}	
		

/***************************************************************/
void option2() {

	/* declare (and initilize when appropriate) local variables */
    int lNum = totalP;
    int earlyArrival;
    int currentP;
    int currentCycle = 0;
	/* for each process, reset "done" field to 0 */
	for (int i = 0; i < totalP; i++) 
		table[i].done = 0;

	/* while there are still processes to schedule */
	while (lNum < totalP) {	
		/* initilize the lowest total remaining time to INT_MAX (largest integer value) */
		earlyArrival = INT_MAX;

		for (int i = 0; i < totalP; i++) {
			if (table[i].done == 0) {
					if (table[i].arrival < earlyArrival) {
					earlyArrival = table[i].arrival;
					currentP = i;
				}
			}
		}

		
		table[currentP].start_time = max(currentCycle, table[currentP].arrival);
		table[currentP].end_time = table[currentP].start_time + table[currentP].total_CPU;
		table[currentP].turnaround_time = table[currentP].end_time - table[currentP].arrival;
		table[currentP].done = 1;

		
		currentCycle = table[currentP].end_time;
		lNum++;
	}

	/* print contents of table */

	return;		
}	



/***************************************************************/
void option3() {

	/* declare (and initilize when appropriate) local variables */
 	int lNum = totalP;
    int lowestCPU;
    int currentP;
    int currentCycle = 0;
	/* for each process, reset "done" field to 0 */
	for (int i = 0; i < totalP; i++) 
		table[i].done = 0;

	/* while there are still processes to schedule */	
	while (lNum != 0) {	
		/* initilize the lowest total remaining time to INT_MAX (largest integer value) */
		lowestCPU = INT_MAX;
		
		for (int i = 0; i < totalP; i++) {
			if (table[i].done == 0) {
				if ((table[i].total_CPU < lowestCPU) && (table[i].arrival <= currentCycle)) {
					lowestCPU = table[i].total_CPU;
					currentP = i;
				}
			}
		}

     	
		table[currentP].start_time = max(currentCycle, table[currentP].arrival);
		table[currentP].end_time = table[currentP].start_time + table[currentP].total_CPU;
		table[currentP].turnaround_time = table[currentP].end_time - table[currentP].arrival;
		table[currentP].done = 1;


		currentCycle = table[currentP].end_time;
		lNum++;
	}

	/* print contents of table */


	return;		
}	
        	

/***************************************************************/
void option4() {

	/* declare (and initilize when appropriate) local variables */
 	int lNum = totalP;
    int lowestRemain;
    int currentP;
    int startP;
	int currentCyc;
	/* for each process, reset "done", "total_remaining" and "already_started" fields to 0 */
	for (int i = 0; i < totalP; i++) { 
		table[i].done = 0;
		table[i].total_remaining = table[i].total_CPU;
		table[i].already_started = 0;
	}

	/* while there are still processes to schedule */	
	while (lNum != 0) {	
		/* initilize the lowest total remaining time to INT_MAX (largest integer value) */
		 lowestRemain = INT_MAX;


		for (int i = 0; i < totalP; i++) {
			if (table[i].done == 0) {

				if ((table[i].total_remaining < lowestRemain) && (table[i].arrival <= currentCyc)) {
					lowestRemain = table[i].total_remaining;
					currentP = i;
				}
			}
		}
		
		if (table[currentP].already_started == 0) {
			table[currentP].start_time = max(currentCyc, table[currentP].arrival);
			table[currentP].end_time = currentCyc + 1;
			table[currentP].turnaround_time = table[currentP].end_time - table[currentP].arrival;
			table[currentP].already_started = 1;
		} else {
			table[currentP].end_time = currentCyc + 1;
			table[currentP].turnaround_time = table[currentP].end_time - table[currentP].arrival;
		}

		table[currentP].total_remaining -= 1;

		if (table[currentP].total_remaining == 0) {
			table[currentP].done = 1;
			lNum++;
		}

		currentCyc++;
	}
	/* print contents of table */
		printChart();

	return;		
}	
        	

/***************************************************************/
void option5() {

	/* free the schedule table if not NULL */
if(table!= NULL){
	free (table);
}
	return;
}


/***************************************************************/
int main() {

	/* declare local vars */
	int ans = 0;
	/* while user has not chosen to quit */
	while(ans != 5){
		//option menu
		printf("choose an option");
		printf("1)option 1\n2)option 2\n3)option 3\n4)optio 4\n5)option 5");
		scanf("%d", &ans);
		
		// switch (ans){
		// 	case 1: option1();
		// 	break;
		// 	case 2: option2();
		// 	break;
		// 	case 3: option3();
		// 	break;
		// 	case 4: option4();
		// 	break;
		// 	case 5: option5();
		// 	break;
		// }

		if( ans ==1){
		    option1();
		}
		else if (ans == 2){
	        option2();
		}
		else if(ans ==3){
		    option3();
		}
		else if(ans ==4){
		    option4();
		}
		else if(ans == 5){
	    option5();
		}
		
	}
	 return 1; /* indicates success */
} /* end of procedure */
