const char *
xinet_ntop(int af, const void *src, char *dst, size_t size)
{
    switch (af) {
    case AF_INET:
        return (inet_ntop4((const u_char*)src, dst, size));
    case AF_INET6:
        return (inet_ntop6((const u_char*)src, dst, size));
    default:
        errno = EAFNOSUPPORT;
        return (NULL);
    }
    /* NOTREACHED */
}