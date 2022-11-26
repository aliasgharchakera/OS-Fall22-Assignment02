#include <stdio.h>
#include <stdlib.h>


// case 2 giving 7856
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

void add_to_tail(struct dll *list,struct dll_node *nodetoadd, int is_freelist)
{
    // if(list->tail==NULL){
    //     list->tail = nodetoadd;
    //     if(is_freelist){
    //         list->available_memory+=nodetoadd->size;
    //     }
    //     else{
    //         list->available_memory-=(nodetoadd->size+8);
    //     }
    //     return;
    // }
     
     
     
     if(list->head==NULL && list->tail==NULL){
         list->head=nodetoadd;
         list->tail=nodetoadd;
     }
     else{
         nodetoadd->pbck=list->tail;
         list->tail->pfwd=nodetoadd;
         list->tail = nodetoadd;
         list->tail->pfwd=NULL;
     }
     
     
    //add code here
    
    if (is_freelist){
        list->available_memory+=nodetoadd->size;
    }
    else{
        // nodetoadd->pbck=list->tail;
        // nodetoadd->pfwd=NULL;
        // nodetoadd->pbck=list->tail->pbck;
        // nodetoadd->pfwd=list->tail->pfwd;
        // list->tail=nodetoadd;
        // list->tail->pfwd=nodetoadd;
        // nodetoadd->pbck=list->tail;
        // nodetoadd->pfwd=NULL;
        // list->tail=nodetoadd;
        list->available_memory-=(nodetoadd->size+8);
    }
};

struct dll_node *remove_from_head(struct dll *const list)
{
    //add code here
    // struct dll_node *afterhead;
    // afterhead=list->head->pfwd;
    // struct dll_node *afterafterhead;
    // afterafterhead=afterhead->pfwd;
    // list->head->pfwd=afterafterhead;
    // afterafterhead->pbck=list->head;
    // // printf("in removefromhead afterhead.size=%d",afterhead->size);
    // return afterhead;
    // struct dll_node *newhead;
    // newhead=list->head->pfwd;
    // struct dll_node *oldhead;
    // oldhead=list->head;
    // list->head=newhead;
    // list->head->pbck=NULL;
    // oldhead->pfwd=NULL;
    // oldhead->pbck=NULL;
    // return oldhead;
    struct dll_node *curnode=list->head;
    // while (curnode->pbck!=NULL){
    //     curnode=curnode->pbck;
    // }
    // struct dll_node *nextnode=curnode->pfwd;
    // nextnode->pbck=NULL;
    // // list->head=nextnode;
    // list->available_memory+=curnode->size+8;
    list->head=list->head->pfwd;
    // printlist(list);
    list->available_memory+=curnode->size+8;
    return curnode;
    
};

struct dll_node *get_new_node(int alloc){
    struct dll_node *temp;
    temp=(struct dll_node*)malloc(sizeof(struct dll_node));
    temp->size=alloc;
    temp->pfwd=NULL;
    temp->pbck=NULL;
    
    return temp;
};

void print_list(struct dll *list){
    // struct dll_node *curnode=list->tail;
    // while (curnode->pbck!=NULL){
    //     printf("( %d ),",curnode->size);
    //     curnode=curnode->pbck;
    // }
    // printf("( %d ),",curnode->size);
    //function above prints and passes 1 testcase but list is in reverse order
    // //need to flip list maybe to pass all cases
    // struct dll_node *curnode=list->tail;
    // int n=1;
    // // if (curnode==NULL){
    // // printf("curnode testcase 3 check");}
    // // else{printf("curnode testcase 3 check %d",curnode->size);}
    // while (curnode->pbck!=NULL){
    //     n+=1;
    //     curnode=curnode->pbck;
    // }
    // //store all nodes in list and print list in reverse
    // struct dll_node *reverseorderlist[n];
    // struct dll_node *loopcurnode=list->tail;
    // for (int count=n;count>-1;count--){
    //         reverseorderlist[count]=loopcurnode;
    // }
    // for (int i=0;i<n;i++){
    //     printf("( %d ),",curnode->size);    
    // }
    // printf("( %d ),",curnode->size);
    
    struct dll_node* curnode = list->head;
    while (curnode!=NULL){
        printf("( %d ),",curnode->size);
        curnode = curnode->pfwd;
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
    
        add_to_tail(&list, get_new_node(alloc), 0);
    }
    // puts("added to tail");
     
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