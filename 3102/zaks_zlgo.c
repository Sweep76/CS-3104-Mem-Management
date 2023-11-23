#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

typedef struct Product{
    char productCode[6];
    int orderNumber;
    int quantityOrdered;
    float priceEach;
    int orderLineNumber;
} Product;

typedef struct Node {
    Product prod;
    struct Node* next;
} Node;

typedef struct {
    Node* table[TABLE_SIZE];
} Hashtable;

// Function to create a new Node
Node* createNode(char productCode[], int orderNumber, int quantityOrdered, float priceEach, int orderLineNumber) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    // newNode->prod.productCode = strdup(productCode);
    strcpy(newNode->prod.productCode, productCode);
    newNode->prod.orderNumber = orderNumber;
    newNode->prod.quantityOrdered = quantityOrdered;
    newNode->prod.priceEach = priceEach;
    newNode->prod.orderLineNumber = orderLineNumber;
    newNode->next = NULL;
    return newNode;
}

void deleteMember(Hashtable* ht, char* productCode) {
    int hash = djb2_hash(productCode);
    Node* current = ht->table[hash];
    Node* prev = NULL;

    while (current != NULL && strcmp(current->prod.productCode, productCode) != 0) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        // Product code not found
        printf("Product code %s not found for deletion.\n", productCode);
        return;
    }

    if (prev == NULL) {
        // Node to be deleted is the first node in the bucket
        ht->table[hash] = current->next;
    } else {
        // Node to be deleted is in the middle or end of the linked list
        prev->next = current->next;
    }

    free(current);
    printf("Product code %s deleted successfully.\n", productCode);
}

int djb2_hash(char *str) {
    int hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash % TABLE_SIZE; // Ensure the hash value fits within the table size
}

void insert(Hashtable* ht, char* productCode, int orderNumber, int quantityOrdered, float priceEach, int orderLineNumber) {
    int hash = djb2_hash(productCode);
    Node* newNode = createNode(productCode, orderNumber, quantityOrdered, priceEach, orderLineNumber);
    newNode->next = ht->table[hash];
    ht->table[hash] = newNode;
}

void initHashTable(Hashtable *ht){
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }
}

int isMember(Hashtable* ht, char* productCode) {
    int hash = djb2_hash(productCode);
    Node* current = ht->table[hash];

    while (current != NULL) {
        if (strcmp(current->prod.productCode, productCode) == 0) {
            return printf("\n-->prod |%s| is found\n", productCode); // Product code found
        }
        current = current->next;
    }

    return printf("\n-->prod |%s| not found", productCode); // Product code not found
}

void displayHashTable(Hashtable* ht) {
    printf("\n---------------------------------\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Bucket %d: ", i);
        if (ht->table[i] == NULL) {
            printf("Empty\n");
        } else {
            Node* current = ht->table[i];
            while (current != NULL) {
                printf("[%s, %d, %d, %.2f, %d] -> ", current->prod.productCode, current->prod.orderNumber,
                       current->prod.quantityOrdered, current->prod.priceEach, current->prod.orderLineNumber);
                current = current->next;
            }
            printf("NULL\n");
        }
    }
    
}

int main()
{
    Hashtable ht;
    initHashTable(&ht);
    insert(&ht, "pc101", 101, 1, 1.00, 10);
    insert(&ht, "pc102", 102, 2, 2.00, 11);
    insert(&ht, "pc103", 103, 3, 3.00, 12);
    insert(&ht, "pc104", 104, 4, 4.00, 13);
    insert(&ht, "pc105", 105, 5, 5.00, 14);
    insert(&ht, "pc106", 106, 6, 6.00, 15);


    displayHashTable(&ht);
    isMember(&ht, "pc104");
    //(isMember(&ht, "pc104") == 1) ? printf("\n<>Product code is found\n") : printf("\n<>prod not found"); 
    insert(&ht, "pc107", 108, 3, 3.00, 129);
    displayHashTable(&ht);

    deleteMember(&ht, "pc102");
    displayHashTable(&ht);
    
    return 0;
}