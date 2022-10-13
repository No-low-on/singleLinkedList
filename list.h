struct Address{
    char name[36];
    char surname[36];
    char phone[16];
    char email[64];
    struct Address *next;
};

void display_list(struct Address* list);
void append(struct Address* list, struct Address* newNode);
void insert(struct Address* list, struct Address* newNode, int index);
void remove_entry(struct Address* list, int index);
void delete_list(struct Address** list);
struct Address *search_index(struct Address* list, int index);
struct Address *search_key(char* key, struct Address* list);
struct Address *create_node(char *name, char *surname, char *phone, char *email);
void display_entry(struct Address* node);