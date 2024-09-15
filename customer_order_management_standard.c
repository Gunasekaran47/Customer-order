#include "header.h"

int32_t main()
{
    struct Customer arr[MAX_CUSTOMERS]; // Array to hold customer records
    struct order a[MAX_ORDERS];         // Array to hold order records
    int32_t n = 0;                         // Number of customers
    int32_t c = 0;                         // Number of orders
    int32_t choice;                        // User menu choice

    // Load existing customer and order data from files
    load_from_file(arr, & n);
    load_orders_from_file(a, & c);

    // Main menu loop
    while (1)
    {
        printf("\nCustomer Management System Menu:\n");
        printf("1. Add a Customer\n");
        printf("2. Search a Customer\n");
        printf("3. List All Customers\n");
        printf("4. Add an Order\n");
        printf("5. List All Orders\n");
        printf("6. Display Order Details Based on Customer ID\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", & choice);

        switch (choice)
        {
            case 1:
            {
                // Add new customers
                add_customer(arr, & n);
                break;
            }
            case 2:
            {
                // Search for a customer by ID
                int32_t id;
                printf("Enter Customer ID to search: ");
                scanf("%d", & id);
                search_customer(arr, n, id);
                break;
            }
            case 3:
            {
                // List all customers
                list_customers(arr, n);
                break;
            }
            case 4:
            {
                // Add new orders
                add_order(a, & c);
                break;
            }
            case 5:
            {
                // List all orders
                list_orders(a, c);
                break;
            }
            case 6:
            {
                // Display orders based on customer ID
                fetch_details(arr, a, n, c);
                break;
            }
            case 7:
            {
                // Save data to files and exit
                save_to_file(arr, n);
                save_orders_to_file(a, c);
                printf("Exiting...\n");
                return 0;
            }
            default:
            {
                // Handle invalid choices
                printf("Invalid choice, please try again.\n");
            }
        }
    }
}


/***  end of file  ***/