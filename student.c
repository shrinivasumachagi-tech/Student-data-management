#include <stdio.h>      // Standard input-output functions
#include <string.h>     // String handling functions
#include <ctype.h>      // Character type checking (isdigit)

/* =====================================================
   COLOR MACROS FOR TERMINAL OUTPUT (ANSI ESCAPE CODES)
   ===================================================== */
#define RED     "\033[1;31m"   // Red color (errors)
#define GREEN   "\033[1;32m"   // Green color (success)
#define YELLOW  "\033[1;33m"   // Yellow color (highlight)
#define BLUE    "\033[1;34m"   // Blue color (headings)
#define CYAN    "\033[1;36m"   // Cyan color (menu titles)
#define RESET   "\033[0m"      // Reset to default color

/* =====================================================
   STRUCTURE DEFINITION FOR STUDENT DATA
   ===================================================== */
struct student
{
    char name[20];     // Student name
    char add[60];      // Student address
    int id;             // Student ID
    char mob[11];       // Mobile number (10 digits + null)
};

/* =====================================================
   FUNCTION: valid_mobile
   PURPOSE : Validate mobile number
   - Must be exactly 10 digits
   - Must contain only digits
   - Must be unique
   ===================================================== */
int valid_mobile(char mob[], struct student arr[], int size, int skipIndex)
{
    // Check length
    if (strlen(mob) != 10)
        return 0;

    // Check each character is a digit
    for (int i = 0; i < 10; i++)
    {
        if (!isdigit(mob[i]))
            return 0;
    }

    // Check for duplicate mobile number
    for (int i = 0; i < size; i++)
    {
        if (i != skipIndex && strcmp(arr[i].mob, mob) == 0)
            return 0;
    }

    return 1; // Mobile number is valid
}

/* =====================================================
   FUNCTION: add_student
   PURPOSE : Add a new student record
   ===================================================== */
void add_student(struct student *arr, int *size)
{
    printf(CYAN "\n--- Add Student ---\n" RESET);

    // Read student name
    printf("Enter Name: ");
    scanf(" %19[^\n]", arr[*size].name);

    // Read student address
    printf("Enter Address: ");
    scanf(" %59[^\n]", arr[*size].add);

    // Read student ID
    printf("Enter ID: ");
    scanf("%d", &arr[*size].id);

    // Read and validate mobile number
    while (1)
    {
        printf("Enter Mobile Number (10 digits): ");
        scanf(" %10s", arr[*size].mob);

        if (valid_mobile(arr[*size].mob, arr, *size, -1))
            break;

        printf(RED "Invalid or duplicate mobile number!\n" RESET);
    }

    // Increase total student count
    (*size)++;

    printf(GREEN "✅ Student added successfully!\n" RESET);
}

/* =====================================================
   FUNCTION: print_all_student
   PURPOSE : Display all student records
   ===================================================== */
void print_all_student(struct student arr[], int size)
{
    if (size == 0)
    {
        printf(RED "No students found!\n" RESET);
        return;
    }

    printf(BLUE "\n--- Student List ---\n" RESET);
    for (int i = 0; i < size; i++)
    {
        printf(YELLOW "\nStudent %d\n" RESET, i + 1);
        printf("Name    : %s\n", arr[i].name);
        printf("Address : %s\n", arr[i].add);
        printf("ID      : %d\n", arr[i].id);
        printf("Mobile  : %s\n", arr[i].mob);
    }
}

/* =====================================================
   FUNCTION: search_student
   PURPOSE : Search student by ID or Name
   ===================================================== */
void search_student(struct student arr[], int size)
{
    int opt, id, found = 0;
    char name[20];

    printf(CYAN "\nSearch By:\n" RESET);
    printf("1. ID\n2. Name\nChoice: ");
    scanf("%d", &opt);

    // Search by ID
    if (opt == 1)
    {
        printf("Enter ID: ");
        scanf("%d", &id);

        for (int i = 0; i < size; i++)
        {
            if (arr[i].id == id)
            {
                found = 1;
                printf(GREEN "Student Found:\n" RESET);
                printf("%s | %s | %d | %s\n",
                       arr[i].name, arr[i].add, arr[i].id, arr[i].mob);
                break;
            }
        }
    }
    // Search by Name
    else if (opt == 2)
    {
        printf("Enter Name: ");
        scanf(" %19[^\n]", name);

        for (int i = 0; i < size; i++)
        {
            if (strcmp(arr[i].name, name) == 0)
            {
                found = 1;
                printf(GREEN "Student Found:\n" RESET);
                printf("%s | %s | %d | %s\n",
                       arr[i].name, arr[i].add, arr[i].id, arr[i].mob);
                break;
            }
        }
    }

    // If record not found
    if (!found)
        printf(RED "Student not found!\n" RESET);
}

/* =====================================================
   FUNCTION: update_student
   PURPOSE : Update student details
   ===================================================== */
void update_student(struct student arr[], int size)
{
    int opt, id;
    char temp[60];

    printf(CYAN "\nUpdate Menu:\n" RESET);
    printf("1. Name\n2. Address\n3. Mobile\nChoice: ");
    scanf("%d", &opt);

    printf("Enter Student ID: ");
    scanf("%d", &id);

    for (int i = 0; i < size; i++)
    {
        if (arr[i].id == id)
        {
            // Update name
            if (opt == 1)
            {
                printf("Enter New Name: ");
                scanf(" %19[^\n]", arr[i].name);
            }
            // Update address
            else if (opt == 2)
            {
                printf("Enter New Address: ");
                scanf(" %59[^\n]", arr[i].add);
            }
            // Update mobile number with validation
            else if (opt == 3)
            {
                while (1)
                {
                    printf("Enter New Mobile: ");
                    scanf(" %10s", temp);

                    if (valid_mobile(temp, arr, size, i))
                    {
                        strcpy(arr[i].mob, temp);
                        break;
                    }
                    printf(RED "Invalid or duplicate mobile!\n" RESET);
                }
            }

            printf(GREEN "✅ Record updated successfully!\n" RESET);
            return;
        }
    }

    printf(RED "Student not found!\n" RESET);
}

/* =====================================================
   FUNCTION: delete_student
   PURPOSE : Delete a student record by ID
   ===================================================== */
void delete_student(struct student arr[], int *size)
{
    int id;

    printf("Enter ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < *size; i++)
    {
        if (arr[i].id == id)
        {
            // Shift records left
            for (int j = i; j < *size - 1; j++)
                arr[j] = arr[j + 1];

            (*size)--;

            printf(GREEN "✅ Student deleted successfully!\n" RESET);
            return;
        }
    }

    printf(RED "Student not found!\n" RESET);
}

/* =====================================================
   FUNCTION: main
   PURPOSE : Program entry point
   ===================================================== */
int main()
{
    struct student arr[50];   // Array to store students
    int size = 0;             // Total students
    int opt;                  // Menu choice

    // Infinite loop for menu-driven program
    while (1)
    {
        printf(BLUE "\n========== STUDENT MANAGEMENT SYSTEM ==========\n" RESET);
        printf("1. Add Student\n");
        printf("2. Print All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &opt);

        // Perform operation based on user choice
        switch (opt)
        {
            case 1: add_student(arr, &size); break;
            case 2: print_all_student(arr, size); break;
            case 3: search_student(arr, size); break;
            case 4: update_student(arr, size); break;
            case 5: delete_student(arr, &size); break;
            case 6:
                printf(GREEN "Thank you!\n" RESET);
                return 0;
            default:
                printf(RED "Invalid choice!\n" RESET);
        }
    }
}
