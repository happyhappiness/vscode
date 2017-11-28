static void
heap_remove(RemovalPolicy * policy, StoreEntry * entry,
            RemovalPolicyNode * node)
{
    HeapPolicyData *heap = (HeapPolicyData *)policy->_data;
    heap_node *hnode = (heap_node *)node->data;

    if (!hnode)
        return;

    heap_delete(heap->theHeap, hnode);

    node->data = NULL;

    heap->count -= 1;
}