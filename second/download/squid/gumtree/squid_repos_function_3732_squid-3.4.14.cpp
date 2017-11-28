bool
Ip::Intercept::Lookup(const Comm::ConnectionPointer &newConn, const Comm::ConnectionPointer &listenConn)
{
    /* --enable-linux-netfilter    */
    /* --enable-ipfw-transparent   */
    /* --enable-ipf-transparent    */
    /* --enable-pf-transparent     */
#if IPF_TRANSPARENT || LINUX_NETFILTER || IPFW_TRANSPARENT || PF_TRANSPARENT

#if 0
    // Crop interception errors down to one per minute.
    int silent = (squid_curtime - lastReported_ > 60 ? 0 : 1);
#else
    // Show all interception errors.
    int silent = 0;
#endif

    debugs(89, 5, HERE << "address BEGIN: me/client= " << newConn->local << ", destination/me= " << newConn->remote);

    newConn->flags |= (listenConn->flags & (COMM_TRANSPARENT|COMM_INTERCEPTION));

    /* NP: try TPROXY first, its much quieter than NAT when non-matching */
    if (transparentActive_ && listenConn->flags&COMM_TRANSPARENT) {
        if (TproxyTransparent(newConn, silent)) return true;
    }

    if (interceptActive_ && listenConn->flags&COMM_INTERCEPTION) {
        /* NAT methods that use sock-opts to return client address */
        if (NetfilterInterception(newConn, silent)) return true;
        if (IpfwInterception(newConn, silent)) return true;

        /* NAT methods that use ioctl to return client address AND destination address */
        if (PfInterception(newConn, silent)) return true;
        if (IpfInterception(newConn, silent)) return true;
    }

#else /* none of the transparent options configured */
    debugs(89, DBG_IMPORTANT, "WARNING: transparent proxying not supported");
#endif

    return false;
}