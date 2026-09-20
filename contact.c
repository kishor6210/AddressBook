#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include <ctype.h>

void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria
    int flag=0;
    for(int i=0; i<addressBook->contactCount; i++)
    {
        if(!flag)
        {
            if(flag==0)
            {
                printf("\n--------------------List of All Contacts-----------------------\n");
                printf("\n%-5s %-25s %-20s %-25s\n","SNO","NAME", "PHONE NUMBER", "EMAIL");
            }
        }
        printf("%-5d %-25s %-20s %-25s\n", i+1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        flag=1;
    }
    if(flag==0)
    {
        printf("\n-------No contacts found-------\n");
    }

}

void initialize(AddressBook *addressBook) {
    //addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
    char name[20];
    char phone_num[50];
    char email_id[50];
	/* Define the logic to create a Contacts */
    while(1)
    {
        printf("\nEnter the name : ");
        getchar();
        scanf("%[^\n]", name);
        if(is_valid_name(name,addressBook))
        {
            strcpy(addressBook->contacts[addressBook->contactCount].name,name);
            break;
        }
    }

    while(1)
    {
        printf("\nEnter the Phone number : ");
        getchar();
        scanf("%[^\n]",phone_num);

        if(is_valid_phonenum(phone_num, addressBook))
        {
            strcpy(addressBook->contacts[addressBook->contactCount].phone, phone_num);
            break;
        }
    }
    
    while(1)
    {
        printf("\nEnter the Email : ");
        getchar();
        scanf("%[^\n]",email_id);

        if(is_valid_email(email_id, addressBook))
        {
            strcpy(addressBook->contacts[addressBook->contactCount].email, email_id);
            break;
        }
    }

    addressBook->contactCount++;
    printf("\nContact created successfully...\n");   
}

int is_valid_name(char* name, AddressBook *addressBook)
{
    int len=0;
    while(name[len]!='\0')
    {
        len++;
    }
    if(len<3)
    {
        printf("\nName should contain atleast 3 characters\n");
        return 0;
    }
    for(int i=0; i<len; i++)
    {
        if(!(isalpha(name[i])|| name[i]==' '||name[i]=='.'))
        {
            printf("\nName should contain only alphabets, single space and single dot\n");
            return 0;
        }
    }
    int space_count=0;
    int dot_count=0;
    for(int i=0;i<len;i++)
    {
       if(name[i]==' ')
       {
        space_count++;
       }
       if(name[i]=='.')
       {
        dot_count++;
       }
       
    }
    if(space_count>1)
    {
        printf("\nOnly one space is allowed\n");
        return 0;
    }
    if(dot_count>1)
    {
        printf("\nOnly one dot is allowed\n");
        return 0;
    }
    return 1;
}

int is_valid_phonenum(char* phone_num, AddressBook *addressBook)
{
    int len=0;
    while(phone_num[len]!='\0')
    {
        len++;
    }

    if(len<10)
    {
        printf("\nPhone number must contain 10 digits\n");
        return 0;
    }

    for(int i=0; i<len ; i++)
    {
        if(!isdigit(phone_num[i]))
        {
            printf("\nOnly digits are allowed\n");
            return 0;
        }
    }
    
    if(!(phone_num[0]>='6' && phone_num[0]<='9'))
    {
        printf("\nFirt digit must be between 6 and 9\n");
        return 0;
    }

    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].phone, phone_num) == 0)
        {
            printf("\nPhone number already exist\n");
            return 0;
        }
    }
    return 1;
}

int is_valid_email(char* email_id, AddressBook *addressBook)
{
    int len=0;
    int at_count=0;
    int dot_count=0;
    int at_index=-1;
    int dot_index=-1;

    while(email_id[len]!='\0')
    {
        len++;
    }

    for(int i=0; i<len; i++)
    {
        if(email_id[i]=='@')
        {
            at_count++;
            at_index=i;
        }
        else if(email_id[i]=='.')
        {
            dot_count++;
            dot_index=i;
        }
        else if(!(isalpha(email_id[i]) || isdigit(email_id[i])))
        {
            printf("\nInvalid symbol\n");
            return 0;
        }
    }

    if(at_count == 0)
    {
        printf("\nMissing @\n");
        return 0;
    }

    if(at_count > 1)
    {
        printf("\nMultiple @ symbols are not allowed\n");
        return 0;
    }

    if(dot_count == 0)
    {
        printf("\nMissing .\n");
        return 0;
    }

    if(dot_index < at_index)
    {
        printf("\nDot must appear after @\n");
        return 0;
    }

    if(dot_index == at_index + 1)
    {
        printf("\nAt least one character is required between @ and .\n");
        return 0;
    }

    char *res=strrchr(email_id,'.');
    if(strcmp(res,".com")!=0)
    {
        printf("\nonly .com should present at the end of email id\n");
        return 0;
    }

    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].email, email_id) == 0)
        {
            printf("Email ID already exists\n");
            return 0;
        }
    }

    return 1;
}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    int choice;
    do{
        printf("\n--------Search Contact---------\n");
        printf("1. Search by name\n");
        printf("2. Search by phone number\n");
        printf("3. Search by email id\n");
        printf("4. Exit\n");
        printf("\nEnetr your choice: ");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
            search_by_name(addressBook);
            break;

            case 2:
            search_by_phone_num(addressBook);
            break;

            case 3:
            search_by_email(addressBook);
            break;

            case 4:
            break;

            default:
            printf("Invalid choice");
        }
    }while(choice!=4);
}

