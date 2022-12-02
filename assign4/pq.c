/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: Tun Aung Thaung 
 * Email: thaungt@oregonstate.edu
 */

#include <stdlib.h>
#include <stdio.h>

#include "pq.h"
#include "dynarray.h"

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct pq{
  struct dynarray* heap;
};


struct pq_node{
  int priority;
  void* value;
};


/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
  struct pq* pq = malloc(sizeof(struct pq));
  pq->heap = dynarray_create();
  return pq;
}


/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
  dynarray_free(pq->heap);
  free(pq);
  pq = NULL;
}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
  int size = dynarray_size(pq->heap);
  if(size == 0) return 1;
  else return 0;
}


/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */
int pq_get(struct pq* pq, int idx){
  struct pq_node* pqnode = dynarray_get(pq->heap,idx);
  return pqnode->priority;
}

void swap(struct pq* pq, int a, int b){
  struct pq_node* pqnode = dynarray_get(pq->heap, a);
  dynarray_set(pq->heap,a,dynarray_get(pq->heap,b));
  dynarray_set(pq->heap,b,pqnode);
}

void pq_insert(struct pq* pq, void* value, int priority) {
  struct pq_node* pqnode = malloc(sizeof(struct pq_node));
  pqnode->value = value;
  pqnode->priority = priority;

  dynarray_insert(pq->heap, pqnode);

  int last_idx = dynarray_size(pq->heap)-1;
  int prt_idx = (last_idx-1)/2;

  while(last_idx != 0 && (pq_get(pq,last_idx) < pq_get(pq,prt_idx))){
    swap(pq, last_idx,prt_idx);
    last_idx = prt_idx;
    prt_idx = (last_idx-1)/2;
  }
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
  struct pq_node* pqnode = dynarray_get(pq->heap,0);
  return pqnode->value;
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
  struct pq_node* pqnode = dynarray_get(pq->heap,0);
  return pqnode->priority;
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_remove_first(struct pq* pq) {
  void* value = pq_first(pq);
  //Intialize index
  int last_idx = dynarray_size(pq->heap)-1;
  int parent = 0;
  int x = 0;
  
  // Replace the value of the first element in the array with the value of the last element and remove the last element.
  swap(pq,last_idx,0);
  
  //Free the last piece memory
  //Remove the last piece
  free(dynarray_get(pq->heap, last_idx));
  dynarray_remove(pq->heap, last_idx);

  //check if array is empty or not
  //compare left and right child
  int size = dynarray_size(pq->heap);
  while (size != 0){
    // calculate indices of children
    int left_child = (2*parent)+1;
    int right_child = (2*parent)+2;
    // if both children out of bound, break out of loop
    if(left_child >= size && right_child >= size) break;

    // if only has left child or left child p is less than right child p
    if(right_child >= size || pq_get(pq,left_child) <= pq_get(pq,right_child)){
      x = left_child;
    }
    else if(left_child >= size || pq_get(pq,left_child) >= pq_get(pq,right_child)){
      x = right_child;
    }

    if(pq_get(pq,x) < pq_get(pq,parent)){
      swap(pq,x,parent);
      parent = x;
    }
    else break;
  }
  return value;
}