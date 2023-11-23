#define TABLE_SIZE 131

// create a hash table
typedef struct {
    int products[TABLE_SIZE];
} HashTable;

int parseProductCode(const char* input) {
    // Check if the input matches the regex pattern
    if (input[0] == 'S') {
        int i = 1;
        int firstNumber = 0;
        int secondNumber = 0;
        int secondNumberIdx = -1;

        // Extract the first number
        while (input[i] >= '0' && input[i] <= '9' && i <= 3) {
            firstNumber = firstNumber * 10 + (input[i] - '0');
            i++;
        }
        
        // Check if the first number has 1 to 3 digits
        if (i == 1 || i > 4) {
            return -1;
        }
        
        // Check if the next character is '_'
        if (input[i] != '_') {
            return -1;
        }
        
        i++;

        secondNumberIdx = i;
        
        // Extract the second number
        while (input[i] >= '0' && input[i] <= '9' && i <= secondNumberIdx + 4) {
            secondNumber = secondNumber * 10 + (input[i] - '0');
            i++;
        }
        
        // Check if the second number has exactly 4 digits
        if (i != secondNumberIdx + 4) {
            return -1;
        }
        
        // Calculate the hash value
        int hash = (firstNumber * 10000 + secondNumber);
        return hash;
    }
    return -1;
}

int hashProductCode(int input) {
    return input % TABLE_SIZE;
}

// initialize the hash table
void initHashTable(HashTable* hashTable) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable->products[i] = -1;
    }
}

// insert a product code into the hash table
int insertProductCode(HashTable* hashTable, const char* productCode) {
    int productInt = parseProductCode(productCode);
    if (productInt != -1) {
        int hash = hashProductCode(productInt);
        int i = hash;
        int end = (hash - 1) % TABLE_SIZE;
        while (hashTable->products[i] != -1 && hashTable->products[i] != productInt) {
            i = (i + 1) % TABLE_SIZE;
            if (i == end) {
                return 0;
            }
        }
        hashTable->products[i] = productInt;
        return 1;
    }
    return 0;
}

// search for a product code in the hash table
int searchProductCode(HashTable* hashTable, const char* productCode) {
    int productInt = parseProductCode(productCode);
    if (productInt != -1) {
        int hash = hashProductCode(productInt);
        int i = hash;
        int end = (hash - 1) % TABLE_SIZE;
        while (hashTable->products[i] != -1 && hashTable->products[i] != productInt) {
            i = (i + 1) % TABLE_SIZE;
            if (i == end) {
                return 0;
            }
        }
        if (hashTable->products[i] == productInt) {
            return 1;
        }
    }
    return 0;
}
