#include <stdio.h>
#include <stdlib.h>
#define HeapMem 20
#define MAX 10 // set storage of array

typedef struct{
	int elem;
	int link;
}Node;

typedef struct{
	Node node[HeapMem];
	int Avail;
}VirtualHeap;

typedef int Dictionary[MAX];


void initHeap(VirtualHeap*);
void initDic(Dictionary);
void Display(VirtualHeap*,Dictionary);
int hash(int);
void insert(VirtualHeap*,Dictionary,int);
void Delete(VirtualHeap*,Dictionary,int);
void isMember(VirtualHeap*,Dictionary,int);

int main(){
	VirtualHeap VHeap;
	Dictionary sample;
	//product code is s18_1749 (sample purposes)

	//store data with sample array
	int ctr, arr[10] = {181749,182248,184409,243969,182325,182795,241937,242022,181342,181367};
	initHeap(&VHeap);
	initDic(sample);

	// initialized Data Array
	Display(&VHeap,sample);

	//Store data to VHeap from normal array
	for(ctr = 0; ctr < 10; ctr++){
		insert(&VHeap,sample,arr[ctr]);
	}

	Display(&VHeap,sample);
	isMember(&VHeap,sample,181749);
	

	//Delete a specific Product Code Key
	Delete(&VHeap,sample,181749);
	Display(&VHeap,sample);

	isMember(&VHeap,sample,181749);
	isMember(&VHeap,sample,243969);

	//Find if the Product Code Exists
    // insert(&VHeap,sample, 247);
    // Display(&VHeap,sample);
	// return 0;
}

void initHeap(VirtualHeap *VH){
	int ctr;
	for(ctr = VH->Avail = HeapMem -1; ctr != 0; ctr--){
		VH->node[ctr].link = ctr -1;
	}
}

void initDic(Dictionary D){
	int ctr;
	for(ctr = 0; ctr < MAX; ctr++){
		D[ctr] = -1;
	}
}

void Display(VirtualHeap *VH, Dictionary D){
	int ctr, trav;
	printf("\n------------------------------------");
	for(ctr = 0; ctr < MAX; ctr++){
		printf("\n[%d]: ",ctr);
		for(trav = D[ctr]; trav != -1; trav = VH->node[trav].link){
			(VH->node[trav].link != -1) ? printf("%d -> ",VH->node[trav].elem):printf("%d",VH->node[trav].elem);
		}
	}
	
}

int hash(int x){
	return x % MAX;
}

void insert(VirtualHeap *VH, Dictionary D, int x){
	int *trav, temp;
	for(trav = &D[hash(x)]; *trav != -1 && VH->node[*trav].elem != x; trav = &VH->node[*trav].link){}
	if(*trav == -1){
		temp = VH->Avail;
		if(temp != -1){
			VH->Avail = VH->node[temp].link;
			VH->node[temp].elem = x;
			VH->node[temp].link = *trav;
			*trav = temp;
		}
	}
}

void Delete(VirtualHeap *VH, Dictionary D, int x){
	int temp, *trav;
	for(trav = &D[hash(x)]; *trav != -1 && VH->node[*trav].elem != x; trav = &VH->node[*trav].link){}
	if(*trav != -1){
		temp = *trav;
		*trav = VH->node[temp].link;
		VH->node[temp].link = VH->Avail;
		VH->Avail = temp;
	}
}

void isMember(VirtualHeap *VH, Dictionary D, int x){
	int trav;
	for(trav = D[hash(x)];trav != -1 && VH->node[trav].elem != x; trav = VH->node[trav].link){}
	return(trav == -1) ? printf("\n<> %d is not a member", x): printf("\n<> %d is a member", x);
}