{
    char ntoabuf[MAX_IPSTRLEN];

    while (s) {
        storeAppendPrintf(e, "%s %s\n",
                          n,
                          s->s.toStr(ntoabuf,MAX_IPSTRLEN));
        s = s->next;
    }
}

static void
free_IpAddress_list(Ip::Address_list ** head)
