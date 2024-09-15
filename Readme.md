# Customer Order Management System

## Overview

This is a **Customer Management System** implemented in C, designed to manage customer and order records. It supports adding and searching customers, adding orders, and generating reports based on customer order details. The system persists data to files and reads from them, enabling data to be maintained between executions.

## Features

- Add customer records, including customer ID, name, phone number, email, and address.
- Search for customers based on their unique customer ID.
- List all existing customers in the system.
- Add orders with details like order ID, customer ID, product name, and order date.
- List all orders placed by customers.
- Generate a report that displays order details based on customer IDs.
- Save and load customer and order data to/from CSV files.
  
## File Structure

The project uses two primary files to store data:

- **Customer.csv**: Stores customer details.
- **Order.csv**: Stores order details.
- **Order_details.txt**: Stores a report of orders based on customer IDs.

## How to Use

### Menu Options

Once you compile and run the program, you will be presented with a menu:

1. **Add a Customer**: Add new customer records to the system.
2. **Search a Customer**: Search for a customer using their customer ID.
3. **List All Customers**: Display a list of all the customers stored in the system.
4. **Add an Order**: Add new orders associated with customers.
5. **List All Orders**: Display all the orders placed in the system.
6. **Display Order Details Based on Customer ID**: Generate a report of orders for each customer and save it to a file.
7. **Exit**: Save all changes to files and exit the program.

### Input Format

- When adding a customer, the following details are required:
  - Customer ID: An integer.
  - Customer Name: A string (up to 50 characters).
  - Phone Number: An integer (a valid phone number format).
  - Email: A string (up to 50 characters).
  - Address: A string (up to 100 characters).
  
- When adding an order, the following details are required:
  - Order ID: An integer.
  - Customer ID: An integer (must be a valid ID from the customer records).
  - Product Name: A string (up to 50 characters).
  - Order Date: A string (up to 15 characters).

### Data Persistence

- **Customer.csv**: Stores customer records in CSV format with columns `cid,name,phone,mail,location`.
- **Order.csv**: Stores order records in CSV format with columns `oid,cid,product name,date`.
- **Order_details.txt**: Contains details of all orders placed by each customer. If a customer has not placed any orders, the report will note that.

### Output Files

- **Customer.csv**: Generated/updated when customer data is added or modified. It stores customer details such as customer ID, name, phone, email, and address.
- **Order.csv**: Generated/updated when order data is added or modified. It stores order details such as order ID, customer ID, product name, and date of the order.
- **Order_details.txt**: Generated when option 6 (Display Order Details Based on Customer ID) is selected. It lists the details of each customer's orders, and if no orders have been placed, it indicates so.

### Example Run

```bash
Customer Management System Menu:
1. Add a Customer
2. Search a Customer
3. List All Customers
4. Add an Order
5. List All Orders
6. Display Order Details Based on Customer ID
7. Exit
Enter your choice: 1

Enter number of Customers to add: 2
Enter customer ID, name, phone number, email, and address for customer 1:
101
Alice
9876543210
alice@example.com
123 Main Street

Enter customer ID, name, phone number, email, and address for customer 2:
102
Bob
9876543211
bob@example.com
456 Oak Avenue
```

## Error handling 

This system includes multiple levels of error handling:

### Input validation 

- **Invalid Customer and Order Data**: The program checks that all required input fields are provided in the correct format.
- **Overflow Prevention**: The system ensures that no more than the maximum allowed number of customers (MAX_CUSTOMERS) or orders (MAX_ORDERS) can be added. If the maximum is reached, a message is displayed, and no more entries are accepted.

### File Handling

- **File Opening/Reading Errors**: If the system fails to open files like Customer.csv, Order.csv, or Order_details.txt, it displays an appropriate error message using perror(). In such cases, the system attempts to handle the error gracefully and either stops execution or proceeds without file interaction.
- **File Writing Failures**: When writing data to files, the program checks if the file is writable. If any errors occur (e.g., insufficient permissions), the program catches these errors and informs the user without crashing.

### Edge cases

- **Empty Records**: When no customer or order records exist, the system handles these cases by printing appropriate messages such as "No customers to list" or "No orders to list."

### Data Consistency 

- **Data Saving**: Every time new customer or order data is added, the system immediately writes the new data to the corresponding file (e.g., Customer.csv or Order.csv) to prevent data loss.

## License

This project is licensed under the copyright of Gunasekaran V (c) 2024. All rights reserved.