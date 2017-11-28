static void
heap_referenced(RemovalPolicy * policy, const StoreEntry * entry,
                RemovalPolicyNode * node)
{
    HeapPolicyData *heap = (HeapPolicyData *)policy->_data;
    heap_node *hnode = (heap_node *)node->data;

    if (!hnode)
        return;

    heap_update(heap->theHeap, hnode, (StoreEntry *) entry);
}