void
idnsPTRLookup(const IpAddress &addr, IDNSCB * callback, void *data)
{
    idns_query *q;

    char ip[MAX_IPSTRLEN];

    addr.NtoA(ip,MAX_IPSTRLEN);

    q = cbdataAlloc(idns_query);

    q->id = idnsQueryID();

    if (addr.IsIPv6()) {
        struct in6_addr addr6;
        addr.GetInAddr(addr6);
        q->sz = rfc3596BuildPTRQuery6(addr6, q->buf, sizeof(q->buf), q->id, &q->query);
    } else {
        struct in_addr addr4;
        addr.GetInAddr(addr4);
        q->sz = rfc3596BuildPTRQuery4(addr4, q->buf, sizeof(q->buf), q->id, &q->query);
    }

    /* PTR does not do inbound A/AAAA */
    q->need_A = false;

    if (q->sz < 0) {
        /* problem with query data -- query not sent */
        callback(data, NULL, 0, "Internal error");
        cbdataFree(q);
        return;
    }

    if (idnsCachedLookup(q->query.name, callback, data)) {
        cbdataFree(q);
        return;
    }

    debugs(78, 3, "idnsPTRLookup: buf is " << q->sz << " bytes for " << ip <<
           ", id = 0x" << std::hex << q->id);

    q->callback = callback;
    q->callback_data = cbdataReference(data);

    q->start_t = current_time;

    idnsCacheQuery(q);
    idnsSendQuery(q);
}