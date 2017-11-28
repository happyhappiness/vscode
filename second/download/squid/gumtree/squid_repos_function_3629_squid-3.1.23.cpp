int
IpIntercept::NatLookup(int fd, const IpAddress &me, const IpAddress &peer, IpAddress &client, IpAddress &dst)
{
    /* --enable-linux-netfilter    */
    /* --enable-ipfw-transparent   */
    /* --enable-ipf-transparent    */
    /* --enable-pf-transparent     */
#if IPF_TRANSPARENT || LINUX_NETFILTER || IPFW_TRANSPARENT || PF_TRANSPARENT

    client = me;
    dst = peer;

#if 0
    // Crop interception errors down to one per minute.
    int silent = (squid_curtime - last_reported > 60 ? 0 : 1);
#else
    // Show all interception errors.
    int silent = 0;
#endif

    debugs(89, 5, HERE << "address BEGIN: me= " << me << ", client= " << client <<
           ", dst= " << dst << ", peer= " << peer);

    /* NP: try TPROXY first, its much quieter than NAT when non-matching */
    if (transparent_active) {
        if ( NetfilterTransparent(fd, me, dst, silent) == 0) return 0;
    }

    /* NAT is only available in IPv4 */
    if ( !me.IsIPv4()   ) return -1;
    if ( !peer.IsIPv4() ) return -1;

    if (intercept_active) {
        /* NAT methods that use sock-opts to return client address */
        if ( NetfilterInterception(fd, me, client, silent) == 0) return 0;
        if ( IpfwInterception(fd, me, client, silent) == 0) return 0;

        /* NAT methods that use ioctl to return client address AND destination address */
        if ( PfInterception(fd, me, client, dst, silent) == 0) return 0;
        if ( IpfInterception(fd, me, client, dst, silent) == 0) return 0;
    }

#else /* none of the transparent options configured */
    debugs(89, DBG_IMPORTANT, "WARNING: transparent proxying not supported");
#endif

    return -1;
}