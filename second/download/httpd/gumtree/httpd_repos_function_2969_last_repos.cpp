static void push_slot(h2_slot **phead, h2_slot *slot)
{
    /* Atomically push a slot to the list */
    ap_assert(!slot->next);
    for (;;) {
        h2_slot *next = slot->next = *phead;
        if (apr_atomic_casptr((void*)phead, slot, next) == next) {
            return;
        }
    }
}