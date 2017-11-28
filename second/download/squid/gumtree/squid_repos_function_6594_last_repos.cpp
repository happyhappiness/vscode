void
netdbBinaryExchange(StoreEntry * s)
{
    HttpReply *reply = new HttpReply;
#if USE_ICMP

    Ip::Address addr;

    netdbEntry *n;
    int i;
    int j;
    int rec_sz;
    char *buf;

    struct in_addr line_addr;
    s->buffer();
    reply->setHeaders(Http::scOkay, "OK", NULL, -1, squid_curtime, -2);
    s->replaceHttpReply(reply);
    rec_sz = 0;
    rec_sz += 1 + sizeof(struct in_addr);
    rec_sz += 1 + sizeof(int);
    rec_sz += 1 + sizeof(int);
    buf = (char *)memAllocate(MEM_4K_BUF);
    i = 0;
    hash_first(addr_table);

    while ((n = (netdbEntry *) hash_next(addr_table))) {
        if (0.0 == n->rtt)
            continue;

        if (n->rtt > 60000) /* RTT > 1 MIN probably bogus */
            continue;

        if (! (addr = n->network) )
            continue;

        /* FIXME INET6 : NetDB cannot yet handle IPv6 addresses. Ensure only IPv4 get sent. */
        if ( !addr.isIPv4() )
            continue;

        buf[i] = (char) NETDB_EX_NETWORK;
        ++i;

        addr.getInAddr(line_addr);
        memcpy(&buf[i], &line_addr, sizeof(struct in_addr));

        i += sizeof(struct in_addr);

        buf[i] = (char) NETDB_EX_RTT;
        ++i;

        j = htonl((int) (n->rtt * 1000));

        memcpy(&buf[i], &j, sizeof(int));

        i += sizeof(int);

        buf[i] = (char) NETDB_EX_HOPS;
        ++i;

        j = htonl((int) (n->hops * 1000));

        memcpy(&buf[i], &j, sizeof(int));

        i += sizeof(int);

        if (i + rec_sz > 4096) {
            s->append(buf, i);
            i = 0;
        }
    }

    if (i > 0) {
        s->append(buf, i);
        i = 0;
    }

    assert(0 == i);
    s->flush();
    memFree(buf, MEM_4K_BUF);
#else

    reply->setHeaders(Http::scBadRequest, "Bad Request", NULL, -1, squid_curtime, -2);
    s->replaceHttpReply(reply);
    storeAppendPrintf(s, "NETDB support not compiled into this Squid cache.\n");
#endif

    s->complete();
}