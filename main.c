/*
 * contact_man.c
 * 
 * This is a simple contact manager program
 * 
 * This program is implemented as a linked list with each contact as a
 * node in the list. The contacts are read from a plaintext file named
 * .contacts with the format
 * name phone_number email
 * 
 * 
 * Usage: ./contacts
 * 
 **/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 40
#define PHONE_LEN 15
#define EMAIL_LEN 50

#define CONTACT_FILE ".contacts"

typedef struct Contact
{
    char name[NAME_LEN];
    char phone[PHONE_LEN];
    char email[EMAIL_LEN];
    struct Contact* next;
}Contact;

// function prototypes
void main_menu(Contact* head);
Contact* load_contacts();
Contact* add_to_list(Contact* head, Contact* new_contact);
void print_contacts(Contact* head);
void add_contact();
void edit_contact();
void remove_contact();

int main(int argc, char* argv[])
{
    Contact* contacts_list = load_contacts();

    main_menu(contacts_list);
    //print_contacts(contacts_list);
    return 0;
}

/*
 * Displays the main menu and handles user selection
 * Paraeter: HEAD, pointer to contact linked list head
 */
 
void main_menu(Contact* head)
{
    // menu loop
    while (1)
    {
        printf("MAIN MENU\n");
        printf("1. Add Contact\n");
        printf("2. Edit Contact\n");
        printf("3. Remove Contact\n");
        printf("4. Print All Contacts\n");
        printf("5. Quit\n\n");
        
        printf("Please select an option (1/2/3/4/5): ");
        
        // a character is expected from the user
        // if more than one charachter is typed, it gets the first one 
        // and discards the rest
        char option;
        scanf(" %c", &option);
        while(option != '\n' && getchar() != '\n');
        
        switch (option)
        {
            case '1':
                //add_contact();
                break;
            case '2':
                //edit_contact();
                break;
            case '3':
                //remove_contact();
                break;
            case '4':
                print_contacts(head);
                break;
            case '5':
                return;
        }
    }
}

/*
 * Load contacts from file to memory
 * Returns pointer to head of contact linked list 
 */
 
Contact* load_contacts()
{
    Contact* head = NULL;

    FILE* fp;
    fp = fopen(CONTACT_FILE, "r");
    if (fp == NULL)
    {
        printf("File not successfully opened\n");
        return NULL;
    }

    Contact new_contact;
    while (fscanf(fp, " %s %s %s \n", new_contact.name, 
           new_contact.phone, new_contact.email) != EOF)
    {
        head = add_to_list(head, &new_contact);
    }

    fclose(fp);
    return head;
}

/*
 * Add a contact to linked list of contacts
 * Parameters: HEAD, pointer to linked list head
 *             NEW_CONTACT, pointer to new contact
 * Returns: pointer to linked list head
 */
 
Contact* add_to_list(Contact* head, Contact* new_contact)
{
    // new node
    Contact* new_node = malloc(sizeof(Contact));
    new_node->next = NULL;

    // copy data
    strcpy(new_node->name, new_contact->name);
    strcpy(new_node->phone, new_contact->phone);
    strcpy(new_node->email, new_contact->email);

    // empty list
    if (head == NULL)
    {
        return new_node;
    }

    // at beginning
    if (strcmp(new_node->name, head->name) <= 0)
    {
        new_node->next = head;
        return new_node;
    }

    // middle
    Contact* cursor = head;
    Contact* previous = NULL;
    while (cursor->next != NULL)
    {
        if (strcmp(new_node->name, cursor->name) <= 0)
        {
            new_node->next = cursor;
            previous->next = new_node;
            return head;
        }
        previous = cursor;
        cursor = cursor->next;
    }
    if (strcmp(new_node->name, cursor->name) <= 0)
    {
        new_node->next = cursor;
        previous->next = new_node;
        return head;
    }

    // end
    cursor->next = new_node;
    return head;
}

/*
 * Print all contacts in memory
 */
 
void print_contacts(Contact* head)
{
    while (head != NULL)
    {
        printf("NAME: %s\n", head->name);
        printf("PHONE: %s\n", head->phone);
        printf("EMAIL: %s\n\n", head->email);
        head = head->next;
    }
}
