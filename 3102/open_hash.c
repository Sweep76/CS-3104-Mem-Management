#include<stdio.h>
#include<stdlib.h>

#define MAX_ELEMENTS 100
#define TABLE_SIZE 10


typedef struct{
   int data;
   int next;
}NodeType;

typedef struct node{
   NodeType node[MAX_ELEMENTS];
   int avail; //holds index of next vacant field
}*VHeap;      //shared virtual heap.

typedef struct{
   int head;
   VHeap vptr;
}List;

typedef struct{
   int table[TABLE_SIZE]; //open hashing, pointer to the nodes
   VHeap vptr;
}HashTable;

void initVirtualHeap(VHeap *VH); 
void displayVirtualHeap(VHeap VH); //optional
void initialize(List *L, VHeap VH);
void displayList(List L);
void insertFirst(List *L, int elem); //test
void populate(List *L);

int hash(int elem);
HashTable makeHashTable(List*); 
void displayHashTable(HashTable H);
int deleteElem(HashTable*,int);

int main(){
   VHeap VH;
   List L;
   HashTable H;	
  
   initVirtualHeap(&VH);
   initialize(&L, VH);
   displayList(L);
	 populate(&L);
   printf("\n");
   displayList(L);

   //perform the conversion to hash table
  H = makeHashTable(&L);
   //display hash table
  displayHashTable(H);
   //delete an element
  
   //display hash table
   return 0;
}

void initVirtualHeap(VHeap *VH){
  *VH=(VHeap)calloc(1,sizeof(struct node));
  int i = 0;
	(*VH)->avail = i;
	for(; i < MAX_ELEMENTS; i++){
		(*VH)->node[i].next = i + 1;
	}
	(*VH)->node[i - 1].next = -1;
}

void displayVirtualHeap(VHeap VH){ //optional
} 

void initialize(List *L, VHeap VH){
  L->head = -1;
  L->vptr = VH;
}

void displayList(List L){
  int i;
  for (i = L.head; i!= -1; i = L.vptr->node[i].next){
    printf("%d ",L.vptr->node[i].data);
  }
}

void insertFirst(List *L, int elem){ // done, now checking
  int oldHead = L->head;
  int newHead = L->vptr->avail;
  int newAvail = L->vptr->node[newHead].next;
  L->vptr->avail = newAvail;
  L->vptr->node[newHead].data = elem;
  L->vptr->node[newHead].next = oldHead;
  L->head = newHead;
} 

void populate(List *L){
  int i; // populating the list
  int arr[] = {29,432,543,2,1,9,123,128,112,28,30,280,11,345,456,567,123,321,345,222};
  int size = sizeof(arr)/sizeof(int);
  for(i = 0; i < size; i++){
    insertFirst(L,arr[i]); // ????
  }
}

int hashByDigitSum(int elem){
  int rem,sum=0;
  
  while(elem!=0){
    rem=elem%10;
    sum+=rem;
    elem/=10;
  }
  return sum%TABLE_SIZE;
}

int hash(int elem){
  return elem%10; //if last digit
}

HashTable makeHashTable(List* L){
  HashTable H;
  H.vptr = L->vptr;
  int i;
  for(i = 0; i < TABLE_SIZE; i++){
    H.table[i] = -1;
  }
  while(L->head != -1){
   int temp;
    temp = L->head;
  	L->head = L->vptr->node[temp].next;
    //it should based on the hash fucntion
    int hashVal = hash(L->vptr->node[temp].data);
    L->vptr->node[temp].next = H.table[hashVal];
    H.table[hashVal] = temp;
  }
  return H;
}

void displayHashTable(HashTable H){
  int i,x;
  for(x=0;x<TABLE_SIZE;x++){
    printf("\n%d-> ",x);
  	for (i = H.table[x]; i!= -1; i = H.vptr->node[i].next){
    	printf("%d ",H.vptr->node[i].data);//okss
  	}
  }
}

int searchElem(HashTable H, int elem){
  //return the index of the target element, -1 if it doesnt exist
}
int deleteElem(HashTable* H, int elem){
	//we can try doing this on our ownnn
  return;
}
