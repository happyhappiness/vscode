static void
heap_walkDone(RemovalPolicyWalker * walker)
{
    RemovalPolicy *policy = walker->_policy;
    HeapPolicyData *heap = (HeapPolicyData *)policy->_data;
    assert(strcmp(policy->_type, "heap") == 0);
    assert(heap->nwalkers > 0);
    heap->nwalkers -= 1;
    safe_free(walker->_data);
    delete walker;
}