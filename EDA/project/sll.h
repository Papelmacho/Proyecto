#ifndef SLL_HEADER
#define SLL_HEADER

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>



typedef struct
{
    Node* first;
    Node* last;
    Node* cursor;
    size_t len;
}Sll;

void Sll_Delete(Sll** this);
bool Sll_IsEmpty(Sll* this);
Sll* Sll_new();
void Sll_pop_front(Sll* this);
void Sll_Push_front(Sll* this,int item);

#endif  /* ----- #ifndef SLL_HEADER ----- */
