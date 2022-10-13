#include "list.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

void print_controls();
struct Address* input_entry();
int get_index();
//char* get_key();
struct Address* populate_list(FILE* file, struct Address* list);
FILE* open_input(char* uri);

int main()
{
    int control = 0;
    char* input;
    int index;
    struct Address* list = NULL;
    char key[64];
    list = populate_list(open_input("address.txt"), list);    
    print_controls();
    do
    {
        printf("Pasirinkite norimą funkciją:\n");
        fscanf(stdin, "%d", &control);
        fflush(stdin);
        switch(control)
        {
            case 0:
            break;
            case 1:
            display_list(list);
            break;
            case 2:
            append(list, input_entry());
            break;
            case 3:
            insert(list, input_entry(), get_index());
            break;
            case 4:
            remove_entry(list, get_index());
            break;
            case 5:
            delete_list(&list);
            break;
            case 6:
            display_entry(search_index(list, get_index()));
            break;
            case 7:
            printf("Įveskite paieškos raktą: ");
            fscanf(stdin, "%s", &key);
            display_entry(search_key(key, list));
            break;
            case 8:
            print_controls();
            break;
            default:
            printf("Pasirinkimas neatpažintas, bandykite dar kartą.\n");
        }        
    } while (control);
}

//Spausdinamas pasirinkimų langas
void print_controls()
{
    printf("1: Spausdinti adresų knygą\n"
    "2: Pridėti įrašą prie galo\n"
    "3: Pridėti įrašą į nurodytą poziciją\n"
    "4: Ištrinti įrašą nurodytoje pozicijoje\n"
    "5: Ištrinti sąrašą\n"
    "6: Ieškoti įrašo pagal poziciją\n"
    "7: Ieškoti įrašo pagal vardą, pavardę, telefono numerį arba el. paštą\n"
    "8: Spausdinti pasirinkimus\n"
    "0: Užbaigti programos veikimą\n");
}

//Nuskaitomi vartotojo duomenys ir sukuriamas įrašas 
struct Address* input_entry()
{
    char name[36], surname[36], phone[16], email[64];
    printf("Įveskite vardą: ");
    fscanf(stdin, "%s", &name);
    fflush(stdin);
    printf("Įveskite pavardę: ");
    fscanf(stdin, "%s", &surname);
    fflush(stdin);
    printf("Įveskite telefono numerį: ");
    fscanf(stdin, "%s", &phone);
    fflush(stdin);
    printf("Įveskite el. paštą: ");
    fscanf(stdin, "%s", &email);
    fflush(stdin);
    struct Address* newNode = create_node(name, surname, phone, email);
    return newNode;
}

//Self-explanatory really
int get_index()
{
    int index;
    printf("Įveskite poziciją: ");
    fscanf(stdin, "%d", &index);
    return index;
}

/*char* get_key(){
    char key[64];
    printf("Įveskite paieškos raktą: ");
    fscanf(stdin, "%s", &key);
    fflush(stdin);
    return key;
}*/

//Inicijuojamas sąrašas iš duomenų, esančių pateiktame faile
struct Address* populate_list(FILE* file, struct Address* list)
{
    struct Address* temp = list; 
   char line[152];
   char* token;
   char name[36], surname[36], phone[16], email[64];
   while(fgets(line, sizeof(line), file) != NULL){
      token = strtok(line, " ");
      strcpy(name, token);
      token = strtok(NULL, " ");
      strcpy(surname, token);
      token = strtok(NULL, " "); 
      strcpy(phone, token);
      token = strtok(NULL, " "); 
      strcpy(email, token);
      struct Address* newNode = create_node(name, surname, phone, email);
      if(temp == NULL)
        temp = newNode;
      else
      append(temp, newNode);
   }
   fclose(file);
   return temp;
}

//Atidaromas failas skaitymui
FILE* open_input(char* uri)
{
    FILE* read;
    if((read = fopen(uri, "r")) == NULL){
        perror("Can't open file for reading");
        exit(1);
    }
    return read;
}