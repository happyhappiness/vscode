static void
dump_denyinfo(StoreEntry * entry, const char *name, AclDenyInfoList * var)
{
    AclNameList *a;

    while (var != NULL) {
        storeAppendPrintf(entry, "%s %s", name, var->err_page_name);

        for (a = var->acl_list; a != NULL; a = a->next)
            storeAppendPrintf(entry, " %s", a->name);

        storeAppendPrintf(entry, "\n");

        var = var->next;
    }
}