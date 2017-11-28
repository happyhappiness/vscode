static RemovalPurgeWalker *
heap_purgeInit(RemovalPolicy * policy, int max_scan)
{
    HeapPolicyData *heap = (HeapPolicyData *)policy->_data;
    RemovalPurgeWalker *walker;
    HeapPurgeData *heap_walk;
    heap->nwalkers += 1;
    walker = new RemovalPurgeWalker;
    heap_walk = (HeapPurgeData *)xcalloc(1, sizeof(*heap_walk));
    heap_walk->min_age = 0.0;
    heap_walk->locked_entries = NULL;
    walker->_policy = policy;
    walker->_data = heap_walk;
    walker->max_scan = max_scan;
    walker->Next = heap_purgeNext;
    walker->Done = heap_purgeDone;
    return walker;
}