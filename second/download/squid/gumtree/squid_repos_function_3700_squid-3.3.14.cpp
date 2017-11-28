bool
Ip::Intercept::NetfilterTransparent(const Comm::ConnectionPointer &newConn, int silent)
{
#if LINUX_NETFILTER
    /* Trust the user configured properly. If not no harm done.
     * We will simply attempt a bind outgoing on our own IP.
     */
    newConn->remote.SetPort(0); // allow random outgoing port to prevent address clashes
    debugs(89, 5, HERE << "address TPROXY: " << newConn);
    return true;
#else
    return false;
#endif
}