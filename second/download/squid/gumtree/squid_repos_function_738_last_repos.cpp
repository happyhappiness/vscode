static void
dump_acl_address(StoreEntry * entry, const char *name, Acl::Address * head)
{
    char buf[MAX_IPSTRLEN];

    for (Acl::Address *l = head; l; l = l->next) {
        if (!l->addr.isAnyAddr())
            storeAppendPrintf(entry, "%s %s", name, l->addr.toStr(buf,MAX_IPSTRLEN));
        else
            storeAppendPrintf(entry, "%s autoselect", name);

        dump_acl_list(entry, l->aclList);

        storeAppendPrintf(entry, "\n");
    }
}