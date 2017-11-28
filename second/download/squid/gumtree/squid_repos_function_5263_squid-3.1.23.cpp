static netdbEntry *
netdbAdd(IpAddress &addr)
{
    netdbEntry *n;

    if (memInUse(MEM_NETDBENTRY) > Config.Netdb.high)
        netdbPurgeLRU();

    if ((n = netdbLookupAddr(addr)) == NULL) {
        n = (netdbEntry *)memAllocate(MEM_NETDBENTRY);
        netdbHashInsert(n, addr);
    }

    return n;
}