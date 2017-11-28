bool
Ip::Address::IsAnyAddr() const
{
    return IN6_IS_ADDR_UNSPECIFIED(&m_SocketAddr.sin6_addr) || IN6_ARE_ADDR_EQUAL(&m_SocketAddr.sin6_addr, &v4_anyaddr);
}