const char *
xinet_ntop(af, src, dst, size)
int af;
const void *src;
char *dst;
size_t size;
{
    switch (af) {
    case AF_INET:
        return (inet_ntop4(src, dst, size));
    case AF_INET6:
        return (inet_ntop6(src, dst, size));
    default:
        errno = EAFNOSUPPORT;
        return (NULL);
    }
    /* NOTREACHED */
}