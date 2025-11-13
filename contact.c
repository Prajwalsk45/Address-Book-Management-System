#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
void sortbyname(AddressBook *addressBook)          //sorts the contacts by name
{
    for(int i = 0 ; i < (addressBook->contactCount)-1 ; i++)
    {
        for(int j = i + 1 ; j < addressBook->contactCount ; j++ )
        {
            if((strcmp(addressBook->contacts[i].name,addressBook->contacts[j].name))>0)
            {
                Contact temp = addressBook->contacts[i];
                addressBook->contacts[i] = addressBook->contacts[j];
                addressBook->contacts[j] = temp;
            }
        }
    }
}
void sortbyphone(AddressBook *addressBook)      //sorts the contacts by phone number
{
    for(int i = 0; i < (addressBook->contactCount)-1 ; i++ )        
    {
        for(int j = i + 1 ; j < addressBook->contactCount ; j++)
        {
            if((strcmp(addressBook->contacts[i].phone,addressBook->contacts[j].phone)) > 0)
            {
                Contact temp = addressBook->contacts[i];
                addressBook->contacts[i] = addressBook->contacts[j];
                addressBook->contacts[j] = temp;
            }
        }
    }
}
void sortbyemail(AddressBook *addressBook)      //sorts the contacts by email_id
{
    for(int i = 0; i< (addressBook->contactCount)-1 ; i++)
    {
        for(int j = i+1 ; j < addressBook->contactCount; j++)
        {
            if((strcmp(addressBook->contacts[i].email,addressBook->contacts[j].email)) > 0)
            {
                Contact temp = addressBook->contacts[i];
                addressBook->contacts[i] = addressBook->contacts[j];
                addressBook->contacts[j] = temp;
            }
        }
    }
}
void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the chosen criteria
    switch(sortCriteria){
        case 1:
            sortbyname(addressBook);
                for(int i = 0 ; i < addressBook->contactCount; i++)
                {
                    printf("%-10s\t %-10s\t %-10s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                }
            break;
        case 2:
            sortbyphone(addressBook);
                for(int i = 0 ; i < addressBook->contactCount; i++)
                {
                    printf("%-10s\t %-10s\t %-10s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                }
            break;
        case 3:
            sortbyemail(addressBook);
            for(int i = 0 ; i < addressBook->contactCount; i++)
            {
                printf("%-10s\t %-10s\t %-10s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            }
        break;
        default:printf("valid option\n");
    }
    
}

void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) 
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

int validate_name(char str[])
{
    //checks for charactres(only alphabets)    
    for(int i = 0 ; str[i] != '\0' ; i++)
    {
        if(!((str[i] >= 'A' && str[i] <= 'Z' ) ||(str[i] >= 'a' && str[i]<= 'z' ) || str[i]== ' ' ))
        {
            printf("Invalid name\n");
            return 0;
        }
    }
    return 1;
}
int validate_phone(AddressBook *addressBook,char str[])
{
    int flag = 0;
    int len = strlen(str);
    if(len != 10){                      //10 digits
        return 0;
    }
    
    for(int i = 0 ; str[i] != '\0'; i++)
    {       //'0' to '9'
        if(!(str[i] >= '0' && str[i] <= '9'))
        {
            return 0;
        }
    }

    for(int i = 0;i <addressBook->contactCount;i ++)
    {              //unique phone number or not
        if(!(strcmp(addressBook->contacts[i].phone,str)))  flag++;
    }

    if(flag >= 1){
        return 0;
    }
    else if(flag == 0){
        return 1;
    }
    
}

int validate_email(AddressBook *addressBook,char str[])
{
    int flag = 0;
    
    for(int i = 0 ;str[i] != '\0'; i++)      //only one @ must be present
    {       
        if(str[i] == '@'){
            flag++;
        }
    }
    
    if(flag == 0 || flag > 1)
    {
        return 0;
    }

    //unique
    int unique = 0;
    for(int i = 0;i < addressBook->contactCount;i++)
    {              //unique email or not
        if(!(strcmp(addressBook->contacts[i].email,str)))   unique++;
    }
    if(unique >= 1 )
    {
        return 0;
    }
    
    
    //.com , .com at the end and only one .com
    char com[] = ".com";
    int f = 0;
    int found = 0;
    int k = 0;
    int count = 0;
    for(int i = 0; str[i] != '\0'; i++)
    {    
        f = 0;
        if(str[i] == com[0])
        {
            k = i+1;
            for(int j = 1 ; com[j] != '\0'; j++)
            {
                
                if(str[k] != com[j])
                {
                    f = 0;               //breaks if didnot match
                    break;
                }
                else
                {
                    f = 1;
                    k++;
                    continue;
                }
                
            }
            count++;
        }
        if (f == 1 && str[k] == '\0' && count == 1)   //makes found one ,if .com has found at end and only one time
        {
                found = 1;
                break;
        }
    
    }
    if(found == 0) return 0;

    //all character should small
    for(int i = 0;str[i] != '\0';i++)
    {
        if(str[i] == '@' || str[i] == '.')
        {

            continue;
        }
        else if(!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9')))
        {
            return 0;
        }
       
        
    }

   //character before and after @
    int index;
    for(int i=0;str[i] != '\0';i++){
        if(str[i]=='@'){
            index=i;
            break;
        }
    }
    if (index == -1) {
         return 0;              // '@' not found
    }
    if (!(((str[index-1] >= 'a' && str[index 1] <= 'z') || (str[index-1] >= '0' && str[index-1] <= '9')) && ((str[index+1] >= 'a' && str[index+1] <= 'z') || (str[index+1] >= '0' && str[index+1] <= '9'))))
    {
        return 0;
    }
    

    return 1;

}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    printf("\nEnter name, phone number and email id to create add contact\n");
    char buffer_name[50];
    char buffer_phone[20];
    char buffer_email[50];
    int valid;
    int flag = 0;
    
    //to add name
    do{
        printf("Enter name :- ");
        scanf(" %[^\n]",buffer_name);
        valid = validate_name(buffer_name);
        if(valid == 1)
        {
            strcpy(addressBook->contacts[addressBook->contactCount].name,buffer_name);
            flag++;
        }
    }while(!valid);

    //to add phone number
    do{
        printf("Enter phone number :- ");
        scanf(" %[^\n]",buffer_phone);
        valid = validate_phone(addressBook,buffer_phone);
        if(valid == 1)
        {
            strcpy(addressBook->contacts[addressBook->contactCount].phone,buffer_phone);
            flag++;
        }
    }while(!valid);

    //to add email
    do{
        printf("Enter Email_Id :- ");
        scanf(" %[^\n]",buffer_email);
        valid = validate_email(addressBook,buffer_email);
        if(valid == 1){
            strcpy(addressBook->contacts[addressBook->contactCount].email,buffer_email);
            flag++;
        }
    }while(!valid);


    if(flag == 3) 
    {
        printf("Conctact Saved Successfully\n");
    }
    

    addressBook->contactCount++;    //incremeants conctactcount by 1;

}

int searchContact(AddressBook *addressBook,int* ptr) 
{
    /* Define the logic for search */
    printf("\nEnter the option to search:-\n1.Name\n2.Phone_number\n3.Email_id\n");
    int option;
    scanf("%d",&option);
    char buffer[50];
    int flag=0;

    switch (option)
    {
        case 1:
            printf("Enter Name to search:-");
            scanf(" %[^\n]",buffer);      //give space
            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(!(strcmp(buffer,addressBook->contacts[i].name)))
                {
                    *ptr = i;
                    printf("%d %s %s %s\n",i,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                    flag++;
                }
            }
            break;
        case 2:
            printf("Enter Phone number to search:-");
            scanf(" %[^\n]",buffer);
            for(int i = 0 ; i < addressBook->contactCount; i++)
            {
                if(!(strcmp(buffer,addressBook->contacts[i].phone)))
                {
                    *ptr=i;
                    printf("%d %s %s %s\n",i,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                    flag++;
                }
            }
            break;
        case 3:
            printf("Enter email_id to search:-");
            scanf(" %[^\n]",buffer);
            for(int i = 0 ; i < addressBook->contactCount; i++)
            {
                if(!(strcmp(buffer,addressBook->contacts[i].email)))
                {
                    *ptr=i;
                    printf("%d %s %s %s\n",i,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                    flag++;
                }
            }
            break;
        default:printf("Enter valid option\n");
            
    }
    if(flag == 0)
    {
        printf("content not found\n");
        return flag;
    }
    else if(flag == 1)
    {
        return flag;
    }
    else if(flag > 1)
    {
        return flag;
    }
}



int editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    int index;
    printf("\nSearch for the contact to edit");
    int res = searchContact(addressBook,&index);

    if(res == 0)
    {
        return 0;
    }
    else if(res > 1)
    {
        printf("enter which index number to edit :- ");
        scanf("%d",&index);
    }

    printf("\n1.Edit Name\n2.Edit Phone number\n3.Edit Email_Id\n");
    int option;
    scanf("%d",&option);
    char buffer[50];
    int valid;
    switch(option){
        case 1:
            do{
                printf("Enter new name : ");
                scanf(" %[^\n]",buffer);
                valid = validate_name(buffer);
                if(valid == 1)
                {
                    strcpy(addressBook->contacts[index].name,buffer);
                    printf("%d %s %s %s\n",index,addressBook->contacts[index].name,addressBook->contacts[index].phone,addressBook->contacts[index].email);
                }
                else
                {
                    printf("Enter Valid name\n");
                }
            }while(!valid);
            break;

        case 2:
            do{
                printf("Enter new Phone number : ");
                scanf(" %[^\n]",buffer);
                valid = validate_phone(addressBook,buffer);
                if(valid == 1)
                {
                    strcpy(addressBook->contacts[index].phone,buffer);
                    printf("%d %s %s %s\n",index,addressBook->contacts[index].name,addressBook->contacts[index].phone,addressBook->contacts[index].email);
                }
                else
                {
                    printf("Enter Valid Phone number\n");
                }
            }while(!valid);
            break;

        case 3:
            do{
                printf("Enter new Email_Id : ");
                scanf(" %[^\n]",buffer);
                valid = validate_email(addressBook,buffer);
                if(valid == 1){
                    strcpy(addressBook->contacts[index].email,buffer);
                    printf("%d %s %s %s\n",index,addressBook->contacts[index].name,addressBook->contacts[index].phone,addressBook->contacts[index].email);
                }
                else
                {
                    printf("Enter Valid Email Id\n");
                }
            }while(!valid);
            break;

        default:printf("enter valid option\n");
    }
    

}

int deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    printf("\nSearch for address to delete");
    int index;
    int res=searchContact(addressBook,&index);
    if(res == 0)
    {
        return 0;
    }
    else if(res > 1)
    {
        printf("enter which index number to delete :- ");
        scanf("%d",&index);
    }

    for(int i = index; i < addressBook->contactCount; i++)
    {
        addressBook->contacts[i]=addressBook->contacts[ i+1 ];
    }
    printf("Contact deleted\n");

    addressBook->contactCount--;

}
