#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TABLE_SIZE 100 // Define hashtable size

// Structure for each node in the hashtable
typedef struct Node {
    char* key;
    struct Node* next;
} Node;

// Structure for the hashtable
typedef struct {
    Node* table[TABLE_SIZE];
} Hashtable;

// Function to create a new node
Node* createNode(char* key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = strdup(key); // strdup allocates memory for the string
    newNode->next = NULL;
    return newNode;
}

// Function to calculate the hash value for a given key
int hashFunction(char* key) {
    int hash = 0;
    while (*key != '\0') {
        hash = (hash + *key) % TABLE_SIZE;
        key++;
    }
    return hash;
}

// Function to insert a key into the hashtable
void insert(Hashtable* ht, char* key) {
    int hash = hashFunction(key);
    Node* newNode = createNode(key);

    // Insert at the beginning of the linked list
    newNode->next = ht->table[hash];
    ht->table[hash] = newNode;
}

// Function to check if a key exists in the hashtable
bool exists(Hashtable* ht, char* key) {
    int hash = hashFunction(key);
    Node* current = ht->table[hash];

    // Traverse the linked list at that hash index
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return true; // Key found
        }
        current = current->next;
    }

    return false; // Key not found
}

// Function to deallocate memory used by the hashtable
void freeHashtable(Hashtable* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = ht->table[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }
}

int main() {
    Hashtable ht;
    // Initialize hashtable
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht.table[i] = NULL;
    }

    // Insert product codes
    insert(&ht, "ABC123");
    insert(&ht, "XYZ789");
    insert(&ht, "PQR456");

    // Check if product codes exist
    printf("Does ABC123 exist? %s\n", exists(&ht, "ABC123") ? "Yes" : "No");
    printf("Does LMN111 exist? %s\n", exists(&ht, "LMN111") ? "Yes" : "No");

    // Free memory used by the hashtable
    freeHashtable(&ht);

    return 0;
}
