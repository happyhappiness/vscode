static void
dump_IpAddress_list(StoreEntry * e, const char *n, const Ip::Address_list * s)
{
    char ntoabuf[MAX_IPSTRLEN];

    while (s) {
        storeAppendPrintf(e, "%s %s\n",
                          n,
                          s->s.toStr(ntoabuf,MAX_IPSTRLEN));
        s = s->next;
    }
}