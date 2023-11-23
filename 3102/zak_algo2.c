#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TABLE_SIZE 5
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

Node* createNode(char productCode[], int orderNumber, int quantityOrdered, float priceEach, int orderLineNumber) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->prod.productCode, productCode);
    newNode->prod.orderNumber = orderNumber;
    newNode->prod.quantityOrdered = quantityOrdered;
    newNode->prod.priceEach = priceEach;
    newNode->prod.orderLineNumber = orderLineNumber;
    newNode->next = NULL;
    return newNode;
}
int djb2_hash(char *str) {
    int hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % TABLE_SIZE;
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
void displayHashTable(Hashtable ht) {
    printf("\n-----------------------------------------------\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Bucket %d: ", i);
        Node* current = ht.table[i];
        while (current != NULL) {
            printf("[%s, %d, %d, %.2f, %d] -> ", current->prod.productCode, current->prod.orderNumber,
                   current->prod.quantityOrdered, current->prod.priceEach, current->prod.orderLineNumber);
            current = current->next;
        }
        printf("NULL\n");
    }
}
int productBinarySearch(Hashtable ht, const char* key) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = ht.table[i];
        while (current != NULL) {
            int cmp = strcmp(current->prod.productCode, key);
            if (cmp == 0) {
                return i;
            } else if (cmp > 0) {
                break;
            }
            current = current->next;
        }
    }
    return -1;
}
void findAndPrintOrderLineNumber(Hashtable ht, char* productCode) {
    int hash = djb2_hash(productCode);
    Node* current = ht.table[hash];

    while (current != NULL) {
        if (strcmp(current->prod.productCode, productCode) == 0) {
            printf("Order Line Number for %s: %d\n", productCode, current->prod.orderLineNumber);
            return;
        }
        current = current->next;
    }

    printf("%s not found in the hash table.\n", productCode);
}
int main()
{
    Hashtable ht;
    initHashTable(&ht);
    insert(&ht, "pc101", 101, 1, 1.00, 10);
    insert(&ht, "pc102", 102, 2, 2.00, 11);
    insert(&ht, "pc103", 103, 3, 3.00, 12);
    insert(&ht, "pc104", 104, 4, 4.00, 13);
    insert(&ht, "pc105", 102, 2, 2.00, 11);
    insert(&ht, "pc106", 103, 3, 3.00, 12);
    insert(&ht, "pc107", 104, 4, 4.00, 13);
    displayHashTable(ht);
    findAndPrintOrderLineNumber(ht, "pc104");

    insert(&ht, "pc109", 103, 3, 3.00, 17);
    insert(&ht, "pc110", 104, 4, 4.00, 19);
    displayHashTable(ht);
    findAndPrintOrderLineNumber(ht, "pc110");

    return 0;
}