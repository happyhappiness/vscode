static h2_slot *pop_slot(h2_slot **phead) 
{
    /* Atomically pop a slot from the list */
    for (;;) {
        h2_slot *first = *phead;
        if (first == NULL) {
            return NULL;
        }
        if (apr_atomic_casptr((void*)phead, first->next, first) == first) {
            first->next = NULL;
            return first;
        }
    }
}