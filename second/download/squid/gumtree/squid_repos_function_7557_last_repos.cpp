static const StoreEntry *
lru_walkNext(RemovalPolicyWalker * walker)
{
    LruWalkData *lru_walk = (LruWalkData *)walker->_data;
    LruNode *lru_node = lru_walk->current;

    if (!lru_node)
        return NULL;

    lru_walk->current = (LruNode *) lru_node->node.next;

    return (StoreEntry *) lru_node->node.data;
}