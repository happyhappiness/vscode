bool IpAddress::SetIPv4()
{
    if ( IsLocalhost() ) {
        m_SocketAddr.sin6_addr = v4_localhost;
        return true;
    }

    if ( IsAnyAddr() ) {
        m_SocketAddr.sin6_addr = v4_anyaddr;
        return true;
    }

    if ( IsIPv4())
        return true;

    // anything non-IPv4 and non-convertable is BAD.
    return false;
}