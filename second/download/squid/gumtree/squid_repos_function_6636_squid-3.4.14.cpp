static void
heap_walkDone(RemovalPolicyWalker * walker)
{
    RemovalPolicy *policy = walker->_policy;
    HeapPolicyData *h = (HeapPolicyData *)policy->_data;
    assert(strcmp(policy->_type, "heap") == 0);
    assert(h->nwalkers > 0);
    h->nwalkers -= 1;
    safe_free(walker->_data);
    delete walker;
}