bool
Ip::Address::getInAddr(struct in_addr &buf) const
{
    if ( isIPv4() ) {
        map6to4(mSocketAddr_.sin6_addr, buf);
        return true;
    }

    // default:
    // non-compatible IPv6 Pure Address

    debugs(14, DBG_IMPORTANT, HERE << "Ip::Address::getInAddr : Cannot convert non-IPv4 to IPv4. IPA=" << *this);
    memset(&buf,0xFFFFFFFF,sizeof(struct in_addr));
    assert(false);
    return false;
}