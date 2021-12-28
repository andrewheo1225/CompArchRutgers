
#include <stdio.h>
#include <stdlib.h>

struct node
{
    int num;
    struct node *next;
};
typedef struct node llNode;
int count = 0;

llNode *insert(llNode *ptr, int num)
{

    //if LL is empty
    if (ptr == NULL)
    {
        ptr = calloc(1, sizeof(llNode));
        ptr->num = num;
        ptr->next = NULL;
        count++;
        return ptr;
    }
    //the head pointer must be changed
    else if (ptr->num > num)
    {
        llNode *node = calloc(1, sizeof(llNode));
        node->next = ptr;
        node->num = num;
        count++;
        return node;
    }
    else
    {
        llNode *cur = ptr;
        llNode *prev = ptr;

        while (cur != NULL)
        {
            //if the input is already in the LL
            if (cur->num == num)
            {
                return ptr;
            }
            else if (cur->num > num)
            {
                llNode *newnode = calloc(1, sizeof(llNode));
                newnode->num = num;
                newnode->next = prev->next;
                prev->next = newnode;
                count++;
                return ptr;
            }
            prev = cur;
            cur = cur->next;
        }

        llNode *newnode = calloc(1, sizeof(llNode));
        newnode->next = NULL;
        newnode->num = num;
        count++;
        prev->next = newnode;

        return ptr;
    }
}

llNode *delete (llNode *head, int num)
{
    //empty
    if (head == NULL)
    {
        return NULL;
    }

    if (head->num == num)
    {
        llNode *temp = head;
        head = head->next;
        free(temp);
        count--;
        return head;
    }

    llNode *cur = head;
    llNode *prev = head;

    while (cur != NULL)
    {
        if (cur->num == num)
        {

            llNode *dummy = cur;
            prev->next = cur->next;
            free(dummy);
            count--;
            return head;
        }
        prev = cur;
        cur = cur->next;
    }
    //want to delete a number not found in the LL
    if (cur == NULL)
    {
        return head;
    }
    return head;
}
void freeList(llNode *head)
{
    //empty
    if (head == NULL)
    {
        exit(EXIT_FAILURE);
    }

    llNode *cur;
    while (head != NULL)
    {
        cur = head->next;
        free(head);
        count--;
        head = cur;
    }
}
void print(llNode *head)
{
    while (head != NULL)
    {
        printf(" %d", head->num);
        head = head->next;
    }
}
int main(int argc, char *argv[])
{
    int num = 0;
    char IorD;
    llNode *start = NULL;

    while (1)
    {
        if (scanf("%c %d", &IorD, &num) == -1)
        {
            break;
        }
        //delete
        if (IorD == 'd')
        {
            start = delete (start, num);
            llNode *ptr = start;

            printf("%d :", count);
            print(ptr);
            printf("\n");
        }
        //insert
        else if (IorD == 'i')
        {
            start = insert(start, num);
            llNode *ptr = start;

            printf("%d :", count);
            print(ptr);
            printf("\n");
        }
    }

    freeList(start);
    return EXIT_SUCCESS;
}