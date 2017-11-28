static void
heap_free(RemovalPolicy * policy)
{
    HeapPolicyData *heap = (HeapPolicyData *)policy->_data;
    /* Make some verification of the policy state */
    assert(strcmp(policy->_type, "heap") == 0);
    assert(heap->nwalkers);
    assert(heap->count);
    /* Ok, time to destroy this policy */
    safe_free(heap);
    memset(policy, 0, sizeof(*policy));
    delete policy;
}