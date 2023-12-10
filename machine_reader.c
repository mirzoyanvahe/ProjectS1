#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for machine details
struct MachineDetails {
    char machineName[50];
    double electricityUsage;
    char machineState[50];
    // Add more details as needed
};

// Function prototypes
void readMachineEvents(const char *filename, struct MachineDetails machines[], int numMachines);
void displayMenu(struct MachineDetails machines[], int numMachines);
void setMachineState(struct MachineDetails machines[], int numMachines);
void provideFeedback(const char *machineName, const char *eventType, const char *machineState, struct MachineDetails machines[], int numMachines);
void handleEmergency(struct MachineDetails machines[], int numMachines);
void exportHistory(struct MachineDetails machines[], int numMachines);

int main() {
    // Define the number of machines
    int numMachines = 8;

    // Declare an array of MachineDetails to store information for each machine
    struct MachineDetails machines[numMachines];

    // Initialize machine names in the array
    const char *machineNames[] = {
        "glass cutting machine",
        "glass edgeing machine",
        "glass processing machine",
        "vertical edgeing machine",
        "glass drilling machine",
        "glass sandblasting machine",
        "glass tempering machine",
        "glass washing machine"};

    for (int i = 0; i < numMachines; ++i) {
        strcpy(machines[i].machineName, machineNames[i]);
    }

    // Read machine events from the file created by the first code
    readMachineEvents("machine_events.txt", machines, numMachines);

    // Display the menu for setting machine details
    displayMenu(machines, numMachines);

    return 0;
}

// Function to read machine events from the file
void readMachineEvents(const char *filename, struct MachineDetails machines[], int numMachines) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error opening file for reading machine events.\n");
        return;
    }

    // Read each line from the file
    char line[256]; // Adjust the buffer size as needed

    while (fgets(line, sizeof(line), file) != NULL) {
        // Extract machine name, event type, and machine state
        char machineName[50], eventType[50];
        if (sscanf(line, "%s %*s %[^\n]", machineName, eventType) == 2) {
            // Provide feedback for each event
            provideFeedback(machineName, eventType, machines->machineState, machines, numMachines);
        }
    }

    fclose(file);
}

// Function to display the menu for setting machine details
void displayMenu(struct MachineDetails machines[], int numMachines) {
    int choice;

    do {
        printf("\nMachine Settings Menu\n");
        printf("1. Set machine state for all machines\n");
        printf("2. Display machine details\n");
        printf("3. Export history to CSV\n");
        printf("4. Trigger emergency for a machine\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                setMachineState(machines, numMachines);
                break;
            case 2:
                printf("\nMachine Details:\n");
                for (int i = 0; i < numMachines; ++i) {
                    printf("%s - Electricity Usage: %.2lf, State: %s\n", machines[i].machineName, machines[i].electricityUsage, machines[i].machineState);
                }
                break;
            case 3:
                exportHistory(machines, numMachines);
                break;
            case 4:
                handleEmergency(machines, numMachines);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 5);
}

// Function to set machine state for all machines
void setMachineState(struct MachineDetails machines[], int numMachines) {
    for (int i = 0; i < numMachines; ++i) {
        printf("\nEnter state and worker name for %s (e.g., working/stopped, John): ", machines[i].machineName);
        scanf("%s", machines[i].machineState);
    }
}

// Function to provide feedback based on the machine event
void provideFeedback(const char *machineName, const char *eventType, const char *machineState, struct MachineDetails machines[], int numMachines) {
    // Add conditions for different event types and provide feedback
    if (strcmp(eventType, "Temperature Alert") == 0) {
        printf("%s: %s - Sending notification and turning on emergency for %s. Current State: %s\n", machineName, eventType, machineName, machineState);

        // Trigger emergency for the specified machine
        for (int i = 0; i < numMachines; ++i) {
            if (strcmp(machines[i].machineName, machineName) == 0) {
                handleEmergency(machines, numMachines);
                break;
            }
        }
    } else if (strcmp(eventType, "Pressure Drop") == 0) {
        printf("%s: %s - Perform maintenance to address pressure drop, sending notification. Current State: %s\n", machineName, eventType, machineState);
        // Add code for other event types as needed
    } else {
        // Default feedback for unknown event types
        printf("%s: %s - Turning on Emergency. Current State: %s\n", machineName, eventType, machineState);
    }
}

// Function to handle emergency for a specific machine and log to history file
void handleEmergency(struct MachineDetails machines[], int numMachines) {
    printf("\nTrigger Emergency\n");

    // Display a list of machines for the user to choose from
    printf("Available Machines:\n");
    for (int i = 0; i < numMachines; ++i) {
        printf("%d. %s\n", i + 1, machines[i].machineName);
    }

    printf("Enter the number of the machine for emergency: ");
    int choice;
    scanf("%d", &choice);

    // Validate the user's choice
    if (choice >= 1 && choice <= numMachines) {
        int machineIndex = choice - 1; // Adjust for zero-based array index

        // Get the machine name for the selected machine
        const char *emergencyMachineName = machines[machineIndex].machineName;

        printf("Emergency triggered for machine: %s\n", emergencyMachineName);

        // Log the emergency event to a history file
        FILE *historyFile = fopen("emergency_history.txt", "a");
        if (historyFile != NULL) {
            fprintf(historyFile, "%s Emergency Triggered\n", emergencyMachineName);
            fclose(historyFile);
        } else {
            printf("Error opening history file for logging.\n");
        }

        // Add code to handle the emergency for the specified machine
        // For example, you can update the machine state or perform other actions
    } else {
        printf("Invalid choice. Emergency not triggered.\n");
    }
}

// Function to export history to CSV
void exportHistory(struct MachineDetails machines[], int numMachines) {
    FILE *csvFile = fopen("history_export.csv", "w");

    if (csvFile == NULL) {
        printf("Error opening CSV file for writing.\n");
        return;
    }

    // Add header to the CSV file
    fprintf(csvFile, "Machine Name,Event,State\n");

    // Loop through machines and write history to the CSV file
    for (int i = 0; i < numMachines; ++i) {
        fprintf(csvFile, "%s,", machines[i].machineName);

        // Read history from the history file
        char historyLine[256];
        char historyFileName[50];
        sprintf(historyFileName, "%s_history.txt", machines[i].machineName);
        FILE *historyFile = fopen(historyFileName, "r");

        if (historyFile == NULL) {
            fprintf(csvFile, "No history available,");
        } else {
            // Read and write history to the CSV file
            while (fgets(historyLine, sizeof(historyLine), historyFile) != NULL) {
                fprintf(csvFile, "%s", historyLine);
            }
            fclose(historyFile);
        }

        // Write machine state to the CSV file
        fprintf(csvFile, "%s\n", machines[i].machineState);
    }

    fclose(csvFile);
    printf("History exported to history_export.csv\n");
}