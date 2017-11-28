static netdbEntry *
netdbLookupHost(const char *key)
{
    net_db_name *x = (net_db_name *) hash_lookup(host_table, key);
    return x ? x->net_db_entry : NULL;
}