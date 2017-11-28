static netdbEntry *
netdbLookupAddr(const IpAddress &addr)
{
    netdbEntry *n;
    char *key = new char[MAX_IPSTRLEN];
    networkFromInaddr(addr).NtoA(key,MAX_IPSTRLEN);
    n = (netdbEntry *) hash_lookup(addr_table, key);
    delete[] key;
    return n;
}