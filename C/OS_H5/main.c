#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int *sequence = NULL;
int sequence_size;

void getParameters()
{
    printf("Enter size of sequence: ");
    scanf("%d", &sequence_size);

    sequence = (int *)malloc(sequence_size * sizeof(int));

    printf("Enter starting track: ");
    scanf("%d", &sequence[0]);

    printf("Enter sequence of tracks to seek: ");

    for (int i = 1; i <= sequence_size - 1; i++)
    {
        scanf("%d", &sequence[i]);
    }

    printf("\n");

    return;
}

void getFIFO()
{
    int total_distance = sequence[0];

    printf("Traversed sequence: ");
    printf("%d ", sequence[0]);

    for (int i = 1; i <= sequence_size - 1; i++)
    {
        total_distance += abs(sequence[i] - sequence[i - 1]);
        printf("%d ", sequence[i]);
    }

    printf("\nThe distance of the traversed tracks is: ");
    printf("%d", total_distance);
    printf("\n\n");

    return;
}

void getSSTF()
{

    int total_distance = sequence[0];
    int current_track = sequence[0];
    int shortest_distance = 0;
    int shortest_index = 0;
    int num_done = 1;
    int *done = (int *)calloc(sequence_size, sizeof(int));

    printf("Traversed sequence: ");
    printf("%d ", sequence[0]);

    while (num_done < sequence_size)
    {

        shortest_distance = INT_MAX;

        for (int i = 1; i <= sequence_size - 1; i++)
        {
            if (done[i] == 0)
            {
                if (abs(sequence[i] - current_track) < shortest_distance)
                {
                    shortest_distance = abs(sequence[i] - current_track);
                    shortest_index = i;
                }
            }
        }
        done[shortest_index] = 1;
        num_done++;
        total_distance += shortest_distance;
        current_track = sequence[shortest_index];
        printf("%d ", sequence[shortest_index]);
    }

    printf("\nThe distance of the traversed tracks is: ");
    printf("%d", total_distance);
    printf("\n\n");

    return;
}

void getScan()
{
    int direction;
    int total_distance = sequence[0];
    int current_track = sequence[0];
    int shortest_distance = 0;
    int shortest_index = 0;
    int num_done = 1;
    int *done = (int *)calloc(sequence_size, sizeof(int));
    int at_least_one;

    printf("Enter initial direction (0 = decreasing, 1 = increasing): ");
    scanf("%d", &direction);

    printf("Traversed sequence: ");
    printf("%d ", sequence[0]);

    while (num_done < sequence_size)
    {
        at_least_one = 0;

        shortest_distance = INT_MAX;

        for (int i = 1; i <= sequence_size - 1; i++)
        {

            if (done[i] == 0)
            {
                if (abs(sequence[i] - current_track) < shortest_distance)
                {
                    if (((sequence[i] - current_track > 0) && (direction == 1)) || ((sequence[i] - current_track < 0) && (direction == 0)))
                    {
                        shortest_distance = abs(sequence[i] - current_track);
                        shortest_index = i;
                        at_least_one = 1;
                    }
                }
            }
        }
        if (at_least_one == 1)
        {
            done[shortest_index] = 1;
            num_done++;
            total_distance += shortest_distance;
            current_track = sequence[shortest_index];
            printf("%d ", sequence[shortest_index]);
        }
        else
        {
            direction = 1 - direction;
        }
    }

    printf("\nThe distance of the traversed tracks is: ");
    printf("%d", total_distance);
    printf("\n\n");

    return;
}

void getCScan()
{

    int total_distance = sequence[0];
    int current_track = sequence[0];
    int shortest_distance = 0;
    int shortest_index = 0;
    int num_done = 1;
    int *done = (int *)calloc(sequence_size, sizeof(int));
    int at_least_one = 0;
    int end_reached = 0;

    printf("Traversed sequence: ");
    printf("%d ", sequence[0]);

    while (num_done < sequence_size)
    {
        at_least_one = 0;

        shortest_distance = INT_MAX;

        for (int i = 1; i <= sequence_size - 1; i++)
        {
            if (done[i] == 0)
            {
                if (abs(sequence[i] - current_track) < shortest_distance)
                {
                    if ((sequence[i] - current_track) > 0)
                    {
                        shortest_distance = abs(sequence[i] - current_track);
                        shortest_index = i;
                        at_least_one = 1;
                    }
                }
            }
        }
        if (at_least_one == 1)
        {
            if (end_reached == 0)
            {
                total_distance += shortest_distance;
            }
            else
            {
                total_distance -= shortest_distance;
                end_reached = 0;
            }
            done[shortest_index] = 1;
            num_done++;

            current_track = sequence[shortest_index];
            printf("%d ", sequence[shortest_index]);
        }
        else
        {
            total_distance += current_track;
            current_track = 0;
            end_reached = 1;
        }
    }

    printf("\nThe distance of the traversed tracks is: ");
    printf("%d", total_distance);
    printf("\n\n");

    return;
}

void freeMemory()
{

    if (sequence != NULL)
    {
        free(sequence);
    }

    printf("Quiitting program...\n");

    return;
}

int main()
{
    int input = 0;

    while (input != 6)
    {
        printf("Disk scheduling \n");
        printf("---------------- \n");
        printf("1) Enter parameters \n");
        printf("2) Calculate distance to traverse tracks using FIFO \n");
        printf("3) Calculate distance to traverse tracks using SSTF \n");
        printf("4) Calculate distance to traverse tracks using Scan \n");
        printf("5) Calculate distance to traverse tracks using C-Scan \n");
        printf("6) Quit the program and free memory \n");

        printf("\nEnter selection: ");
        scanf("%d", &input);

        switch (input)
        {
        case 1:
            getParameters();
            break;
        case 2:
            getFIFO();
            break;
        case 3:
            getSSTF();
            break;
        case 4:
            getScan();
            break;
        case 5:
            getCScan();
            break;
        case 6:
            freeMemory();
            break;
        }
    }
}