#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TABLE_SIZE 10
#define EMPTY -1 // Special value to mark an empty slot
#define DELETED -2 // Special value to mark a deleted slot

int hashTable[TABLE_SIZE]; // Hash table array

// Hash function
int hashFunction(int key) {
    return key % TABLE_SIZE;
}

// Insert a key into the hash table with linear probing
void insert(int key) {
    int index = hashFunction(key);
    int originalIndex = index;
    int i = 0;

    while (hashTable[index] != EMPTY && hashTable[index] != DELETED) {
        index = (originalIndex + ++i) % TABLE_SIZE; // Linear probing
        if (index == originalIndex) { // If we've circled back to the original index, the table is full
            printf("Table is full. Unable to insert %d.\n", key);
            return;
        }
    }
    hashTable[index] = key;
    printf("Inserted %d at index %d.\n", key, index);
}

// Search for a key in the hash table
bool search(int key) {
    int index = hashFunction(key);
    int originalIndex = index;
    int i = 0;

    while (hashTable[index] != EMPTY) {
        if (hashTable[index] == key) {
            printf("Key %d found at index %d.\n", key, index);
            return true;
        }
        index = (originalIndex + ++i) % TABLE_SIZE; // Linear probing
        if (index == originalIndex) { // If we've circled back to the original index
            break;
        }
    }
    printf("Key %d not found.\n", key);
    return false;
}

// Delete a key from the hash table
void delete(int key) {
    int index = hashFunction(key);
    int originalIndex = index;
    int i = 0;

    while (hashTable[index] != EMPTY) {
        if (hashTable[index] == key) {
            hashTable[index] = DELETED; // Mark the slot as deleted
            printf("Key %d deleted from index %d.\n", key, index);
            return;
        }
        index = (originalIndex + ++i) % TABLE_SIZE; // Linear probing
        if (index == originalIndex) { // If we've circled back to the original index
            break;
        }
    }
    printf("Key %d not found for deletion.\n", key);
}

// Display the hash table
void display() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i] == EMPTY) {
            printf("Index %d: EMPTY\n", i);
        } else if (hashTable[i] == DELETED) {
            printf("Index %d: DELETED\n", i);
        } else {
            printf("Index %d: %d\n", i, hashTable[i]);
        }
    }
}

// Initialize the hash table with EMPTY values
void initializeTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = EMPTY;
    }
}

int main() {
    initializeTable();

    int choice, key;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert\n2. Search\n3. Delete\n4. Display\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                insert(key);
                break;
            case 2:
                printf("Enter key to search: ");
                scanf("%d", &key);
                search(key);
                break;
            case 3:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                delete(key);
                break;
            case 4:
                display();
                break;
            case 5:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
