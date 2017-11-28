bool
Ip::Intercept::IpfInterception(const Comm::ConnectionPointer &newConn, int silent)
{
#if IPF_TRANSPARENT  /* --enable-ipf-transparent */

    struct natlookup natLookup;
    static int natfd = -1;
    int x;

    // all fields must be set to 0
    memset(&natLookup, 0, sizeof(natLookup));
    // for NAT lookup set local and remote IP:port's
    natLookup.nl_inport = htons(newConn->local.GetPort());
    newConn->local.GetInAddr(natLookup.nl_inip);
    natLookup.nl_outport = htons(newConn->remote.GetPort());
    newConn->remote.GetInAddr(natLookup.nl_outip);
    // ... and the TCP flag
    natLookup.nl_flags = IPN_TCP;

    if (natfd < 0) {
        int save_errno;
        enter_suid();
#ifdef IPNAT_NAME
        natfd = open(IPNAT_NAME, O_RDONLY, 0);
#else
        natfd = open(IPL_NAT, O_RDONLY, 0);
#endif
        save_errno = errno;
        leave_suid();
        errno = save_errno;
    }

    if (natfd < 0) {
        if (!silent) {
            debugs(89, DBG_IMPORTANT, "IPF (IPFilter) NAT open failed: " << xstrerror());
            lastReported_ = squid_curtime;
            return false;
        }
    }

#if defined(IPFILTER_VERSION) && (IPFILTER_VERSION >= 4000027)
    struct ipfobj obj;
    memset(&obj, 0, sizeof(obj));
    obj.ipfo_rev = IPFILTER_VERSION;
    obj.ipfo_size = sizeof(natLookup);
    obj.ipfo_ptr = &natLookup;
    obj.ipfo_type = IPFOBJ_NATLOOKUP;

    x = ioctl(natfd, SIOCGNATL, &obj);
#else
    /*
    * IP-Filter changed the type for SIOCGNATL between
    * 3.3 and 3.4.  It also changed the cmd value for
    * SIOCGNATL, so at least we can detect it.  We could
    * put something in configure and use ifdefs here, but
    * this seems simpler.
    */
    static int siocgnatl_cmd = SIOCGNATL & 0xff;
    if (63 == siocgnatl_cmd) {
        struct natlookup *nlp = &natLookup;
        x = ioctl(natfd, SIOCGNATL, &nlp);
    } else {
        x = ioctl(natfd, SIOCGNATL, &natLookup);
    }

#endif
    if (x < 0) {
        if (errno != ESRCH) {
            if (!silent) {
                debugs(89, DBG_IMPORTANT, "IPF (IPFilter) NAT lookup failed: ioctl(SIOCGNATL) (v=" << IPFILTER_VERSION << "): " << xstrerror());
                lastReported_ = squid_curtime;
            }

            close(natfd);
            natfd = -1;
        }

        debugs(89, 9, HERE << "address: " << newConn);
        return false;
    } else {
        newConn->local = natLookup.nl_realip;
        newConn->local.SetPort(ntohs(natLookup.nl_realport));
        debugs(89, 5, HERE << "address NAT: " << newConn);
        return true;
    }

#endif /* --enable-ipf-transparent */
    return false;
}