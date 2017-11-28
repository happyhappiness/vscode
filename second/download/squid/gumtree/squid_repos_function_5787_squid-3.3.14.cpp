static void
netdbPurgeLRU(void)
{
    netdbEntry *n;
    netdbEntry **list;
    int k = 0;
    int list_count = 0;
    int removed = 0;
    list = (netdbEntry **)xcalloc(memInUse(MEM_NETDBENTRY), sizeof(netdbEntry *));
    hash_first(addr_table);

    while ((n = (netdbEntry *) hash_next(addr_table))) {
        assert(list_count < memInUse(MEM_NETDBENTRY));
        *(list + list_count) = n;
        ++list_count;
    }

    qsort((char *) list,
          list_count,
          sizeof(netdbEntry *),
          netdbLRU);

    for (k = 0; k < list_count; ++k) {
        if (memInUse(MEM_NETDBENTRY) < Config.Netdb.low)
            break;

        netdbRelease(*(list + k));

        ++removed;
    }

    xfree(list);
}