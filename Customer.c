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
#define MAX_ORDERS 100      // Maximum number of orders that can be handled

typedef int int32_t;
typedef long long int int64_t;
typedef char char8_t;

// Structure to represent a customer
struct Customer {
    int32_t custid;              // Unique ID for the customer
    char8_t cname[50];           // Customer's name
    int64_t phone;               // Customer's phone number
    char8_t email[50];           // Customer's email address
    char8_t address[100];        // Customer's address
};

// Structure to represent an order details
struct order {
    int32_t oid;                // Unique ID for the order
    int32_t custid;             // Customer ID who placed the order
    char8_t pname[50];          // Product name ordered
    char8_t date[15];           // Date of the order
};

// Function prototypes
void add_customer(struct Customer arr[], int32_t *n);
void search_customer(struct Customer arr[], int32_t n, int32_t id);
void list_customers(struct Customer arr[], int32_t n);
void save_to_file(struct Customer arr[], int32_t n);
void load_from_file(struct Customer arr[], int32_t *n);
void add_order(struct order a[], int32_t *c);
void list_orders(struct order a[], int32_t c);
void save_orders_to_file(struct order a[], int32_t c);
void load_orders_from_file(struct order a[], int32_t *c);
void fetch_details(struct Customer arr[], struct order a[], int32_t n, int32_t c);

int32_t main() {
    struct Customer arr[MAX_CUSTOMERS] = {0}; // Array to hold customer records, zero-initialized
    struct order a[MAX_ORDERS] = {0};         // Array to hold order records, zero-initialized
    int32_t n = 0;                            // Number of customers
    int32_t c = 0;                            // Number of orders
    int32_t choice;                           // User menu choice

    // Load existing customer and order data from files
    load_from_file(arr, &n);
    load_orders_from_file(a, &c);

    // Main menu loop
    while (1) {
        printf("\nCustomer Management System Menu:\n");
        printf("1. Add a Customer\n");
        printf("2. Search a Customer\n");
        printf("3. List All Customers\n");
        printf("4. Add an Order\n");
        printf("5. List All Orders\n");
        printf("6. Display Order Details Based on Customer ID\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please try again.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        switch (choice) {
            case 1:
                add_customer(arr, &n);
                break;
            case 2: {
                int32_t id;
                printf("Enter Customer ID to search: ");
                if (scanf("%d", &id) != 1) {
                    printf("Invalid input.\n");
                    break;
                }
                search_customer(arr, n, id);
                break;
            }
            case 3:
                list_customers(arr, n);
                break;
            case 4:
                add_order(a, &c);
                break;
            case 5:
                list_orders(a, c);
                break;
            case 6:
                fetch_details(arr, a, n, c);
                break;
            case 7:
                save_to_file(arr, n);
                save_orders_to_file(a, c);
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice, please try again.\n");
                break;
        }
    }
}

// Function to add customers to the array
void add_customer(struct Customer arr[], int32_t *n) {
    if (*n >= MAX_CUSTOMERS) {
        printf("Cannot add more customers. Limit reached.\n");
        return;
    }

    int32_t count;
    printf("Enter number of Customers to add: ");
    if (scanf("%d", &count) != 1 || count < 1 || *n + count > MAX_CUSTOMERS) {
        printf("Invalid count or limit reached.\n");
        return;
    }

    for (int32_t i = 0; i < count; i++) {
        printf("Enter customer ID, name, phone number, email, and address for customer %d:\n", *n + 1);
        if (scanf("%d", &arr[*n].custid) != 1 ||
            scanf("%49s", arr[*n].cname) != 1 ||
            scanf("%lld", &arr[*n].phone) != 1 ||
            scanf("%49s", arr[*n].email) != 1 ||
            scanf("%99[^\n]", arr[*n].address) != 1) {
            printf("Invalid input, customer %d not added.\n", *n + 1);
            return;
        }
        (*n)++;
    }

    save_to_file(arr, *n);
}

// Function to search for a customer by ID
void search_customer(struct Customer arr[], int32_t n, int32_t id) {
    for (int32_t i = 0; i < n; i++) {
        if (arr[i].custid == id) {
            printf("Customer ID: %d\nName: %s\nPhone: %lld\nEmail: %s\nAddress: %s\n",
                   arr[i].custid, arr[i].cname, arr[i].phone, arr[i].email, arr[i].address);
            return;
        }
    }
    printf("Customer with ID %d not found.\n", id);
}

// Function to list all customers
void list_customers(struct Customer arr[], int32_t n) {
    if (n == 0) {
        printf("No customers to list.\n");
        return;
    }

    for (int32_t i = 0; i < n; i++) {
        printf("Customer ID: %d\nName: %s\nPhone: %lld\nEmail: %s\nAddress: %s\n----------------------------\n",
               arr[i].custid, arr[i].cname, arr[i].phone, arr[i].email, arr[i].address);
    }
}

