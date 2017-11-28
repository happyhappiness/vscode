static StoreEntry *
heap_purgeNext(RemovalPurgeWalker * walker)
{
    HeapPurgeData *heap_walker = (HeapPurgeData *)walker->_data;
    RemovalPolicy *policy = walker->_policy;
    HeapPolicyData *h = (HeapPolicyData *)policy->_data;
    StoreEntry *entry;
    heap_key age;

try_again:

    if (heap_empty(h->theHeap))
        return NULL;        /* done */

    age = heap_peepminkey(h->theHeap);

    entry = (StoreEntry *)heap_extractmin(h->theHeap);

    if (entry->locked()) {

        entry->lock("heap_purgeNext");
        heap_walker->locked_entries.push(entry);

        goto try_again;
    }

    heap_walker->min_age = age;
    h->setPolicyNode(entry, NULL);
    return entry;
}