# Telephone Management System

This project is a simple telephone management system implemented in C++ using MySQL for database operations. It allows users to manage customers and their bills through a command-line interface.

## Requirements

- C++ compiler
- MySQL server
- MySQL C++ Connector

## Installation

1. Clone the repository:

    ```bash
    git clone git@github.com:salemwhd/Telephone-Mobile-Billing-Management-System.git
    ```

2. Navigate to the project directory:

    ```bash
    cd telephone-management-system
    ```

3. Compile the code:

    ```bash
    g++ main.cpp -o telephone_manager -lmysqlclient
    ```

4. Run the executable:

    ```bash
    ./telephone_manager
    ```

## Usage

Upon running the executable, the program will attempt to establish a connection with the MySQL database. If successful, it will display a success message; otherwise, it will show an error message.

The main functionality of the system includes:
- Adding a new customer
- Adding bills for customers
- Viewing customer names and IDs


