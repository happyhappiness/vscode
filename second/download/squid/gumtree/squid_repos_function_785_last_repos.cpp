static void
dump_denyinfo(StoreEntry * entry, const char *name, AclDenyInfoList * var)
{
    while (var != NULL) {
        storeAppendPrintf(entry, "%s %s", name, var->err_page_name);

        for (auto *a = var->acl_list; a != NULL; a = a->next)
            storeAppendPrintf(entry, " %s", a->name);

        storeAppendPrintf(entry, "\n");

        var = var->next;
    }
}