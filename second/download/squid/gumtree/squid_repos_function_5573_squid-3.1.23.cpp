static StoreEntry *
lru_purgeNext(RemovalPurgeWalker * walker)
{
    LruPurgeData *lru_walker = (LruPurgeData *)walker->_data;
    RemovalPolicy *policy = walker->_policy;
    LruPolicyData *lru = (LruPolicyData *)policy->_data;
    LruNode *lru_node;
    StoreEntry *entry;

try_again:
    lru_node = lru_walker->current;

    if (!lru_node || walker->scanned >= walker->max_scan)
        return NULL;

    walker->scanned += 1;

    lru_walker->current = (LruNode *) lru_node->node.next;

    if (lru_walker->current == lru_walker->start) {
        /* Last node found */
        lru_walker->current = NULL;
    }

    entry = (StoreEntry *) lru_node->node.data;
    dlinkDelete(&lru_node->node, &lru->list);

    if (entry->locked()) {
        /* Shit, it is locked. we can't return this one */
        walker->locked++;
        dlinkAddTail(entry, &lru_node->node, &lru->list);
        goto try_again;
    }

    lru_node_pool->free(lru_node);
    lru->count -= 1;
    lru->setPolicyNode(entry, NULL);
    return entry;
}