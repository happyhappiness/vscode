static void
dump_acl_nfmark(StoreEntry * entry, const char *name, acl_nfmark * head)
{
    for (acl_nfmark *l = head; l; l = l->next) {
        if (l->nfmark > 0)
            storeAppendPrintf(entry, "%s 0x%02X", name, l->nfmark);
        else
            storeAppendPrintf(entry, "%s none", name);

        dump_acl_list(entry, l->aclList);

        storeAppendPrintf(entry, "\n");
    }
}