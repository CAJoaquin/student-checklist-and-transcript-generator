/*********************************************************************************************
 
file name: student_checklist_and_transcript_generator.c

----------------------------------------------------------------------------------------------
 
Purpose: Generate either a semestral GWA report, a full checklist, or an overall transcript.
Author: Charles Ansbert P. Joaquin
Creation Date: 10 November 2023
 
Instructions: 
    The “Student Checklist and Transcript Generator” is a system that allows a single user
    to input a student’s grades obtained for one or more semesters, with the option to
    generate either a semestral GWA report, a full checklist, or an overall transcript.
 
**********************************************************************************************/
#include <stdio.h>
#include <string.h>

// semester struct
typedef struct
{
    char sem;
    int yearStart;
    int yearEnd;
    int subjectCount;
} Semester;

// subject struct
typedef struct
{
    char name[20];
    float unit;
    float grade;
} Subject;

// student struct
typedef struct
{
    char lastName[20];
    char firstName[20];
    char middleName[20];
    int studentNumber;
    char course[30];
    int year;
    int semesterCount;
    Semester semester[15];
    Subject subject[15];
} Student;


// function to clear screen
void clearScreen()
{
    printf("\033[H\033[J"); // ANSI escape codes to clear screen
}

// function to calculate student GWA
float getGWA(Student student, int sem)
{
    double totalUnit = 0, totalGradePoint = 0;
    for (int i = 0; i < student.semester[sem].subjectCount; i++)
    {
        totalUnit += student.subject[i].unit;
        totalGradePoint += (student.subject[i].grade * student.subject[i].unit);
    }
    return totalGradePoint / totalUnit;
}

// function to display Semestral Grade Report
void printReport(Student student, int sem)
{
    printf("\tUNIVERSITY OF THE PHILIPPINES BAGUIO\n");
    printf("\n");
    printf("\t\tSEMESTRAL GRADE REPORT\n");
    printf("\n");
    printf("Name: %s, %s, %s\n", student.lastName, student.firstName, student.middleName);
    printf("Student Number: %i\n", student.studentNumber);
    printf("Course: %s\n", student.course);
    printf("Year Level: %i\n", student.year);
    printf("AY: %i-%i\n", student.semester[sem].yearStart, student.semester[sem].yearEnd);
    printf("Semester: %c\n", student.semester[sem].sem);
    printf("\n");
    
    printf("Subject\t\t\tUnits\tGrade\n");
    for (int i = 0; i < student.semester[sem].subjectCount; i++)
    {
        if (strlen(student.subject[i].name) < 8)
        {
            printf("%s\t\t\t%.2f\t%.2f\n", student.subject[i].name, student.subject[i].unit, student.subject[i].grade);
        }
        else if (strlen(student.subject[i].name) < 16)
        {
            printf("%s\t\t%.2f\t%.2f\n", student.subject[i].name, student.subject[i].unit, student.subject[i].grade);
        }
        else
        {
            printf("%s\t%.2f\t%.2f\n", student.subject[i].name, student.subject[i].unit, student.subject[i].grade);
        }
    }

    double gwa = getGWA(student, sem);

    printf("\n");
    printf("GWA: %.2f", gwa);
    printf("\n");
    
    if (gwa <= 1.45) 
    {
        printf("CONGRATULATIONS!\n");
        printf("You have qualified as a University Scholar.");
    }
    else if (gwa <= 1.75) 
    {
        printf("CONGRATULATIONS!\n");
        printf("You have qualified as a College Scholar.\n");
    }
}

int main(void) 
{
    // declare student
    Student student;

    // *temp* declare variables
    strcpy(student.lastName, "Joaquin");
    strcpy(student.firstName, "Charles Ansbert");
    strcpy(student.middleName, "Palapas");
    student.studentNumber = 202235278;
    strcpy(student.course, "BS Computer Science");
    student.year = 2;

    student.semester[0].sem = '1';
    student.semester[0].yearStart = 23;
    student.semester[0].yearEnd = 24;
    student.semester[0].subjectCount = 4;

    strcpy(student.subject[0].name, "CMSC 55");
    student.subject[0].unit = 5;
    student.subject[0].grade = 1.75;

    strcpy(student.subject[1].name, "HIST I");
    student.subject[1].unit = 3;
    student.subject[1].grade = 3;

    strcpy(student.subject[2].name, "MATH 10");
    student.subject[2].unit = 3;
    student.subject[2].grade = 1.5;

    strcpy(student.subject[3].name, "MATH 53");
    student.subject[3].unit = 5;
    student.subject[3].grade = 2;
    
    //declare variables
    char option = 'M';
    student.semesterCount = 0;
    int sem;

    do
    {
        // clear screen
        clearScreen();

        switch (option)
        {
            case '1':
                student.semesterCount ++;
                printf("\tStudent Checklist and Transcript Generator\n");
                printf("\t\tEnter Semestral Data\n");
                printf("\n");
                printf("Enter Semester (1 / 2 / S) => \n");
                printf("Enter Academic Year => 20   to 20  \n");
                printf("Enter Total Number of Subjects => \n");
                printf("\n");
                
                printf("Subject\t\tUnits\tGrade\n");
                for (int i = 0; i < student.semester[student.semesterCount].subjectCount; i++)
                {
                    printf("\n");
                }

                printf("Please Choose Option => \n");
                printf("\t1 - Enter Semestral Data\n");
                printf("\tM - Exit to Main Menu\n");
                break;
            
            case '2':
                printf("\tStudent Checklist and Transcript Generator\n");
                printf("\t\tGenerate Semestral GWA Report\n");
                printf("\n");
                printf("Enter AY and Semester to Generate:\n");
                printf("\tAY 20   to 20  \n");
                printf("\tSEMESTER => \n");
                printf("\n");
                printf("Please Choose Option => \n");
                printf("\t1 - Generate Report\n");
                printf("\tM - Exit to Main Menu\n");
                break;
            
            case '3':
                printf("Case 3\n");
                break;

            case '4':
                printf("Case 4\n");
                break;

            case 'M':
                printf("\tStudent Checklist and Transcript Generator\n");
                printf("\t\t\tMain Menu\n");
                printf("\n");
                printf("Student Name\n");
                printf("\tLast Name => \n");
                printf("\tFirst Name => \n");
                printf("\tMiddle Name => \n");
                printf("Student Number => \n");
                printf("Course => \n");
                printf("Year Level => \n");
                printf("\n");
                printf("Please Choose Option => \n");
                printf("\t1 - Enter Semestral Data\n");
                printf("\t2 - Generate Semestral GWA Report\n");
                printf("\t3 - Generate Full Transcirpt\n");
                printf("\t4 - Generate Full Checklist\n");
                printf("\tX - Exit Program\n");
                break;

            case 'R':
                sem = 0; // *temp*
                printReport(student, sem);
                printf("\n");
                printf("Please Choose Option => \n");
                printf("\tM - Exit to Main Menu\n");
                printf("\tX - Exit Program\n");
                break;

            default: 
                printf("Invalid Input\n");
        }

        // *temp* prompt user to enter the next menu
        printf("Please Choose Option => ");
        scanf(" %c", &option);
        
    } 
    while (option != 'X');
    

    return 0;
}