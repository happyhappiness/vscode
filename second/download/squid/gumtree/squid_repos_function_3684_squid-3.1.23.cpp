void IpAddress::GetInAddr(in6_addr &buf) const
{
    memcpy(&buf, &m_SocketAddr.sin6_addr, sizeof(struct in6_addr));
}