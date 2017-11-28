unsigned short
IpAddress::SetPort(unsigned short prt)
{
    m_SocketAddr.sin6_port = htons(prt);

    return prt;
}