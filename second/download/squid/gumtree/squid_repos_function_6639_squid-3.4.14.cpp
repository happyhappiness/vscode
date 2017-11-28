static void
heap_purgeDone(RemovalPurgeWalker * walker)
{
    HeapPurgeData *heap_walker = (HeapPurgeData *)walker->_data;
    RemovalPolicy *policy = walker->_policy;
    HeapPolicyData *h = (HeapPolicyData *)policy->_data;
    StoreEntry *entry;
    assert(strcmp(policy->_type, "heap") == 0);
    assert(h->nwalkers > 0);
    h->nwalkers -= 1;

    if (heap_walker->min_age > 0) {
        h->theHeap->age = heap_walker->min_age;
        debugs(81, 3, "Heap age set to " << h->theHeap->age);
    }

    /*
     * Reinsert the locked entries
     */
    while ((entry = (StoreEntry *)linklistShift(&heap_walker->locked_entries))) {
        heap_node *node = heap_insert(h->theHeap, entry);
        h->setPolicyNode(entry, node);
        entry->unlock();
    }

    safe_free(walker->_data);
    delete walker;
}