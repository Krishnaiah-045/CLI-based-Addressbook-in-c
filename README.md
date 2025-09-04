# CLI-based-Addressbook-in-

A fully functional **Address Book Management System** built in **C language**.  
It provides a **menu-driven interface** to manage contacts with operations like **Create, Search, Edit, Delete, and List**.  

This project demonstrates:
- 📂 **File Handling** for persistent data storage.  
- 🧩 **Modular Programming** with separate `.c` and `.h` files.  
- 🎨 **User-friendly console interface** using **color-coded messages**.  
- ✅ **Input validation** to ensure data integrity.  

---

## 🚀 Why This Project?
The Address Book project is a great **beginner-friendly C project** to learn:
- Structs & arrays for data management.
- String handling functions (`strcmp`, `strcpy`, `strstr`, etc.).
- File I/O (`fopen`, `fscanf`, `fprintf`) for persistence.
- Modular code design with **headers & source files**.
- User interaction with formatted, colored console outputs.

---

## ✨ Features
- ➕ **Create Contact** – Add a new contact with full validation.
- 🔍 **Search Contact** – Find contacts by **Name**, **Phone**, **Email**, or **Location**.
- 📝 **Edit Contact** – Modify existing details (with duplicate prevention).
- ❌ **Delete Contact** – Remove unwanted contacts.
- 📋 **List Contacts** – Display all contacts in a neat table (sorted alphabetically).
- 💾 **Save & Exit** – Ensures all changes are written to `Contact.txt`.

# **Validations**
Input Validations

**Name** → Only alphabets and spaces.

**Phone** → Exactly 10 digits.

**Email** → Must follow name@example.com (basic .com validation).

**Location** → Only alphabets and spaces.

**No duplicates** → Name, Phone, and Email must be unique.

---

## 📂 Project Structure
Each module has a clear role:

