#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
int is_valid_name(char* name, AddressBook *addressBook);
int is_valid_phonenum(char* phone_num, AddressBook *addressBook);
int is_valid_email(char* email_id, AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void search_by_name(AddressBook *addressBook);
void search_by_phone_num(AddressBook *addressBook);
void search_by_email(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void editByName(AddressBook *addressBook);
void editByPhone(AddressBook *addressBook);
void editByEmail(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void deleteByName(AddressBook *addressBook);
void deleteByPhone(AddressBook *addressBook);
void deleteByEmail(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);

#endif
