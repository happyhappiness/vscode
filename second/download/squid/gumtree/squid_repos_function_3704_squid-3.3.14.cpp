bool
Ip::Intercept::PfInterception(const Comm::ConnectionPointer &newConn, int silent)
{
#if PF_TRANSPARENT  /* --enable-pf-transparent */

    struct pfioc_natlook nl;
    static int pffd = -1;

    if (pffd < 0)
        pffd = open("/dev/pf", O_RDONLY);

    if (pffd < 0) {
        if (!silent) {
            debugs(89, DBG_IMPORTANT, HERE << "PF open failed: " << xstrerror());
            lastReported_ = squid_curtime;
        }
        return false;
    }

    memset(&nl, 0, sizeof(struct pfioc_natlook));
    newConn->remote.GetInAddr(nl.saddr.v4);
    nl.sport = htons(newConn->remote.GetPort());

    newConn->local.GetInAddr(nl.daddr.v4);
    nl.dport = htons(newConn->local.GetPort());

    nl.af = AF_INET;
    nl.proto = IPPROTO_TCP;
    nl.direction = PF_OUT;

    if (ioctl(pffd, DIOCNATLOOK, &nl)) {
        if (errno != ENOENT) {
            if (!silent) {
                debugs(89, DBG_IMPORTANT, HERE << "PF lookup failed: ioctl(DIOCNATLOOK)");
                lastReported_ = squid_curtime;
            }
            close(pffd);
            pffd = -1;
        }
        debugs(89, 9, HERE << "address: " << newConn);
        return false;
    } else {
        newConn->local = nl.rdaddr.v4;
        newConn->local.SetPort(ntohs(nl.rdport));
        debugs(89, 5, HERE << "address NAT: " << newConn);
        return true;
    }

#endif /* --enable-pf-transparent */
    return false;
}