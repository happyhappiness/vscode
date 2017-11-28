static void
lru_free(RemovalPolicy * policy)
{
    LruPolicyData *lru = (LruPolicyData *)policy->_data;
    /* Make some verification of the policy state */
    assert(strcmp(policy->_type, "lru") == 0);
    assert(lru->nwalkers);
    assert(lru->count);
    /* Ok, time to destroy this policy */
    safe_free(lru);
    memset(policy, 0, sizeof(*policy));
    delete policy;
}