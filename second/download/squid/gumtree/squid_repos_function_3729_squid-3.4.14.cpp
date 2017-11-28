bool
Ip::Intercept::IpfwInterception(const Comm::ConnectionPointer &newConn, int silent)
{
#if IPFW_TRANSPARENT
    /* The getsockname() call performed already provided the TCP packet details.
     * There is no way to identify whether they came from NAT or not.
     * Trust the user configured properly.
     */
    debugs(89, 5, HERE << "address NAT: " << newConn);
    return true;
#else
    return false;
#endif
}