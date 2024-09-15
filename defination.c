#include "header.h"

// Function to add customers to the array
void add_customer(struct Customer arr[], int32_t * n)
{
    if (* n >= MAX_CUSTOMERS)
    {
        printf("Cannot add more customers. Limit reached.\n");
        return;
    }

    int32_t count;
    printf("Enter number of Customers to add: ");
    scanf("%d", & count);

    if (* n + count > MAX_CUSTOMERS)
    {
        printf("Cannot add more customers. Limit reached.\n");
        return;
    }

    for (int32_t i = 0; i < count; i++)
    {
        printf("Enter customer ID, name, phone number, email, and "
        "address for customer %d:\n", * n + 1);
        scanf("%d ",& arr[* n].custid);
        scanf("%49s ",arr[* n].cname);
        scanf("%lld ",& arr[* n].phone);
        scanf("%49s ",arr[* n].email);
        scanf("%99[^\n]",arr[* n].address);
        (* n)++;
    }

    // Save updated customer list to file
    save_to_file(arr, * n);
}

// Function to search for a customer by ID
void search_customer(struct Customer arr[], int32_t n, int32_t id)
{
    for (int32_t i = 0; i < n; i++)
    {
        if (arr[i].custid == id)
        {
            // Print customer details if found
            printf("Customer ID: %d\n",arr[i].custid);
            printf("Name: %s\n",arr[i].cname);
            printf("Phone: %lld\n",arr[i].phone);
            printf("Email: %s\n",arr[i].email);
            printf("Address: %s\n",arr[i].address);
            return;
        }
    }
    // If not found
    printf("Customer with ID %d not found.\n", id);
}

// Function to list all customers
void list_customers(struct Customer arr[], int32_t n)
{
    if (n == 0)
    {
        printf("No customers to list.\n");
        return;
    }
    for (int32_t i = 0; i < n; i++)
    {
        // Print each customer's details
        printf("Customer ID: %d\n",arr[i].custid);
        printf("Name: %s\n",arr[i].cname);
        printf("Phone: %lld\n",arr[i].phone);
        printf("Email: %s\n",arr[i].email);
        printf("Address: %s\n",arr[i].address);
        printf("----------------------------\n");
    }
}

// Function to add orders to the array
void add_order(struct order a[], int32_t * c)
{
    if (* c >= MAX_ORDERS)
    {
        printf("Cannot add more orders. Limit reached.\n");
        return;
    }

    int32_t count;
    printf("Enter number of orders to add: ");
    scanf("%d", & count);

    if (* c + count > MAX_ORDERS)
    {
        printf("Cannot add more orders. Limit reached.\n");
        return;
    }

    for (int32_t i = 0; i < count; i++)
    {
        printf("Enter order ID, customer ID, product name "
              "and ordered date for order %d:\n", * c + 1);
        scanf("%d ",& a[* c].oid);
        scanf("%d ",& a[* c].custid);
        scanf("%49s ",a[* c].pname);
        scanf("%14[^\n]",a[* c].date);
        (* c)++;
    }

    // Save updated orders list to file
    save_orders_to_file(a, * c);
}

// Function to list all orders
void list_orders(struct order a[], int32_t c)
{
    if (c == 0)
    {
        printf("No orders to list.\n");
        return;
    }
    for (int32_t i = 0; i < c; i++)
    {
        // Print each order's details
        printf("Order ID: %d\n",a[i].oid);
        printf("Customer ID: %d\n",a[i].custid);
        printf("Product Name: %s\n",a[i].pname);
        printf("Date: %s\n",a[i].date);
        printf("----------------------------\n");
    }
}

// Function to save customer data to a file
void save_to_file(struct Customer arr[], int32_t n)
{
    FILE * file = fopen("Customer.csv", "w");
    if (file == NULL)
    {
        perror("Failed to open file for writing");
        exit(EXIT_FAILURE);
    }
    // Write header for CSV file
    fprintf(file, "cid,name,phone,mail,location\n");
    for (int32_t i = 0; i < n; i++)
    {
        // Write each customer's data to file
        fprintf(file, "%d,%s,%lld,%s,%s\n", 
                arr[i].custid, arr[i].cname, arr[i].phone, arr[i].email, arr[i].address);
    }
    fclose(file);
}

// Function to load customer data from a file
void load_from_file(struct Customer arr[], int32_t * n)
{
    FILE * file = fopen("Customer.csv", "r");
    if (file == NULL)
    {
        perror("Failed to open file for reading");
        return;
    }

    * n = 0;
    char8_t line[256];
    // Read each line of the file and parse customer data
    while (* n < MAX_CUSTOMERS && fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "%d,%49[^,],%lld,%49[^,],%99[^\n]", 
                   & arr[*n].custid, arr[*n].cname, & arr[*n].phone, 
                   arr[*n].email, arr[*n].address) == 5) {
            (* n)++;
        }
    }
    fclose(file);
}

// Function to save order data to a file
void save_orders_to_file(struct order a[], int32_t c)
{
    FILE * file = fopen("Order.csv", "w");
    if (file == NULL)
    {
        perror("Failed to open file for writing");
        exit(EXIT_FAILURE);
    }
    // Write header for CSV file
    fprintf(file, "oid,cid,product name,date\n");
    for (int32_t i = 0; i < c; i++)
    {
        // Write each order's data to file
        fprintf(file, "%d,%d,%s,%s\n", a[i].oid, a[i].custid, a[i].pname, a[i].date);
    }
    fclose(file);
}

// Function to load order data from a file
void load_orders_from_file(struct order arr[], int32_t * c)
{
    FILE * file = fopen("Order.csv", "r");
    if (file == NULL)
    {
        perror("Failed to open file for reading");
        return;
    }

    * c = 0;
    char8_t line[256];
    // Read each line of the file and parse order data
    while (* c < MAX_ORDERS && fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "%d,%d,%49[^,],%14[^\n]", & arr[*c].oid,
                   & arr[*c].custid, arr[*c].pname, arr[*c].date) == 4)
                   {
            (* c)++;
        }
    }
    fclose(file);
}

// Function to fetch and display order details based on customer ID
void fetch_details(struct Customer arr[], struct order a[], int32_t n, int32_t c)
{
    FILE * file = fopen("Order_details.txt", "w");
    if (file == NULL)
    {
        perror("Failed to open file for writing");
        return;
    }

    // Loop through each customer
    for (int32_t i = 0; i < n; i++)
    {
        int32_t flag = 0;
        fprintf(file, "Customer ID: %d\n", arr[i].custid);
        // Loop through each order and match with customer ID
        for (int32_t j = 0; j < c; j++)
        {
            if (arr[i].custid == a[j].custid)
            {
                // Write order details for the matched customer
                fprintf(file, "Customer Name: %s, Order ID: %d, Product Name: %s, "
                        "Ordered Date: %s\n", arr[i].cname, a[j].oid, a[j].pname, a[j].date);
                flag = 1;
            }
        }
        // If no orders found for the customer
        if (!flag)
        {
            fprintf(file, "No orders placed yet!\n");
        }
    }
    fclose(file);
}