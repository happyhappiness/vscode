unsigned char
ClassCHostPool::makeHostKey (IpAddress &src_addr) const
{
    /* IPv4 required for this pool */
    if ( !src_addr.IsIPv4() )
        return 1;

    /* Temporary bypass for IPv4-only */
    struct in_addr host;
    src_addr.GetInAddr(host);
    return (ntohl(host.s_addr) & 0xff);
}