// Function to save customer data to a file
void save_to_file(struct Customer arr[], int32_t n) {
    FILE *file = fopen("Customer.csv", "w");
    if (file == NULL) {
        perror("Failed to open file for writing");
        return;
    }

    fprintf(file, "cid,name,phone,mail,location\n");
    for (int32_t i = 0; i < n; i++) {
        fprintf(file, "%d,%s,%lld,%s,%s\n", arr[i].custid, arr[i].cname, arr[i].phone, arr[i].email, arr[i].address);
    }
    fclose(file);
}

// Function to load customer data from a file
void load_from_file(struct Customer arr[], int32_t *n) {
    FILE *file = fopen("Customer.csv", "r");
    if (file == NULL) {
        perror("Failed to open file for reading");
        return;
    }

    *n = 0;
    char8_t line[256];
    fgets(line, sizeof(line), file); // Skip header line
    while (*n < MAX_CUSTOMERS && fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d,%49[^,],%lld,%49[^,],%99[^\n]", 
                   &arr[*n].custid, arr[*n].cname, &arr[*n].phone, arr[*n].email, arr[*n].address) == 5) {
            (*n)++;
        }
    }
    fclose(file);
}

// Function to add orders to the array
void add_order(struct order a[], int32_t *c) {
    if (*c >= MAX_ORDERS) {
        printf("Cannot add more orders. Limit reached.\n");
        return;
    }

    int32_t count;
    printf("Enter number of orders to add: ");
    if (scanf("%d", &count) != 1 || count < 1 || *c + count > MAX_ORDERS) {
        printf("Invalid count or limit reached.\n");
        return;
    }

    for (int32_t i = 0; i < count; i++) {
        printf("Enter order ID, customer ID, product name and ordered date for order %d:\n", *c + 1);
        if (scanf("%d", &a[*c].oid) != 1 ||
            scanf("%d", &a[*c].custid) != 1 ||
            scanf("%49s", a[*c].pname) != 1 ||
            scanf("%14s", a[*c].date) != 1) {
            printf("Invalid input, order %d not added.\n", *c + 1);
            return;
        }
        (*c)++;
    }

    // Save updated orders list to file
    save_orders_to_file(a, *c);
}

// Function to list all orders
void list_orders(struct order a[], int32_t c) {
    if (c == 0) {
        printf("No orders to list.\n");
        return;
    }

    for (int32_t i = 0; i < c; i++) {
        printf("Order ID: %d\nCustomer ID: %d\nProduct Name: %s\nDate: %s\n----------------------------\n",
               a[i].oid, a[i].custid, a[i].pname, a[i].date);
    }
}

// Function to save order data to a file
void save_orders_to_file(struct order a[], int32_t c) {
    FILE *file = fopen("Order.csv", "w");
    if (file == NULL) {
        perror("Failed to open file for writing");
        return;
    }

    // Write header for CSV file
    fprintf(file, "oid,cid,product name,date\n");
    for (int32_t i = 0; i < c; i++) {
        fprintf(file, "%d,%d,%s,%s\n", a[i].oid, a[i].custid, a[i].pname, a[i].date);
    }
    fclose(file);
}

// Function to load order data from a file
void load_orders_from_file(struct order a[], int32_t *c) {
    FILE *file = fopen("Order.csv", "r");
    if (file == NULL) {
        perror("Failed to open file for reading");
        return;
    }

    *c = 0;
    char8_t line[256];
    fgets(line, sizeof(line), file);  // Skip header line
    while (*c < MAX_ORDERS && fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d,%d,%49[^,],%14[^\n]", &a[*c].oid, &a[*c].custid, a[*c].pname, a[*c].date) == 4) {
            (*c)++;
        }
    }
    fclose(file);
}

// Function to fetch and display order details based on customer ID
void fetch_details(struct Customer arr[], struct order a[], int32_t n, int32_t c) {
    FILE *file = fopen("Order_details.txt", "w");
    if (file == NULL) {
        perror("Failed to open file for writing");
        return;
    }

    // Loop through each customer
    for (int32_t i = 0; i < n; i++) {
        int32_t flag = 0;
        fprintf(file, "Customer ID: %d\n", arr[i].custid);
        // Loop through each order and match with customer ID
        for (int32_t j = 0; j < c; j++) {
            if (arr[i].custid == a[j].custid) {
                // Write order details for the matched customer
                fprintf(file, "Customer Name: %s, Order ID: %d, Product Name: %s, Ordered Date: %s\n",
                        arr[i].cname, a[j].oid, a[j].pname, a[j].date);
                flag = 1;
            }
        }
        // If no orders found for the customer
        if (!flag) {
            fprintf(file, "No orders placed yet!\n");
        }
        fprintf(file, "----------------------------\n");
    }
    fclose(file);
}
