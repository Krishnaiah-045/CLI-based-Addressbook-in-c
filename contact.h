#ifndef CONTACT_H
#define CONTACT_H
#include <stdio.h>
#include <stdlib.h>

#define MAX_CONTACTS 100

// 🎨 ANSI Color Codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

typedef struct Contact
{
    char name[50];
    char phone[20];
    char email[50];
    char location[50];
} Contact;

typedef struct
{
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

// Function declarations
void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook, int sortCriteria);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *addressBook);
void loadContactsFromFile(AddressBook *addressBook);
void saveAndExit(AddressBook *addressBook);

int is_validname(char *name);
int is_validnumber(AddressBook *addressBook, char *number);
int is_validemail(AddressBook *addressBook, char *mail);
int is_duplicate_name(AddressBook *addressBook, char *name);
int is_duplicate_number(AddressBook *addressBook, char *number);
int is_duplicate_email(AddressBook *addressBook, char *mail);
int askToSaveContact();
void sortContacts(AddressBook *addressBook);
int is_validlocation(char *location);

#endif
