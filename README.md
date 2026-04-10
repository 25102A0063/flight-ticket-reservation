# ✈️ Flight Reservation System (C)

A console-based **Flight Reservation System** built in C using **arrays and a doubly linked list** to simulate real-world airline booking operations.

This project supports both **Admin** and **Customer** roles with separate functionalities, including ticket booking, cancellation, seat management, and waiting list handling.

---

## 🔑 Key Features

### 👤 Customer
- User **signup & login system**
- Book tickets with **automatic seat allocation**
- **Waiting list management** when seats are full
- View, search, update, and cancel bookings
- Check **seat availability in real-time**
- View personal booking history

### 🛠️ Admin
- View all bookings (forward & reverse using DLL)
- Search bookings by ID, name, or destination
- Add or remove flights
- Modify seat capacity
- Override booking updates
- View waiting list
- Generate reports (occupancy, cancellations, etc.)

---

## ⚙️ Core Concepts Used
- **Structures & Arrays** → for users and flights  
- **Doubly Linked List** → for dynamic ticket storage  
- **Dynamic Memory Allocation (malloc)**  
- **String handling & validation**  
- **Menu-driven CLI system**

---

## 🧠 Logic Highlights
- Tickets are assigned **BOOKED or WAITING** based on seat availability  
- Seat count is dynamically tracked per flight  
- Deleting a flight automatically **cancels related bookings**  
- Admin can traverse bookings **both forward and backward**

---

## 🚀 Purpose
Designed as a **Data Structures and C Programming project** to demonstrate real-world application of linked lists and system design logic.

---

## ▶️ How to Run

1. Compile the code:
   ```bash
   gcc main.c -o flight
   ```

2. Run the program:
   ```bash
   ./flight
   ```

---

## 🔐 Default Admin Access
- **Password:** `admin123`

---

## 📌 Notes
- This is a **console-based application** (no GUI)
- Data is stored **in-memory only** (no file/database persistence)
- Suitable for **academic projects and learning purposes**

---
