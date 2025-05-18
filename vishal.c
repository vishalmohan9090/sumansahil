#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LENGTH 50

typedef struct {
    int id;
    char name[NAME_LENGTH];
    float gpa;
} Student;

Student students[MAX_STUDENTS];
int student_count = 0;

// Function prototypes
void addStudent();
void displayStudents();
void searchStudentById();
void sortStudentsByGPA();
void saveToFile();
void loadFromFile();
void menu();

int main() {
    loadFromFile();  // Load existing data if any
    menu();
    saveToFile();    // Save data before exit
    return 0;
}

void menu() {
    int choice;
    do {
        printf("\n--- Student Management System ---\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student by ID\n");
        printf("4. Sort Students by GPA\n");
        printf("5. Save to File\n");
        printf("6. Load from File\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch(choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudentById(); break;
            case 4: sortStudentsByGPA(); break;
            case 5: saveToFile(); break;
            case 6: loadFromFile(); break;
            case 0: printf("Exiting...\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 0);
}

void addStudent() {
    if (student_count >= MAX_STUDENTS) {
        printf("Cannot add more students. Limit reached.\n");
        return;
    }

    Student s;
    printf("Enter student ID: ");
    scanf("%d", &s.id);
    getchar(); // consume newline
    printf("Enter name: ");
    fgets(s.name, NAME_LENGTH, stdin);
    s.name[strcspn(s.name, "\n")] = 0; // remove newline
    printf("Enter GPA: ");
    scanf("%f", &s.gpa);

    students[student_count++] = s;
    printf("Student added successfully.\n");
}

void displayStudents() {
    printf("\n%-10s %-20s %-5s\n", "ID", "Name", "GPA");
    for (int i = 0; i < student_count; i++) {
        printf("%-10d %-20s %-5.2f\n", students[i].id, students[i].name, students[i].gpa);
    }
}

void searchStudentById() {
    int id;
    printf("Enter student ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < student_count; i++) {
        if (students[i].id == id) {
            printf("Student found:\n");
            printf("ID: %d\nName: %s\nGPA: %.2f\n", students[i].id, students[i].name, students[i].gpa);
            return;
        }
    }
    printf("Student with ID %d not found.\n", id);
}

void sortStudentsByGPA() {
    for (int i = 0; i < student_count - 1; i++) {
        for (int j = 0; j < student_count - i - 1; j++) {
            if (students[j].gpa < students[j + 1].gpa) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    printf("Students sorted by GPA in descending order.\n");
}

void saveToFile() {
    FILE *file = fopen("students.dat", "wb");
    if (!file) {
        printf("Error saving data.\n");
        return;
    }
    fwrite(&student_count, sizeof(int), 1, file);
    fwrite(students, sizeof(Student), student_count, file);
    fclose(file);
    printf("Data saved successfully.\n");
}

void loadFromFile() {
    FILE *file = fopen("students.dat", "rb");
    if (!file) {
        printf("No existing data found.\n");
        return;
    }
    fread(&student_count, sizeof(int), 1, file);
    fread(students, sizeof(Student), student_count, file);
    fclose(file);
    printf("Data loaded successfully.\n");
}
