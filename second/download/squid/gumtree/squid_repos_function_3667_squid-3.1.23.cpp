int IpAddress::matchIPAddr(const IpAddress &rhs) const
{
    uint8_t *l = (uint8_t*)m_SocketAddr.sin6_addr.s6_addr;
    uint8_t *r = (uint8_t*)rhs.m_SocketAddr.sin6_addr.s6_addr;

    // loop a byte-wise compare
    // NP: match MUST be R-to-L : L-to-R produces inconsistent gt/lt results at varying CIDR
    //     expected difference on CIDR is gt/eq or lt/eq ONLY.
    for (unsigned int i = 0 ; i < sizeof(m_SocketAddr.sin6_addr) ; i++) {

        if (l[i] < r[i])
            return -1;

        if (l[i] > r[i])
            return 1;
    }

    return 0;
}