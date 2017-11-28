static void
heap_remove(RemovalPolicy * policy, StoreEntry * entry,
            RemovalPolicyNode * node)
{
    HeapPolicyData *h = (HeapPolicyData *)policy->_data;
    heap_node *hnode = (heap_node *)node->data;

    if (!hnode)
        return;

    heap_delete(h->theHeap, hnode);

    node->data = NULL;

    h->count -= 1;
}