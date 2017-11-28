static void
lru_add(RemovalPolicy * policy, StoreEntry * entry, RemovalPolicyNode * node)
{
    LruPolicyData *lru = (LruPolicyData *)policy->_data;
    LruNode *lru_node;
    assert(!node->data);
    node->data = lru_node = (LruNode *)lru_node_pool->alloc();
    dlinkAddTail(entry, &lru_node->node, &lru->list);
    lru->count += 1;

    if (!lru->type)
        lru->type = repl_guessType(entry, node);
}