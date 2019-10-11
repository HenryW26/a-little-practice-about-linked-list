//
//  main.c
//  linux_programming_experiment_1
//
//  Created by 抠鼻小新 on 2019/10/11.
//  Copyright © 2019 抠鼻小新. All rights reserved.
//

//
//  main.c
//  linux_programming_experiment_1
//
//  Created by 抠鼻小新 on 2019/10/11.
//  Copyright © 2019 抠鼻小新. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define NAME_LENGTH 10
#define PATH "/home/corbinxl/Desktop/stu_Info.txt"

typedef struct stuInfo
{
    char stuName[NAME_LENGTH];
    int Age;
} ElemType;

typedef struct node
{
    ElemType data;
    struct node * next;
} ListNode, * ListPtr;

struct node * CreateList(char * path);
int PrintList(ListPtr head);
int InsertList(ListPtr head);
int saveList(ListPtr head, char * path);
ListPtr findLast(ListPtr head);
void clean_stdin(void);


int main(int argc, const char * argv[]) {
    // insert code here...
    ListPtr ListHead = NULL;
    int fResult;
    while(1)
    {
        printf("\n\n1 Create List\n");
        printf("2 Print List\n");
        printf("3 Insert List\n");
        printf("4 save\n");
        printf("5 Quit\n");
        printf("Pleas enter your command: ");
        fflush(stdin);
        char command = getchar();
        clean_stdin();
        fflush(stdin);
        
        switch (command) {
            case '1':
                if((ListHead = CreateList(PATH)) == NULL)
                {
                    printf("Failed!\n");
                    continue;
                }
                break;
                
            case '2':
                if((fResult = PrintList(ListHead)) == -1)
                {
                    printf("Failed!\n");
                    continue;
                }
                break;

            case '3':
                if((fResult = InsertList(ListHead)) == -1)
                {
                    printf("Failed!\n");
                    continue;
                }
                break;
                
            case '4':
                if((fResult = saveList(ListHead, PATH)) == -1)
                {
                    printf("Failed!\n");
                    continue;
                }
                break;


            case '5':
                return 0;
                break;

            default:
                printf("Wrong Command!!");
                continue;
                break;
        }
    }
    return 0;
}

struct node * CreateList(char * path)
{
    ListPtr head = (ListPtr)malloc(sizeof(ListNode));
    head->next = NULL;
    ListPtr preNode;
    ListPtr nexNode;
    FILE * fp;
    if((fp = fopen(path, "rb+")) == 0)
    {
        printf("Open File Erro!!\n");
        return NULL;
    }
    preNode = head;
    while(!feof(fp))
    {
        nexNode = (ListPtr)malloc(sizeof(ListNode));
        nexNode->next = NULL;
        preNode->next = nexNode;
        fscanf(fp, "%s %d", nexNode->data.stuName, &nexNode->data.Age);
//        printf("%s %d\n", nexNode->data.stuName, nexNode->data.Age);
        preNode = nexNode;
    }
    fclose(fp);
    return head;
}

int PrintList(ListPtr head)
{
    if(head == NULL)
    {
        printf("Please Create List First!!\n");
        return -1;
    }
    ListPtr pre;
    ListPtr nex;
    pre = head;
    while(pre->next != NULL)
    {
        nex = pre->next;
        printf("%s %d\n", nex->data.stuName, nex->data.Age);
        pre = nex;
    }
    return 0;
}


int InsertList(ListPtr head)
{
    if(head == NULL)
    {
        printf("Please Create List First!!\n");
        return -1;
    }
    ListPtr pre = findLast(head);
    ListPtr nex = (ListPtr)malloc(sizeof(ListNode));
    nex->next = NULL;
    
    printf("Please enter the name: ");
    scanf("%s", nex->data.stuName);
    printf("Please enter the age:");
    scanf("%d", &nex->data.Age);
    clean_stdin();
    pre->next = nex;
    
    return 0;
}

ListPtr findLast(ListPtr head)
{
    ListPtr pre;
    pre = head;
    while(pre->next != NULL)
    {
        pre = pre->next;
    }
    return pre;
}

int saveList(ListPtr head, char * path)
{
    if(head == NULL)
    {
        printf("Please Create List First!!\n");
        return -1;
    }
    
    FILE * fp;
    if((fp = fopen(path, "wb+")) == 0)
    {
        printf("Open File Erro!\n");
        return -1;
    }
    
    ListPtr pre = head;
    while (pre->next != NULL)
    {
        pre = pre->next;
        fprintf(fp, "%s %d", pre->data.stuName, pre->data.Age);
        if(pre->next != NULL)
        {
            fprintf(fp, "\n");
        }
    }
    fclose(fp);
    return 0;
}


void clean_stdin(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

