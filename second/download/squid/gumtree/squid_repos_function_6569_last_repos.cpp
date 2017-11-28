static netdbEntry *
netdbLookupAddr(const Ip::Address &addr)
{
    netdbEntry *n;
    char *key = new char[MAX_IPSTRLEN];
    networkFromInaddr(addr).toStr(key,MAX_IPSTRLEN);
    n = (netdbEntry *) hash_lookup(addr_table, key);
    delete[] key;
    return n;
}