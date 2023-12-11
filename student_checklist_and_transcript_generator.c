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

// subject struct
typedef struct
{
    char name[20];
    float unit;
    float grade;
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

// function to calculate student GWA
float getGWA(Student student, int sem)
{
    double totalUnit = 0, totalGradePoint = 0;
    for (int i = 0; i < student.semester[sem].subjectCount; i++)
    {
        totalUnit += student.semester[sem].subject[i].unit;
        totalGradePoint += (student.semester[sem].subject[i].grade * student.semester[sem].subject[i].unit);
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
        if (strlen(student.semester[sem].subject[i].name) < 8)
        {
            printf("%s\t\t\t%.2f\t%.2f\n", student.semester[sem].subject[i].name, student.semester[sem].subject[i].unit, student.semester[sem].subject[i].grade);
        }
        else if (strlen(student.semester[sem].subject[i].name) < 16)
        {
            printf("%s\t\t%.2f\t%.2f\n", student.semester[sem].subject[i].name, student.semester[sem].subject[i].unit, student.semester[sem].subject[i].grade);
        }
        else
        {
            printf("%s\t%.2f\t%.2f\n", student.semester[sem].subject[i].name, student.semester[sem].subject[i].unit, student.semester[sem].subject[i].grade);
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
    
    //declare variables
    char option = 'M', semOfYear;
    student.semesterCount = 0;
    int semester = 0;
    int i, j, yearStart, yearEnd;

    do
    {
        // clear screen
        clearScreen();

        switch (option)
        {
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

                    moveToPosition(9 + i, 25);
                    scanf("%f", &student.semester[currentSemester].subject[i].grade);
                    getchar();
                }

                moveToPosition(10 + student.semester[currentSemester].subjectCount, 25);
                scanf(" %c", &option);
                getchar();
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

                        moveToPosition(8, 25);
                        scanf(" %c", &option);
                        getchar();
                        break;
                    }
                }

                printf("ERROR: Can't find semester requested");
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

                moveToPosition(12, 25);
                scanf(" %c", &option);
                getchar();
                break;

            case 'R':
                printReport(student, semester);
                printf("\n");
                printf("Please Choose Option => \n");
                printf("\tM - Exit to Main Menu\n");
                printf("\tX - Exit Program\n");

                moveToPosition(16 + student.semester[semester].subjectCount, 25);
                scanf(" %c", &option);
                getchar();
                break;

            default: 
                printf("Invalid Input\n");
        }
    } 
    while (option != 'X');
    
    clearScreen();
    return 0;
}