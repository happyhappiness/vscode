static const StoreEntry *
heap_walkNext(RemovalPolicyWalker * walker)
{
    HeapWalkData *heap_walk = (HeapWalkData *)walker->_data;
    RemovalPolicy *policy = walker->_policy;
    HeapPolicyData *h = (HeapPolicyData *)policy->_data;
    StoreEntry *entry;

    if (heap_walk->current >= heap_nodes(h->theHeap))
        return NULL;		/* done */

    entry = (StoreEntry *) heap_peep(h->theHeap, heap_walk->current++);

    return entry;
}