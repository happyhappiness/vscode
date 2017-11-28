bool
Ip::Address::IsNoAddr() const
{
    // IFF the address == 0xff..ff (all ones)
    return IN6_ARE_ADDR_EQUAL( &m_SocketAddr.sin6_addr, &v6_noaddr )
           || IN6_ARE_ADDR_EQUAL( &m_SocketAddr.sin6_addr, &v4_noaddr );
}