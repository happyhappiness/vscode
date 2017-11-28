static void
doV2Query(int fd, Ip::Address &from, char *buf, icp_common_t header)
{
    int rtt = 0;
    int src_rtt = 0;
    uint32_t flags = 0;
    /* We have a valid packet */
    char *url = buf + sizeof(icp_common_t) + sizeof(uint32_t);
    HttpRequest *icp_request = icpGetRequest(url, header.reqnum, fd, from);

    if (!icp_request)
        return;

    HTTPMSGLOCK(icp_request);

    if (!icpAccessAllowed(from, icp_request)) {
        icpDenyAccess(from, url, header.reqnum, fd);
        HTTPMSGUNLOCK(icp_request);
        return;
    }
#if USE_ICMP
    if (header.flags & ICP_FLAG_SRC_RTT) {
        rtt = netdbHostRtt(icp_request->GetHost());
        int hops = netdbHostHops(icp_request->GetHost());
        src_rtt = ((hops & 0xFFFF) << 16) | (rtt & 0xFFFF);

        if (rtt)
            flags |= ICP_FLAG_SRC_RTT;
    }
#endif /* USE_ICMP */

    /* The peer is allowed to use this cache */
    ICP2State *state = new ICP2State(header, icp_request);
    state->fd = fd;
    state->from = from;
    state->url = xstrdup(url);
    state->flags = flags;
    state->rtt = rtt;
    state->src_rtt = src_rtt;

    StoreEntry::getPublic(state, url, Http::METHOD_GET);

    HTTPMSGUNLOCK(icp_request);
}