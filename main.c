/*
 * contact_man.c
 * 
 * This is a simple contact manager program
 * 
 * This program is implemented as a linked list with each contact as a
 * node in the list. The contacts are read from a plaintext file named
 * .contacts with the format
 * name:phone number:email
 * The name email and phone number cannot contain the ":" character 
 * which is used as a delimeter
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

Contact* add_to_list(Contact* head, Contact* new_contact);
void print_contacts(Contact* head);

int main(int argc, char* argv[])
{
    Contact* head = NULL;

    FILE* fp;
    fp = fopen(CONTACT_FILE, "r");
    if (fp == NULL)
    {
        printf("File not successfully opened\n");
        return -1;
    }

    Contact new_contact;
    while (fscanf(fp, " %s %s %s \n", new_contact.name, 
           new_contact.phone, new_contact.email) != EOF)
    {
        head = add_to_list(head, &new_contact);
    }

    fclose(fp);

    print_contacts(head);
    return 0;
}

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
