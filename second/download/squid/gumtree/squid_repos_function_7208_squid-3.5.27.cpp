static enum HeapPolicyData::heap_entry_type
heap_guessType(StoreEntry * entry, RemovalPolicyNode * node)
{
    if (node == &entry->repl)
        return HeapPolicyData::TYPE_STORE_ENTRY;

    if (entry->mem_obj && node == &entry->mem_obj->repl)
        return HeapPolicyData::TYPE_STORE_MEM;

    fatal("Heap Replacement: Unknown StoreEntry node type");

    return HeapPolicyData::TYPE_UNKNOWN;
}