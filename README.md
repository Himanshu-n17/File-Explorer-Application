# 🗂️ File Explorer Application (Linux Console-Based)

## 📖 Overview
The **File Explorer Application** is a console-based project written in **C++** that interacts directly with the **Linux operating system** to manage files and directories.  
It offers a simple, menu-driven interface to navigate, search, and manipulate files efficiently — similar to using basic Linux shell commands such as `ls`, `cd`, and `cp`.

---

## 🧠 Features
✅ **List Directory Contents** — Display all files and subdirectories  
✅ **Directory Navigation** — Move into folders, parent directories, or home directory  
✅ **File and Directory Creation** — Create new files or folders  
✅ **Delete, Copy, and Move Files** — Manage your filesystem easily  
✅ **Search Functionality** — Search for files by name within the current directory  
✅ **Permission Management** — View and modify file/directory permissions (e.g., `755`)  
✅ **User-Friendly Interface** — Clear menu system with prompts and formatted output  

---

## 🛠️ Technologies Used
- **Language:** C++  
- **System:** Linux / WSL (Windows Subsystem for Linux)  
- **Libraries Used:**
  - `<dirent.h>` — Directory handling  
  - `<sys/stat.h>` — File and permission management  
  - `<unistd.h>` — Directory navigation  
  - `<fstream>` — File operations  
  - `<algorithm>`, `<vector>`, `<string>` — Data handling utilities  

---

## 🖼️ Output Screenshots
1. **MENU :**
<img width="1920" height="1080" alt="Image" src="https://github.com/user-attachments/assets/8bfc18ec-fd1b-4c2e-abd0-d0461f7c8e6a" />

2. **Changing The Current Directory :**
<img width="1920" height="1080" alt="Image" src="https://github.com/user-attachments/assets/121b9a72-fb82-46d0-8f1c-041c3b06bd59" />

3. **Listing all Files and Diretories :**
<img width="1920" height="1080" alt="Image" src="https://github.com/user-attachments/assets/e9ba0199-8dc8-4590-9110-97f06e2b220d" />

4. **Navigate to Parent and Home  Directory :**
<img width="1920" height="1080" alt="Image" src="https://github.com/user-attachments/assets/5a05b105-30d0-4c17-b9af-6a03cc5f35b7" />
<img width="1920" height="1080" alt="Image" src="https://github.com/user-attachments/assets/d90bb070-295a-4f19-aaa8-881c88c45506" />

5. **File Creation:**
<img width="1920" height="1080" alt="Image" src="https://github.com/user-attachments/assets/554d7aae-9ec2-48b6-9ee8-510aee8f0b81" />

6. **Folder Creation:**
<img width="1920" height="1080" alt="Image" src="https://github.com/user-attachments/assets/2a61689e-b013-4d7d-8e8c-d44c81f64791" />

7. **List Includes new File and Folder Created:**
<img width="1920" height="1080" alt="Image" src="https://github.com/user-attachments/assets/9aaefd56-961e-44ea-8c8e-30089c257094" />

8. **Created New Files and directories in The Demo Folder**
<img width="1920" height="1080" alt="Image" src="https://github.com/user-attachments/assets/caf5cdb6-0085-42c6-86c2-7928090dc5ab" />

9. **File and Directory deleted at Demo Folder:**
<img width="1920" height="1080" alt="Image" src="https://github.com/user-attachments/assets/0dd018a6-e57f-4011-858f-df354a1f308e" />
<img width="1920" height="1080" alt="Image" src="https://github.com/user-attachments/assets/de7f2e29-6bde-4e49-afb4-b66735288a24" />

10. **File Copying:**
<img width="1920" height="1080" alt="Image" src="https://github.com/user-attachments/assets/7de9f301-c6a1-434e-8af3-7f2fd833d56d" />

11. **Moving/Renaming File :**
<img width="1920" height="1080" alt="Image" src="https://github.com/user-attachments/assets/bdc3fc41-4f14-4ecf-81b4-63910a9d3152" />

12. **Search File:**
<img width="1920" height="1080" alt="Image" src="https://github.com/user-attachments/assets/f0e8a084-58ed-423e-a7d0-a3bbc8cff6f0" />

13. **Change Permissions:**
<img width="1920" height="1080" alt="Image" src="https://github.com/user-attachments/assets/6c4bef2d-1b61-4fea-98b7-ad23916c61b4" />

14. **Display Permissions:**
<img width="1920" height="1080" alt="Image" src="https://github.com/user-attachments/assets/06cb301f-ed7f-465a-b4ff-7e32eb1df605" />

15. **Exiting the Application:**
<img width="1920" height="1080" alt="Image" src="https://github.com/user-attachments/assets/6352d67b-12f8-4113-93bf-f41baab058e7" />
---

## 🚀 How to Run
### Compile the Program
g++ -std=c++11 -o fileexplorer fileexplorer.cpp
### Run the Application
./fileexplorer
