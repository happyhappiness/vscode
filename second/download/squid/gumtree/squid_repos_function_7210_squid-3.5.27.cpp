static void
heap_add(RemovalPolicy * policy, StoreEntry * entry, RemovalPolicyNode * node)
{
    HeapPolicyData *h = (HeapPolicyData *)policy->_data;
    assert(!node->data);

    if (EBIT_TEST(entry->flags, ENTRY_SPECIAL))
        return;         /* We won't manage these.. they messes things up */

    node->data = heap_insert(h->theHeap, entry);

    h->count += 1;

    if (!h->type)
        h->type = heap_guessType(entry, node);

    /* Add a little more variance to the aging factor */
    h->theHeap->age += h->theHeap->age / 100000000;
}