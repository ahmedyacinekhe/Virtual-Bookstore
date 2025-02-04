#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Constants that'll be used inside the code:
#define TITLE_LENGTH 100
#define NAME_LENGTH 50

//The book structure definition:
typedef struct Book {
    int id;
    char title[NAME_LENGTH];
    char author[NAME_LENGTH];
    int available;
    int studentId;
    struct Book* next;
} Book;

//Student structure definition:
typedef struct Student {
    int id;
    char familyName[NAME_LENGTH];
    char name[NAME_LENGTH];
    struct Student* next;
} Student;

//Initializing the linked lists by their head pointers:
Book* library = NULL;
Student* studentsList = NULL;

//Initializing the number of list elements (This number is considered to be the id number):
int bookIdCounter = 1;
int studentIdCounter = 1;

//This is a function that searches a student using its ID number, it returns the corresponding list element, here's its prototype:
Student* findStudent(int id);

//This is a function that searches a book using its ID number, it returns the corresponding list element, here's its prototype:
Book* findBook(int id);

//This is a function that displays the list of the books in the library,  here's its prototype:
void displayBooks();

// Clears the screen (cross-platform)
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
//This is a function that allows the user to add a new book,  here's its definition:
void addBook() {
    clearScreen();
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
    //Confirmation message for the user:
    printf("\n%d books has been added successfully!\n",quantity);
}

//This function displays the list of books in the library, here's its definition:
void displayBooks() {

    //Control over empty library:
    if (!library) {
        printf("\nThe library is empty!\n");
        return;
    }
clearScreen(); // Clears before displaying, so output stays visible
    printf("\nThe list of books in the library:\n");

    //Walking through the library books:
    Book* current = library;
    while (current) {
        printf("ID: %d, title: %s, author: %s, available: %s",
               current->id,
               current->title,
               current->author,
               current->available ? "Yes" : "No");


        if (!current->available) {
            Student* Student = findStudent(current->studentId);

            //Control over the student's information existence:
            if (Student) {
                printf(", Borrowed by: ID: %d, Family Name: %s, Name: %s",
                       Student->id,
                       Student->familyName,
                       Student->name);
            } else {
                printf(", Borrowed by an unknown student! (ID: %d)", current->studentId);
            }
        }
        printf("\n");
        current = current->next;
    }
    printf("\nPress Enter to return to the menu...");
    getchar();
    getchar(); // Pause before clearing the screen again
}

//This function searches a book's title in the books' list, here's its definition:
void searchBook() {
    clearScreen(); // Clears before displaying, so output stays visible
    char title[TITLE_LENGTH];
    int found = 0;

    printf("Enter the title of the book: ");
     getchar();  // Consume any leftover newline
    fgets(title, TITLE_LENGTH, stdin);
    title[strcspn(title, "\n")] = 0;  // Remove trailing newline

    Book* current = library;

    printf("\n=== RESULT ===\n");
    while (current) {
        if (strcmp(current->title, title) == 0 ) {
            printf("ID : %d, Title: %s, Author: %s\n", current->id, current->title, current->author);
            found = 1;
        }
        current = current->next;
    }

    if (!found) {
        printf("The book with the title: '%s'  is not found!\n", title);
    }
     printf("\nPress Enter to continue...");
    getchar();  // Wait for user input before refreshing to menu
}

//This function searches a book's author in the books' list, here's its definition:
void searchBookByAuthor() {
    clearScreen(); // Clears before displaying, so output stays visible
    char author[NAME_LENGTH];
    int found = 0;

    printf("Enter the author of the book: ");
    getchar();  // Consume any leftover newline
   fgets(author, NAME_LENGTH, stdin);
    author[strcspn(author, "\n")] = 0;  // Remove trailing newline

    Book* current = library;

    printf("\n=== RESULT ===\n");
    while (current) {
        if (strcmp(current->author, author) == 0 ) {
            printf("ID : %d, Title: %s, Author: %s\n", current->id, current->title, current->author);
            found = 1;
        }
        current = current->next;
    }

    if (!found) {
        printf("The book written by: '%s'  is not found!\n", author);
    }
    printf("\nPress Enter to continue...");
    getchar();  // Wait for user input before refreshing to menu
}

