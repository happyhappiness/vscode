bool
Ip::Intercept::PfTransparent(const Comm::ConnectionPointer &newConn, int silent)
{
#if PF_TRANSPARENT && defined(SO_BINDANY)
    /* Trust the user configured properly. If not no harm done.
     * We will simply attempt a bind outgoing on our own IP.
     */
    newConn->remote.SetPort(0); // allow random outgoing port to prevent address clashes
    debugs(89, 5, HERE << "address DIVERT: " << newConn);
    return true;
#else
    return false;
#endif
}