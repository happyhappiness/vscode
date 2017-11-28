static void
heap_add(RemovalPolicy * policy, StoreEntry * entry, RemovalPolicyNode * node)
{
    HeapPolicyData *heap = (HeapPolicyData *)policy->_data;
    assert(!node->data);

    if (EBIT_TEST(entry->flags, ENTRY_SPECIAL))
        return;			/* We won't manage these.. they messes things up */

    node->data = heap_insert(heap->theHeap, entry);

    heap->count += 1;

    if (!heap->type)
        heap->type = heap_guessType(entry, node);

    /* Add a little more variance to the aging factor */
    heap->theHeap->age += heap->theHeap->age / 100000000;
}