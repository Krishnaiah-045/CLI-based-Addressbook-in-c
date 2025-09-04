#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"

// Sort contacts alphabetically by name
void sortContacts(AddressBook *addressBook)
{
    for (int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for (int j = 0; j < addressBook->contactCount - 1 - i; j++)
        {
            if (strcmp(addressBook->contacts[j].name, addressBook->contacts[j + 1].name) > 0)
            {
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }
}

// Display all contacts
void listContacts(AddressBook *addressBook, int sortCriteria)
{
    if (addressBook->contactCount == 0) 
    {
        printf(RED "\n+-------------------------------------------------------------+\n" RESET);
        printf(RED "|                  No contacts available                      |\n" RESET);
        printf(RED "+-------------------------------------------------------------+\n" RESET);
        return;
    }

    printf(BOLD CYAN "\n+-----------------------------------------------------------------------------------------------+\n" RESET);
    printf(BOLD CYAN "|%-3s | %-20s | %-15s | %-30s | %-20s \n" RESET, 
           "S.No", "Name", "Phone", "Email", "Location");
    printf(BOLD CYAN "+-----------------------------------------------------------------------------------------------+\n" RESET);

    for (int i = 0; i < addressBook->contactCount; i++) {
        printf("| %-3d | %-20s | %-15s | %-30s | %-20s \n",
               i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email,
               addressBook->contacts[i].location);
    }
    printf(BOLD CYAN "+-----------------------------------------------------------------------------------------------+\n" RESET);
}

// Initialize address book and load data
void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook);
    sortContacts(addressBook);
    printf(GREEN "\n[ INFO ] " RESET "Address Book initialized. %d contact(s) loaded and sorted by name.\n", addressBook->contactCount);
}

// Save and exit program
void saveAndExit(AddressBook *addressBook)
{
    sortContacts(addressBook);
    saveContactsToFile(addressBook);
    printf(GREEN "All contacts saved. Exiting program...\n" RESET);
    exit(EXIT_SUCCESS);
}

// Validation functions
int is_validname(char *name)
{
    if (name == NULL || strlen(name) == 0)
        return 0;
    for (int i = 0; name[i] != '\0'; i++)
    {
        if (!isalpha(name[i]) && name[i] != ' ')
        {
            return 0;
        }
    }
    return 1;
}

int is_validnumber(AddressBook *addressBook, char *number)
{
    int i = 0;
    while (number[i])
    {
        if (number[i] < '0' || number[i] > '9')
            return 0;
        i++;
    }
    return (i == 10);
}

int is_validemail(AddressBook *addressBook, char *mail)
{
    if (mail == NULL || strlen(mail) < 8)
        return 0;
    if (!isalpha(mail[0]))
        return 0;

    char *at = strchr(mail, '@');
    if (at == NULL || strchr(at + 1, '@') != NULL)
        return 0;

    char *dot_com = strstr(at, ".com");
    if (dot_com == NULL || strcmp(dot_com, ".com") != 0 || (dot_com - at) <= 1)
        return 0;

    int alpha_between = 0;
    for (char *p = at + 1; p < dot_com; p++)
    {
        if (isalpha(*p))
            alpha_between = 1;
        if (!isalnum(*p) && *p != '.')
            return 0;
    }
    if (!alpha_between)
        return 0;

    for (int i = 0; i < strlen(mail); i++)
    {
        if (isspace(mail[i])) return 0;
        if (!isalnum(mail[i]) && mail[i] != '.' && mail[i] != '@')
            return 0;
        if (mail[i] == '.' && (i == 0 || i == strlen(mail) - 1 || mail[i + 1] == '.'))
            return 0;
    }
    return 1;
}

int is_duplicate_name(AddressBook *addressBook, char *name)
{
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].name, name) == 0)
            return 1;
    }
    return 0;
}

int is_duplicate_number(AddressBook *addressBook, char *number)
{
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].phone, number) == 0)
            return 1;
    }
    return 0;
}

int is_duplicate_email(AddressBook *addressBook, char *mail)
{
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].email, mail) == 0)
            return 1;
    }
    return 0;
}

int is_validlocation(char *location)
{
    if (location == NULL || strlen(location) == 0)
        return 0;

    for (int i = 0; location[i] != '\0'; i++)
    {
        if (!isalpha(location[i]) && location[i] != ' ')
            return 0;
    }

    return 1;
}

// Confirm save
int askToSaveContact()
{
    char choice;
    while (1)
    {
        printf(YELLOW "Do you want to save this contact? (y/n): " RESET);
        scanf(" %c", &choice);
        while (getchar() != '\n');
        if (choice == 'y' || choice == 'Y')
            return 1;
        else if (choice == 'n' || choice == 'N')
            return 0;
        else
            printf(RED "Invalid choice. Please enter y or n.\n" RESET);
    }
}

