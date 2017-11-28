int
aclMatchArp(SplayNode<acl_arp_data *> **dataptr, IpAddress &c)
{
    struct arpreq arpReq;
#if !defined(_SQUID_WIN32_)
    struct sockaddr_in *sa = NULL;
#endif

    IpAddress ipAddr = c;
    ipAddr.SetPort(0);  // ARP will fail if the port is included in the match.

#if defined(_SQUID_LINUX_)

    unsigned char ifbuffer[sizeof(struct ifreq) * 64];
    struct ifconf ifc;

    struct ifreq *ifr;
    int offset;

    SplayNode<acl_arp_data*> **Top = dataptr;

    /* IPv6 builds do not provide the first http_port as an IPv4 socket for ARP */
    int tmpSocket = socket(AF_INET,SOCK_STREAM,0);

    /*
     * The linux kernel 2.2 maintains per interface ARP caches and
     * thus requires an interface name when doing ARP queries.
     *
     * The older 2.0 kernels appear to use a unified ARP cache,
     * and require an empty interface name
     *
     * To support both, we attempt the lookup with a blank interface
     * name first. If that does not succeed, the try each interface
     * in turn
     */

    /*
     * Set up structures for ARP lookup with blank interface name
     */
    memset(&arpReq, '\0', sizeof(arpReq));

    sa = (sockaddr_in*)&arpReq.arp_pa;
    ipAddr.GetSockAddr(*sa);
    /* Query ARP table */

    if (ioctl(tmpSocket, SIOCGARP, &arpReq) != -1) {
        /* Skip non-ethernet interfaces */
        close(tmpSocket);

        if (arpReq.arp_ha.sa_family != ARPHRD_ETHER) {
            return 0;
        }

        debugs(28, 4, "Got address "<< std::setfill('0') << std::hex <<
               std::setw(2) << (arpReq.arp_ha.sa_data[0] & 0xff)  << ":" <<
               std::setw(2) << (arpReq.arp_ha.sa_data[1] & 0xff)  << ":" <<
               std::setw(2) << (arpReq.arp_ha.sa_data[2] & 0xff)  << ":" <<
               std::setw(2) << (arpReq.arp_ha.sa_data[3] & 0xff)  << ":" <<
               std::setw(2) << (arpReq.arp_ha.sa_data[4] & 0xff)  << ":" <<
               std::setw(2) << (arpReq.arp_ha.sa_data[5] & 0xff));

        /* Do lookup */
        acl_arp_data X;
        memcpy (X.eth, arpReq.arp_ha.sa_data, 6);
        *Top = (*Top)->splay(&X, aclArpCompare);
        debugs(28, 3, "aclMatchArp: '" << ipAddr << "' " << (splayLastResult ? "NOT found" : "found"));
        return (0 == splayLastResult);
    }

    /* lookup list of interface names */
    ifc.ifc_len = sizeof(ifbuffer);

    ifc.ifc_buf = (char *)ifbuffer;

    if (ioctl(tmpSocket, SIOCGIFCONF, &ifc) < 0) {
        debugs(28, 1, "Attempt to retrieve interface list failed: " << xstrerror());
        close(tmpSocket);
        return 0;
    }

    if (ifc.ifc_len > (int)sizeof(ifbuffer)) {
        debugs(28, 1, "Interface list too long - " << ifc.ifc_len);
        close(tmpSocket);
        return 0;
    }

    /* Attempt ARP lookup on each interface */
    offset = 0;

    while (offset < ifc.ifc_len) {

        ifr = (struct ifreq *) (ifbuffer + offset);
        offset += sizeof(*ifr);
        /* Skip loopback and aliased interfaces */

        if (0 == strncmp(ifr->ifr_name, "lo", 2))
            continue;

        if (NULL != strchr(ifr->ifr_name, ':'))
            continue;

        debugs(28, 4, "Looking up ARP address for " << ipAddr << " on " << ifr->ifr_name);

        /* Set up structures for ARP lookup */

        memset(&arpReq, '\0', sizeof(arpReq));

        sa = (sockaddr_in*)&arpReq.arp_pa;
        ipAddr.GetSockAddr(*sa);

        strncpy(arpReq.arp_dev, ifr->ifr_name, sizeof(arpReq.arp_dev) - 1);

        arpReq.arp_dev[sizeof(arpReq.arp_dev) - 1] = '\0';

        /* Query ARP table */
        if (-1 == ioctl(tmpSocket, SIOCGARP, &arpReq)) {
            /*
             * Query failed.  Do not log failed lookups or "device
             * not supported"
             */

            if (ENXIO == errno)
                (void) 0;
            else if (ENODEV == errno)
                (void) 0;
            else
                debugs(28, 1, "ARP query failed: " << ifr->ifr_name << ": " << xstrerror());

            continue;
        }

        /* Skip non-ethernet interfaces */
        if (arpReq.arp_ha.sa_family != ARPHRD_ETHER)
            continue;

        debugs(28, 4, "Got address "<< std::setfill('0') << std::hex <<
               std::setw(2) << (arpReq.arp_ha.sa_data[0] & 0xff)  << ":" <<
               std::setw(2) << (arpReq.arp_ha.sa_data[1] & 0xff)  << ":" <<
               std::setw(2) << (arpReq.arp_ha.sa_data[2] & 0xff)  << ":" <<
               std::setw(2) << (arpReq.arp_ha.sa_data[3] & 0xff)  << ":" <<
               std::setw(2) << (arpReq.arp_ha.sa_data[4] & 0xff)  << ":" <<
               std::setw(2) << (arpReq.arp_ha.sa_data[5] & 0xff)  << " on "<<
               std::setfill(' ') << ifr->ifr_name);

        /* Do lookup */
        acl_arp_data X;

        memcpy (X.eth, arpReq.arp_ha.sa_data, 6);

        *Top = (*Top)->splay(&X, aclArpCompare);

        /* Return if match, otherwise continue to other interfaces */
        if (0 == splayLastResult) {
            debugs(28, 3, "aclMatchArp: " << ipAddr << " found on " << ifr->ifr_name);
            close(tmpSocket);
            return 1;
        }

        /*
         * Should we stop looking here? Can the same IP address
         * exist on multiple interfaces?
         */
    }

    close(tmpSocket);

#elif defined(_SQUID_SOLARIS_)

    SplayNode<acl_arp_data *> **Top = dataptr;

    /* IPv6 builds do not provide the first http_port as an IPv4 socket for ARP */
    int tmpSocket = socket(AF_INET,SOCK_STREAM,0);

    /*
    * Set up structures for ARP lookup with blank interface name
    */

    memset(&arpReq, '\0', sizeof(arpReq));

    sa = (sockaddr_in*)&arpReq.arp_pa;
    ipAddr.GetSockAddr(*sa);

    /* Query ARP table */
    if (ioctl(tmpSocket, SIOCGARP, &arpReq) != -1) {
        /*
        *  Solaris (at least 2.6/x86) does not use arp_ha.sa_family -
        * it returns 00:00:00:00:00:00 for non-ethernet media
        */
        close(tmpSocket);

        if (arpReq.arp_ha.sa_data[0] == 0 &&
                arpReq.arp_ha.sa_data[1] == 0 &&
                arpReq.arp_ha.sa_data[2] == 0 &&
                arpReq.arp_ha.sa_data[3] == 0 &&
                arpReq.arp_ha.sa_data[4] == 0 && arpReq.arp_ha.sa_data[5] == 0)
            return 0;

        debugs(28, 4, "Got address "<< std::setfill('0') << std::hex <<
               std::setw(2) << (arpReq.arp_ha.sa_data[0] & 0xff)  << ":" <<
               std::setw(2) << (arpReq.arp_ha.sa_data[1] & 0xff)  << ":" <<
               std::setw(2) << (arpReq.arp_ha.sa_data[2] & 0xff)  << ":" <<
               std::setw(2) << (arpReq.arp_ha.sa_data[3] & 0xff)  << ":" <<
               std::setw(2) << (arpReq.arp_ha.sa_data[4] & 0xff)  << ":" <<
               std::setw(2) << (arpReq.arp_ha.sa_data[5] & 0xff));

        /* Do lookup */
        *Top = (*Top)->splay((acl_arp_data *)&arpReq.arp_ha.sa_data, aclArpCompare);

        debugs(28, 3, "aclMatchArp: '" << ipAddr << "' " << (splayLastResult ? "NOT found" : "found"));

        return (0 == splayLastResult);
    }

    close(tmpSocket);

#elif defined(_SQUID_FREEBSD_) || defined(_SQUID_NETBSD_) || defined(_SQUID_OPENBSD_) || defined(_SQUID_DRAGONFLY_) || defined(_SQUID_KFREEBSD_)

    SplayNode<acl_arp_data *> **Top = dataptr;

    int mib[6];

    size_t needed;

    char *lim, *buf, *next;

    struct rt_msghdr *rtm;

    struct sockaddr_inarp *sin;

    struct sockaddr_dl *sdl;

    /*
    * Set up structures for ARP lookup with blank interface name
    */

    memset(&arpReq, '\0', sizeof(arpReq));

    sa = (struct sockaddr_in*) &arpReq.arp_pa;
    ipAddr.GetSockAddr(*sa);

    /* Query ARP table */
    mib[0] = CTL_NET;

    mib[1] = PF_ROUTE;

    mib[2] = 0;

    mib[3] = AF_INET;

    mib[4] = NET_RT_FLAGS;

    mib[5] = RTF_LLINFO;

    if (sysctl(mib, 6, NULL, &needed, NULL, 0) < 0) {
        debugs(28, 0, "Can't estimate ARP table size!");
        return 0;
    }

    if ((buf = (char *)xmalloc(needed)) == NULL) {
        debugs(28, 0, "Can't allocate temporary ARP table!");
        return 0;
    }

    if (sysctl(mib, 6, buf, &needed, NULL, 0) < 0) {
        debugs(28, 0, "Can't retrieve ARP table!");
        xfree(buf);
        return 0;
    }

    lim = buf + needed;

    for (next = buf; next < lim; next += rtm->rtm_msglen) {

        rtm = (struct rt_msghdr *) next;

        sin = (struct sockaddr_inarp *) (rtm + 1);
        /*sdl = (struct sockaddr_dl *) (sin + 1); */

#define ROUNDUP(a) \
        ((a) > 0 ? (1 + (((a) - 1) | (sizeof(long) - 1))) : sizeof(long))

        sdl = (struct sockaddr_dl *)((char *) sin + ROUNDUP(sin->sin_len));

        if (c == sin->sin_addr) {
            if (sdl->sdl_alen) {

                arpReq.arp_ha.sa_len = sizeof(struct sockaddr);
                arpReq.arp_ha.sa_family = AF_UNSPEC;
                memcpy(arpReq.arp_ha.sa_data, LLADDR(sdl), sdl->sdl_alen);
            }
        }
    }

    xfree(buf);

    if (arpReq.arp_ha.sa_data[0] == 0 && arpReq.arp_ha.sa_data[1] == 0 &&
            arpReq.arp_ha.sa_data[2] == 0 && arpReq.arp_ha.sa_data[3] == 0 &&
            arpReq.arp_ha.sa_data[4] == 0 && arpReq.arp_ha.sa_data[5] == 0)
        return 0;

    debugs(28, 4, "Got address "<< std::setfill('0') << std::hex <<
           std::setw(2) << (arpReq.arp_ha.sa_data[0] & 0xff)  << ":" <<
           std::setw(2) << (arpReq.arp_ha.sa_data[1] & 0xff)  << ":" <<
           std::setw(2) << (arpReq.arp_ha.sa_data[2] & 0xff)  << ":" <<
           std::setw(2) << (arpReq.arp_ha.sa_data[3] & 0xff)  << ":" <<
           std::setw(2) << (arpReq.arp_ha.sa_data[4] & 0xff)  << ":" <<
           std::setw(2) << (arpReq.arp_ha.sa_data[5] & 0xff));

    /* Do lookup */
    *Top = (*Top)->splay((acl_arp_data *)&arpReq.arp_ha.sa_data, aclArpCompare);

    debugs(28, 3, "aclMatchArp: '" << ipAddr << "' " << (splayLastResult ? "NOT found" : "found"));

    return (0 == splayLastResult);

#elif defined(_SQUID_WIN32_)

    DWORD           dwNetTable = 0;

    DWORD           ipNetTableLen = 0;

    PMIB_IPNETTABLE NetTable = NULL;

    DWORD            i;

    SplayNode<acl_arp_data *> **Top = dataptr;

    memset(&arpReq, '\0', sizeof(arpReq));

    /* Get size of Windows ARP table */
    if (GetIpNetTable(NetTable, &ipNetTableLen, FALSE) != ERROR_INSUFFICIENT_BUFFER) {
        debugs(28, 0, "Can't estimate ARP table size!");
        return 0;
    }

    /* Allocate space for ARP table and assign pointers */
    if ((NetTable = (PMIB_IPNETTABLE)xmalloc(ipNetTableLen)) == NULL) {
        debugs(28, 0, "Can't allocate temporary ARP table!");
        return 0;
    }

    /* Get actual ARP table */
    if ((dwNetTable = GetIpNetTable(NetTable, &ipNetTableLen, FALSE)) != NO_ERROR) {
        debugs(28, 0, "Can't retrieve ARP table!");
        xfree(NetTable);
        return 0;
    }

    /* Find MAC address from net table */
    for (i = 0 ; i < NetTable->dwNumEntries ; i++) {
        in_addr a;
        a.s_addr = NetTable->table[i].dwAddr;
        if (c == a && (NetTable->table[i].dwType > 2)) {
            arpReq.arp_ha.sa_family = AF_UNSPEC;
            memcpy(arpReq.arp_ha.sa_data, NetTable->table[i].bPhysAddr, NetTable->table[i].dwPhysAddrLen);
        }
    }

    xfree(NetTable);

    if (arpReq.arp_ha.sa_data[0] == 0 && arpReq.arp_ha.sa_data[1] == 0 &&
            arpReq.arp_ha.sa_data[2] == 0 && arpReq.arp_ha.sa_data[3] == 0 &&
            arpReq.arp_ha.sa_data[4] == 0 && arpReq.arp_ha.sa_data[5] == 0)
        return 0;

    debugs(28, 4, "Got address "<< std::setfill('0') << std::hex <<
           std::setw(2) << (arpReq.arp_ha.sa_data[0] & 0xff)  << ":" <<
           std::setw(2) << (arpReq.arp_ha.sa_data[1] & 0xff)  << ":" <<
           std::setw(2) << (arpReq.arp_ha.sa_data[2] & 0xff)  << ":" <<
           std::setw(2) << (arpReq.arp_ha.sa_data[3] & 0xff)  << ":" <<
           std::setw(2) << (arpReq.arp_ha.sa_data[4] & 0xff)  << ":" <<
           std::setw(2) << (arpReq.arp_ha.sa_data[5] & 0xff));

    /* Do lookup */
    *Top = (*Top)->splay((acl_arp_data *)&arpReq.arp_ha.sa_data, aclArpCompare);

    debugs(28, 3, "aclMatchArp: '" << ipAddr << "' " << (splayLastResult ? "NOT found" : "found"));

    return (0 == splayLastResult);

#else

#error "ARP type ACL not supported on this operating system."

#endif
    /*
     * Address was not found on any interface
     */
    debugs(28, 3, "aclMatchArp: " << ipAddr << " NOT found");

    return 0;
}