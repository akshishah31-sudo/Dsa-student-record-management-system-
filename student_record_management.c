/*
 * Student Record Management System Using a Singly Linked List
 * Language: C (C11)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 100
#define COURSE_LEN 100

typedef struct Student {
    int roll_no;
    char name[NAME_LEN];
    char course[COURSE_LEN];
    float cgpa;
    struct Student *next;
} Student;

static Student *head = NULL;

void clear_input_buffer(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        /* discard remaining input */
    }
}

void read_line(char *buffer, size_t size) {
    if (fgets(buffer, (int)size, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        } else {
            clear_input_buffer();
        }
    } else {
        buffer[0] = '\0';
    }
}

int read_int(const char *prompt, int *value) {
    char line[128];
    char extra;
    printf("%s", prompt);
    if (fgets(line, sizeof(line), stdin) == NULL) return 0;
    if (sscanf(line, "%d %c", value, &extra) != 1) {
        printf("Invalid input. Please enter a whole number.\n");
        return 0;
    }
    return 1;
}

int read_float(const char *prompt, float *value) {
    char line[128];
    char extra;
    printf("%s", prompt);
    if (fgets(line, sizeof(line), stdin) == NULL) return 0;
    if (sscanf(line, "%f %c", value, &extra) != 1) {
        printf("Invalid input. Please enter a numeric value.\n");
        return 0;
    }
    return 1;
}

Student *find_student(int roll_no) {
    Student *current = head;
    while (current != NULL) {
        if (current->roll_no == roll_no) return current;
        current = current->next;
    }
    return NULL;
}

void add_student(void) {
    int roll_no;
    float cgpa;
    char name[NAME_LEN];
    char course[COURSE_LEN];

    if (!read_int("Enter roll number: ", &roll_no)) return;
    if (roll_no <= 0) {
        printf("Roll number must be positive.\n");
        return;
    }
    if (find_student(roll_no) != NULL) {
        printf("A student with this roll number already exists.\n");
        return;
    }

    printf("Enter student name: ");
    read_line(name, sizeof(name));
    printf("Enter course: ");
    read_line(course, sizeof(course));

    if (!read_float("Enter CGPA (0.0 - 10.0): ", &cgpa)) return;
    if (cgpa < 0.0f || cgpa > 10.0f) {
        printf("CGPA must be between 0.0 and 10.0.\n");
        return;
    }

    Student *new_student = (Student *)malloc(sizeof(Student));
    if (new_student == NULL) {
        printf("Memory allocation failed. Student was not added.\n");
        return;
    }

    new_student->roll_no = roll_no;
    snprintf(new_student->name, sizeof(new_student->name), "%s", name);
    snprintf(new_student->course, sizeof(new_student->course), "%s", course);
    new_student->cgpa = cgpa;
    new_student->next = NULL;

    if (head == NULL) {
        head = new_student;
    } else {
        Student *current = head;
        while (current->next != NULL) current = current->next;
        current->next = new_student;
    }
    printf("Student record added successfully.\n");
}

void display_students(void) {
    Student *current = head;
    if (current == NULL) {
        printf("No student records found.\n");
        return;
    }

    printf("\n--- Student Records ---\n");
    while (current != NULL) {
        printf("Roll Number: %d\n", current->roll_no);
        printf("Name       : %s\n", current->name);
        printf("Course     : %s\n", current->course);
        printf("CGPA       : %.2f\n", current->cgpa);
        printf("-----------------------\n");
        current = current->next;
    }
}

void search_student(void) {
    int roll_no;
    if (!read_int("Enter roll number to search: ", &roll_no)) return;

    Student *student = find_student(roll_no);
    if (student == NULL) {
        printf("Student record not found.\n");
        return;
    }

    printf("\nStudent found:\n");
    printf("Roll Number: %d\n", student->roll_no);
    printf("Name       : %s\n", student->name);
    printf("Course     : %s\n", student->course);
    printf("CGPA       : %.2f\n", student->cgpa);
}

void update_student(void) {
    int roll_no;
    float cgpa;
    char name[NAME_LEN];
    char course[COURSE_LEN];

    if (!read_int("Enter roll number to update: ", &roll_no)) return;
    Student *student = find_student(roll_no);
    if (student == NULL) {
        printf("Student record not found.\n");
        return;
    }

    printf("Enter new student name: ");
    read_line(name, sizeof(name));
    printf("Enter new course: ");
    read_line(course, sizeof(course));
    if (!read_float("Enter new CGPA (0.0 - 10.0): ", &cgpa)) return;
    if (cgpa < 0.0f || cgpa > 10.0f) {
        printf("CGPA must be between 0.0 and 10.0.\n");
        return;
    }

    snprintf(student->name, sizeof(student->name), "%s", name);
    snprintf(student->course, sizeof(student->course), "%s", course);
    student->cgpa = cgpa;
    printf("Student record updated successfully.\n");
}

void delete_student(void) {
    int roll_no;
    if (!read_int("Enter roll number to delete: ", &roll_no)) return;

    Student *current = head;
    Student *previous = NULL;

    while (current != NULL && current->roll_no != roll_no) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Student record not found.\n");
        return;
    }

    if (previous == NULL) {
        head = current->next;
    } else {
        previous->next = current->next;
    }
    free(current);
    printf("Student record deleted successfully.\n");
}

void free_memory(void) {
    Student *current = head;
    while (current != NULL) {
        Student *next = current->next;
        free(current);
        current = next;
    }
    head = NULL;
}

int main(void) {
    int choice;

    do {
        printf("\n===== Student Record Management System =====\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("0. Exit\n");

        if (!read_int("Enter your choice: ", &choice)) {
            continue;
        }

        switch (choice) {
            case 1: add_student(); break;
            case 2: display_students(); break;
            case 3: search_student(); break;
            case 4: update_student(); break;
            case 5: delete_student(); break;
            case 0: printf("Exiting program. Goodbye!\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    free_memory();
    return 0;
}
