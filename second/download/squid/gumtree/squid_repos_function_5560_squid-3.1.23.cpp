static StoreEntry *
heap_purgeNext(RemovalPurgeWalker * walker)
{
    HeapPurgeData *heap_walker = (HeapPurgeData *)walker->_data;
    RemovalPolicy *policy = walker->_policy;
    HeapPolicyData *heap = (HeapPolicyData *)policy->_data;
    StoreEntry *entry;
    heap_key age;

try_again:

    if (!heap_nodes(heap->theHeap) > 0)
        return NULL;		/* done */

    age = heap_peepminkey(heap->theHeap);

    entry = (StoreEntry *)heap_extractmin(heap->theHeap);

    if (entry->locked()) {

        entry->lock();
        linklistPush(&heap_walker->locked_entries, entry);

        goto try_again;
    }

    heap_walker->min_age = age;
    heap->setPolicyNode(entry, NULL);
    return entry;
}