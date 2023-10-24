#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define size 11
int usednodes = 0;

void insert(int nodes[], int keys[], int key, int parent) {
    if(usednodes == size) {
        printf("Memory limit reached.\n");
        return;
    }

    if(usednodes == 0) {
        nodes[0] = 0;
        keys[0] = key;
    }
    else {
        nodes[usednodes] = parent;
        keys[usednodes] = key;
    }

    usednodes++;
}

// deletes a node and it's subtree
void naiveDelete(int nodes[], int keys[], int node) {
    if(usednodes == 0) {
        printf("Tree empty\n");
        return;
    }

    nodes[node] = -1;
    keys[node] = -1;
    usednodes--;
    for(int i = 0; i < size; i++) {
        if(nodes[i] == node) {
            nodes[i] = -1;
            keys[i] = -1;
            naiveDelete(nodes, keys, i);
        }
    }
}

int find_node(int nodes[], int keys[], int key) {
    for(int i = 0; i < usednodes; i++) {
        if(keys[i] == key) {
            return i;
        }
    }
    return -1;
}

int update(int keys[], int key, int new_key) {
    for(int i = 0; i < size; i++) {
        if(keys[i] == key) {
            keys[i] = new_key;
            return 1;
        }
    }
    return 0;
}

int parent(int nodes[], int node) {
    return nodes[node];
}

void print_array(int array[]) {
    for(int i = 0; i < size; i++) {
        printf("%-3d ", array[i]);
    }
    printf("\n");
}

int main() {
    int nodes[size] = { [0 ... size - 1] = -1};
    int keys[size] = { [0 ... size - 1] = -1};

    insert(nodes, keys, 30, 0);
    insert(nodes, keys, 40, 0);
    insert(nodes, keys, 50, 0);
    insert(nodes, keys, 69, 0);
    insert(nodes, keys, 70, 2);
    insert(nodes, keys, 80, 2);
    insert(nodes, keys, 100, 3);
    insert(nodes, keys, 110, 4);
    insert(nodes, keys, 124, 4);
    insert(nodes, keys, 130, 5);
    insert(nodes, keys, 140, 6);

    int button = 1;

    while(1) {
        printf("0. Exit\n");
        printf("1. Find node with key\n");
        printf("2. Update key\n");
        printf("3. Naive delete\n");
        printf("4. Show parent\n");
        printf("5. Print tree\n");
        scanf("%d", &button);

        if(button == 0) {
            break;
        }

        int key, new_key;
        int node;

        switch(button) {
            case 1:
                printf("Enter key\n");
                scanf("%d", &key);
                printf("Key %d is found in node %d\n", key, find_node(nodes, keys, key));
                break;

            case 2:
                printf("Key to be updated:\n");
                scanf("%d", &key);
                printf("New key:\n");
                scanf("%d", &new_key);
                if(update(keys, key, new_key)) {
                    printf("Key updated\n");
                }
                else {
                    printf("Key not found\n");
                }
                break;

            case 3:
                printf("Enter node index\n");
                scanf("%d", &node);
                naiveDelete(nodes, keys, node);
                break;

            case 4:
                printf("Enter node index\n");
                scanf("%d", &node);
                printf("Parent index is %d\n", parent(nodes, node));
                break;

            case 5:
                printf("\n");
                print_array(nodes);
                print_array(keys);
                printf("Used nodes: %d\n\n", usednodes);
                break;

            default:
                break; 
        }
    }

    return 0;
}