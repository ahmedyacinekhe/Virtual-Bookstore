# 📚 Virtual Library Management System – C Language

A console-based **Library Management System** built in **C** using **linked lists** to manage books and students.  
This program allows users to **add, search, borrow, return, and delete books**, as well as **manage student records** efficiently.

---

## 🚀 Features

### 📘 Book Management
- Add new books (with quantity)
- Display all available books
- Search by **title**, **author**, or **ID**
- Borrow & return books
- Delete books from the library

### 🧑‍🎓 Student Management
- Add students
- Display all subscribed students
- Search students by **name** or **ID**
- Prevent delete if student borrowed books
- Delete students safely

### 🔍 Searching & Filtering
| Search by | Entity |
|-----------|--------|
| Book Title | 📘 Book |
| Book Author | 📘 Book |
| Book ID | 📘 Book |
| Student Name | 🧑‍🎓 Student |
| Student ID | 🧑‍🎓 Student |

---

## 🏗️ Technologies Used

| Language | Purpose |
|----------|---------|
| C | Full program logic |
| Stdlib / StdIO | I/O & memory management |
| Linked Lists | Dynamic data storage |
| User Input Handling | Interactive menu |

---


---

## ▶️ How to Compile & Run

```bash
gcc main.c -o library
./library
```

---

=== Main Menu ===
1. add a Book
2. display Books
3. borrow a Book
4. return a Book
5. delete a Book
6. add a student
7. display students
8. delete a student
9. Search a student by name
10. Search a student by ID
11. Search a Book by title
12. Search a Book by author
13. Search a Book by ID
0. Exit

---

## 🧠 Concepts Used

- Dynamic memory allocation (malloc, free)
- Linked list traversal & insertion
- Modular programming with functions
- Input validation & error handling
- Simple UI / Menu system

## 📈 Future Improvements

- Save data to files (.txt or .csv)
- Load previous session on startup
- Improve UI (colored output)
- Add login system (admin & users)
- Create GUI version with C++ or Python

## 🤝 Contributing

Contributions are welcome! If you'd like to improve this project, feel free to fork it and submit a pull request.

## 📜 License

This project is open-source and free to use for educational purposes.
