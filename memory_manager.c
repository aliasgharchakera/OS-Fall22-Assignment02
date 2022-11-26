#include <stdio.h>
#include <stdlib.h>



typedef struct dll_node {
    struct dll_node *pfwd;
    struct dll_node *pbck;
    int size; //size of allocation in KBs
}dll_node; 

typedef struct dll {
    struct dll_node *head;
    struct dll_node *tail;
    int available_memory;        //total size of memory available in KBs
}dll;

dll_node *get_new_node(int alloc){
    dll_node *temp = malloc(sizeof(dll_node));
    temp->size = alloc;
    temp->pbck = NULL; temp->pfwd = NULL;
    return temp;
}

void add_to_tail(dll *list, dll_node *new_node, int is_freelist)
{
    //add code here
    
    if((list->head == NULL) && (list->tail == NULL)){
        list->head = new_node;
        list->tail = new_node;
    }
    else{
        new_node->pbck = list->tail;
        list->tail->pfwd = new_node;
        list->tail = new_node;
        list->tail->pfwd = NULL;
    }
    if(is_freelist)
        list->available_memory += new_node->size;
    else
        list->available_memory -= (new_node->size + 8);
}

dll_node *remove_from_head(dll *const list)
{
    //add code here
    dll_node* temp = malloc(sizeof(dll_node));
    temp = list->head;
    list->head = list->head->pfwd;
    list->available_memory += (temp->size + 8);
    return temp;
}

void print_list(dll *list){
    int done = 0;
    dll_node *node = malloc(sizeof(dll_node*));
    node = list->head;
    while(node != NULL){
        printf("( %d ),", node->size);
        node = node->pfwd;
    }
}

int main() {
    dll list, freelist;
    int available  = 0;
    int num_allocs = 0;
    int num_deallocs = 0;
    
    list.head = NULL;
    list.tail = NULL;
    freelist.head = NULL;
    freelist.tail = NULL;
    freelist.available_memory = 0;    //freelist is empty
    
    //first line is available memory given in bytes
    scanf("%d", &available);
    list.available_memory = available - 8;  
    
    //second line is the number of allocations
    scanf("%d", &num_allocs);
    
    for(int i=0; i<num_allocs; ++i)
    {
        int alloc=0;
        scanf("%d", &alloc);
        add_to_tail(&list, get_new_node(alloc), 0);
    }
     
    //following line is the number of deallocations
    scanf("%d", &num_deallocs);
    for(int i=0; i<num_deallocs; ++i)
    {
         add_to_tail(&freelist, remove_from_head(&list), 1);
    }
    
    puts("Allocator:");
    print_list(&list);    
    printf("\nAvailable mem: %d\n", list.available_memory);

    puts("Freelist:");
    print_list(&freelist);
    printf("\nAvailable mem (freelist): %d\n", freelist.available_memory);
    return 0;
}