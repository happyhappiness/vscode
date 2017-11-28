static void
netdbHashInsert(netdbEntry * n, IpAddress &addr)
{
    networkFromInaddr(addr).NtoA(n->network, MAX_IPSTRLEN);
    n->hash.key = n->network;
    assert(hash_lookup(addr_table, n->network) == NULL);
    hash_join(addr_table, &n->hash);
}