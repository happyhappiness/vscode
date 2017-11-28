static void
idnsAddNameserver(const char *buf)
{
    Ip::Address A;

    if (!(A = buf)) {
        debugs(78, DBG_CRITICAL, "WARNING: rejecting '" << buf << "' as a name server, because it is not a numeric IP address");
        return;
    }

    if (A.IsAnyAddr()) {
        debugs(78, DBG_CRITICAL, "WARNING: Squid does not accept " << A << " in DNS server specifications.");
        A.SetLocalhost();
        debugs(78, DBG_CRITICAL, "Will be using " << A << " instead, assuming you meant that DNS is running on the same machine");
    }

    if (!Ip::EnableIpv6 && !A.SetIPv4()) {
        debugs(78, DBG_IMPORTANT, "WARNING: IPv6 is disabled. Discarding " << A << " in DNS server specifications.");
        return;
    }

    if (nns == nns_alloc) {
        int oldalloc = nns_alloc;
        ns *oldptr = nameservers;

        if (nns_alloc == 0)
            nns_alloc = 2;
        else
            nns_alloc <<= 1;

        nameservers = (ns *)xcalloc(nns_alloc, sizeof(*nameservers));

        if (oldptr && oldalloc)
            memcpy(nameservers, oldptr, oldalloc * sizeof(*nameservers));

        if (oldptr)
            safe_free(oldptr);
    }

    assert(nns < nns_alloc);
    A.SetPort(NS_DEFAULTPORT);
    nameservers[nns].S = A;
#if WHEN_EDNS_RESPONSES_ARE_PARSED
    nameservers[nns].last_seen_edns = RFC1035_DEFAULT_PACKET_SZ;
    // TODO generate a test packet to probe this NS from EDNS size and ability.
#endif
    debugs(78, 3, "idnsAddNameserver: Added nameserver #" << nns << " (" << A << ")");
    ++nns;
}