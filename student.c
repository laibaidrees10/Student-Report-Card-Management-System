#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int roll;
    char name[50];
    float marks[5]; 
    float average;
};

void calculateAverage(struct Student *s) {
    float total = 0;
    for (int i = 0; i < 5; i++) {
        total += s->marks[i];
    }
    s->average = total / 5;
}

void addStudent() {
    struct Student s;
    FILE *fp = fopen("students.txt", "ab");

    printf("Enter Roll Number: ");
    scanf("%d", &s.roll);
    getchar(); // clear newline
    printf("Enter Name: ");
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = 0;

    for (int i = 0; i < 5; i++) {
        printf("Enter marks for subject %d: ", i + 1);
        scanf("%f", &s.marks[i]);
    }

    calculateAverage(&s);
    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("Student record added.\n");
}

void displayStudents() {
    struct Student s;
    FILE *fp = fopen("students.txt", "rb");

    printf("\nAll Student Records:\n");
    printf("Roll\tName\t\tAverage\n");

    while (fread(&s, sizeof(s), 1, fp)) {
        printf("%d\t%s\t\t%.2f\n", s.roll, s.name, s.average);
    }

    fclose(fp);
}

void searchStudent() {
    struct Student s;
    int roll, found = 0;

    printf("Enter Roll Number to search: ");
    scanf("%d", &roll);

    FILE *fp = fopen("students.txt", "rb");
    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            printf("\nRecord Found:\n");
            printf("Name: %s\n", s.name);
            printf("Average: %.2f\n", s.average);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Record not found.\n");

    fclose(fp);
}

void updateMarks() {
    struct Student s;
    int roll, found = 0;

    printf("Enter Roll Number to update: ");
    scanf("%d", &roll);

    FILE *fp = fopen("students.txt", "rb+");
    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            printf("Enter new marks for 5 subjects:\n");
            for (int i = 0; i < 5; i++) {
                printf("Subject %d: ", i + 1);
                scanf("%f", &s.marks[i]);
            }
            calculateAverage(&s);

            fseek(fp, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);
            found = 1;
            break;
        }
    }

    if (found)
        printf("Record updated.\n");
    else
        printf("Record not found.\n");

    fclose(fp);
}

void deleteStudent() {
    struct Student s;
    int roll, found = 0;

    printf("Enter Roll Number to delete: ");
    scanf("%d", &roll);

    FILE *fp = fopen("students.txt", "rb");
    FILE *temp = fopen("temp.txt", "wb");

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            found = 1;
            continue;
        }
        fwrite(&s, sizeof(s), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        printf("Record deleted.\n");
    else
        printf("Record not found.\n");
}

int main() {
    int choice;

    do {
        printf("\n===== Student Report Card System =====\n");
        printf("1. Add Student\n");
        printf("2. View All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Marks\n");
        printf("5. Delete Student\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateMarks(); break;
            case 5: deleteStudent(); break;
            case 0: printf("Exiting...\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);

    return 0;
}
