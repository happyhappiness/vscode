static
void header_mangler_dump_access(StoreEntry * entry, const char *option,
                                const header_mangler &m, const char *name)
{
    if (m.access_list != NULL) {
        storeAppendPrintf(entry, "%s ", option);
        dump_acl_access(entry, name, m.access_list);
    }
}