#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) 
{
  int limit=addressBook->contactCount;

  FILE *fp;
  fp= fopen("addressbook.csv","w+");
  
  for(int i=0; i<limit; i++)
  {
    fprintf(fp,"%s,%s,%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
  }

  fclose(fp);
}

void loadContactsFromFile(AddressBook *addressBook)
{
  int i = 0;
  FILE *fp;

  fp = fopen("addressbook.csv", "r");

  if(fp == NULL)
  {
    printf("File doesn't exist\n");
    return;
  }

  while(fscanf(fp, "%49[^,],%19[^,],%49[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email) == 3)
  {
    i++;
  }

  addressBook->contactCount = i;

  fclose(fp);
}
