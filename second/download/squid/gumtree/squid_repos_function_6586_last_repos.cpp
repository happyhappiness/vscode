void
netdbFreeMemory(void)
{
#if USE_ICMP
    hashFreeItems(addr_table, netdbFreeNetdbEntry);
    hashFreeMemory(addr_table);
    addr_table = NULL;
    hashFreeItems(host_table, netdbFreeNameEntry);
    hashFreeMemory(host_table);
    host_table = NULL;
    wordlistDestroy(&peer_names);
    peer_names = NULL;
#endif
}