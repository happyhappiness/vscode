static void
netdbHostInsert(netdbEntry * n, const char *hostname)
{
    net_db_name *x = (net_db_name *)memAllocate(MEM_NET_DB_NAME);
    x->hash.key = xstrdup(hostname);
    x->next = n->hosts;
    n->hosts = x;
    x->net_db_entry = n;
    assert(hash_lookup(host_table, hostname) == NULL);
    hash_join(host_table, &x->hash);
    n->link_count++;
}