// Create new contact
void createContact(AddressBook *addressBook)
{
    if (addressBook->contactCount >= MAX_CONTACTS)
    {
        printf(RED "\nThe address book is full. Cannot add more contacts.\n" RESET);
        return;
    }

    Contact newContact;
    int valid_input = 0;

    // Name
    while (!valid_input)
    {
        printf(CYAN "\nEnter name: " RESET);
        scanf(" %[^\n]", newContact.name);
        while (getchar() != '\n');

        if (is_validname(newContact.name))
        {
            if (!is_duplicate_name(addressBook, newContact.name))
                valid_input = 1;
            else
                printf(RED "Name already exists. Please enter a unique name.\n" RESET);
        }
        else
        {
            printf(RED "Invalid name. Only letters and spaces are allowed.\n" RESET);
        }
    }

    // Phone
    char number[20];
    valid_input = 0;
    while (!valid_input)
    {
        printf(CYAN "Enter phone number (10 digits): " RESET);
        scanf(" %19s", number);
        while (getchar() != '\n');

        if (is_validnumber(addressBook, number))
        {
            if (!is_duplicate_number(addressBook, number))
                valid_input = 1;
            else
                printf(RED "Phone number already exists.\n" RESET);
        }
        else
        {
            printf(RED "Invalid phone number. Must be exactly 10 digits.\n" RESET);
        }
    }
    strcpy(newContact.phone, number);

    // Email
    char mail[50];
    valid_input = 0;
    while (!valid_input)
    {
        printf(CYAN "Enter email: " RESET);
        scanf(" %[^\n]", mail);
        while (getchar() != '\n');

        if (is_validemail(addressBook, mail))
        {
            if (!is_duplicate_email(addressBook, mail))
                valid_input = 1;
            else
                printf(RED "Email already exists.\n" RESET);
        }
        else
        {
            printf(RED "Invalid email format. Example: name@example.com\n" RESET);
        }
    }
    strcpy(newContact.email, mail);

    // Location
    char location[50];
    valid_input = 0;
    while (!valid_input)
    {
        printf(CYAN "Enter location: " RESET);
        scanf(" %[^\n]", location);
        while (getchar() != '\n');

        if (is_validlocation(location))
            valid_input = 1;
        else
            printf(RED "Location cannot be empty.\n" RESET);
    }
    strcpy(newContact.location, location);

    printf(GREEN "\nContact details entered successfully.\n" RESET);
    if (askToSaveContact())
    {
        addressBook->contacts[addressBook->contactCount++] = newContact;
        sortContacts(addressBook);
        saveContactsToFile(addressBook);
        printf(GREEN "Contact saved to address book.\n" RESET);
    }
    else
    {
        printf(YELLOW "Contact not saved.\n" RESET);
    }
}

// Search contacts
void searchContact(AddressBook *addressBook)
{
    int choice;
    char searchTerm[50];
    int found = 0;

    printf(BOLD "\nSearch by:\n" RESET);
    printf("1. Name\n2. Phone Number\n3. Email\n4. Location\n");
    printf(CYAN "Enter choice: " RESET);
    scanf("%d", &choice);
    while (getchar() != '\n');

    printf(CYAN "Enter search term: " RESET);
    scanf(" %[^\n]", searchTerm);
    while (getchar() != '\n');

    printf(MAGENTA "\nSearch Results:\n" RESET);
    printf("--------------------------------------------------------------\n");

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if ((choice == 1 && strstr(addressBook->contacts[i].name, searchTerm) != NULL) ||
            (choice == 2 && strcmp(addressBook->contacts[i].phone, searchTerm) == 0) ||
            (choice == 3 && strcmp(addressBook->contacts[i].email, searchTerm) == 0) ||
            (choice == 4 && strstr(addressBook->contacts[i].location, searchTerm) != NULL))
        {
            printf(GREEN "Name: %s\nPhone: %s\nEmail: %s\nLocation: %s\n\n" RESET,
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email,
                   addressBook->contacts[i].location);
            found = 1;
        }
    }

    if (!found)
        printf(RED "No matching contact found.\n" RESET);
}

