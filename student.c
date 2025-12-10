#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* ===== COLOR MACROS ===== */
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define CYAN    "\033[1;36m"
#define RESET   "\033[0m"

struct student
{
    char name[20];
    char add[60];
    int id;
    char mob[11];   // 10 digits + '\0'
};

/* ===== MOBILE VALIDATION FUNCTION ===== */
int valid_mobile(char mob[], struct student arr[], int size, int skipIndex)
{
    if (strlen(mob) != 10)
        return 0;

    for (int i = 0; i < 10; i++)
    {
        if (!isdigit(mob[i]))
            return 0;
    }

    for (int i = 0; i < size; i++)
    {
        if (i != skipIndex && strcmp(arr[i].mob, mob) == 0)
            return 0;
    }

    return 1;
}

/* ===== ADD STUDENT ===== */
void add_student(struct student *arr, int *size)
{
    printf(CYAN "\n--- Add Student ---\n" RESET);

    printf("Enter Name: ");
    scanf(" %19[^\n]", arr[*size].name);

    printf("Enter Address: ");
    scanf(" %59[^\n]", arr[*size].add);

    printf("Enter ID: ");
    scanf("%d", &arr[*size].id);

    while (1)
    {
        printf("Enter Mobile Number (10 digits): ");
        scanf(" %10s", arr[*size].mob);

        if (valid_mobile(arr[*size].mob, arr, *size, -1))
            break;

        printf(RED "Invalid or duplicate mobile number!\n" RESET);
    }

    (*size)++;
    printf(GREEN "✅ Student added successfully!\n" RESET);
}

/* ===== PRINT ALL ===== */
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

/* ===== SEARCH ===== */
void search_student(struct student arr[], int size)
{
    int opt, id, found = 0;
    char name[20];

    printf(CYAN "\nSearch By:\n" RESET);
    printf("1. ID\n2. Name\nChoice: ");
    scanf("%d", &opt);

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

    if (!found)
        printf(RED "Student not found!\n" RESET);
}

/* ===== UPDATE ===== */
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
            if (opt == 1)
            {
                printf("Enter New Name: ");
                scanf(" %19[^\n]", arr[i].name);
            }
            else if (opt == 2)
            {
                printf("Enter New Address: ");
                scanf(" %59[^\n]", arr[i].add);
            }
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

/* ===== DELETE ===== */
void delete_student(struct student arr[], int *size)
{
    int id;

    printf("Enter ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < *size; i++)
    {
        if (arr[i].id == id)
        {
            for (int j = i; j < *size - 1; j++)
                arr[j] = arr[j + 1];

            (*size)--;
            printf(GREEN "✅ Student deleted successfully!\n" RESET);
            return;
        }
    }
    printf(RED "Student not found!\n" RESET);
}

/* ===== MAIN ===== */
int main()
{
    struct student arr[50];
    int size = 0, opt;

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

        switch (opt)
        {
            case 1: add_student(arr, &size); break;
            case 2: print_all_student(arr, size); break;
            case 3: search_student(arr, size); break;
            case 4: update_student(arr, size); break;
            case 5: delete_student(arr, &size); break;
            case 6: printf(GREEN "Thank you!\n" RESET); return 0;
            default: printf(RED "Invalid choice!\n" RESET);
        }
    }
}