//This function displays the book's info based on a given ID number, here's its definition:
void displayBooksById() {
    clearScreen(); // Clears before displaying, so output stays visible
    int id;
    printf("\nEnter the book's ID: ");
    // Clear input buffer before reading integer
    while (getchar() != '\n');  
    if (scanf("%d", &id) != 1) {
        printf("\nInvalid input! Please enter a valid number.\n");
        while (getchar() != '\n'); // Clear input buffer
        return;
    }
    Book* Book = findBook(id);

    if (Book) {
        printf("\n=== RESULT ===\n");
        printf("ID: %d, Title: %s, Written by: %s\n", Book->id, Book->title, Book->author);
    } else {
        printf("\nThe book with the ID number: %d, is not found!\n", id);
    }
    printf("\nPress Enter to continue...");
    getchar();
    getchar();  // Wait for user input before refreshing to menu
}


//This is a function that searches a book using its ID number, it returns the corresponding list element, here's its definition:
Book* findBook(int id) {
    Book* current = library;
    while (current) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

//This is a function that searches a student using its ID number, it returns the corresponding list element, here's its definition:
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

//This is a function that allows to borrow a book, here's its definition:
void borrowBook() {
    clearScreen();
    int bookId, studentId;
    printf("\nEnter the ID number of the book that you want to borrow: ");
    scanf("%d", &bookId);

    Book* currentBook = library;
    while (currentBook) {
        //Control over the book existence
        if (currentBook->id == bookId) {

            //Control over the book availability
            if (!currentBook->available) {
                printf("\nThis book is borrowed already!\n");
                return;
            }
            printf("\nEnter the student's ID: ");
            scanf("%d", &studentId);

            if (!findStudent(studentId)) {
                printf("\nStudent not found!\n");
                return;
            }

            currentBook->available = 0;
            currentBook->studentId = studentId;
            printf("\nThe book %s has been borrowed successfully! \n", currentBook->title);
            return;
        }
        currentBook = currentBook->next;
    }
    //In case of the ID finding failure:
    printf("\nBook ID not found!\n");
}

//This is a function that allows to return a borrowed book to the library, here's its definition:
void returnBook() {
    clearScreen();
    int id;
    printf("\nEnter the ID of the book that you want to return: ");
    scanf("%d", &id);

    Book* current = library;
    //Searching the book in the library, in case it's returned already:
    while (current) {
        if (current->id == id) {
            if (current->available) {
                printf("\nThis book is in the library already!\n");
                return;
            }
            current->available = 1;
            current->studentId = 0;
            printf("\nThe book %s has been returned successfully!\n", current->title);
            return;
        }
        current = current->next;
    }

    printf("\nID not found!\n");
}

//This function is meant to delete an existing book from the library, here's its definition:
void deleteBook() {
    clearScreen();
    int id;
    printf("\nEnter the ID number of the book that you want to delete: ");
    scanf("%d", &id);

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
            printf("\nThe book has been deleted successfully!\n");
            return;
        }
        previous = current;
        current = current->next;
    }

    printf("\nID not found!\n");
}

//This is a function to allow adding a student to the students' list, here's its definition:
void addStudent() {
    clearScreen();
    Student* newStudent = (Student*)malloc(sizeof(Student));
    if (!newStudent) {
        printf("\nMemory allocation failed!\n");
        return;
    }

    newStudent->id = studentIdCounter++;
    printf("\nEnter the family name of the student: ");
    getchar();
    fgets(newStudent->familyName, NAME_LENGTH, stdin);
    newStudent->familyName[strcspn(newStudent->familyName, "\n")] = 0;
    printf("Enter the name of the student: ");
    fgets(newStudent->name, NAME_LENGTH, stdin);
    newStudent->name[strcspn(newStudent->name, "\n")] = 0;
    newStudent->next = studentsList;
    studentsList = newStudent;
    //Confirmation message:
    printf("\nThe student has been added successfully!\n");
}

//This function is meant to display the list of all the subscribed students:
void displayStudents() {
    if (!studentsList) {
        printf("\nNo student is subscribed!\n");
        return;
    }
    clearScreen(); // Clears before displaying, so output stays visible

    printf("\nThe list of subscribed students:\n");
    Student* current = studentsList;
    while (current) {
        printf("ID: %d, Family Name: %s, Name: %s\n",
               current->id,
               current->familyName,
               current->name);
        current = current->next;
    }
    printf("\nPress Enter to return to the menu...");
    getchar();
    getchar(); // Pause before clearing the screen again
}

