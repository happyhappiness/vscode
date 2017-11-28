static RemovalPolicyWalker *
lru_walkInit(RemovalPolicy * policy)
{
    LruPolicyData *lru = (LruPolicyData *)policy->_data;
    RemovalPolicyWalker *walker;
    LruWalkData *lru_walk;
    lru->nwalkers += 1;
    walker = new RemovalPolicyWalker;
    lru_walk = (LruWalkData *)xcalloc(1, sizeof(*lru_walk));
    walker->_policy = policy;
    walker->_data = lru_walk;
    walker->Next = lru_walkNext;
    walker->Done = lru_walkDone;
    lru_walk->current = (LruNode *) lru->list.head;
    return walker;
}