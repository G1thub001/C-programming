#include <stdio.h>
#include <float.h>

#define EMPLOYEES 5
#define FT 40
#define OT 1.5

typedef struct
{
    char firstName[30];
    char midInit;
    char lastName[30];
} Name;

typedef struct
{
    int month;
    int day;
    int year;
} Date;

typedef struct
{
    Name name;
    Date startDate;
    int id;
    float wage;
    float hours;
    float gross;
} Employee;

typedef struct
{
    float wageTotal;
    float hoursTotal;
    float grossTotal;
    float grossMin;
    float grossMax;
    float wageMin;
    float wageMax;
    float hoursMin;
    float hoursMax;
} Totals;

void getHours(Employee emps[]);
void calculateGross(Employee emps[]);
void printOutput(Employee emps[], Totals tots);
Totals accumulate(Employee emps[]);

int main()
{
    Employee employees[EMPLOYEES] =
        {
            {{"Alice", 'A', "Smith"}, {1, 1, 2022}, 1, 15.0},
            {{"Bob", 'B', "Johnson"}, {1, 1, 2022}, 2, 20.0},
            {{"Charlie", 'C', "Williams"}, {1, 1, 2022}, 3, 25.0},
            {{"David", 'D', "Brown"}, {1, 1, 2022}, 4, 30.0},
            {{"Eve", 'E', "Jones"}, {1, 1, 2022}, 5, 35.0}};
    Totals weeklyTotals = {0, 0, 0, FLT_MAX, FLT_MIN, FLT_MAX, FLT_MIN, FLT_MAX, FLT_MIN};

    printf("\n\tThis program calculates gross weekly pay.");
    printf("\n\tYou will be prompted for input for %i employees.\n\n", EMPLOYEES);

    getHours(employees);
    calculateGross(employees);
    weeklyTotals = accumulate(employees);
    printOutput(employees, weeklyTotals);

    return 0;
}

void getHours(Employee emps[])
{
    for (int i = 0; i < EMPLOYEES; i++)
    {
        printf("\tEnter the hours worked by employee %i: ", emps[i].id);
        scanf("%f", &emps[i].hours);
    }
}

void calculateGross(Employee emps[])
{
    for (int i = 0; i < EMPLOYEES; i++)
    {
        if (emps[i].hours > 0 && emps[i].hours <= FT)
        {
            emps[i].gross = emps[i].hours * emps[i].wage;
        }
        else if (emps[i].hours > FT && emps[i].hours < 168)
        {
            emps[i].gross = FT * emps[i].wage + (emps[i].hours - FT) * emps[i].wage * OT;
        }
        else if (emps[i].hours > 168)
        {
            printf("\t!! fraud alert: there are not that many hours in a week!");
            continue;
        }
        else // hours < 0
        {
            printf("\t!! alert: employee cannot work negative hours, setting gross to $0");
            emps[i].gross = 0;
        }
    }
}

void printOutput(Employee emps[], Totals tots)
{
    printf("\n\t------------------------------------------------------");
    printf("\n\tName\t\tID Num  Start Date   Wage   Hours        Gross");
    printf("\n\t-------------------------------------------------------");
    for (int i = 0; i < EMPLOYEES; i++)
    {
        printf("\n\t%s, %s %c. \t%06i %02i/%02i/%02i %6.2f %5.1f $ %7.2f",
               emps[i].name.lastName,
               emps[i].name.firstName,
               emps[i].name.midInit,
               emps[i].id,
               emps[i].startDate.month,
               emps[i].startDate.day,
               emps[i].startDate.year % 100,
               emps[i].wage,
               emps[i].hours,
               emps[i].gross);

        // Update total, min, max values
        tots.wageTotal += emps[i].wage;
        tots.hoursTotal += emps[i].hours;
        tots.grossTotal += emps[i].gross;
        if (emps[i].wage < tots.wageMin)
            tots.wageMin = emps[i].wage;
        if (emps[i].wage > tots.wageMax)
            tots.wageMax = emps[i].wage;
        if (emps[i].hours < tots.hoursMin)
            tots.hoursMin = emps[i].hours;
        if (emps[i].hours > tots.hoursMax)
            tots.hoursMax = emps[i].hours;
        if (emps[i].gross < tots.grossMin)
            tots.grossMin = emps[i].gross;
        if (emps[i].gross > tots.grossMax)
            tots.grossMax = emps[i].gross;
    }
    printf("\n\t-------------------------------------------------------");
    printf("\n\tTotals:\t\t\t\t   %6.2f %5.1f $ %7.2f",
           tots.wageTotal, tots.hoursTotal, tots.grossTotal);
    printf("\n\tAverage:\t\t\t\t%6.2f %5.1f $ %7.2f",
           tots.wageTotal / EMPLOYEES, tots.hoursTotal / EMPLOYEES, tots.grossTotal / EMPLOYEES);
    printf("\n\tMinimum:\t\t\t\t%6.2f %5.1f $ %7.2f",
           tots.wageMin, tots.hoursMin, tots.grossMin);
    printf("\n\tMaximum:\t\t\t\t%6.2f %5.1f $ %7.2f",
           tots.wageMax, tots.hoursMax, tots.grossMax);
    printf("\n\t----------------------------------------------------\n\n");
}

Totals accumulate(Employee emps[])
{
    Totals tots = {0, 0, 0, FLT_MAX, FLT_MIN, FLT_MAX, FLT_MIN, FLT_MAX, FLT_MIN};
    return tots;
}

