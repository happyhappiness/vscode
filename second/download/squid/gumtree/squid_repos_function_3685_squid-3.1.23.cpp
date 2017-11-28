bool IpAddress::GetInAddr(struct in_addr &buf) const
{
    if ( IsIPv4() ) {
        Map6to4((const in6_addr)m_SocketAddr.sin6_addr, buf);
        return true;
    }

    // default:
    // non-compatible IPv6 Pure Address

    debugs(14,1, HERE << "IpAddress::GetInAddr : Cannot convert non-IPv4 to IPv4. IPA=" << *this);
    memset(&buf,0xFFFFFFFF,sizeof(struct in_addr));
    assert(false);
    return false;
}