static void
idnsSendQuery(idns_query * q)
{
    if (DnsSocketA < 0 && DnsSocketB < 0) {
        debugs(78, DBG_IMPORTANT, "WARNING: idnsSendQuery: Can't send query, no DNS socket!");
        return;
    }

    if (nns <= 0) {
        debugs(78, DBG_IMPORTANT, "WARNING: idnsSendQuery: Can't send query, no DNS nameservers known!");
        return;
    }

    assert(q->lru.next == NULL);

    assert(q->lru.prev == NULL);

    int x = -1, y = -1;
    int nsn;

    do {
        // only use mDNS resolvers for mDNS compatible queries
        if (!q->permit_mdns)
            nsn = nns_mdns_count + q->nsends % (nns-nns_mdns_count);
        else
            nsn = q->nsends % nns;

        if (q->need_vc) {
            idnsSendQueryVC(q, nsn);
            x = y = 0;
        } else {
            if (DnsSocketB >= 0 && nameservers[nsn].S.isIPv6())
                y = comm_udp_sendto(DnsSocketB, nameservers[nsn].S, q->buf, q->sz);
            else if (DnsSocketA >= 0)
                x = comm_udp_sendto(DnsSocketA, nameservers[nsn].S, q->buf, q->sz);
        }

        ++ q->nsends;

        q->sent_t = current_time;

        if (y < 0 && nameservers[nsn].S.isIPv6())
            debugs(50, DBG_IMPORTANT, "idnsSendQuery: FD " << DnsSocketB << ": sendto: " << xstrerror());
        if (x < 0 && nameservers[nsn].S.isIPv4())
            debugs(50, DBG_IMPORTANT, "idnsSendQuery: FD " << DnsSocketA << ": sendto: " << xstrerror());

    } while ( (x<0 && y<0) && q->nsends % nns != 0);

    if (y > 0) {
        fd_bytes(DnsSocketB, y, FD_WRITE);
    }
    if (x > 0) {
        fd_bytes(DnsSocketA, x, FD_WRITE);
    }

    ++ nameservers[nsn].nqueries;
    q->queue_t = current_time;
    dlinkAdd(q, &q->lru, &lru_list);
    q->pending = 1;
    idnsTickleQueue();
}