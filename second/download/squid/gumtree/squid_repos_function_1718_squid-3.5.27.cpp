unsigned int
IndividualPool::makeKey(Ip::Address &src_addr) const
{
    /* IPv4 required for this pool */
    if ( !src_addr.isIPv4() )
        return 1;

    struct in_addr host;
    src_addr.getInAddr(host);
    return (ntohl(host.s_addr) & 0xff);
}