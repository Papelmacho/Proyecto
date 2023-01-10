#include <stdlib.h>
#include "sll.h"
#include <assert.h>

Sll* Sll_new()
{
    Sll* Sll=malloc(sizeof(Sll));
    if(Sll)
    {
        Sll->first=Sll->last=Sll->cursor=NULL;
        Sll->len=0;
    }
    return Sll;
}

bool Sll_IsEmpty(Sll* this)
{
    return this->len==0;
}

void Sll_Delete(Sll** this)
{
    assert(*this);
    Sll* lst=*this;
    while(lst->first != NULL)
    {
      Node* tmp=lst->first->next;
      free(lst->first);
      lst->first=tmp;
    }
    free(lst);
    lst=NULL;
}
static Node* newNode(int item)
{
   Node* n=(Node*) malloc(sizeof(Node));
   if(n)
   {
      n->index=item;
      n->next=NULL;
   }
   return n;
}
void Sll_Push_front(Sll* this,int item)
{
   //Node* n = (Node*) calloc( 1, sizeof( Node ) );
    Node* n= newNode(item);
    if(Sll_IsEmpty(this))
    {
        this->first=this->last=this->cursor=n;
    }else
        {
            n->next=this->first;
            this->last->next=n;
            this->first=n;
            
        }
        this->len++;
}

void Sll_pop_front(Sll* this)
{
    assert(this);
    if(this->first==this->last)
    {
        free(this->first);
        this->first=this->last=this->cursor=NULL;
    }else
        {
            Node* right=this->first->next;
            free(this->first);
            this->first=right;
            
        }
    --this->len;
}
