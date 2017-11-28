void
neighbors_init(void)
{
    IpAddress nul;
    struct addrinfo *AI = NULL;
    struct servent *sep = NULL;
    const char *me = getMyHostname();
    peer *thisPeer = NULL;
    peer *next = NULL;
    int fd = theInIcpConnection;

    neighborsRegisterWithCacheManager();

    /* setup addrinfo for use */
    nul.InitAddrInfo(AI);

    if (fd >= 0) {

        if (getsockname(fd, AI->ai_addr, &AI->ai_addrlen) < 0)
            debugs(15, 1, "getsockname(" << fd << "," << AI->ai_addr << "," << &AI->ai_addrlen << ") failed.");

        for (thisPeer = Config.peers; thisPeer; thisPeer = next) {
            http_port_list *s = NULL;
            next = thisPeer->next;

            if (0 != strcmp(thisPeer->host, me))
                continue;

            for (s = Config.Sockaddr.http; s; s = s->next) {
                if (thisPeer->http_port != s->s.GetPort())
                    continue;

                debugs(15, 1, "WARNING: Peer looks like this host");

                debugs(15, 1, "         Ignoring " <<
                       neighborTypeStr(thisPeer) << " " << thisPeer->host <<
                       "/" << thisPeer->http_port << "/" <<
                       thisPeer->icp.port);

                neighborRemove(thisPeer);
            }
        }
    }

    peerRefreshDNS((void *) 1);

    if (ICP_INVALID == echo_hdr.opcode) {
        echo_hdr.opcode = ICP_SECHO;
        echo_hdr.version = ICP_VERSION_CURRENT;
        echo_hdr.length = 0;
        echo_hdr.reqnum = 0;
        echo_hdr.flags = 0;
        echo_hdr.pad = 0;
        nul = *AI;
        nul.GetInAddr( *((struct in_addr*)&echo_hdr.shostid) );
        sep = getservbyname("echo", "udp");
        echo_port = sep ? ntohs((unsigned short) sep->s_port) : 7;
    }

    first_ping = Config.peers;
    nul.FreeAddrInfo(AI);
}