static void
neighborIgnoreNonPeer(const IpAddress &from, icp_opcode opcode)
{
    peer *np;

    for (np = non_peers; np; np = np->next) {
        if (np->in_addr != from)
            continue;

        if (np->in_addr.GetPort() != from.GetPort())
            continue;

        break;
    }

    if (np == NULL) {
        np = (peer *)xcalloc(1, sizeof(peer));
        np->in_addr = from;
        np->icp.port = from.GetPort();
        np->type = PEER_NONE;
        np->host = new char[MAX_IPSTRLEN];
        from.NtoA(np->host,MAX_IPSTRLEN);
        np->next = non_peers;
        non_peers = np;
    }

    np->icp.counts[opcode]++;

    if (isPowTen(++np->stats.ignored_replies))
        debugs(15, 1, "WARNING: Ignored " << np->stats.ignored_replies << " replies from non-peer " << np->host);
}