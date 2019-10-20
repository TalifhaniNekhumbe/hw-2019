// allocator.c
#define _DEFAULT_SOURCE
#include "allocator.h"
#include <stdio.h>
#include <unistd.h>
#include <stddef.h>
#include <string.h>


int Round(size_t size);
void* nullpt();


/** Allocate a block of at least the requested size **/
void* custom_malloc(size_t size) {


	size +=sizeof(struct block);
	struct block* newblock;
       // printf("%d\n",size)
	size = Round(size);
	if(head == NULL){
	newblock =(struct block*)sbrk(MAX_SIZE);
	newblock->size  =MAX_SIZE;
	newblock->buddy	=NULL;
	newblock->free  =true;
	for(int i =0;i<20;i++){
		newblock->merge_buddy[i] = NULL;
	}
	newblock->next = NULL;
	head =newblock;


	}




		int k=0;
		while(head->size >size){

	        struct block* newnewblock =(struct block*)sbrk(((head->size)/2)+head->size);
		head->free  =true;
		newnewblock->free = true;
		head->buddy = newnewblock;

                head->merge_buddy[k] = head->buddy;
		k++;

		head->size /=2;
	//	print_list();



}


	head->data = head +sizeof(struct block);

return head->data;


}



/** Mark a data block as free and merge free buddy blocks **/
void custom_free(void* ptr) {
  if(ptr == NULL)
	return;

}

/** Change the memory allocation of the data to have at least the requested size **/
void* custom_realloc(void* ptr, size_t size) {
    // TODO
		if((ptr == NULL )){
			    return custom_malloc(0);
		}
		if(ptr == NULL){
			return custom_malloc(size);
		}
    void *newptr = custom_malloc(size);
		if(newptr == NULL){
			    return NULL;
		}

return newptr;
}




int Round(size_t size){

size_t power= 1;

while(power <size){
power *=2;
}
return power;;
}

void* nullpt(){
return NULL;
}


/*------------------------------------*\
|            DEBUG FUNCTIONS           |
\*------------------------------------*/

/** Prints the metadata of a block **/
void print_block(struct block* b) {
    if(!b) {
        printf("NULL block\n");
    }
    else {
        int i = 0;
        printf("Strt = %p\n",b);
        printf("Size = %lu\n",b->size);
        printf("Free = %s\n",(b->free)?"true":"false");
        printf("Data = %p\n",b->data);
        printf("Next = %p\n",b->next);
        printf("Buddy = %p\n",b->buddy);
        printf("Merge Buddies = ");
        while(b->merge_buddy[i] && i < MAX_EXP) {
            printf("%p, ",b->merge_buddy[i]);
            i++;
        }
        printf("\n\n");
    }
}

/** Prints the metadata of all blocks **/
void print_list() {
    struct block* curr = head;
    printf("--HEAP--\n");
    if(!head) printf("EMPTY\n");
    while(curr) {
        print_block(curr);
        curr = curr->next;
    }
    printf("--END--\n");
}
