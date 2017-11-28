int
xinet_pton(int af, const char *src, void *dst)
{
    switch (af) {
    case AF_INET:
        return (inet_pton4(src, (u_char*)dst));
    case AF_INET6:
        return (inet_pton6(src, (u_char*)dst));
    default:
        errno = EAFNOSUPPORT;
        return (-1);
    }
    /* NOTREACHED */
}