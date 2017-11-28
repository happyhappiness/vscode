static ipcache_entry *
ipcache_get(const char *name)
{
    if (ip_table != NULL)
        return (ipcache_entry *) hash_lookup(ip_table, name);
    else
        return NULL;
}