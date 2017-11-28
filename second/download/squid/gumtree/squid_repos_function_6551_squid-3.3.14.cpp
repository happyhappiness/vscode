static RemovalPolicyWalker *
heap_walkInit(RemovalPolicy * policy)
{
    HeapPolicyData *heap = (HeapPolicyData *)policy->_data;
    RemovalPolicyWalker *walker;
    HeapWalkData *heap_walk;
    heap->nwalkers += 1;
    walker = new RemovalPolicyWalker;
    heap_walk = (HeapWalkData *)xcalloc(1, sizeof(*heap_walk));
    heap_walk->current = 0;
    walker->_policy = policy;
    walker->_data = heap_walk;
    walker->Next = heap_walkNext;
    walker->Done = heap_walkDone;
    return walker;
}