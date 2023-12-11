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
#include <stdlib.h>
#include <string.h>

// subject struct
typedef struct
{
    char name[20];
    float unit;
    char grade[6];
} Subject;

// semester struct
typedef struct
{
    char sem;
    int yearStart;
    int yearEnd;
    int subjectCount;
    Subject subject[15];
} Semester;

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
} Student;

// function to clear screen
void clearScreen()
{
    printf("\033[H\033[J"); // ANSI escape codes to clear screen
}

// function to manipulate cursor position
void moveToPosition(int line, int column)
{
    printf("\033[%i;%iH", line, column);
}

// function to remove next line
void cleanString(char *c)
{
	for (int i = 0; c[i] != '\0'; i++)
	{
		if (c[i] == '\n')
		{
			c[i] = '\0';
		}
	}
}

// function to check if the entered grade is valid
int isValidGrade(const char *grade)
{
    // Check for numerical grades
    float numInput = atof(grade);
    if ((numInput >= 1.00 && numInput <= 3.00 && ((int)(numInput * 100) % 25 == 0)) || numInput == 4.00 || numInput == 5.00) 
    {
        return 1; // Valid numerical grade
    }

    // Check for non-numerical grades
    if (strcmp(grade, "INC") == 0 || strcmp(grade, "DRP") == 0) 
    {
        return 1; // Valid non-numerical grade
    }

    return 0; // Invalid grade
}

// function to calculate student GWA
float getGWA(Student student, int semester)
{
    double totalUnit = 0, totalGradePoint = 0;
    for (int i = 0; i < student.semester[semester].subjectCount; i++)
    {
        float grade = atof(student.semester[semester].subject[i].grade);
        if ((grade >= 1.00 && grade <= 3.00 && ((int)(grade * 100) % 25 == 0)) || grade == 4.00 || grade == 5.00)
        {
            totalUnit += student.semester[semester].subject[i].unit;
            totalGradePoint += (grade * student.semester[semester].subject[i].unit);
        }
    }
    return totalGradePoint / totalUnit;
}

// function to display Semestral Grade Report
void printReport(Student student, int semester)
{
    float numGrade;
    printf("\tUNIVERSITY OF THE PHILIPPINES BAGUIO\n");
    printf("\n");
    printf("\t\tSEMESTRAL GRADE REPORT\n");
    printf("\n");
    printf("Name: %s, %s, %s\n", student.lastName, student.firstName, student.middleName);
    printf("Student Number: %i\n", student.studentNumber);
    printf("Course: %s\n", student.course);
    printf("Year Level: %i\n", student.year);
    printf("AY: %i-%i\n", student.semester[semester].yearStart, student.semester[semester].yearEnd);
    printf("Semester: %c\n", student.semester[semester].sem);
    printf("\n");
    
    printf("Subject\t\t\tUnits\tGrade\n");
    for (int i = 0; i < student.semester[semester].subjectCount; i++)
    {
        numGrade = atof(student.semester[semester].subject[i].grade);

        if (strlen(student.semester[semester].subject[i].name) < 8)
        {
            if (strcmp(student.semester[semester].subject[i].grade, "INC") == 0 || strcmp(student.semester[semester].subject[i].grade, "DRP") == 0)
            {
                printf("%s\t\t\t%.2f\t%s\n", student.semester[semester].subject[i].name, student.semester[semester].subject[i].unit, student.semester[semester].subject[i].grade);
            }
            else
            {
                printf("%s\t\t\t%.2f\t%.2f\n", student.semester[semester].subject[i].name, student.semester[semester].subject[i].unit, numGrade);
            }
        }
        else if (strlen(student.semester[semester].subject[i].name) < 16)
        {
            if (strcmp(student.semester[semester].subject[i].grade, "INC") == 0 || strcmp(student.semester[semester].subject[i].grade, "DRP") == 0)
            {
                printf("%s\t\t%.2f\t%s\n", student.semester[semester].subject[i].name, student.semester[semester].subject[i].unit, student.semester[semester].subject[i].grade);
            }
            else
            {
                printf("%s\t\t%.2f\t%.2f\n", student.semester[semester].subject[i].name, student.semester[semester].subject[i].unit, numGrade);
            }
        }
        else
        {
            if (strcmp(student.semester[semester].subject[i].grade, "INC") == 0 || strcmp(student.semester[semester].subject[i].grade, "DRP") == 0)
            {
                printf("%s\t%.2f\t%s\n", student.semester[semester].subject[i].name, student.semester[semester].subject[i].unit, student.semester[semester].subject[i].grade);
            }
            else
            {
                printf("%s\t%.2f\t%.2f\n", student.semester[semester].subject[i].name, student.semester[semester].subject[i].unit, numGrade);
            }
        }
    }

    double gwa = getGWA(student, semester);

    printf("\n");
    printf("GWA: %.2f\n", gwa);
    printf("\n");
    
    if (gwa <= 1.45) 
    {
        printf("CONGRATULATIONS!\n");
        printf("You have qualified as a University Scholar.\n");
        printf("\n");
    }
    else if (gwa <= 1.75) 
    {
        printf("CONGRATULATIONS!\n");
        printf("You have qualified as a College Scholar.\n");
        printf("\n");
    }
}

