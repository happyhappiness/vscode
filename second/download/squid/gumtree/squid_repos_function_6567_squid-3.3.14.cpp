static RemovalPurgeWalker *
lru_purgeInit(RemovalPolicy * policy, int max_scan)
{
    LruPolicyData *lru = (LruPolicyData *)policy->_data;
    RemovalPurgeWalker *walker;
    LruPurgeData *lru_walk;
    lru->nwalkers += 1;
    walker = new RemovalPurgeWalker;
    lru_walk = (LruPurgeData *)xcalloc(1, sizeof(*lru_walk));
    walker->_policy = policy;
    walker->_data = lru_walk;
    walker->max_scan = max_scan;
    walker->Next = lru_purgeNext;
    walker->Done = lru_purgeDone;
    lru_walk->start = lru_walk->current = (LruNode *) lru->list.head;
    return walker;
}