void
Ip::Address::getSockAddr(struct sockaddr_in6 &buf) const
{
    memcpy(&buf, &mSocketAddr_, sizeof(struct sockaddr_in6));
    /* maintain address family. It may have changed inside us. */
    buf.sin6_family = AF_INET6;

#if HAVE_SIN6_LEN_IN_SAI
    /* not all OS have this field, BUT when they do it can be a problem if set wrong */
    buf.sin6_len = sizeof(struct sockaddr_in6);
#endif
}