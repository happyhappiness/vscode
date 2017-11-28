static void
heap_referenced(RemovalPolicy * policy, const StoreEntry * entry,
                RemovalPolicyNode * node)
{
    HeapPolicyData *h = (HeapPolicyData *)policy->_data;
    heap_node *hnode = (heap_node *)node->data;

    if (!hnode)
        return;

    heap_update(h->theHeap, hnode, (StoreEntry *) entry);
}