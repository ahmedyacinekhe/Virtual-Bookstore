#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TITLE_LENGTH 100
#define NAME_LENGTH 50

typedef struct Book {
    int id;
    char title[TITLE_LENGTH];
    char author[NAME_LENGTH];
    int available;
    int studentId;
    struct Book* next;
} Book;

typedef struct Student {
    int id;
    char lastName[NAME_LENGTH];
    char firstName[NAME_LENGTH];
    struct Student* next;
} Student;

Book* library = NULL;
Student* studentsList = NULL;
int bookIdCounter = 1;
int studentIdCounter = 1;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void waitForEnter() {
    printf("\nPress Enter to return to menu...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    getchar();
}

Student* findStudent(int id);
void displayBooks();

void addBook() {
        int quantity;
    char newBookTitle[NAME_LENGTH];
    char newBookAuthor[NAME_LENGTH];

    //Reading the new book title:
    printf("\nEnter the book title: ");
    getchar();
    fgets(newBookTitle, TITLE_LENGTH, stdin);
    newBookTitle[strcspn(newBookTitle, "\n")] = 0;

    //Reading the author's name of the new book:
    printf("Enter the author's name: ");
    fgets(newBookAuthor, NAME_LENGTH, stdin);
    newBookAuthor[strcspn(newBookAuthor, "\n")] = 0;

    //Reading the quantity that the user needs to add
    printf("\nEnter the number of books that you want to add with the same title: ");
    scanf("%d", &quantity);

    for(int i=1; i<=quantity; i++){
        Book* newBook = (Book*)malloc(sizeof(Book));

        //Checking for allocation failure:
        if (!newBook) {
            printf("\nMemory allocation failed!\n");
            return;
        }

        //Setting the book title:
        strcpy(newBook->title, newBookTitle);

        //Setting the book author's name:
        strcpy(newBook->author, newBookAuthor);

        //Setting the availability:
        newBook->available = 1;

        //Resetting the student ID to 0:
        newBook->studentId = 0;

        //Assigning an ID number to the new book:
        newBook->id = bookIdCounter++;
        //Connecting the new book to the library list, making it the head of the library list:
        newBook->next = library;
        library = newBook;
    }

    clearScreen();
    //Confirmation message for the user:
    printf("\n%d books has been added successfully!\n",quantity);
    waitForEnter();
}

void displayBooks() {
    clearScreen();
    if (!library) {
        printf("No books in the library.\n");
    } else {
        printf("Library Book List:\n");
        Book* current = library;
        while (current) {
            printf("ID: %d, Title: %s, Author: %s, Available: %s",
                   current->id,
                   current->title,
                   current->author,
                   current->available ? "Yes" : "No");
            if (!current->available) {
                Student* student = findStudent(current->studentId);
                if (student) {
                    printf(", Borrowed by: ID: %d, Name: %s %s",
                           student->id,
                           student->lastName,
                           student->firstName);
                } else {
                    printf(", Borrowed by unknown student (ID: %d)", current->studentId);
                }
            }
            printf("\n");
            current = current->next;
        }
    }
    waitForEnter();
}

Student* findStudent(int id) {
    Student* current = studentsList;
    while (current) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void borrowBook() {
    int bookId, studentId;
    clearScreen();
    printf("Enter book ID to borrow: ");
    scanf("%d", &bookId);
    while (getchar() != '\n');

    Book* currentBook = library;
    while (currentBook) {
        if (currentBook->id == bookId) {
            if (!currentBook->available) {
                clearScreen();
                printf("Book is already borrowed.\n");
                waitForEnter();
                return;
            }
            clearScreen();
            printf("Enter student ID: ");
            scanf("%d", &studentId);
            while (getchar() != '\n');

            if (!findStudent(studentId)) {
                clearScreen();
                printf("Student not found!\n");
                waitForEnter();
                return;
            }

            currentBook->available = 0;
            currentBook->studentId = studentId;
            clearScreen();
            printf("Book '%s' borrowed successfully!\n", currentBook->title);
            waitForEnter();
            return;
        }
        currentBook = currentBook->next;
    }

    clearScreen();
    printf("Invalid book ID.\n");
    waitForEnter();
}

void returnBook() {
    int id;
    clearScreen();
    printf("Enter book ID to return: ");
    scanf("%d", &id);
    while (getchar() != '\n');

    Book* current = library;
    while (current) {
        if (current->id == id) {
            if (current->available) {
                clearScreen();
                printf("Book is already in the library.\n");
                waitForEnter();
                return;
            }
            current->available = 1;
            current->studentId = 0;
            clearScreen();
            printf("Book '%s' returned successfully!\n", current->title);
            waitForEnter();
            return;
        }
        current = current->next;
    }

    clearScreen();
    printf("Invalid ID.\n");
    waitForEnter();
}

void deleteBook() {
    int id;
    clearScreen();
    printf("Enter book ID to delete: ");
    scanf("%d", &id);
    while (getchar() != '\n');

    Book* current = library;
    Book* previous = NULL;

    while (current) {
        if (current->id == id) {
            if (previous) {
                previous->next = current->next;
            } else {
                library = current->next;
            }
            free(current);
            clearScreen();
            printf("Book deleted successfully!\n");
            waitForEnter();
            return;
        }
        previous = current;
        current = current->next;
    }

    clearScreen();
    printf("Invalid ID.\n");
    waitForEnter();
}

void addStudent() {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    if (!newStudent) {
        clearScreen();
        printf("Memory allocation failed!\n");
        waitForEnter();
        return;
    }

    newStudent->id = studentIdCounter++;
    
    clearScreen();
    printf("Enter student last name: ");
    fgets(newStudent->lastName, NAME_LENGTH, stdin);
    newStudent->lastName[strcspn(newStudent->lastName, "\n")] = 0;
    
    clearScreen();
    printf("Enter student first name: ");
    fgets(newStudent->firstName, NAME_LENGTH, stdin);
    newStudent->firstName[strcspn(newStudent->firstName, "\n")] = 0;
    
    newStudent->next = studentsList;
    studentsList = newStudent;

    clearScreen();
    printf("Student added successfully!\n");
    waitForEnter();
}

void displayStudents() {
    clearScreen();
    if (!studentsList) {
        printf("No registered students.\n");
    } else {
        printf("Student List:\n");
        Student* current = studentsList;
        while (current) {
            printf("ID: %d, Name: %s %s\n",
                   current->id,
                   current->lastName,
                   current->firstName);
            current = current->next;
        }
    }
    waitForEnter();
}

void searchStudent() {
    char lastName[NAME_LENGTH];
    char firstName[NAME_LENGTH];
    int found = 0;

    clearScreen();
    printf("Enter student last name: ");
    scanf("%s", lastName);
    printf("Enter student first name: ");
    scanf("%s", firstName);
    while (getchar() != '\n');

    Student* current = studentsList;

    clearScreen();
    printf("=== Search Results ===\n");
    while (current) {
        if (strcmp(current->lastName, lastName) == 0 && 
            strcmp(current->firstName, firstName) == 0) {
            printf("ID: %d, Name: %s %s\n", 
                   current->id, 
                   current->lastName, 
                   current->firstName);
            found = 1;
        }
        current = current->next;
    }

    if (!found) {
        printf("No student found with name: %s %s\n", lastName, firstName);
    }
    waitForEnter();
}

void displayStudentById() {
    int id;
    clearScreen();
    printf("Enter student ID: ");
    scanf("%d", &id);
    while (getchar() != '\n');

    Student* student = findStudent(id);

    clearScreen();
    if (student) {
        printf("=== Search Results ===\n");
        printf("ID: %d, Name: %s %s\n", 
               student->id, 
               student->lastName, 
               student->firstName);
    } else {
        printf("No student found with ID: %d\n", id);
    }
    waitForEnter();
}

void deleteStudent() {
    int id;
    clearScreen();
    printf("Enter student ID to delete: ");
    scanf("%d", &id);
    while (getchar() != '\n');

    Book* currentBook = library;
    while (currentBook) {
        if (currentBook->studentId == id) {
            clearScreen();
            printf("Cannot delete student. Borrowed books exist.\n");
            waitForEnter();
            return;
        }
        currentBook = currentBook->next;
    }

    Student* current = studentsList;
    Student* previous = NULL;

    while (current) {
        if (current->id == id) {
            if (previous) {
                previous->next = current->next;
            } else {
                studentsList = current->next;
            }
            free(current);
            clearScreen();
            printf("Student deleted successfully!\n");
            waitForEnter();
            return;
        }
        previous = current;
        current = current->next;
    }

    clearScreen();
    printf("Invalid ID.\n");
    waitForEnter();
}

void freeMemory() {
    Book* currentBook = library;
    while (currentBook) {
        Book* temp = currentBook;
        currentBook = currentBook->next;
        free(temp);
    }

    Student* currentStudent = studentsList;
    while (currentStudent) {
        Student* temp = currentStudent;
        currentStudent = currentStudent->next;
        free(temp);
    }
}

void menu() {
    printf("\n=== Virtual Library System ===\n");
    printf("1. Add Book\n");
    printf("2. Display Books\n");
    printf("3. Borrow Book\n");
    printf("4. Return Book\n");
    printf("5. Delete Book\n");
    printf("6. Add Student\n");
    printf("7. Display Students\n");
    printf("8. Delete Student\n");
    printf("9. Search Student by Name\n");
    printf("10. Search Student by ID\n");
    printf("0. Exit\n");
    printf("===============================\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;

    do {
        clearScreen();
        menu();

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: borrowBook(); break;
            case 4: returnBook(); break;
            case 5: deleteBook(); break;
            case 6: addStudent(); break;
            case 7: displayStudents(); break;
            case 8: deleteStudent(); break;
            case 9: searchStudent(); break;
            case 10: displayStudentById(); break;
            case 0: 
                clearScreen();
                printf("Goodbye!\n");
                break;
            default:
                clearScreen();
                printf("Invalid choice. Please try again.\n");
                waitForEnter();
        }
    } while (choice != 0);

    freeMemory();
    return 0;
}
