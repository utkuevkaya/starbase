#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
} Node;

Node *createNode(int data);
Node *insert(Node *root, int value);
void inorder(Node *root);
void delete(int value);

int main()
{

    Node *root = createNode(50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);
    root = insert(root, 10);

    inorder(root);

    return 0;
}

Node *createNode(int data)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->right = newNode->left = NULL;

    return newNode;
}

Node *insert(Node *root, int value)
{
    if (root == NULL)
    {
        return createNode(value);
    }

    if (root->data == value)
    {
        return root;
    }

    else if (value < root->data)
    {
        root->left = insert(root->left, value);
    }

    else if (value > root->data)
    {
        root->right = insert(root->right, value);
    }
}

void inorder(Node *root)
{
    if(root != NULL)
    {
        inorder(root->left);
        printf("%d -> ", root->data);
        inorder(root->right);
    }
}