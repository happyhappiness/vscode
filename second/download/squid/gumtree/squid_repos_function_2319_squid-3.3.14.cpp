void
idnsPTRLookup(const Ip::Address &addr, IDNSCB * callback, void *data)
{
    idns_query *q;

    char ip[MAX_IPSTRLEN];

    addr.NtoA(ip,MAX_IPSTRLEN);

    q = cbdataAlloc(idns_query);

    // idns_query is POD so no constructors are called after allocation
    q->xact_id.change();
    q->query_id = idnsQueryID();

    if (addr.IsIPv6()) {
        struct in6_addr addr6;
        addr.GetInAddr(addr6);
        q->sz = rfc3596BuildPTRQuery6(addr6, q->buf, sizeof(q->buf), q->query_id, &q->query, Config.dns.packet_max);
    } else {
        struct in_addr addr4;
        addr.GetInAddr(addr4);
        // see EDNS notes at top of file why this sends 0
        q->sz = rfc3596BuildPTRQuery4(addr4, q->buf, sizeof(q->buf), q->query_id, &q->query, 0);
    }

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
           ", id = 0x" << std::hex << q->query_id);

    idnsStartQuery(q, callback, data);
}