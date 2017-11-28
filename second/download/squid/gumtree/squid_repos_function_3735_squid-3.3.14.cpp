Ip::Address &
Ip::Address::operator =(const struct sockaddr_storage &s)
{
    /* some AF_* magic to tell socket types apart and what we need to do */
    if (s.ss_family == AF_INET6) {
        memcpy(&m_SocketAddr, &s, sizeof(struct sockaddr_in6));
    } else { // convert it to our storage mapping.
        struct sockaddr_in *sin = (struct sockaddr_in*)&s;
        m_SocketAddr.sin6_port = sin->sin_port;
        Map4to6( sin->sin_addr, m_SocketAddr.sin6_addr);
    }
    return *this;
}