static RemovalPurgeWalker *
heap_purgeInit(RemovalPolicy * policy, int max_scan)
{
    HeapPolicyData *h = (HeapPolicyData *)policy->_data;
    RemovalPurgeWalker *walker;
    HeapPurgeData *heap_walk;
    h->nwalkers += 1;
    walker = new RemovalPurgeWalker;
    heap_walk = new HeapPurgeData;
    walker->_policy = policy;
    walker->_data = heap_walk;
    walker->max_scan = max_scan;
    walker->Next = heap_purgeNext;
    walker->Done = heap_purgeDone;
    return walker;
}