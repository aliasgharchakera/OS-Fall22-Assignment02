#include <stdio.h>
#include <stdlib.h>
// copying the struct as given in the question

struct dll_node {
    struct dll_node *pfwd;
    struct dll_node *pbck;
    int size; //size of allocation in KBs
}; 

struct dll {
    struct dll_node *head;
    struct dll_node *tail;
    int available_memory;        //total size of memory available in KBs
};

// The code works on the free list or the other list depending on the value of the 
// s_freelist

void add_to_tail(struct dll *list, struct dll_node *new, int is_freelist)
{
    //add code here
    if (is_freelist==0){
    if ((list->head==NULL) && (list->tail==NULL)){
        list->head=new;
        list->tail=new;
        new->pfwd=NULL;
        new->pbck=list->head;
    }
    else {
     
     if(list->tail!=NULL)
      {list->tail->pfwd=new;  
      new->pbck=list->tail;
      list->tail=new;
      
      list->tail->pfwd=NULL; 
      }
    }
    list->available_memory-=(new->size+8);
    }
    else if ( is_freelist==1){
      if ((list->head==NULL) && (list->tail==NULL)){
        list->head=new;
        list->tail=new;
        new->pfwd=NULL;
        new->pbck=NULL;
    }
    else {
       
      list->tail->pfwd=new;  
      new->pbck=list->tail;
      list->tail=new;
      
      list->tail->pfwd=NULL; 
      
    }
    list->available_memory+=new->size;
    } 
              
        
    }
    
// getting new node using this struct command    
    
struct dll_node* get_new_node(alloc){
  struct dll_node* b = malloc(sizeof b);  
    b->size=alloc;
    b->pfwd=NULL;
    b->pbck=NULL;
  return b;  
    
}    
    
    
//remove the node once it is removed from the meory

struct dll_node *remove_from_head( struct dll *const list)
{
    //add code here
    struct dll_node* temp=malloc(sizeof temp);
    temp=list->head;
    list->head=list->head->pfwd;
    list->available_memory+=(temp->size+8);
    return temp;
}

//print list works only until the temp node does not point to the null

void  print_list(struct dll*list_1){
    struct dll_node *temp=list_1->head;
    while (temp!=NULL){
       printf("( %d ),",temp->size);
       temp=temp->pfwd; 
    }  
    
}



int main() {
    struct dll list, freelist;
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
        //struct dll_node *t = malloc(sizeof(struct dll_node));
        add_to_tail(&list, get_new_node(alloc), 0);
        //t->size = alloc;
        //t->pfwd=t->pbck=NULL;
        //add_to_tail(&list, t, 0);
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