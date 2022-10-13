#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/*
int main(){
    struct Address* list = NULL;
    list = create_node("jonas", "jonaitis", "+37061232201", "kekw@onlywin.com");
    append(list, create_node("nejonas", "nejonaitis", "512", "kas@yra.lt"));
    display_list(list);
    insert(list, create_node("aye", "lmao", "what's", "good?"), 1);
    display_list(list);
    insert(list, create_node("aye", "aye", "aye", "aye"), 7);
    display_list(list);


}
*/

//Sukuriamas sąrašo elementas
struct Address* create_node(char* name, char* surname, char* phone, char* email){
    struct Address* node = (struct Address*) malloc(sizeof(struct Address));
    strcpy(node->name, name);
    strcpy(node->surname, surname);
    strcpy(node->phone, phone);
    strcpy(node->email, email);
    node->next = NULL;
    return node;
}

//Sąrašas atspausdinamas nuo pateikto elemento
void display_list(struct Address* list)
{
    struct Address *current = list;
    while(current != NULL){
        printf("Name: %s %s\n"
        "Phone Number: %s\n"
        "Email: %s\n",
        current->name, current->surname,
        current->phone,
        current->email);
        printf("_________________________\n");
        current = current -> next;
    }
}

//Pridedamas elementas prie sąrašo galo
void append(struct Address* list, struct Address* newNode)
{
    struct Address* head = list;
    while(head->next != NULL){
        head = head->next;
    }
    head->next = newNode;
}

//Pašalinamas sąrašo elementas, duotoje pozicijoje
void remove_entry(struct Address* list, int index)
{
    struct Address* head = list;
    for(int i = 0; i < index - 1; i++){
        if(head->next!=NULL)
            head = head->next;
        else{
            printf("Cannot remove list member %d, it does not exist\n\n", index);
            return;
        }
    }
    struct Address* temp = head;
    head = head->next;
    temp->next = head->next;
    free(head);
    printf("\nĮrašas ištrintas.\n");
}

//Ištrinamas visas pateiktas sąrašas, atlaisvinama jam skirta atmintis
void delete_list(struct Address** list)
{
    struct Address* temp = *list;
    struct Address* next = NULL;
    while(temp != NULL){
        next = temp->next;
        free(temp);
        temp = next;
    }
    *list = NULL;
    printf("\nSąrašas ištrintas.\n");
}

//Grąžinamas sąrašo elementas pagal pateiktą poziciją
struct Address *search_index(struct Address* list, int index)
{
    struct Address* temp = list;
    for(int i = 0; i < index - 1 ; i++){
        if(temp->next != NULL)
            temp = temp -> next;
        else
            return NULL;
    }
    return temp;
}

//Grąžinamas pirmas sąrašo elementas pagal pateiktą paieškos raktą
//Neradus tokio elemento, grąžinama NULL
struct Address *search_key(char* key, struct Address* list)
{
    
    struct Address* temp = list;
    while(temp != NULL){
        if(!strcmp(temp->name, key) ||
        !strcmp(temp->surname, key) ||
        !strcmp(temp->phone, key) ||
        !strcmp(temp->email, key))
            return temp;
        else 
            temp = temp->next;
    }
    return NULL;
}

//Atspausdinamas pateiktas sąrašo elementas
void display_entry(struct Address* node){
    if(node != NULL){
        printf("Vardas: %s %s\n"
        "Telefono numeris: %s\n"
        "El. paštas: %s\n",
        node->name, node->surname,
        node->phone,
        node->email);
    }else{
        printf("Įrašas nerastas.\n");
    }
}

//Pateiktas elementas įterpiamas į pasirinktą poziciją sąraše
void insert(struct Address* list, struct Address* newNode, int index)
{
    struct Address* head = list;
    for(int i = 0; i < index - 2; i++){
        if(head != NULL)
            head = head->next;
        else{
            printf("Provided index (%d) is out of bounds for insertion\n", index);
            return;
        }
    }
    struct Address* nextNode = head->next;
    head->next = newNode;
    newNode->next = nextNode;
}