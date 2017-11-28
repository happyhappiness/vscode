static void
heap_purgeDone(RemovalPurgeWalker * walker)
{
    HeapPurgeData *heap_walker = (HeapPurgeData *)walker->_data;
    RemovalPolicy *policy = walker->_policy;
    HeapPolicyData *heap = (HeapPolicyData *)policy->_data;
    StoreEntry *entry;
    assert(strcmp(policy->_type, "heap") == 0);
    assert(heap->nwalkers > 0);
    heap->nwalkers -= 1;

    if (heap_walker->min_age > 0) {
        heap->theHeap->age = heap_walker->min_age;
        debugs(81, 3, "heap_purgeDone: Heap age set to " << heap->theHeap->age  );
    }

    /*
     * Reinsert the locked entries
     */
    while ((entry = (StoreEntry *)linklistShift(&heap_walker->locked_entries))) {
        heap_node *node = heap_insert(heap->theHeap, entry);
        heap->setPolicyNode(entry, node);
        entry->unlock();
    }

    safe_free(walker->_data);
    delete walker;
}