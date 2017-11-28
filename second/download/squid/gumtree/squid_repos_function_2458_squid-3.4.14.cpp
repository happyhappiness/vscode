static int
ipcacheParse(ipcache_entry *i, const char *inbuf)
{
    LOCAL_ARRAY(char, buf, DNS_INBUF_SZ);
    char *token;
    int ipcount = 0;
    int ttl;
    char *A[32];
    const char *name = (const char *)i->hash.key;
    i->expires = squid_curtime + Config.negativeDnsTtl;
    i->flags.negcached = 1;
    safe_free(i->addrs.in_addrs);
    safe_free(i->addrs.bad_mask);
    safe_free(i->error_message);
    i->addrs.count = 0;

    if (inbuf == NULL) {
        debugs(14, DBG_IMPORTANT, "ipcacheParse: Got <NULL> reply");
        i->error_message = xstrdup("Internal Error");
        return -1;
    }

    xstrncpy(buf, inbuf, DNS_INBUF_SZ);
    debugs(14, 5, "ipcacheParse: parsing: {" << buf << "}");
    token = strtok(buf, w_space);

    if (NULL == token) {
        debugs(14, DBG_IMPORTANT, "ipcacheParse: expecting result, got '" << inbuf << "'");

        i->error_message = xstrdup("Internal Error");
        return -1;
    }

    if (0 == strcmp(token, "$fail")) {
        token = strtok(NULL, "\n");
        assert(NULL != token);
        i->error_message = xstrdup(token);
        return 0;
    }

    if (0 != strcmp(token, "$addr")) {
        debugs(14, DBG_IMPORTANT, "ipcacheParse: expecting '$addr', got '" << inbuf << "' in response to '" << name << "'");

        i->error_message = xstrdup("Internal Error");
        return -1;
    }

    token = strtok(NULL, w_space);

    if (NULL == token) {
        debugs(14, DBG_IMPORTANT, "ipcacheParse: expecting TTL, got '" << inbuf << "' in response to '" << name << "'");

        i->error_message = xstrdup("Internal Error");
        return -1;
    }

    ttl = atoi(token);

    while (NULL != (token = strtok(NULL, w_space))) {
        A[ipcount] = token;

        if (++ipcount == 32)
            break;
    }

    if (ipcount > 0) {
        int j, k;

        i->addrs.in_addrs = static_cast<Ip::Address *>(xcalloc(ipcount, sizeof(Ip::Address)));
        for (int l = 0; l < ipcount; ++l)
            i->addrs.in_addrs[l].setEmpty(); // perform same init actions as constructor would.
        i->addrs.bad_mask = (unsigned char *)xcalloc(ipcount, sizeof(unsigned char));
        memset(i->addrs.bad_mask, 0, sizeof(unsigned char) * ipcount);

        for (j = 0, k = 0; k < ipcount; ++k) {
            if ((i->addrs.in_addrs[j] = A[k]))
                ++j;
            else
                debugs(14, DBG_IMPORTANT, "ipcacheParse: Invalid IP address '" << A[k] << "' in response to '" << name << "'");
        }

        i->addrs.count = (unsigned char) j;
    }

    if (i->addrs.count <= 0) {
        debugs(14, DBG_IMPORTANT, "ipcacheParse: No addresses in response to '" << name << "'");
        return -1;
    }

    if (ttl == 0 || ttl > Config.positiveDnsTtl)
        ttl = Config.positiveDnsTtl;

    if (ttl < Config.negativeDnsTtl)
        ttl = Config.negativeDnsTtl;

    i->expires = squid_curtime + ttl;

    i->flags.negcached = 0;

    return i->addrs.count;
}