/** @file Customer order management.c
*
* @brief Create a Customer Management System in C that supports adding and searching customers,
* managing orders, and generating reports on customer-order details with data stored from files.
*
* @par
* COPYRIGHT NOTICE: (c) 2024 Gunasekaran V. All rights reserved.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CUSTOMERS 100   // Maximum number of customers that can be handled
#define MAX_ORDERS 100  // Maximum number of orders that can be handled

typedef int int32_t;
typedef long long int int64_t;
typedef char char8_t;

// Structure to represent a customer
struct Customer
{
    int32_t custid;              // Unique ID for the customer
    char8_t cname[50];         // Customer's name
    int64_t phone;    // Customer's phone number
    char8_t email[50];         // Customer's email address
    char8_t address[100];      // Customer's address
};

// Structure to represent an order details
struct order
{
    int32_t oid;                // Unique ID for the order
    int32_t custid;             // Customer ID who placed the order
    char8_t pname[50];         // Product name ordered
    char8_t date[15];          // Date of the order
};

// Function prototypes

/**
 * @brief Adds the customer details.
 * 
 * This function gets the details of the 
 * customer from user and add the details to array.
 * 
 * @param Customer arr[] represents the details of customers in a array.
 * @param int32_t *n is the number of customers currently present.
 */
void add_customer(struct Customer arr[], int32_t * n);

/**
 * @brief Search for customer in a file.
 * 
 * This function search for the customer details 
 * using the customer id given by user.
 * 
 * @param Customer arr[] represents the details of customers in a array.
 * @param int32_t n is the number of customer currently present.
 * @param int32_t id is the customer id given by user.
 */
void search_customer(struct Customer arr[], int32_t n, int32_t id);

/**
 * @brief Display the details of all customers
 * 
 * This function print the details of all customers
 * present in a file.
 * 
 * @param Customer arr[] represents the details of customers in a array.
 * @param int32_t n is the number of customers currently present.
 */
void list_customers(struct Customer arr[], int32_t n);

/**
 * @brief writes the customer data to file
 * 
 * This function writes the details of
 * customers to a file.
 * 
 * @param Customer arr[] represents the details of customers in a array.
 * @param int32_t n is the number of customers currently present.
 */
void save_to_file(struct Customer arr[], int32_t n);

/**
 * @brief reads the data from file
 * 
 * This function reads the details of
 * customers from a file.
 * 
 * @param customer arr[] represents the details of customers in a array.
 * @param int32_t *n is the number of customers currently present.
 */
void load_from_file(struct Customer arr[], int32_t * n);

/**
 * @brief Adds the order details.
 * 
 * This function gets the details of the 
 * order from user and add the details to array.
 * 
 * @param order a[] represents the details of orders in a array.
 * @param int32_t *c is the number of orders currently placed.
 */
void add_order(struct order a[], int32_t * c);

/**
 * @brief Display the details of all orders.
 * 
 * This function print the details of all orders
 * present in a file.
 * 
 * @param order a[] represents the details of orders  in a array.
 * @param int32_t c is the number of orders currently placed.
 */
void list_orders(struct order a[], int32_t c);

/**
 * @brief writes the order details data to file
 * 
 * This function writes the details of
 * orders placed to a file.
 * 
 * @param order a[] represents the details of orders in a array.
 * @param int32_t c is the number of orders currently placed.
 */
void save_orders_to_file(struct order a[], int32_t c);

/**
 * @brief reads the order details from file
 * 
 * This function reads the details of
 * orders placed from a file.
 * 
 * @param order a[] represents the details of orders in a array.
 * @param int32_t *c is the number of orders currently present.
 */
void load_orders_from_file(struct order a[], int32_t * c);

/**
 * @brief writes the order details for each customer
 * 
 * This function reads the data from customer details and order details
 * and writes the order details based on customer id in another file
 * 
 * @param Customer arr[] represents the details of customers in a array.
 * @param int32_t n is the number of customers currently present.
 * @param order a[] represents the details of orders in a array.
 * @param int32_t c is the number of orders currently present.
 */
void fetch_details(struct Customer arr[], struct order a[], int32_t n, int32_t c);