int
Ip::Address::ApplyMask(Ip::Address const &mask_addr)
{
    uint32_t *p1 = (uint32_t*)(&m_SocketAddr.sin6_addr);
    uint32_t const *p2 = (uint32_t const *)(&mask_addr.m_SocketAddr.sin6_addr);
    unsigned int blen = sizeof(m_SocketAddr.sin6_addr)/sizeof(uint32_t);
    unsigned int changes = 0;

    for (unsigned int i = 0; i < blen; ++i) {
        if ((p1[i] & p2[i]) != p1[i])
            ++changes;

        p1[i] &= p2[i];
    }

    return changes;
}