#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

//#define DEBUG

struct Node
{
    int_fast16_t  data;
    struct Node *next;
};


int main()
{
    uint_fast32_t t = 0;
    uint_fast32_t numlen = 0;
    struct Node* head = (struct Node*)malloc(sizeof(struct Node));
    head->next = NULL;
    struct Node* pos = head;
    uint_fast32_t c;

    //read t
    register int ch = getc_unlocked(stdin);
    for( ; ((ch<48 || ch>57)); ch = getc_unlocked(stdin) );
    for( ;ch>47 && ch<58; ch = getc_unlocked(stdin) ) {
        t = (t << 1) + (t << 3) + ch - 48;
        ++numlen;
    }
    //read and build linked list
    int_fast16_t num = 0;
    struct Node* curr = head;
    struct Node* prev = head;
    ch = getc_unlocked(stdin);
    while(ch != EOF)
    {
        num = (num << 1) + (num << 3) + ch - 48;
        ++numlen;
        ch = getc_unlocked(stdin);

        if(ch == 10 || ch == 32)
        {
            curr->data = num;
            curr->next = (struct Node*)malloc(sizeof(struct Node));
            prev = curr;
            curr = curr->next;
            curr->next = NULL;
            num = 0;
            ch = getc_unlocked(stdin);
        }
    }
    prev->next = head;





//    c = remove_element(arr, &size, 1);
//    fprintf(stdout, "deleted %d\n", c);
//    arr = insert(arr, &size, 1, 8);
//    printList(head);
//    return 0;


    uint_fast32_t i;
    for(i=t;i>0;i--)
    {
        if((pos->data & 0x01) == 0)
        {
            //job R
            struct Node* del;
            del = pos->next;
            c = del->data;
            #ifdef DEBUG
                fprintf(stdout, "c:   %lli\n", c);
            #endif // DEBUG
            pos->next = del->next;
            free(del);
            #ifdef DEBUG
                fprintf(stdout, "L: ");
                struct Node* check = pos;
                while (check->next != pos)
                {
                    fprintf(stdout, "%d ", check->data);
                    check = check->next;
                }
                fprintf(stdout, "%d\n", check->data);
            #endif
            //for(; c>0; c--) pos = pos->next;
            while(c--) pos = pos->next;
        }
        else
        {
            //job X
            c = pos->data;
            #ifdef DEBUG
                fprintf(stdout, "c:   %lli\n", c);
            #endif // DEBUG
            struct Node* ins = (struct Node*)malloc(sizeof(struct Node*));
            ins->data = c-1;
            ins->next = pos->next;
            pos->next = ins;
            #ifdef DEBUG
                fprintf(stdout, "X: ");
                struct Node* check = pos;
                while (check->next != pos)
                {
                    fprintf(stdout, "%d ", check->data);
                    check = check->next;
                }
                fprintf(stdout, "%d\n", check->data);
            #endif // DEBUG
            //for(; c>0; c--)
            while(c--) pos = pos->next;
        }
        #ifdef DEBUG
            fprintf(stdout, "t:  %d\n", i);
        #endif // DEBUG
    }
    struct Node* check = pos;
    while (check->next != pos)
    {
        int i=10;
        char output_buffer[11];
        do{
            output_buffer[--i]=(check->data%10)+48;
            check->data/=10;
        }while(check->data);
        do{
            putchar_unlocked(output_buffer[i]);
        }while(++i<11);
        putchar_unlocked(32);
        check = check->next;
    }
    i=10;
    char output_buffer[11];
    do{
        output_buffer[--i]=(check->data%10)+48;
        check->data/=10;
    }while(check->data);
    do{
        putchar_unlocked(output_buffer[i]);
    }while(++i<11);
    putchar_unlocked(10);
        //check = check->next;
    //fprintf(stdout, "%d\n", check->data);
    //fprintf(stdout, "%u", numlen);
    i=10;
    //char output_buffer[11];
    do{
        output_buffer[--i]=(numlen%10)+48;
        numlen/=10;
    }while(numlen);
    do{
        putchar_unlocked(output_buffer[i]);
    }while(++i<11);
    //putchar_unlocked(0);
    //free(arr);
    return 0;
}
