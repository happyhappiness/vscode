static void
dump_address(StoreEntry * entry, const char *name, Ip::Address &addr)
{
    char buf[MAX_IPSTRLEN];
    storeAppendPrintf(entry, "%s %s\n", name, addr.toStr(buf,MAX_IPSTRLEN) );
}