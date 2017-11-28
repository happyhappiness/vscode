unsigned char
ClassCHostPool::makeHostKey(Ip::Address &src_addr) const
{
    /* IPv4 required for this pool */
    if ( !src_addr.isIPv4() )
        return 1;

    /* Temporary bypass for IPv4-only */
    struct in_addr host;
    src_addr.getInAddr(host);
    return (ntohl(host.s_addr) & 0xff);
}