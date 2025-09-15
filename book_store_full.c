#include<stdio.h>
#include<string.h>

// Staff Panel Structure
struct Books {
    char book_name[50];
    char author[50];
    float price;
    int quantity;
};

struct Books count[100];
int bcount = 0;


// Remove newline function
void removenewline(char *str) {
    int len = strlen(str);
    if(len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

// Add book
void addBook() {
    getchar();
    printf("Enter Book name : ");
    fgets(count[bcount].book_name, sizeof(count[bcount].book_name), stdin);
    removenewline(count[bcount].book_name);

    printf("Enter Book Author : ");
    fgets(count[bcount].author, sizeof(count[bcount].author), stdin);
    removenewline(count[bcount].author);

    printf("Enter Book Price : ");
    scanf("%f", &count[bcount].price);
    getchar();

    printf("Enter Book quantity : ");
    scanf("%d", &count[bcount].quantity);
    getchar();

    printf("\nBook added successfully!\n");
    bcount++;
}

// Update book
void updateBook() {
    char bukuname[50];
    int found = 0;

    getchar();
    printf("Search your book by name:\n");
    fgets(bukuname, sizeof(bukuname), stdin);
    removenewline(bukuname);

    for (int i = 0; i < bcount; i++) {
        if (strcmp(count[i].book_name, bukuname) == 0) {
            found = 1;
            printf("Update Book name: ");
            fgets(count[i].book_name, sizeof(count[i].book_name), stdin);
            removenewline(count[i].book_name);

            printf("Update Book Author: ");
            fgets(count[i].author, sizeof(count[i].author), stdin);
            removenewline(count[i].author);

            printf("Update Book Price: ");
            scanf("%f", &count[i].price);
            getchar();

            printf("Update Book quantity: ");
            scanf("%d", &count[i].quantity);
            getchar();

            printf("Book Updated Successfully!\n");
            break;
        }
    }
    if (!found) {
        printf("Book not found\n");
    }
}

// Remove book
void removebook() {
    char name1[50];
    int bookfound = 0;

    getchar();
    printf("Search your book that you want to remove: ");
    fgets(name1, sizeof(name1), stdin);
    removenewline(name1);

    for (int ii = 0; ii < bcount; ii++) {
        if (strcmp(count[ii].book_name, name1) == 0) {
            bookfound = 1;
            for (int j = ii; j < bcount - 1; j++) {
                count[j] = count[j + 1];
            }
            bcount--;
            printf("Book removed successfully!\n");
            break;
        }
    }
    if (!bookfound) {
        printf("Book not found\n");
    }
}

// Display books
void displaybooks() {
    if (bcount == 0) {
        printf("No books available.\n");
        return;
    }
    for (int i = 0; i < bcount; i++) {
        printf("\n\tBOOK %d\n", i + 1);
        printf("\tNAME: %s\n", count[i].book_name);
        printf("\tAUTHOR: %s\n", count[i].author);
        printf("\tPRICE: %.2f\n", count[i].price);
        printf("\tQUANTITY: %d\n", count[i].quantity);
    }
}

void stuff() {
    int choice;
    do {
        printf("\n\t|| STAFF PANEL ||\n");
        printf("\t1. ADD BOOKS\n");
        printf("\t2. UPDATE BOOKS\n");
        printf("\t3. DISPLAY BOOKS\n");
        printf("\t4. REMOVE BOOKS\n");
        printf("\t5. EXIT\n");

        printf("Enter Your Choice: ");
        scanf("%d", &choice);

        if (choice == 1) addBook();
        else if (choice == 2) updateBook();
        else if (choice == 3) displaybooks();
        else if (choice == 4) removebook();
        else if (choice == 5) printf("You have exited the program.\n");
        else printf("Wrong Input! Please try again.\n");

    } while (choice != 5);
}

// Order structure
struct order {
    char order_name[50];
    int order_quantity;
};
struct order totalorder[100];
int book_order_quantity = 0;

//==>search book by name or title
void search_book() {
    char search_name[50];
    getchar();
    printf("Enter your book name that you want to search: ");
    fgets(search_name, sizeof(search_name), stdin);
    removenewline(search_name);

    int found = 0;
    for (int i = 0; i < bcount; i++) {
        if (strcmp(count[i].book_name, search_name) == 0) {
            found = 1;
            printf("\tNAME: %s\n", count[i].book_name);
            printf("\tAUTHOR: %s\n", count[i].author);
            printf("\tPRICE: %.2f\n", count[i].price);
            printf("\tQUANTITY: %d\n", count[i].quantity);
        }
    }
    if (!found) printf("Book not found\n");
}

//==>Place an order
void book_order() {
    char search_name[50];
    getchar();
    printf("Enter your book name that you want to order: ");
    fgets(search_name, sizeof(search_name), stdin);
    removenewline(search_name);

    if (bcount == 0) {
        printf("No books available.\n");
        return;
    }

    int found = 0;
    for (int i = 0; i < bcount; i++) {
        if (strcmp(count[i].book_name, search_name) == 0 && count[i].quantity > 0) {
            found = 1;
            strcpy(totalorder[book_order_quantity].order_name, count[i].book_name);
            totalorder[book_order_quantity].order_quantity = 1;
            book_order_quantity++;
            count[i].quantity--;
            printf("Your Order placed successfully\n");
            break;
        }
    }
    if (!found) printf("The book was not found or out of stock\n");
}

//==> Cancel order
void cancel_order() {
    char cancel_book[50];
    getchar();
    printf("Enter the book name that you want to cancel: ");
    fgets(cancel_book, sizeof(cancel_book), stdin);
    removenewline(cancel_book);

    int found = 0;
    for (int i = 0; i < book_order_quantity; i++) {
        if (strcmp(totalorder[i].order_name, cancel_book) == 0) {
            found = 1;
            // restore stock
            for (int j = 0; j < bcount; j++) {
                if (strcmp(count[j].book_name, cancel_book) == 0) {
                    count[j].quantity += totalorder[i].order_quantity;
                    break;
                }
            }

            for (int j = i; j < book_order_quantity - 1; j++) {
                totalorder[j] = totalorder[j + 1];
            }
            book_order_quantity--;
            printf("Order cancelled and stock updated successfully!\n");
            break;
        }
    }
    if (!found) printf("Order Not found\n");
}

//view order function
void view_order() {
    if (book_order_quantity == 0) {
        printf("You have ordered no books\n");
        return;
    }
    for (int i = 0; i < book_order_quantity; i++) {
        printf("Order No: %d\n", i + 1);
        printf("Book: %s\n", totalorder[i].order_name);
        printf("Quantity: %d\n", totalorder[i].order_quantity);
    }
}

void customer() {
    int choice1;
    do {
        printf("\n\t|| CUSTOMER PANEL ||\n");
        printf("\t1. SEARCH BOOKS\n");
        printf("\t2. ORDER BOOKS\n");
        printf("\t3. CANCEL ORDER\n");
        printf("\t4. DISPLAY ORDERS\n");
        printf("\t5. EXIT\n");

        printf("ENTER YOUR CHOICE: ");
        scanf("%d", &choice1);

        if (choice1 == 1) search_book();
        else if (choice1 == 2) book_order();
        else if (choice1 == 3) cancel_order();
        else if (choice1 == 4) view_order();
        else if (choice1 == 5) printf("You have exited the program.\n");
        else printf("Wrong Input! Please try again.\n");

    } while (choice1 != 5);
}

int main() {
    int mainchoice;
    do {
        printf("\n\tChoose your option:\n");
        printf("\t1. STAFF PANEL\n");
        printf("\t2. CUSTOMER PANEL\n");
        printf("\t3. EXIT MENU\n");

        printf("Enter Your Choice: ");
        scanf("%d", &mainchoice);

        if (mainchoice == 1) stuff();
        else if (mainchoice == 2) customer();
        else if (mainchoice == 3) printf("Exited successfully\n");
        else printf("Wrong choice\n");

    } while (mainchoice != 3);

    return 0;
}
