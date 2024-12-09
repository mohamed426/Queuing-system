
# Bank Queue Management System

## Description
This is a simple console-based C++ application for managing a bank's customer queue. 
It supports both VIP and normal customers, allowing them to enqueue, dequeue, and search for their information.

## Features
- Separate queues for VIP and normal clients.
- Enqueue and dequeue operations.
- Display all customers or only VIP customers.
- Search functionality by phone number or service name.
- Update functionality to convert a customer to VIP.

## How to Use
1. Compile the code using a C++ compiler (e.g., g++, clang++).
2. Run the compiled program.
3. Choose an operation from the menu:
   - Enqueue (E/e)
   - Dequeue (D/d)
   - Print All Clients (PA/pa)
   - Print VIP Clients (PV/pv)
   - Search (S/s)
   - Update (U/u)
   - Quit (Q/q)

## Services
The available services are:
- Teller
- Loans
- Customer Service

## Requirements
- C++11 or later
- A console environment

## Notes
- VIP customers are identified by specific phone numbers.
- Phone numbers must be 11 digits long and contain only numbers.
- Service names must contain only letters and be valid (Teller, Loans, Customer Service).

