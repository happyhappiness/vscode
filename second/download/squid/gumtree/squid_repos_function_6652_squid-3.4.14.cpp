static void
lru_purgeDone(RemovalPurgeWalker * walker)
{
    RemovalPolicy *policy = walker->_policy;
    LruPolicyData *lru = (LruPolicyData *)policy->_data;
    assert(strcmp(policy->_type, "lru") == 0);
    assert(lru->nwalkers > 0);
    lru->nwalkers -= 1;
    safe_free(walker->_data);
    delete walker;
}