int main(void) 
{
    // declare student
    Student student;
    
    //declare variables
    char option = '0', semOfYear;
    student.semesterCount = 0;
    int semester = 0;
    int i, j, yearStart, yearEnd, congratulatory, foundSemester;

    do
    {
        // clear screen
        clearScreen();

        switch (option)
        {
            // Screen 0 - Main Menu and Student Data
            case '0':
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
                
                moveToPosition(5, 22);
                fgets(student.lastName, 20, stdin);
                cleanString(student.lastName);

                moveToPosition(6, 23);
                fgets(student.firstName, 20, stdin);
                cleanString(student.firstName);

                moveToPosition(7, 24);
                fgets(student.middleName, 20, stdin);
                cleanString(student.middleName);

                moveToPosition(8, 19);
                scanf("%i", &student.studentNumber);
                getchar();

                moveToPosition(9, 11);
                fgets(student.course, 30, stdin);
                cleanString(student.course);

                moveToPosition(10, 15);
                scanf("%i", &student.year);
                getchar();

                do
                {
                    moveToPosition(12, 25);
                    scanf(" %c", &option);
                    getchar();
                    if (option != '1' && option != '2' && option != '3' && option != '4' && option != 'X')
                    {
                        moveToPosition(19, 1);
                        printf("Error: Invalid Input. Please enter a valid option.");
                    }
                }
                while (option != '1' && option != '2' && option != '3' && option != '4' && option != 'X');

                break;
            
            // Screen 1 - Enter Semestral Data
            case '1':
                student.semesterCount ++;
                int currentSemester = student.semesterCount - 1;
                printf("\tStudent Checklist and Transcript Generator\n");
                printf("\t\tEnter Semestral Data\n");
                printf("\n");
                printf("Enter Semester (1 / 2 / S) => \n");
                printf("Enter Academic Year => 20   to 20  \n");
                printf("Enter Total Number of Subjects => \n");

                moveToPosition(4, 31);
                scanf("%c", &student.semester[currentSemester].sem);
                getchar();

                moveToPosition(5, 26);
                scanf("%i", &student.semester[currentSemester].yearStart);
                getchar();

                moveToPosition(5, 34);
                scanf("%i", &student.semester[currentSemester].yearEnd);
                getchar();

                moveToPosition(6, 35);
                scanf("%i", &student.semester[currentSemester].subjectCount);
                getchar();

                printf("\n");
                printf("Subject\t\tUnits\tGrade\n");
                for (i = 0; i < student.semester[currentSemester].subjectCount; i++)
                {
                    printf("\n");
                }

                printf("\n");
                printf("Please Choose Option => \n");
                printf("\t1 - Enter Semestral Data\n");
                printf("\tM - Exit to Main Menu\n");

                for (i = 0; i < student.semester[currentSemester].subjectCount; i++)
                {
                    moveToPosition(9 + i, 1);
                    fgets(student.semester[currentSemester].subject[i].name, 20, stdin);
                    cleanString(student.semester[currentSemester].subject[i].name);

                    moveToPosition(9 + i, 17);
                    scanf("%f", &student.semester[currentSemester].subject[i].unit);
                    getchar();

                    do 
                    {
                        moveToPosition(9 + i, 25);
                        fgets(student.semester[currentSemester].subject[i].grade, 6, stdin);
                        cleanString(student.semester[currentSemester].subject[i].grade);
                        if (isValidGrade(student.semester[currentSemester].subject[i].grade) == 0)
                        {
                            moveToPosition(9 + i, 25);
                            printf("                                                      ");
                            moveToPosition(14 + student.semester[currentSemester].subjectCount, 1);
                            printf("Error: Invalid Input. Please enter a valid grade.");
                        }
                    }
                    while (isValidGrade(student.semester[currentSemester].subject[i].grade) == 0);
                    moveToPosition(14 + student.semester[currentSemester].subjectCount, 1);
                    printf("                                                      ");
                }
                
                do
                {
                    moveToPosition(10 + student.semester[currentSemester].subjectCount, 25);
                    scanf(" %c", &option);
                    getchar();
                    if (option != '1' && option != 'M')
                    {
                        moveToPosition(14 + student.semester[currentSemester].subjectCount, 1);
                        printf("Error: Invalid Input. Please enter a valid option.");
                    }
                }
                while (option != '1' && option != 'M');
                break;
            
            // Screen 2 - Generate GWA
            case '2':
                foundSemester = 0;
                
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

                moveToPosition(5, 14);
                scanf("%d", &yearStart);
                getchar();

                moveToPosition(5, 22);
                scanf("%d", &yearEnd);
                getchar();

                moveToPosition(6, 21);
                scanf(" %c", &semOfYear);
                getchar();

                for (i = 0; i  < student.semesterCount; i++)
                {
                    if (yearStart == student.semester[i].yearStart && yearEnd == student.semester[i].yearEnd && semOfYear == student.semester[i].sem)
                    {
                        semester = i;

                        do
                        {
                            moveToPosition(8, 25);
                            scanf(" %c", &option);
                            getchar();
                            if (option != '1' && option != 'M')
                            {
                                moveToPosition(12, 1);
                                printf("Error: Invalid Input. Please enter a valid option.");
                            }
                        }
                        while (option != '1' && option != 'M');

                        if (option == '1')
                        {
                            option = 'R';
                        }
                        foundSemester = 1;
                    }
                }

                if (foundSemester == 0)
                {
                    moveToPosition(9, 13);
                    printf("Enter Semestral Data\n");
                    moveToPosition(12, 1);
                    printf("ERROR: Can't find semester requested\n");
                    do
                    {
                        moveToPosition(8, 25);
                        scanf(" %c", &option);
                        getchar();
                        if (option != '1' && option != 'M')
                        {
                            moveToPosition(12, 1);
                            printf("Error: Invalid Input. Please enter a valid option.");
                        }
                    }
                    while (option != '1' && option != 'M');
                }

                break;
            
            // Screen 3 - Generate Full Transcript
            case '3':
                printf("UNDER CONSTRUCTION\n");
                printf("\n");
                printf("Please Choose Option => \n");
                printf("\t1 - Enter Semestral Data\n");
                printf("\t2 - Generate Semestral GWA Report\n");
                printf("\t3 - Generate Full Transcirpt\n");
                printf("\t4 - Generate Full Checklist\n");
                printf("\tX - Exit Program\n");

                do
                {
                    moveToPosition(3, 25);
                    scanf(" %c", &option);
                    getchar();
                    if (option != '1' && option != '2' && option != '3' && option != '4' && option != 'X')
                    {
                        moveToPosition(19, 1);
                        printf("Error: Invalid Input. Please enter a valid option.");
                    }
                }
                while (option != '1' && option != '2' && option != '3' && option != '4' && option != 'X');
                break;

            // Screen 4 - Generate Full Checklist
            case '4':
                printf("UNDER CONSTRUCTION\n");
                printf("\n");
                printf("Please Choose Option => \n");
                printf("\t1 - Enter Semestral Data\n");
                printf("\t2 - Generate Semestral GWA Report\n");
                printf("\t3 - Generate Full Transcirpt\n");
                printf("\t4 - Generate Full Checklist\n");
                printf("\tX - Exit Program\n");

                do
                {
                    moveToPosition(3, 25);
                    scanf(" %c", &option);
                    getchar();
                    if (option != '1' && option != '2' && option != '3' && option != '4' && option != 'X')
                    {
                        moveToPosition(19, 1);
                        printf("Error: Invalid Input. Please enter a valid option.");
                    }
                }
                while (option != '1' && option != '2' && option != '3' && option != '4' && option != 'X');
                break;

            // Screen M - Main Menu
            case 'M':
                printf("\tStudent Checklist and Transcript Generator\n");
                printf("\t\t\tMain Menu\n");
                printf("\n");
                printf("Student Name\n");
                printf("\tLast Name => %s\n", student.lastName);
                printf("\tFirst Name => %s\n", student.firstName);
                printf("\tMiddle Name => %s\n", student.middleName);
                printf("Student Number => %i\n", student.studentNumber);
                printf("Course => %s\n", student.course);
                printf("Year Level => %i\n", student.year);
                printf("\n");
                printf("Please Choose Option => \n");
                printf("\t1 - Enter Semestral Data\n");
                printf("\t2 - Generate Semestral GWA Report\n");
                printf("\t3 - Generate Full Transcirpt\n");
                printf("\t4 - Generate Full Checklist\n");
                printf("\tX - Exit Program\n");

                do
                {
                    moveToPosition(12, 25);
                    scanf(" %c", &option);
                    getchar();
                    if (option != '1' && option != '2' && option != '3' && option != '4' && option != 'X')
                    {
                        moveToPosition(19, 1);
                        printf("Error: Invalid Input. Please enter a valid option.");
                    }
                }
                while (option != '1' && option != '2' && option != '3' && option != '4' && option != 'X');
                break;
          
            // Screen R - Semestral Grade Report
            case 'R':
                printReport(student, semester);
                printf("Please Choose Option => \n");
                printf("\tM - Exit to Main Menu\n");
                printf("\tX - Exit Program\n");

                double gwa = getGWA(student, semester);
                congratulatory = 0;
                if (gwa <= 1.75) 
                {
                    congratulatory = 3;
                }

                do
                {
                    moveToPosition(16 + student.semester[semester].subjectCount + congratulatory, 25);
                    scanf(" %c", &option);
                    getchar();
                    if (option != 'X' && option != 'M')
                    {
                        moveToPosition(20 + student.semester[currentSemester].subjectCount + congratulatory, 1);
                        printf("Error: Invalid Input. Please enter a valid option.");
                    }
                }
                while (option != 'X' && option != 'M');
                break;

            // default
            default: 
                printf("Invalid Input\n");
        }
    } 
    while (option != 'X');
    
    clearScreen();
    return 0;
}