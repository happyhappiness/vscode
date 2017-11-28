Ip::Address &
Ip::Address::operator =(const struct sockaddr_storage &s)
{
    /* some AF_* magic to tell socket types apart and what we need to do */
    if (s.ss_family == AF_INET6) {
        memcpy(&mSocketAddr_, &s, sizeof(struct sockaddr_in6));
    } else { // convert it to our storage mapping.
        struct sockaddr_in *sin = (struct sockaddr_in*)&s;
        mSocketAddr_.sin6_port = sin->sin_port;
        map4to6( sin->sin_addr, mSocketAddr_.sin6_addr);
    }
    return *this;
}