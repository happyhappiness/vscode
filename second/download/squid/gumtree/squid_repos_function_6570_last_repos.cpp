static netdbEntry *
netdbAdd(Ip::Address &addr)
{
    netdbEntry *n;

    if (netdbEntry::UseCount() > Config.Netdb.high)
        netdbPurgeLRU();

    if ((n = netdbLookupAddr(addr)) == NULL) {
        n = new netdbEntry;
        netdbHashInsert(n, addr);
    }

    return n;
}