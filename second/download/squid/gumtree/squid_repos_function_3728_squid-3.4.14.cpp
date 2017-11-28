bool
Ip::Intercept::TproxyTransparent(const Comm::ConnectionPointer &newConn, int silent)
{
#if (LINUX_NETFILTER && defined(IP_TRANSPARENT)) || \
    (PF_TRANSPARENT && defined(SO_BINDANY)) || \
    (IPFW_TRANSPARENT && defined(IP_BINDANY))

    /* Trust the user configured properly. If not no harm done.
     * We will simply attempt a bind outgoing on our own IP.
     */
    newConn->remote.port(0); // allow random outgoing port to prevent address clashes
    debugs(89, 5, HERE << "address TPROXY: " << newConn);
    return true;
#else
    return false;
#endif
}