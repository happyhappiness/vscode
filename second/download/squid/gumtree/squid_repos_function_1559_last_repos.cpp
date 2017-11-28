void
peerConnectSucceded(CachePeer * p)
{
    if (!p->tcp_up) {
        debugs(15, 2, "TCP connection to " << p->host << "/" << p->http_port << " succeded");
        p->tcp_up = p->connect_fail_limit; // NP: so peerAlive(p) works properly.
        peerAlive(p);
        if (!p->n_addresses)
            ipcache_nbgethostbyname(p->host, peerDNSConfigure, p);
    } else
        p->tcp_up = p->connect_fail_limit;
}