void search_by_name(AddressBook *addressBook)
{
    char name[20];
    printf("Enter the name to search : ");
    getchar();
    scanf("%[^\n]", name);
    int flag=0;
    for(int i=0; i<addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].name,name)==0)
        {
            printf("\n-----------------Contact Found-------------------\n");
            printf("\n%-25s %-20s %-25s\n","NAME", "PHONE NUMBER", "EMAIL");
            printf("%-25s %-20s %-25s\n",addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            // printf("%s %s %s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            flag=0;
        }
    }

    if(flag=0)
    {
        printf("Name not found");
    }
}

void search_by_phone_num(AddressBook *addressBook)
{
    char phone_num[20];;
    printf("Enter the phone number to search : ");
    getchar();
    scanf("%[^\n]", phone_num);
    int flag=0;
    for(int i=0; i<addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].phone, phone_num)==0)
        {
            printf("\n-----------------Contact Found-------------------\n");
            printf("\n%-25s %-20s %-25s\n","NAME", "PHONE NUMBER", "EMAIL");
            printf("%-25s %-20s %-25s\n",addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            // printf("%s %s %s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            flag=1;
        }
    }

    if(flag=0)
    {
        printf("Phone number not found");
    }
}

void search_by_email(AddressBook *addressBook)
{
    char email_id[20];
    printf("Enter email id to search : ");
    getchar();
    scanf("%[^\n]", email_id);
    int flag=0;
    for(int i=0; i<addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].email,email_id)==0)
        {
            printf("\n-----------------Contact Found-------------------\n");
            printf("\n%-25s %-20s %-25s\n","NAME", "PHONE NUMBER", "EMAIL");
            printf("%-25s %-20s %-25s\n",addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            // printf("%s %s %s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            flag=1;
        }
    }
    if(flag=0)
    {
        printf("Email id not found");
    }

}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    int choice;
    do{
        printf("\n-------------Edit contact-----------\n");
        printf("1. Edit by Name\n");
        printf("2. Edit by Phone Number\n");
        printf("3. Edit by Email ID\n");
        printf("4. Exit\n");
        printf("\nEnter your choice : ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
            editByName(addressBook);
            break;

            case 2:
            editByPhone(addressBook);
            break;

            case 3:
            editByEmail(addressBook);
            break;

            case 4:
            break;

            default:
            printf("invalid Choice..");
        }
    }while(choice!=4); 
    
}

void editByName(AddressBook *addressBook)
{
    char name[50];
    char new_name[50];
    int count = 0;
    int index[100];
    int choice;

    printf("Enter name to edit: ");
    scanf(" %[^\n]", name);

    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].name, name) == 0)
        {
            index[count] = i;
            count++;
        }
    }

    if(count == 0)
    {
        printf("Contact not found\n");
        return;
    }

    if(count > 1)
    {
        printf("\nMultiple contacts found:\n");

        for(int i = 0; i < count; i++)
        {
            printf("%d. %s  %s  %s\n",
                   i + 1,
                   addressBook->contacts[index[i]].name,
                   addressBook->contacts[index[i]].phone,
                   addressBook->contacts[index[i]].email);
        }

        printf("Select contact: ");
        scanf("%d", &choice);

        if(choice < 1 || choice > count)
        {
            printf("Invalid choice\n");
            return;
        }

        choice = index[choice - 1];
    }
    else
    {
        choice = index[0];
    }

    while(1)
    {
        printf("Enter new name: ");
        scanf(" %[^\n]", new_name);

        if(is_valid_name(new_name,addressBook))
        {
            strcpy(addressBook->contacts[choice].name, new_name);
            printf("Name updated successfully\n");
            break;
        }
    }
}

void editByPhone(AddressBook *addressBook)
{
    char phone[20];
    char new_phone[20];
    int index = -1;

    printf("Enter phone number to edit: ");
    scanf("%s", phone);

    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].phone, phone) == 0)
        {
            index = i;
            break;
        }
    }

    if(index == -1)
    {
        printf("Contact not found\n");
        return;
    }

    while(1)
    {
        printf("Enter new phone number: ");
        scanf("%s", new_phone);

        if(is_valid_phonenum(new_phone, addressBook))
        {
            strcpy(addressBook->contacts[index].phone, new_phone);
            printf("Phone number updated successfully\n");
            break;
        }
    }
}

