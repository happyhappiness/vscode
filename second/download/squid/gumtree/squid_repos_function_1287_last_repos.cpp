unsigned int
ClassCNetPool::makeKey(Ip::Address &src_addr) const
{
    /* IPv4 required for this pool */
    if ( !src_addr.isIPv4() )
        return 1;

    struct in_addr net;
    src_addr.getInAddr(net);
    return ( (ntohl(net.s_addr) >> 8) & 0xff);
}