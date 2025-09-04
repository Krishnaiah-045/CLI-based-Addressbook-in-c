#include <stdio.h>
#include "contact.h"

int main()
{
    int choice;
    AddressBook addressBook;
    initialize(&addressBook);

    do
    {
        printf(BOLD CYAN "\n========================================\n" RESET);
        printf(BOLD BLUE  "-------- ADDRESS BOOK MAIN MENU --------\n" RESET);
        printf(BOLD CYAN "========================================\n" RESET);
        printf(YELLOW "|  1. Create Contact                  |\n" RESET);
        printf(YELLOW "|  2. Search Contact                  |\n" RESET);
        printf(YELLOW "|  3. Edit Contact                    |\n" RESET);
        printf(YELLOW "|  4. Delete Contact                  |\n" RESET);
        printf(YELLOW "|  5. List All Contacts               |\n" RESET);
        printf(YELLOW "|  6. Save and Exit                   |\n" RESET);
        printf(BOLD CYAN "========================================\n" RESET);
        printf(CYAN "Enter your choice (1-6): " RESET);
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf(BOLD GREEN "\n========================================\n" RESET);
            printf(BOLD GREEN "         >>> CREATE NEW CONTACT <<<     \n" RESET);
            printf(BOLD GREEN "========================================\n" RESET);
            createContact(&addressBook);
            printf(BOLD GREEN "========================================\n\n" RESET);
            break;

        case 2:
            printf(BOLD GREEN "\n========================================\n" RESET);
            printf(BOLD GREEN "          >>> SEARCH CONTACT <<<        \n" RESET);
            printf(BOLD GREEN "========================================\n" RESET);
            searchContact(&addressBook);
            printf(BOLD GREEN "========================================\n\n" RESET);
            break;

        case 3:
            printf(BOLD GREEN "\n========================================\n" RESET);
            printf(BOLD GREEN "           >>> EDIT CONTACT <<<         \n" RESET);
            printf(BOLD GREEN "========================================\n" RESET);
            editContact(&addressBook);
            printf(BOLD GREEN "========================================\n\n" RESET);
            break;

        case 4:
            printf(BOLD GREEN "\n========================================\n" RESET);
            printf(BOLD GREEN "          >>> DELETE CONTACT <<<        \n" RESET);
            printf(BOLD GREEN "========================================\n" RESET);
            deleteContact(&addressBook);
            printf(BOLD GREEN "========================================\n\n" RESET);
            break;

        case 5:
            printf(BOLD GREEN "\n========================================\n" RESET);
            printf(BOLD GREEN "       >>> LIST OF ALL CONTACTS <<<     \n" RESET);
            printf(BOLD GREEN "========================================\n" RESET);
            listContacts(&addressBook, 0);
            printf(BOLD GREEN "========================================\n\n" RESET);
            break;

        case 6:
            printf(BOLD GREEN "\n========================================\n" RESET);
            printf(BOLD GREEN "       Saving data and exiting...       \n" RESET);
            printf(BOLD GREEN "========================================\n\n" RESET);
            saveAndExit(&addressBook);
            break;

        default:
            printf(RED "\n========================================\n" RESET);
            printf(RED "       Invalid choice. Try again.       \n" RESET);
            printf(RED "========================================\n\n" RESET);
        }

    } while (choice != 6);

    return 0;
}