void editByEmail(AddressBook *addressBook)
{
    char email[50];
    char new_email[50];
    int index = -1;

    printf("Enter email ID to edit: ");
    scanf("%s", email);

    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].email, email) == 0)
        {
            index = i;
            break;
        }
    }

    if(index == -1)
    {
        printf("Contact not found\n");
        return;
    }

    while(1)
    {
        printf("Enter new email ID: ");
        scanf("%s", new_email);

        if(is_valid_email(new_email, addressBook))
        {
            strcpy(addressBook->contacts[index].email, new_email);
            printf("Email ID updated successfully\n");
            break;
        }
    }
}

void deleteContact(AddressBook *addressBook)
{
    int choice;

    while(1)
    {
        printf("\n---------- Delete Contact ----------\n");
        printf("1. Delete by Name\n");
        printf("2. Delete by Phone Number\n");
        printf("3. Delete by Email ID\n");
        printf("4. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                deleteByName(addressBook);
                break;

            case 2:
                deleteByPhone(addressBook);
                break;

            case 3:
                deleteByEmail(addressBook);
                break;

            case 4:
                return;

            default:
                printf("Invalid choice\n");
        }
    }
}

void deleteByName(AddressBook *addressBook)
{
    char name[50];
    int index[100];
    int count = 0;
    int choice;
    int confirm;

    printf("Enter name to delete: ");
    scanf(" %[^\n]", name);

    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].name, name) == 0)
        {
            index[count] = i;
            count++;
        }
    }

    if(count == 0)
    {
        printf("Contact not found\n");
        return;
    }

    if(count > 1)
    {
        printf("\nMultiple contacts found:\n");

        for(int i = 0; i < count; i++)
        {
            printf("%d. %s  %s  %s\n",
                   i + 1,
                   addressBook->contacts[index[i]].name,
                   addressBook->contacts[index[i]].phone,
                   addressBook->contacts[index[i]].email);
        }

        printf("Select contact to delete: ");
        scanf("%d", &choice);

        if(choice < 1 || choice > count)
        {
            printf("Invalid choice\n");
            return;
        }

        choice = index[choice - 1];
    }
    else
    {
        choice = index[0];
    }

    printf("\nName  : %s\n", addressBook->contacts[choice].name);
    printf("Phone : %s\n", addressBook->contacts[choice].phone);
    printf("Email : %s\n", addressBook->contacts[choice].email);

    printf("\nAre you sure you want to delete?\n");
    printf("1. Yes\n");
    printf("2. No\n");
    printf("Enter your choice: ");
    scanf("%d", &confirm);

    if(confirm == 1)
    {
        for(int i = choice; i < addressBook->contactCount - 1; i++)
        {
            addressBook->contacts[i] = addressBook->contacts[i + 1];
        }

        addressBook->contactCount--;

        printf("Contact deleted successfully\n");
    }
}

void deleteByPhone(AddressBook *addressBook)
{
    char phone[20];
    int index = -1;
    int confirm;

    printf("Enter phone number to delete: ");
    scanf("%s", phone);

    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].phone, phone) == 0)
        {
            index = i;
            break;
        }
    }

    if(index == -1)
    {
        printf("Contact not found\n");
        return;
    }

    printf("\nName  : %s\n", addressBook->contacts[index].name);
    printf("Phone : %s\n", addressBook->contacts[index].phone);
    printf("Email : %s\n", addressBook->contacts[index].email);

    printf("\nAre you sure you want to delete?\n");
    printf("1. Yes\n");
    printf("2. No\n");
    printf("Enter your choice: ");
    scanf("%d", &confirm);

    if(confirm == 1)
    {
        for(int i = index; i < addressBook->contactCount - 1; i++)
        {
            addressBook->contacts[i] = addressBook->contacts[i + 1];
        }

        addressBook->contactCount--;

        printf("Contact deleted successfully\n");
    }
}

void deleteByEmail(AddressBook *addressBook)
{
    char email[50];
    int index = -1;
    int confirm;

    printf("Enter email ID to delete: ");
    scanf("%s", email);

    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].email, email) == 0)
        {
            index = i;
            break;
        }
    }

    if(index == -1)
    {
        printf("Contact not found\n");
        return;
    }

    printf("\nName  : %s\n", addressBook->contacts[index].name);
    printf("Phone : %s\n", addressBook->contacts[index].phone);
    printf("Email : %s\n", addressBook->contacts[index].email);

    printf("\nAre you sure you want to delete?\n");
    printf("1. Yes\n");
    printf("2. No\n");
    printf("Enter your choice: ");
    scanf("%d", &confirm);

    if(confirm == 1)
    {
        for(int i = index; i < addressBook->contactCount - 1; i++)
        {
            addressBook->contacts[i] = addressBook->contacts[i + 1];
        }

        addressBook->contactCount--;

        printf("Contact deleted successfully\n");
    }
}
