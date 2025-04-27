# 🎓 Student Report Card Management System

A simple C project that uses **file handling** to manage student report cards. This command-line application allows you to add, view, search, update, and delete student records. Perfect for beginners to understand file operations in C.

---

## 🛠️ Features

- ✅ Add a new student record (name, roll number, and marks)
- 📄 Display all student records with calculated average
- 🔍 Search student by roll number
- ✏️ Update student marks and average
- ❌ Delete a student record
- 📁 File-based storage (`students.txt`)


🖥️ How to Run

1. **Compile the code:**
   
        gcc student.c -o report

2. **Run the code:**
   
         report.exe

## Sample Output

![image](https://github.com/user-attachments/assets/d113011a-5c05-4ed0-b3c3-bb7dc7339e01)

## 📌 Student Record Format

Each student record stores:

* Roll number (int)

* Name (string)

* Marks in 5 subjects (float array)

* Average marks (float)

## 💾 File Handling Concepts Used
* fopen, fclose
* fread, fwrite
* fseek for record updates
* rename, remove for deletion

✅ Ideal For:
C programming beginners
Learning file I/O
Understanding structs and menus
Academic mini-projects



