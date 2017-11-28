static void dump_sslproxy_ssl_bump(StoreEntry *entry, const char *name, acl_access *ssl_bump)
{
    acl_access *sb;
    for (sb = ssl_bump; sb != NULL; sb = sb->next) {
        storeAppendPrintf(entry, "%s ", name);
        storeAppendPrintf(entry, "%s ", Ssl::bumpMode(sb->allow.kind));
        if (sb->aclList)
            dump_acl_list(entry, sb->aclList);
        storeAppendPrintf(entry, "\n");
    }
}