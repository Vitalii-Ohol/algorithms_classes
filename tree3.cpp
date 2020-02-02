#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <iostream>
using namespace std;
//#define DEBUG

struct Node
{
    uint_fast64_t  data;
    struct Node *next;
};


int main()
{
    uint_fast64_t t;
    t = 0;
    uint_fast64_t numlen;
    numlen = 0;
    struct Node* head;
    head = (struct Node*)malloc(sizeof(struct Node));
    head->next = NULL;
    struct Node* pos;
    pos = head;
    uint_fast64_t c;
    uint_fast64_t counted;
    counted = 0;

    //read t
    register int ch = getc_unlocked(stdin);
    for( ; ((ch<48 || ch>57)); ch = getc_unlocked(stdin) );
    for( ;ch>47 && ch<58; ch = getc_unlocked(stdin) ) {
        t = (t << 1) + (t << 3) + ch - 48;
        ++numlen;
    }
    //read and build linked list
    uint_fast64_t num = 0;
    struct Node* curr = head;
    struct Node* prev = head;
    ch = getc_unlocked(stdin);
    while(ch != EOF && ch!= '\n')
    {
        num = (num << 1) + (num << 3) + ch - 48;
        ++numlen;
        ch = getc_unlocked(stdin);

        if(ch == 10 || ch == 32)
        {
            curr->data = num;
            ++counted;
            curr->next = (struct Node*)malloc(sizeof(struct Node));
            prev = curr;
            curr = curr->next;
            curr->next = NULL;
            num = 0;
            ch = getc_unlocked(stdin);
        }
    }
    prev->next = head;

    for(;t>0;t--)
    {
        if((pos->data & 0x01) == 0)
        {
            //job R
            struct Node* del;
            del = pos->next;
            //if(pos == del) break;
            c = del->data;
            pos->next = del->next;
            //free(del);
            --counted;
            if(counted == 0) break;
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
        }
        else
        {
            //job X
            c = pos->data;

            struct Node* ins = (struct Node*)malloc(sizeof(struct Node*));
            ins->data = c-1;
            ins->next = pos->next;
            pos->next = ins;
            ++counted;
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
        }
        #ifdef DEBUG
            fprintf(stdout, "c before modulo:  %llu   num of elements:  %llu\n", c, counted);
        #endif // DEBUG
        c = c % counted;
         #ifdef DEBUG
            fprintf(stdout, "c after modulo:  %llu    num of elements:  %llu\n", c, counted);
        #endif // DEBUG
        //while(--c) pos = pos->next;
        register int ii;
        for(ii = 0; ii < c; ii++)
        {
            pos = pos->next;
        }
        #ifdef DEBUG
           // fprintf(stdout, "t:  %d\n", t);
        #endif // DEBUG
    }
    struct Node* check = pos;
    if(counted == 0)
    {
        cout << "-1\n";
    }
    else
    {
        while (check->next != pos)
        {
            cout << check->data << ' ';
            check = check->next;
        }
        cout << check->data << '\n';
    }

    //if(pos == pos->next) ;
    //else

    cout << numlen;
    return 0;
}
