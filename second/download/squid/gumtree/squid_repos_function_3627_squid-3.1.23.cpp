int
IpIntercept::IpfInterception(int fd, const IpAddress &me, IpAddress &client, IpAddress &dst, int silent)
{
#if IPF_TRANSPARENT  /* --enable-ipf-transparent */

#if defined(IPFILTER_VERSION) && (IPFILTER_VERSION >= 4000027)
    struct ipfobj obj;
#else
    static int siocgnatl_cmd = SIOCGNATL & 0xff;
#endif
    struct natlookup natLookup;
    static int natfd = -1;
    int x;

#if defined(IPFILTER_VERSION) && (IPFILTER_VERSION >= 4000027)

    obj.ipfo_rev = IPFILTER_VERSION;
    obj.ipfo_size = sizeof(natLookup);
    obj.ipfo_ptr = &natLookup;
    obj.ipfo_type = IPFOBJ_NATLOOKUP;
    obj.ipfo_offset = 0;
#endif

    natLookup.nl_inport = htons(me.GetPort());
    natLookup.nl_outport = htons(dst.GetPort());
    me.GetInAddr(natLookup.nl_inip);
    dst.GetInAddr(natLookup.nl_outip);
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
            debugs(89, DBG_IMPORTANT, HERE << "NAT open failed: " << xstrerror());
            last_reported = squid_curtime;
            return -1;
        }
    }

#if defined(IPFILTER_VERSION) && (IPFILTER_VERSION >= 4000027)
    x = ioctl(natfd, SIOCGNATL, &obj);
#else
    /*
    * IP-Filter changed the type for SIOCGNATL between
    * 3.3 and 3.4.  It also changed the cmd value for
    * SIOCGNATL, so at least we can detect it.  We could
    * put something in configure and use ifdefs here, but
    * this seems simpler.
    */
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
                debugs(89, DBG_IMPORTANT, HERE << "NAT lookup failed: ioctl(SIOCGNATL)");
                last_reported = squid_curtime;
            }

            close(natfd);
            natfd = -1;
        }

        return -1;
    } else {
        if (client != natLookup.nl_realip) {
            client = natLookup.nl_realip;
            client.SetPort(ntohs(natLookup.nl_realport));
        }
        // else. we already copied it.

        debugs(89, 5, HERE << "address NAT: me= " << me << ", client= " << client << ", dst= " << dst);
        return 0;
    }

    debugs(89, 9, HERE << "address: me= " << me << ", client= " << client << ", dst= " << dst);

#endif /* --enable-ipf-transparent */
    return -1;
}