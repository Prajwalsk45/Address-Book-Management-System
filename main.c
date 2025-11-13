/*
Project Title      : Address Book Management System
Author             : Prajwal S K
Date               : 3/11/2025
-------------------------------------------------------------------------------------------
Description:
This project implements a simple Address Book Management System in C. 
It allows users to store, manage, and retrieve contact details such as 
name, phone number, and email ID. 

-------------------------------------------------------------------------------------------
Functions:
1. create         :- Add new contacts with validation for name, phone number and emailid.
2. Search         :- Search contacts by name, phone number and emailid.
3. Edit           :- Edit existing contact details.
4. Delete         :- Delete contacts from the address book.
5. List           :- Display all contacts with sorting options (by name, phone, or email).
6. Save and exit  :- Save and load contact data from a file.

-------------------------------------------------------------------------------------------
Files :-
1. main.c       – Contains the main menu and program flow control.
2. contact.c    – Implements contact management functions (create, edit, delete, validate, sort, search, list).
3. file.c       – Handles saving and loading contacts from "contacts.txt".
4. populate.c   – (Optional) Provides dummy data for testing or initialization.
5. contact.h    – Contains structure definitions and function declarations.
6. file.h, populate.h – Contain respective module declarations.

-------------------------------------------------------------------------------------------

*/


#include <stdio.h>
#include "contact.h"

int main() {
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book
    //printf("%s %s %s\n",addressBook.contacts[0].name,addressBook.contacts[0].phone,addressBook.contacts[0].email);

    do {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                int z;
                searchContact(&addressBook,&z);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:
                printf("Select sort criteria:\n");
                printf("1. Sort by name\n");
                printf("2. Sort by phone\n");
                printf("3. Sort by email\n");
                printf("Enter your choice: ");
                int sortChoice;
                scanf("%d", &sortChoice);
                listContacts(&addressBook, sortChoice);
                break;
            case 6:
                printf("Saving and Exiting...\n");
                saveContactsToFile(&addressBook);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
    
       return 0;
}
