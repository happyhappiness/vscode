void
LruPolicyData::setPolicyNode (StoreEntry *entry, void *value) const
{
    switch (type) {

    case TYPE_STORE_ENTRY:
        entry->repl.data = value;
        break ;

    case TYPE_STORE_MEM:
        entry->mem_obj->repl.data = value ;
        break ;

    default:
        break;
    }
}