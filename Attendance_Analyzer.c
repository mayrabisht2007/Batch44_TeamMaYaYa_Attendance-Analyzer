/* Problem 7: Student Attendance Analyzer
Problem statement: Develop a program to record and analyze attendance for a class of students.
Requirements:
• Store attendance for at least 10 students across multiple classes.
• Record attendance as present or absent.
• Calculate each student's attendance percentage.
• Identify students below a specified attendance threshold, such as 75%.
Expected output: Student-wise attendance report and list of students below the threshold.#include <stddef.h>*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STUDENTS 10
#define MAX_CLASSES 10
#define SAP_LEN 9
#define THRESHOLD 75.0
void exitNoInput()
{
    printf("\nNo more input. Exiting.\n");
    exit(1);
}
int readPresentAbsent()
{
    char input[100];
    while (1)
    {
        if (scanf("%99s", input) != 1)
            exitNoInput();
        if (strlen(input) == 1)
        {
            if (input[0] == 'P' || input[0] == 'p')
                return 1;
            if (input[0] == 'A' || input[0] == 'a')
                return 0;
        }
        printf("Invalid! Enter only P or A: ");
    }
}
int readClasses()
{
    int n, r, ch;
    printf("Enter number of classes (1-10): ");
    while (1)
    {
        r = scanf("%d", &n);
        if (r == EOF)
            exitNoInput();
        if (r == 1 && n >= 1 && n <= MAX_CLASSES)
            return n;
        while ((ch = getchar()) != '\n' && ch != EOF);
        printf("Invalid! Enter number from 1 to 10: ");
    }
}
void readSAP(char sap[])
{
    int i;
    while (1)
    {
        if (scanf("%19s", sap) != 1)
            exitNoInput();
        if (strlen(sap) == SAP_LEN)
        {
            for (i = 0; i < SAP_LEN; i++)
            {
                if (sap[i] < '0' || sap[i] > '9')
                    break;
            }
            if (i == SAP_LEN)
                return;
        }
        printf("Invalid SAP ID! Enter exactly 9 digits: ");
    }
}
int isDuplicateSAP(char sap[][20], int count)
{
    int i;
    for (i = 0; i < count; i++)
    {
        if (strcmp(sap[count], sap[i]) == 0)
            return 1;
    }
    return 0;
}
void inputSAP(char sap[][20], int s)
{
    printf("Enter 9-digit SAP ID: ");
    while (1)
    {
        readSAP(sap[s]);
        if (!isDuplicateSAP(sap, s))
            return;
        printf("SAP ID already exists! Enter a different SAP ID: ");
    }
}
int inputAttendance(int attendance[], int classes)
{
    int c, present = 0;
    for (c = 0; c < classes; c++)
    {
        printf("Class %d (P/A): ", c + 1);
        attendance[c] = readPresentAbsent();
        if (attendance[c] == 1)
            present++;
    }
    return present;
}
float calculatePercentage(int present, int classes)
{
    return (present * 100.0f) / classes;
}
void inputStudent(char sap[][20], int attendance[][MAX_CLASSES],
 int presentCount[], float percent[], int s, int classes)
{
    printf("\n--- Student %d ---\n", s + 1);
    inputSAP(sap, s);
    presentCount[s] = inputAttendance(attendance[s], classes);
    percent[s] = calculatePercentage(presentCount[s], classes);
}
void inputAllStudents(char sap[][20], int attendance[][MAX_CLASSES],
 int presentCount[], float percent[], int classes)
{
    int s;
    for (s = 0; s < STUDENTS; s++)
        inputStudent(sap, attendance, presentCount, percent, s, classes);
}
void displayTitle()
{
    printf("===== STUDENT ATTENDANCE ANALYZER =====\n");
}
void displayStudentReport(const char sap[], const int attendance[],
 int present, int classes, float percent)
{
    int c;
    printf("\nSAP ID: %s\n", sap);
    printf("Attendance: ");
    for (c = 0; c < classes; c++)
        printf("%c ", attendance[c] ? 'P' : 'A');
    printf("\nPresent: %d/%d", present, classes);
    printf("\nPercentage: %.1f%%\n", percent);
}

void displayAllReports(char sap[][20], int attendance[][MAX_CLASSES],
 int presentCount[], float percent[], int classes)
{
    int s;
    printf("\n===== STUDENT ATTENDANCE REPORT =====\n");
    for (s = 0; s < STUDENTS; s++)
        displayStudentReport(sap[s], attendance[s], presentCount[s],
classes, percent[s]);
}
int displayBelowThreshold(char sap[][20], float percent[])
{
    int s, below = 0;
    printf("\n===== STUDENTS BELOW %.0f%% =====\n", THRESHOLD);
    for (s = 0; s < STUDENTS; s++)
    {
        if (percent[s] < THRESHOLD)
        {
            printf("SAP: %s | %.1f%%\n", sap[s], percent[s]);
            below++;
        }
    }
    if (below == 0)
        printf("No student is below %.0f%%.\n", THRESHOLD);
    return below;
}
void displaySummary(int below)
{
    printf("\nTotal below threshold: %d out of %d\n", below, STUDENTS);
}
int main()
{
    char sap[STUDENTS][20];
    int attendance[STUDENTS][MAX_CLASSES];
    int presentCount[STUDENTS];
    float percent[STUDENTS];
    int classes, below;
    displayTitle();
    classes = readClasses();
    inputAllStudents(sap, attendance, presentCount, percent, classes);
    displayAllReports(sap, attendance, presentCount, percent, classes);
    below = displayBelowThreshold(sap, percent);
    displaySummary(below);
    return 0;
}
