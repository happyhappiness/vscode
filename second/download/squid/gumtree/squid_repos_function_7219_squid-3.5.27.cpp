static void
heap_free(RemovalPolicy * policy)
{
    HeapPolicyData *h = (HeapPolicyData *)policy->_data;
    /* Make some verification of the policy state */
    assert(strcmp(policy->_type, "heap") == 0);
    assert(h->nwalkers);
    assert(h->count);
    /* Ok, time to destroy this policy */
    safe_free(h);
    memset(policy, 0, sizeof(*policy));
    delete policy;
}