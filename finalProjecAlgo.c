#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITINERARIES 100
#define MAX_STEPS 50
#define MAX_NAME_LENGTH 50
#define MAX_HISTORY 150

// Records
typedef struct {
    char name[MAX_NAME_LENGTH];
    char description[MAX_NAME_LENGTH];
    int priority; // only 3 types of priority (1 = high, 2 = medium, 3 = low)
} Step;

typedef struct {
    char name[MAX_NAME_LENGTH];
    char destination[MAX_NAME_LENGTH];
    Step steps[MAX_STEPS];
    int stepCount;
} Itinerary;

typedef struct {
    char name[MAX_NAME_LENGTH];
    char destination[MAX_NAME_LENGTH];
} HistoryEntry;

// Variables
Itinerary itineraries[MAX_ITINERARIES];
int itineraryCount = 0;
HistoryEntry history[MAX_HISTORY];
int historyCount = 0;

// bubble sort of priority 1 -> 2 -> 3
void sortStepsByPriority(Step steps[], int stepCount) {
    int swapped;
    for (int i = 0; i < stepCount - 1; i++) {
        swapped = 0;
        for (int j = 0; j < stepCount - i - 1; j++) {
            if (steps[j].priority > steps[j + 1].priority) {
                Step temp = steps[j];
                steps[j] = steps[j + 1];
                steps[j + 1] = temp;
                swapped = 1;
            }
        }
        if (!swapped) break;  // If no swaps, list is sorted
    }
}


//add procedure
void addItinerary() {
    if (itineraryCount >= MAX_ITINERARIES) {
        printf("Itinerary limit reached.\n");
        return; // to exit directly the procedure without executing the other lines
    }

    Itinerary itinerary;
    printf("Name of itinerary : ");
    scanf(" %[^\n]", itinerary.name); /*to read a string including the space" ", fgets function works too*/
    strlwr(itinerary.name);// to avoid the problem of UPPER =! lower
    printf("Destination : ");
    scanf(" %[^\n]", itinerary.destination); /*to read a string with space as well*/

    // Adding Steps
    do {
    printf("How many steps would you like to add? ");
    scanf("%d", &itinerary.stepCount);
    if (itinerary.stepCount > MAX_STEPS) {
        printf("Too many steps! The limit is %d.\n", MAX_STEPS);
    }
    } while (itinerary.stepCount > MAX_STEPS);

    

    for (int i = 0; i < itinerary.stepCount; i++) {
        printf("\nStep %d :\n", i + 1);
        printf("Name : ");
        scanf(" %[^\n]", itinerary.steps[i].name);
        
        printf("Description : ");
        scanf(" %[^\n]", itinerary.steps[i].description);
        
        do {
            printf("Priority (1 = high, 2 = medium, 3 = low): ");
            scanf("%d", &itinerary.steps[i].priority);
            if (itinerary.steps[i].priority < 1 || itinerary.steps[i].priority > 3) {
            printf("Invalid priority! Please enter 1, 2, or 3.\n");
            }
        } while (itinerary.steps[i].priority < 1 || itinerary.steps[i].priority > 3);

    }

    // Sorting
    sortStepsByPriority(itinerary.steps, itinerary.stepCount);

    itineraries[itineraryCount] = itinerary;
    itineraryCount++;
    printf("Itinerary added successfully.\n");
}


// Deleting and Adding to history
void deleteItinerary() {
    char itineraryName[MAX_NAME_LENGTH];

    if (itineraryCount == 0){
        printf("There is no itinerary to Delete!\n");
        return;
    }
    
    printf("Name of the itinerary to delete : ");
    scanf(" %[^\n]", itineraryName);
    strlwr(itineraryName);

    for (int i = 0; i < itineraryCount; i++) {
        if (strcmp(itineraries[i].name, itineraryName) == 0) {
            // Add to history
            if (historyCount < MAX_HISTORY) {
                strcpy(history[historyCount].name, itineraries[i].name);
                strcpy(history[historyCount].destination, itineraries[i].destination);
                historyCount++;
            }

            // Deleting the itinerary
            for (int j = i; j < itineraryCount - 1; j++) {
                itineraries[j] = itineraries[j + 1];
            }
            itineraryCount--;
            printf("Itinerary deleted and added to history.\n");
            return;
        }
    }
    printf("Itinerary not found.\n");
}

// Search for specific itinerary
void searchItinerary() {
    char itineraryName[MAX_NAME_LENGTH];

    if (itineraryCount == 0){
        printf("There is no itinerary to Search for!\n");
        return;
    }

    printf("Name of the itinerary to research : ");
    scanf(" %[^\n]", itineraryName);
    strlwr(itineraryName);

    for (int i = 0; i < itineraryCount; i++) {
        if (strcmp(itineraries[i].name, itineraryName) == 0) {
            printf("\nItinerary : %s\nDestination : %s\n", itineraries[i].name, itineraries[i].destination);

            if (itineraries[i].stepCount == 0) {
                printf("No steps added.\n");
                return;
            }

            printf("Steps (classed by priority) :\n");
            for (int j = 0; j < itineraries[i].stepCount; j++) {
                printf("  - %s (Priority : %d) : %s\n", itineraries[i].steps[j].name, itineraries[i].steps[j].priority, itineraries[i].steps[j].description);
            }
            return;
        }
    }
    printf("Itinerary not found.\n");
}

// display history of deleted itinerary
void displayHistory() {
    if (historyCount == 0) {
        printf("No itinerary found in history.\n");
        return;
    }

    printf("\nHistory of deleted itineraries:\n");

    for (int i = 0; i < historyCount; i++) {
        printf("- %s (Destination : %s)\n", history[i].name, history[i].destination);
    }
}

int main() {
    int choice;

    do {
        printf("\n===Travel Planning App ===\n");
        printf("1. Add an itinerary\n");
        printf("2. Delete an itinerary\n");
        printf("3. Search for a specific itinerary\n");
        printf("4. View travel history\n");
        printf("0. Leave\n");
        printf("Choose an option : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addItinerary();
                break;
            case 2:
                deleteItinerary();
                break;
            case 3:
                searchItinerary();
                break;
            case 4:
                displayHistory();
                break;
            case 0:
                printf("See you later !\n");
                break;
            default:
                printf("Invalid option.\n");
        }
    } while (choice != 0);
    return 0;
}