#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *left;
    struct node *right;
};

struct node* newnode(int val) {
    struct node *new_node = malloc(sizeof *new_node);
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->value = val;

    return new_node;
}

void printtabs(int numtabs) {
    for(int i = 0; i < numtabs; i++) {
        printf("\t");
    }
}

void printtree_preorder_recursively(struct node *root, int level) {
    if(root == NULL) {
        printtabs(level);
        printf("---<empty>---\n");
        return;
    }
    printtabs(level);
    printf("value = %d\n", root->value);
    printtabs(level);
    printf("left\n");

    printtree_preorder_recursively(root->left, level + 1);
    printtabs(level);
    printf("right\n");

    printtree_preorder_recursively(root->right, level + 1);
    printtabs(level);
    printf("\n");
}

void printttree_preorder(struct node *root) {
    printtree_preorder_recursively(root, 0);
}

void printttree_inorder(struct node *root) {
    if(root == NULL) {
        return;
    }

    printttree_inorder(root->left);
    printf("%d ", root->value);
    printttree_inorder(root->right);
}

void printtree_postorder(struct node *root) {
    if(root == NULL) {
        return;
    }

    printtree_postorder(root->left);
    printtree_postorder(root->right);
    printf("%d ", root->value);
}

void printtree_preorder_reversed(struct node *root) {
    if(root == NULL) {
        return;
    }

    printf("%d ", root->value);
    printtree_preorder_reversed(root->right);
    printtree_preorder_reversed(root->left);
}

void printtree_inorder_reversed(struct node *root) {
    if(root == NULL) {
        return;
    }

    printtree_inorder_reversed(root->right);
    printf("%d ", root->value);
    printtree_inorder_reversed(root->left);
}

void printtree_postorder_reversed(struct node *root) {
    if(root == NULL) {
        return;
    }

    printtree_postorder_reversed(root->right);
    printtree_postorder_reversed(root->left);
    printf("%d ", root->value);
}


int main() {
    struct node *n1 = newnode(40);
    struct node *n2 = newnode(30);
    struct node *n3 = newnode(50);
    struct node *n4 = newnode(25);
    struct node *n5 = newnode(35);
    struct node *n6 = newnode(45);
    struct node *n7 = newnode(60);
    struct node *n8 = newnode(15);
    struct node *n9 = newnode(28);
    struct node *n10 = newnode(55);
    struct node *n11 = newnode(70);

    n1->left =  n2;
    n1->right = n3;
    n2->left =  n4;
    n2->right = n5;
    n3->left = n6;
    n3->right = n7;
    n4->left = n8;
    n4->right = n9;
    n7->left = n10;
    n7->right = n11;

    printttree_preorder(n1);
    printttree_inorder(n1);
    printf("\n");
    printtree_postorder(n1);
    printf("\n");
    printtree_preorder_reversed(n1);
    printf("\n");
    printtree_inorder_reversed(n1);
    printf("\n");
    printtree_postorder_reversed(n1);
    printf("\n");
    
    free(n1);
    free(n2);
    free(n3);
    free(n4);
    free(n5);
    free(n6);
    free(n7);
    free(n8);
    free(n9);
    free(n10);
    free(n11);

    return 0;
}