void
neighbors_init(void)
{
    struct servent *sep = NULL;
    const char *me = getMyHostname();
    CachePeer *thisPeer = NULL;
    CachePeer *next = NULL;

    neighborsRegisterWithCacheManager();

    if (Comm::IsConnOpen(icpIncomingConn)) {

        for (thisPeer = Config.peers; thisPeer; thisPeer = next) {
            next = thisPeer->next;

            if (0 != strcmp(thisPeer->host, me))
                continue;

            for (AnyP::PortCfg *s = Config.Sockaddr.http; s; s = s->next) {
                if (thisPeer->http_port != s->s.GetPort())
                    continue;

                debugs(15, DBG_IMPORTANT, "WARNING: Peer looks like this host");

                debugs(15, DBG_IMPORTANT, "         Ignoring " <<
                       neighborTypeStr(thisPeer) << " " << thisPeer->host <<
                       "/" << thisPeer->http_port << "/" <<
                       thisPeer->icp.port);

                neighborRemove(thisPeer);
            }
        }
    }

    peerRefreshDNS((void *) 1);

    sep = getservbyname("echo", "udp");
    echo_port = sep ? ntohs((unsigned short) sep->s_port) : 7;

    first_ping = Config.peers;
}