void
dump_acl_list(StoreEntry * entry, ACLList * head)
{
    dump_SBufList(entry, head->dump());
}