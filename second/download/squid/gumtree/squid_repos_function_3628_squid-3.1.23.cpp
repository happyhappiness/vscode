int
IpIntercept::PfInterception(int fd, const IpAddress &me, IpAddress &client, IpAddress &dst, int silent)
{
#if PF_TRANSPARENT  /* --enable-pf-transparent */

    struct pfioc_natlook nl;
    static int pffd = -1;

    if (pffd < 0)
        pffd = open("/dev/pf", O_RDONLY);

    if (pffd < 0) {
        if (!silent) {
            debugs(89, DBG_IMPORTANT, HERE << "PF open failed: " << xstrerror());
            last_reported = squid_curtime;
        }
        return -1;
    }

    memset(&nl, 0, sizeof(struct pfioc_natlook));
    dst.GetInAddr(nl.saddr.v4);
    nl.sport = htons(dst.GetPort());

    me.GetInAddr(nl.daddr.v4);
    nl.dport = htons(me.GetPort());

    nl.af = AF_INET;
    nl.proto = IPPROTO_TCP;
    nl.direction = PF_OUT;

    if (ioctl(pffd, DIOCNATLOOK, &nl)) {
        if (errno != ENOENT) {
            if (!silent) {
                debugs(89, DBG_IMPORTANT, HERE << "PF lookup failed: ioctl(DIOCNATLOOK)");
                last_reported = squid_curtime;
            }
            close(pffd);
            pffd = -1;
        }
    } else {
        int natted = (client != nl.rdaddr.v4);
        client = nl.rdaddr.v4;
        client.SetPort(ntohs(nl.rdport));

        if (natted) {
            debugs(89, 5, HERE << "address NAT: me= " << me << ", client= " << client << ", dst= " << dst);
            return 0;
        }
    }

    debugs(89, 9, HERE << "address: me= " << me << ", client= " << client << ", dst= " << dst);

#endif /* --enable-pf-transparent */
    return -1;
}