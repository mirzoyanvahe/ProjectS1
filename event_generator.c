#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// Define structures for data storage
struct MachineEvent {
    char machineName[50];
    char eventType[50];
};

// Function prototype
char *getCurrentTime();

// Define machine names
const char *machineNames[] = {
    "glass cutting machine",
    "glass edgeing machine",
    "glass processing machine",
    "vertical edgeing machine",
    "glass drilling machine",
    "glass sandblasting machine",
    "glass tempering machine",
    "glass washing machine"};

// Function to generate a random event for a specific machine
void generateRandomEvent(FILE *file, const char *machineName)
{
    srand(time(NULL));

    // Generate a random event for the specified machine
    int eventCode = rand() % 21; // Adjust the number of event types as needed
    char eventType[50];

    switch (eventCode)
    {
    case 0:
        sprintf(eventType, "Module Alarm");
        break;
    case 1:
        sprintf(eventType, "Temperature Alert");
        break;
    case 2:
        sprintf(eventType, "Vibration Issue");
        break;
    // Add more event types if needed
    case 3:
        sprintf(eventType, "Pressure Drop");
        break;
    case 4:
        sprintf(eventType, "Power Supply Failure");
        break;
    // Add more event types as needed
    case 5: // New event type: "Soft limit"
        sprintf(eventType, "Soft limit");
        break;
    default:
        sprintf(eventType, "Communication error");
        break;
    }

    char *currentTime = getCurrentTime();

    // Write the event to the file
    if (file != NULL) {
        fprintf(file, "%s %s: %s\n", currentTime, machineName, eventType);
        // Flush the file buffers to ensure content is written to the file
        fflush(file);
    } else {
        printf("Error writing to the file.\n");
    }

    // Free the allocated memory for the time string
    free(currentTime);
}

// Function to get the current time as a string
char *getCurrentTime()
{
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    // Allocate memory for the formatted time string
    char *buffer = (char *)malloc(30); // Adjust the buffer size as needed
    strftime(buffer, 30, "%H:%M", timeinfo);

    return buffer;
}

int main()
{
    // Open a file to write random events in append mode
    FILE *eventsFile = fopen("machine_events.txt", "a");

    if (eventsFile == NULL)
    {
        printf("Error opening file for writing events.\n");
        return 1;
    }

    // Define the number of machines
    int numMachines = 8; // Number of machine names provided

    // Prompt the user to input the interval in minutes
    int intervalMinutes;
    printf("Enter the interval in minutes (1-10): ");
    scanf("%d", &intervalMinutes);
    getchar(); // Consume the newline character

    if (intervalMinutes < 1 || intervalMinutes > 10)
    {
        printf("Invalid input. Please enter a valid interval.\n");
        fclose(eventsFile);
        return 1;
    }

    // Enter a loop to generate events at the specified interval until manually stopped
    while (1)
    {
        for (int j = 0; j < numMachines; ++j)
        {
            generateRandomEvent(eventsFile, machineNames[j]);
            sleep(intervalMinutes * 60); // Convert minutes to seconds
        }
    }

    // The loop will continue indefinitely until manually stopped
    // Close the file (this part may not be reached in this example)
    fclose(eventsFile);

    return 0;
}
