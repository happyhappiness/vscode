static void
dump_acl_address(StoreEntry * entry, const char *name, AclAddress * head)
{
    char buf[MAX_IPSTRLEN];
    AclAddress *l;

    for (l = head; l; l = l->next) {
        if (!l->addr.IsAnyAddr())
            storeAppendPrintf(entry, "%s %s", name, l->addr.NtoA(buf,MAX_IPSTRLEN));
        else
            storeAppendPrintf(entry, "%s autoselect", name);

        dump_acl_list(entry, l->aclList);

        storeAppendPrintf(entry, "\n");
    }
}