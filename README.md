# Student Management System in C

This project is a menu-driven **Student Management System** written in C.
It allows adding, searching, updating, and deleting student records with proper validations.

The program also includes **mobile number validation, duplicate checks, and colorful terminal output**
to make the interface more user-friendly.

---

## 📌 Features

- Add new student
- Display all student records
- Search student by **ID** or **Name**
- Update student details (Name, Address, Mobile)
- Delete student record
- Duplicate mobile number protection
- Mobile number must be exactly **10 digits**
- Colorful terminal UI for better readability

---

## 📁 File Structure

StudentManagement/
│── student.c      → Main C program
│── README.md      → Project documentation file

---

## 🛠️ How to Compile & Run

Open a terminal inside the project folder and run:

gcc student.c -o student
./student

---

## 🧰 Requirements

- GCC compiler
- Linux terminal / VS Code terminal / Git Bash
- ANSI color support for terminal

---

## 👤 Author

Shrinivas Umachagi  
Electronics & Communication Engineering  

---

## 📜 Notes

- Uses ANSI escape codes for colorful output.
- Supports up to **50 students**.
- Ideal for mini-projects and interview demonstrations.
