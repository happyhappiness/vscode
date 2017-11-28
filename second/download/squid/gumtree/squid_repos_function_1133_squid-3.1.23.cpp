static void
dump_IpAddress_list(StoreEntry * e, const char *n, const IpAddress_list * s)
{
    char ntoabuf[MAX_IPSTRLEN];

    while (s) {
        storeAppendPrintf(e, "%s %s\n",
                          n,
                          s->s.NtoA(ntoabuf,MAX_IPSTRLEN));
        s = s->next;
    }
}