//This function searches a student's full name in the students' list, here's its definition:
void searchStudent() {
    clearScreen();  // Added screen clear
    char familyName[NAME_LENGTH];
    char name[NAME_LENGTH];
    int found = 0;

    printf("\nEnter the family name of the student: ");
    scanf("%s", familyName);
    printf("Enter the name of the student: ");
    scanf("%s", name);

    Student* current = studentsList;

    printf("\n=== RESULT ===\n");
    while (current) {
        if (strcmp(current->familyName, familyName) == 0 && strcmp(current->name, name) == 0) {
            printf("ID : %d, Family Name: %s, Name: %s\n", current->id, current->familyName, current->name);
            found = 1;
        }
        current = current->next;
    }

    if (!found) {
        printf("The student with the family name: '%s' and the name '%s' is not found!\n", familyName, name);
    }
    // Pause before returning to the menu
    printf("\nPress Enter to return to the menu...");
    getchar();
    getchar();
}

//This function displays the students' info based on a given ID number, here's its definition:
void displayStudentById() {
    clearScreen();  // Added screen clear
    int id;
    printf("\nEnter the student's ID: ");
    scanf("%d", &id);

    Student* Student = findStudent(id);

    if (Student) {
        printf("\n=== RESULT ===\n");
        printf("ID : %d, Family Name : %s, Name : %s\n", Student->id, Student->familyName, Student->name);
    } else {
        printf("\nThe student with the ID number: %d, is not found!\n", id);
    }
    // Pause before returning to the menu
    printf("\nPress Enter to return to the menu...");
    getchar();
    getchar();
}

//To delete a student from the students' list based on a given ID number, we use the following function:
void deleteStudent() {
    clearScreen();  // Added screen clear
    int id;
    printf("\nEnter the ID number of the student that you want to delete: ");
    scanf("%d", &id);

    Book* currentBook = library;
    while (currentBook) {
        if (currentBook->studentId == id) {
            printf("\nStudent can't be deleted: He has borrowed one or multiple books!\n");
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
            printf("\nThe student has been deleted successfully!\n");
            return;
        }
        previous = current;
        current = current->next;
    }

    printf("\nID not found!\n");
}

//This function is meant to free unnecessary occupied memory space:
void freeMemory() {
    Book* currentBook = library;
    while (currentBook) {
        Book* tempBook = currentBook;
        currentBook = currentBook->next;
        free(tempBook);
    }

    Student* currentStudent = studentsList;
    while (currentStudent) {
        Student* tempStudent = currentStudent;
        currentStudent = currentStudent->next;
        free(tempStudent);
    }
}

void menu() {
    printf("\n=== Main Menu ===\n");
    printf("1. add a Book\n");
    printf("2. display Books\n");
    printf("3. borrow a Book\n");
    printf("4. return a Book\n");
    printf("5. delete a Book\n");
    printf("6. add a student\n");
    printf("7. display students\n");
    printf("8. delete a student\n");
    printf("9. Search a student by his family name and name\n");
    printf("10. Search a student by his ID number\n");
    printf("11. Search a Book by its title\n");
    printf("12. Search a book by its author name\n");
    printf("13. Search a book by its ID number\n");
    printf("0. Exit\n");
    printf("===================================\n");
    printf("Enter your choice number: ");
}

int main() {
    int choice;

    do {
        clearScreen();  // Added screen clear
        menu();

    while (scanf("%d", &choice) != 1) { // If input is not an integer
        printf("Invalid input! Please enter an integer: ");
        while (getchar() != '\n'); // Clear input buffer
    }
        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                displayBooks();
                break;
            case 3:
                borrowBook();
                break;
            case 4:
                returnBook();
                break;
            case 5:
                deleteBook();
                break;
            case 6:
                addStudent();
                break;
            case 7:
                displayStudents();
                break;
            case 8:
                deleteStudent();
                break;
            case 9:
                searchStudent();
                break;
            case 10:
                displayStudentById();
                break;
            case 11:
                searchBook();
                break;
            case 12:
                searchBookByAuthor();
                break;
            case 13:
                displayBooksById();
                break;
            case 0:
                clearScreen();
                printf("\nGoodbye!\n");
                break;
            default:
                clearScreen();  // Added screen clear
                printf("\nCHOICE ERROR: THERE'S NO SUCH A CHOICE NUMBER, PLEASE TRY AGAIN!\n");
        }
    } while (choice != 0);

    freeMemory();
    return 0;
}
