static void
dump_acl_list(StoreEntry * entry, ACLList * head)
{
    ACLList *l;

    for (l = head; l; l = l->next) {
        storeAppendPrintf(entry, " %s%s",
                          l->op ? null_string : "!",
                          l->_acl->name);
    }
}