void
idnsPTRLookup(const Ip::Address &addr, IDNSCB * callback, void *data)
{
    char ip[MAX_IPSTRLEN];

    addr.toStr(ip,MAX_IPSTRLEN);

    idns_query *q = new idns_query;
    q->query_id = idnsQueryID();

    if (addr.isIPv6()) {
        struct in6_addr addr6;
        addr.getInAddr(addr6);
        q->sz = rfc3596BuildPTRQuery6(addr6, q->buf, sizeof(q->buf), q->query_id, &q->query, Config.dns.packet_max);
    } else {
        struct in_addr addr4;
        addr.getInAddr(addr4);
        // see EDNS notes at top of file why this sends 0
        q->sz = rfc3596BuildPTRQuery4(addr4, q->buf, sizeof(q->buf), q->query_id, &q->query, 0);
    }

    if (q->sz < 0) {
        /* problem with query data -- query not sent */
        callback(data, NULL, 0, "Internal error");
        delete q;
        return;
    }

    if (idnsCachedLookup(q->query.name, callback, data)) {
        delete q;
        return;
    }

    debugs(78, 3, "idnsPTRLookup: buf is " << q->sz << " bytes for " << ip <<
           ", id = 0x" << std::hex << q->query_id);

    q->permit_mdns = Config.onoff.dns_mdns;
    idnsStartQuery(q, callback, data);
}