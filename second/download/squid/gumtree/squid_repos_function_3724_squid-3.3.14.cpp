bool
Ip::Address::IsSlaac() const
{
    return m_SocketAddr.sin6_addr.s6_addr[10] == static_cast<uint8_t>(0xff) &&
           m_SocketAddr.sin6_addr.s6_addr[11] == static_cast<uint8_t>(0xfe);
}