// Edit contact
void editContact(AddressBook *addressBook)
{
    char nameToEdit[50];
    int foundIndex = -1;
    int choice_field;
    int modified = 0;

    printf(CYAN "Enter name of contact to edit: " RESET);
    scanf(" %[^\n]", nameToEdit);
    while (getchar() != '\n');

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].name, nameToEdit) == 0)
        {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1)
    {
        printf(RED "Contact not found.\n" RESET);
        return;
    }

    Contact original = addressBook->contacts[foundIndex];
    Contact updated = original;

    printf(MAGENTA "\nContact found:\n" RESET);
    printf("Name: %s\nPhone: %s\nEmail: %s\nLocation: %s\n",
           original.name, original.phone, original.email, original.location);

    do
    {
        printf("\nEdit Menu:\n1. Name\n2. Phone\n3. Email\n4. Location\n5. Finish Editing\n");
        printf(CYAN "Enter choice: " RESET);
        if (scanf("%d", &choice_field) != 1)
        {
            printf(RED "Invalid input. Enter a number between 1 and 5.\n" RESET);
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (choice_field)
        {
        case 1: 
        {
            char newName[50];
            int valid = 0;
            while (!valid)
            {
                printf(CYAN "Enter new name: " RESET);
                scanf(" %[^\n]", newName);
                while (getchar() != '\n');

                if (!is_validname(newName))
                {
                    printf(RED "Invalid name. Only letters and spaces allowed.\n" RESET);
                    continue;
                }
                if (strcmp(original.name, newName) == 0 || !is_duplicate_name(addressBook, newName))
                {
                    strcpy(updated.name, newName);
                    modified = 1;
                    valid = 1;
                }
                else
                {
                    printf(RED "Name already exists.\n" RESET);
                }
            }
            break;
        }
        case 2: 
        {
            char newPhone[20];
            int valid = 0;
            while (!valid)
            {
                printf(CYAN "Enter new phone number: " RESET);
                scanf(" %19s", newPhone);
                while (getchar() != '\n');

                if (!is_validnumber(addressBook, newPhone))
                {
                    printf(RED "Invalid phone number. Must be 10 digits.\n" RESET);
                    continue;
                }
                if (strcmp(original.phone, newPhone) == 0 || !is_duplicate_number(addressBook, newPhone))
                {
                    strcpy(updated.phone, newPhone);
                    modified = 1;
                    valid = 1;
                }
                else
                {
                    printf(RED "Phone number already exists.\n" RESET);
                }
            }
            break;
        }
        case 3: 
        {
            char newEmail[50];
            int valid = 0;
            while (!valid)
            {
                printf(CYAN "Enter new email: " RESET);
                scanf(" %[^\n]", newEmail);
                while (getchar() != '\n');

                if (!is_validemail(addressBook, newEmail))
                {
                    printf(RED "Invalid email format.\n" RESET);
                    continue;
                }
                if (strcmp(original.email, newEmail) == 0 || !is_duplicate_email(addressBook, newEmail))
                {
                    strcpy(updated.email, newEmail);
                    modified = 1;
                    valid = 1;
                }
                else
                {
                    printf(RED "Email already exists.\n" RESET);
                }
            }
            break;
        }
        case 4: 
        {
            char newLocation[50];
            int valid = 0;
            while (!valid)
            {
                printf(CYAN "Enter new location: " RESET);
                scanf(" %[^\n]", newLocation);
                while (getchar() != '\n');

                if (is_validlocation(newLocation))
                {
                    strcpy(updated.location, newLocation);
                    modified = 1;
                    valid = 1;
                }
                else
                {
                    printf(RED "Location cannot be empty.\n" RESET);
                }
            }
            break;
        }
        case 5:
            printf(GREEN "Editing finished.\n" RESET);
            break;
        default:
            printf(RED "Invalid choice. Select between 1 and 5.\n" RESET);
        }
    }
    while (choice_field != 5);

    if (modified)
    {
        addressBook->contacts[foundIndex] = updated;
        sortContacts(addressBook);
        if (askToSaveContact())
        {
            saveContactsToFile(addressBook);
            printf(GREEN "Contact updated and saved.\n" RESET);
        }
        else
        {
            printf(YELLOW "Changes applied but not saved to file.\n" RESET);
        }
    }
    else
    {
        printf(YELLOW "No changes made to this contact.\n" RESET);
    }
}

// Delete contact
void deleteContact(AddressBook *addressBook)
{
    char nameToDelete[50];
    int foundIndex = -1;

    printf(CYAN "Enter name of contact to delete: " RESET);
    scanf(" %[^\n]", nameToDelete);
    while (getchar() != '\n');

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].name, nameToDelete) == 0)
        {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1)
    {
        for (int i = foundIndex; i < addressBook->contactCount - 1; i++)
        {
            addressBook->contacts[i] = addressBook->contacts[i + 1];
        }
        addressBook->contactCount--;
        sortContacts(addressBook);
        saveContactsToFile(addressBook);
        printf(GREEN "Contact deleted successfully.\n" RESET);
    }
    else
    {
        printf(RED "Contact not found.\n" RESET);
    }
}
