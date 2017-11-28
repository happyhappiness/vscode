static void
lru_remove(RemovalPolicy * policy, StoreEntry * entry, RemovalPolicyNode * node)
{
    LruPolicyData *lru = (LruPolicyData *)policy->_data;
    LruNode *lru_node = (LruNode *)node->data;

    if (!lru_node)
        return;

    /*
     * It seems to be possible for an entry to exist in the hash
     * but not be in the LRU list, so check for that case rather
     * than suffer a NULL pointer access.
     */
    if (NULL == lru_node->node.data)
        return;

    assert(lru_node->node.data == entry);

    node->data = NULL;

    dlinkDelete(&lru_node->node, &lru->list);

    lru_node_pool->freeOne(lru_node);

    lru->count -= 1;
}