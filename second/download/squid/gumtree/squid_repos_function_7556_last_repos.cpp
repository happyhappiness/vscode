static void
lru_referenced(RemovalPolicy * policy, const StoreEntry * entry,
               RemovalPolicyNode * node)
{
    LruPolicyData *lru = (LruPolicyData *)policy->_data;
    LruNode *lru_node = (LruNode *)node->data;

    if (!lru_node)
        return;

    dlinkDelete(&lru_node->node, &lru->list);

    dlinkAddTail((void *) entry, &lru_node->node, &lru->list);
}