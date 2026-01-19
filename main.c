'#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h> // enable ANSI sequences on Windows console
#endif

// define color (ANSI escape sequences)
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

struct record {
    char name[50];
    int roll;
    float marks;
};

static void clear_stdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

static void strip_newline(char *s) {
    size_t len = strlen(s);
    if (len > 0 && s[len - 1] == '\n') s[len - 1] = '\0';
}

void addRecord(void) {
    struct record student;
    FILE *ptr = fopen("Neelakshi.txt", "ab");
    if (!ptr) {
        printf(RED "\nError: could not open file for appending\n" RESET);
        return;
    }

    int another = 1;
    while (another == 1) {
        printf(GREEN "\nEnter the name: " RESET);
        if (!fgets(student.name, sizeof(student.name), stdin)) {
            printf(RED "\nInput error\n" RESET);
            break;
        }
        strip_newline(student.name);

        printf(GREEN "Enter the Roll: " RESET);
        if (scanf("%d", &student.roll) != 1) {
            printf(RED "\nInvalid roll\n" RESET);
            clear_stdin();
            continue;
        }
        clear_stdin();

        printf(GREEN "Enter the marks: " RESET);
        if (scanf("%f", &student.marks) != 1) {
            printf(RED "\nInvalid marks\n" RESET);
            clear_stdin();
            continue;
        }
        clear_stdin();

        if (fwrite(&student, sizeof(student), 1, ptr) != 1) {
            printf(RED "\nError writing record\n" RESET);
        } else {
            printf(CYAN "\nRecord saved\n" RESET);
        }

        printf(RED "\nFor more record press 1, else press 0: " RESET);
        if (scanf("%d", &another) != 1) {
            another = 0;
        }
        clear_stdin();
    }

    fclose(ptr);
}

void showRecord(void) {
    struct record student;
    FILE *ptr = fopen("Neelakshi.txt", "rb");
    if (!ptr) {
        printf(YELLOW "\nNo records found (file not present)\n" RESET);
        return;
    }

    printf(CYAN "\n--- Student Records ---\n" RESET);
    while (fread(&student, sizeof(student), 1, ptr) == 1) {
        printf(YELLOW "\n%s\t%d\t%.2f" RESET, student.name, student.roll, student.marks);
    }
    printf("\n");

    fclose(ptr);
}

void searchRecord(void) {
    int r;
    struct record student;
    FILE *ptr = fopen("Neelakshi.txt", "rb");
    if (!ptr) {
        printf(YELLOW "\nNo records found (file not present)\n" RESET);
        return;
    }

    printf(GREEN "Enter the roll to search: " RESET);
    if (scanf("%d", &r) != 1) {
        clear_stdin();
        printf(RED "Invalid input\n" RESET);
        fclose(ptr);
        return;
    }
    clear_stdin();

    int found = 0;
    while (fread(&student, sizeof(student), 1, ptr) == 1) {
        if (student.roll == r) {
            printf(RED "\n%s\t%d\t%.2f\n" RESET, student.name, student.roll, student.marks);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf(YELLOW "\nRecord not found\n" RESET);
    }

    fclose(ptr);
}

void deleteRecord(void) {
    struct record student;
    FILE *ptr = fopen("Neelakshi.txt", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    if (!ptr || !temp) {
        printf(RED "\nError opening file(s)\n" RESET);
        if (ptr) fclose(ptr);
        if (temp) fclose(temp);
        return;
    }

    int r;
    printf(GREEN "\nEnter the roll number to delete: " RESET);
    if (scanf("%d", &r) != 1) {
        clear_stdin();
        printf(RED "Invalid input\n" RESET);
        fclose(ptr);
        fclose(temp);
        return;
    }
    clear_stdin();

    int found = 0;
    while (fread(&student, sizeof(student), 1, ptr) == 1) {
        if (student.roll != r) {
            fwrite(&student, sizeof(student), 1, temp);
        } else {
            found = 1;
            printf(RED "\nRecord Deleted: %s %d %.2f\n" RESET, student.name, student.roll, student.marks);
        }
    }

    fclose(ptr);
    fclose(temp);

    if (remove("Neelakshi.txt") != 0) {
        printf(RED "\nError removing original file\n" RESET);
    } else if (rename("temp.dat", "Neelakshi.txt") != 0) {
        printf(RED "\nError renaming temporary file\n" RESET);
    }

    if (!found) {
        printf(YELLOW "\nNo record found with that roll number!\n" RESET);
    } else {
        printf(CYAN "\nRecord successfully deleted\n" RESET);
    }
}

int main(void) {
#ifdef _WIN32
    // Enable ANSI escape sequences on Windows 10+ consoles
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD mode = 0;
        if (GetConsoleMode(hOut, &mode)) {
            SetConsoleMode(hOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
        }
    }
#endif

    int choice;
    do {
        printf(MAGENTA "\n\t\t\t\t Student Record System\n" RESET);
        printf(BLUE "\n\t\t\t\t Press 1: for Add Record" RESET);
        printf(BLUE "\n\t\t\t\t Press 2: for Show Record" RESET);
        printf(BLUE "\n\t\t\t\t Press 3: for Search Record" RESET);
        printf(BLUE "\n\t\t\t\t Press 4: for Delete Record" RESET);
        printf(BLUE "\n\t\t\t\t Press 5: for Exit" RESET);
        printf(YELLOW "\n\t\t\t\t Enter Your Choice: " RESET);

        if (scanf("%d", &choice) != 1) {
            clear_stdin();
            choice = 0;
        }
        clear_stdin();

        switch (choice) {
            case 1: addRecord(); break;
            case 2: showRecord(); break;
            case 3: searchRecord(); break;
            case 4: deleteRecord(); break;
            case 5: printf(GREEN "\n\t\t\t\t Exiting...\n" RESET); break;
            default: printf(RED "\n\t\t\t\t Wrong Choice..\n" RESET);
        }
    } while (choice != 5);

    return 0;
}'},