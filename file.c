#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"

void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fptr = fopen("Contact.txt", "w");
    if (fptr == NULL)
    {
        printf(RED "\n[ ERROR ] " RESET "Cannot open file: Contact.txt for writing.\n");
        return;
    }

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fptr, "%s,%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email,
                addressBook->contacts[i].location);
    }

    fclose(fptr);

    printf(GREEN "\n[ SUCCESS ] " RESET "All contacts saved to file: Contact.txt\n");
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fptr = fopen("Contact.txt", "r");
    if (fptr == NULL)
    {
        printf(YELLOW "\n[ INFO ] " RESET "No contact file found (Contact.txt). Starting with an empty address book.\n");
        addressBook->contactCount = 0;
        return;
    }

    int i = 0;
    while (i < MAX_CONTACTS &&
           fscanf(fptr, "%49[^,],%19[^,],%49[^,],%49[^\n]\n",
                  addressBook->contacts[i].name,
                  addressBook->contacts[i].phone,
                  addressBook->contacts[i].email,
                  addressBook->contacts[i].location) == 4)
    {
        i++;
    }

    addressBook->contactCount = i;
    fclose(fptr);

    printf(GREEN "\n[ SUCCESS ] " RESET "Loaded %d contact(s) from file: Contact.txt\n", addressBook->contactCount);
}
