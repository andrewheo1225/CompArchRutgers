#include <stdio.h>
#include <stdlib.h>

#define FALSE 0

#define TRUE 1

struct Node
{
    struct Node *right;
    struct Node *left;
    int num;
};
typedef struct Node BSTNODE;
int FLAGFOUND = FALSE;

void freeTree(BSTNODE *root)
{
    BSTNODE *leftNode = root->left;
    BSTNODE *rightNode = root->right;

    if (rightNode != NULL && leftNode != NULL)
    {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
    else if (rightNode == NULL && leftNode != NULL)
    {
        freeTree(root->left);
        free(root);
    }
    else if (rightNode != NULL && leftNode == NULL)
    {
        freeTree(root->right);
        free(root);
    }
    
    else if (root->right == NULL && root->left == NULL)
        free(root);
}

void printTheStatement(char *phrase)
{
    printf("%s", phrase);
}

BSTNODE *delete (BSTNODE *root, int num)
{
    //if root is null
    if (root == NULL)
        return NULL;

    if (num < root->num)
        root->left = delete (root->left, num);
    else if (num == root->num)
    {
        if (root->right == NULL && root->left == NULL)
        {
            free(root);
            return NULL;
        }
        else if (root->left == NULL)
        {

            if (root->right == NULL)
            {
                BSTNODE *leftNode = root->left;
                int currdata = leftNode->num;
                free(leftNode);
                root->left = NULL;
                root->num = currdata;
            }
            else if (root->left == NULL)
            {
                BSTNODE *rightNode = root->right;
                int currdata = rightNode->num;
                free(rightNode);
                root->right = NULL;
                root->num = currdata;
            }
        }
        else
        {
            BSTNODE *ptr = root->left;
            while (NULL != ptr->right)
            {
                ptr = ptr->right;
            }
            int num = ptr->num;
            root->num = num;
            root->left = delete (root->left, num);
        }
    }
    else if (num > root->num)
        root->right = delete (root->right, num);

    return root;
}

int search(BSTNODE *root, int num)
{
    //if root is null
    if (root == NULL)
    {
        FLAGFOUND = FALSE;
        return FALSE;
    }
    if (num == root->num)
    {
        FLAGFOUND = TRUE;
        return FLAGFOUND;
    }
    else if (num < root->num)
        return search(root->left, num);
    else if (num > root->num)
        return search(root->right, num);
    return FLAGFOUND;
}

void print(BSTNODE *root)
{
    if (root == NULL)
        return;
    printTheStatement("(");
    print(root->left);
    printf("%d", root->num);
    print(root->right);
    printTheStatement(")");
}
BSTNODE *insert(BSTNODE *root, int num)
{
    if (root == NULL)
    {
        root = calloc(1, sizeof(BSTNODE));
        root->num = num;
        root->left = NULL;
        root->right = NULL;
        printTheStatement("inserted");
        printf("\n");

        return root;
    }
    if (num == root->num)
    {
        printTheStatement("not inserted");
        printf("\n");

        return root;
    }
    else if (num < root->num)
        root->left = insert(root->left, num);
    else if (num > root->num)
        root->right = insert(root->right, num);
    return root;
}

int main(int argc, char *argv[])
{
    BSTNODE *bstTree = NULL;
    char path;
    int val;

    while (1)
    {
        if (scanf("%c", &path) == -1)
            break;
        if (path != 'p')
            scanf("%d", &val);
        if (path == 'i')
            bstTree = insert(bstTree, val);
   
        else if (path == 's')
        {
            int founded = search(bstTree, val);

            if (founded == TRUE)
            {
                printTheStatement("present");
                printf("\n");
            }

            else
            {
                printTheStatement("absent");
                printf("\n");
            }
        }
             
        else if (path == 'p')
        {
            print(bstTree);
            printf("\n");
        }
        else if (path == 'd')
        {
            int valFound = search(bstTree, val);
            if (TRUE == valFound)
            {
                bstTree = delete (bstTree, val);
                printTheStatement("deleted");
                printf("\n");
            }
            else
            {
                printTheStatement("absent");
                printf("\n");
            }
        }
    }

    freeTree(bstTree);
    return EXIT_SUCCESS;
}