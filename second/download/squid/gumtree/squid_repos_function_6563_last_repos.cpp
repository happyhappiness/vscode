static void
netdbHostInsert(netdbEntry * n, const char *hostname)
{
    net_db_name *x = new net_db_name(hostname, n);
    assert(hash_lookup(host_table, hostname) == NULL);
    hash_join(host_table, &x->hash);
}