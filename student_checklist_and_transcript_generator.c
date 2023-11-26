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

// function to clear screen
void clearScreen()
{
    printf("\033[H\033[J"); // ANSI escape codes to clear screen
}

int main(void) 
{
    // declare variables
    char option = 'M';
    int subjectCount = 5;
    double gwa = 1.75;

    do
    {
        // clear screen
        clearScreen();

        switch (option)
        {
            case '1':
                printf("\tStudent Checklist and Transcript Generator\n");
                printf("\t\tEnter Semestral Data\n");
                printf("\n");
                printf("Enter Semester (1 / 2 / S) => \n");
                printf("Enter Academic Year => 20   to 20  \n");
                printf("Enter Total Number of Subjects => \n");
                printf("\n");
                
                printf("Subject\t\tUnits\tGrade\n");
                for (int i = 0; i < subjectCount; i++)
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
                printf("\tUNIVERSITY OF THE PHILIPPINES BAGUIO\n");
                printf("\n");
                printf("\t\tSEMESTRAL GRADE REPORT\n");
                printf("\n");
                printf("Name: (NAME, FIRST NAME, MIDDLE NAME)\n");
                printf("Student Number: (STUDENT NO)\n");
                printf("Course: (COURSE)\n");
                printf("Year Level: (YEAR LEVEL)\n");
                printf("AY: (ACADEMIC YEAR)\n");
                printf("Semester: (1 / 2 / S)\n");
                printf("\n");
                
                printf("Subject\t\tUnits\tGrade\n");
                for (int i = 0; i < subjectCount; i++)
                {
                    printf("\n");
                }

                printf("\n");
                printf("GWA: \n");
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
                
                printf("\n");
                printf("Please Choose Option => \n");
                printf("\tM - Exit to Main Menu\n");
                printf("\tX - Exit Program\n");
                break;

            default: 
                printf("Invalid Input\n");
        }

        // prompt user to enter the next menu
        printf("Please Choose Option => ");
        scanf(" %c", &option);
        
    } while (option != 'X');
    

    return 0;
}