#include <stdlib.h>

#define HASH_SIZE 10000

typedef struct Node {
    int key;
    int value;
    struct Node* next;
} Node;

typedef struct {
    Node* data[HASH_SIZE];
} HashMap;

int hash(int key) {
    return abs(key) % HASH_SIZE;
}

HashMap* createMap() {
    HashMap* map = malloc(sizeof(HashMap));
    for (int i = 0; i < HASH_SIZE; i++)
        map->data[i] = NULL;
    return map;
}

void put(HashMap* map, int key, int value) {
    int idx = hash(key);
    Node* node = map->data[idx];
    while (node) {
        if (node->key == key) {
            node->value = value;
            return;
        }
        node = node->next;
    }
    Node* new_node = malloc(sizeof(Node));
    new_node->key = key;
    new_node->value = value;
    new_node->next = map->data[idx];
    map->data[idx] = new_node;
}

int get(HashMap* map, int key, int* found) {
    int idx = hash(key);
    Node* node = map->data[idx];
    while (node) {
        if (node->key == key) {
            *found = 1;
            return node->value;
        }
        node = node->next;
    }
    *found = 0;
    return -1;
}

void freeMap(HashMap* map) {
    for (int i = 0; i < HASH_SIZE; i++) {
        Node* node = map->data[i];
        while (node) {
            Node* tmp = node;
            node = node->next;
            free(tmp);
        }
    }
    free(map);
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    HashMap* map = createMap();
    int* result = malloc(2 * sizeof(int));
    *returnSize = 2;

    for (int i = 0; i < numsSize; i++) {
        int complement = target - nums[i];
        int found = 0;
        int idx = get(map, complement, &found);
        if (found) {
            result[0] = idx;
            result[1] = i;
            freeMap(map);
            return result;
        }
        put(map, nums[i], i);
    }
    freeMap(map);
    *returnSize = 0;
    return NULL; // As per constraint, should not be reached
}
