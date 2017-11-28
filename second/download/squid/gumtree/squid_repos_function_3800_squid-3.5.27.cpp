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
    if (newConn->remote.isIPv6()) {
#if IPFILTER_VERSION < 5000003
        // warn once every 10 at critical level, then push down a level each repeated event
        static int warningLevel = DBG_CRITICAL;
        debugs(89, warningLevel, "IPF (IPFilter v4) NAT does not support IPv6. Please upgrade to IPFilter v5.1");
        warningLevel = (warningLevel + 1) % 10;
        return false;
    }
    newConn->local.getInAddr(natLookup.nl_inip);
    newConn->remote.getInAddr(natLookup.nl_outip);
#else
        natLookup.nl_v = 6;
        newConn->local.getInAddr(natLookup.nl_inipaddr.in6);
        newConn->remote.getInAddr(natLookup.nl_outipaddr.in6);
    }